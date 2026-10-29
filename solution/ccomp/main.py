#!/usr/bin/env python3
"""Reference C-subset compiler: C source -> x86-64 GNU assembly (System V, Linux).

Usage: python3 main.py input.c -o output.s
Supports: int/void, globals, locals, block scope, all int operators, if/while/
do/for/break/continue/return, functions (any arity), string literals, calls to
libc (printf, putchar, ...). Int arithmetic wraps at 32 bits.
"""
import re
import sys

KEYWORDS = {"int", "void", "return", "if", "else", "while", "for", "do", "break", "continue"}
TOKEN_RE = re.compile(r"""
    (?P<ws>\s+|//[^\n]*|/\*.*?\*/)
  | (?P<num>0[xX][0-9a-fA-F]+|\d+)
  | (?P<char>'(?:\\.|[^\\'])')
  | (?P<str>"(?:\\.|[^\\"])*")
  | (?P<id>[A-Za-z_]\w*)
  | (?P<op><<=|>>=|\+\+|--|<<|>>|<=|>=|==|!=|&&|\|\||[-+*/%&|^]=|[-+*/%<>=!~&|^?:;,(){}])
""", re.X | re.S)
ESC = {"n": 10, "t": 9, "r": 13, "0": 0, "\\": 92, "'": 39, '"': 34, "a": 7, "b": 8, "f": 12, "v": 11}


class CompileError(Exception):
    pass


def lex(src):
    toks, pos = [], 0
    while pos < len(src):
        m = TOKEN_RE.match(src, pos)
        if not m:
            raise CompileError("bad character %r at offset %d" % (src[pos], pos))
        pos = m.end()
        k = m.lastgroup
        if k == "ws":
            continue
        t = m.group()
        if k == "id" and t in KEYWORDS:
            k = "kw"
        toks.append((k, t))
    toks.append(("eof", ""))
    return toks


def unescape(body):
    out, i = [], 0
    while i < len(body):
        c = body[i]
        if c == "\\":
            i += 1
            out.append(ESC.get(body[i], ord(body[i])))
        else:
            out.append(ord(c))
        i += 1
    return out


ASSIGN_OPS = {"=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>="}
BINPREC = [["||"], ["&&"], ["|"], ["^"], ["&"], ["==", "!="], ["<", ">", "<=", ">="], ["<<", ">>"],
           ["+", "-"], ["*", "/", "%"]]


class Parser:
    def __init__(self, toks):
        self.t, self.i = toks, 0

    def peek(self, off=0):
        return self.t[self.i + off]

    def next(self):
        tok = self.t[self.i]
        self.i += 1
        return tok

    def accept(self, text):
        if self.peek()[1] == text and self.peek()[0] in ("op", "kw"):
            self.i += 1
            return True
        return False

    def expect(self, text):
        if not self.accept(text):
            raise CompileError("expected %r, got %r" % (text, self.peek()[1]))

    def ident(self):
        k, t = self.next()
        if k != "id":
            raise CompileError("expected identifier, got %r" % t)
        return t

    # ---- top level
    def program(self):
        items = []
        while self.peek()[0] != "eof":
            self.next()  # type (int / void)
            name = self.ident()
            if self.accept("("):
                params = self.params()
                if self.accept(";"):
                    continue  # prototype
                items.append(("func", name, params, self.block()))
            else:
                items.append(("global", name, self.global_init()))
                while self.accept(","):
                    items.append(("global", self.ident(), self.global_init()))
                self.expect(";")
        return items

    def global_init(self):
        if not self.accept("="):
            return 0
        neg = self.accept("-")
        k, t = self.next()
        if k != "num":
            raise CompileError("global initializer must be a constant")
        v = int(t, 0)
        return -v if neg else v

    def params(self):
        ps = []
        if self.accept(")"):
            return ps
        if self.peek()[1] == "void" and self.peek(1)[1] == ")":
            self.i += 2
            return ps
        while True:
            self.next()  # type
            ps.append(self.ident())
            if self.accept(")"):
                return ps
            self.expect(",")

    # ---- statements
    def block(self):
        self.expect("{")
        body = []
        while not self.accept("}"):
            body.append(self.stmt())
        return ("block", body)

    def decl(self):
        self.expect("int")
        items = []
        while True:
            name = self.ident()
            init = self.expr_assign() if self.accept("=") else None
            items.append((name, init))
            if not self.accept(","):
                break
        return ("decl", items)

    def stmt(self):
        k, t = self.peek()
        if t == "{" and k == "op":
            return self.block()
        if k == "kw":
            if t == "int":
                d = self.decl()
                self.expect(";")
                return d
            if t == "return":
                self.next()
                e = None if self.peek()[1] == ";" else self.expr()
                self.expect(";")
                return ("return", e)
            if t == "if":
                self.next()
                self.expect("(")
                c = self.expr()
                self.expect(")")
                a = self.stmt()
                b = self.stmt() if self.accept("else") else None
                return ("if", c, a, b)
            if t == "while":
                self.next()
                self.expect("(")
                c = self.expr()
                self.expect(")")
                return ("while", c, self.stmt())
            if t == "do":
                self.next()
                body = self.stmt()
                self.expect("while")
                self.expect("(")
                c = self.expr()
                self.expect(")")
                self.expect(";")
                return ("do", body, c)
            if t == "for":
                self.next()
                self.expect("(")
                if self.peek()[1] == "int":
                    init = self.decl()
                    self.expect(";")
                elif self.accept(";"):
                    init = None
                else:
                    init = ("expr", self.expr())
                    self.expect(";")
                cond = None if self.peek()[1] == ";" else self.expr()
                self.expect(";")
                step = None if self.peek()[1] == ")" else self.expr()
                self.expect(")")
                return ("for", init, cond, step, self.stmt())
            if t in ("break", "continue"):
                self.next()
                self.expect(";")
                return (t,)
        if self.accept(";"):
            return ("block", [])
        e = self.expr()
        self.expect(";")
        return ("expr", e)

    # ---- expressions
    def expr(self):
        e = self.expr_assign()
        while self.accept(","):
            e = ("comma", e, self.expr_assign())
        return e

    def expr_assign(self):
        lhs = self.ternary()
        k, t = self.peek()
        if k == "op" and t in ASSIGN_OPS:
            if lhs[0] != "var":
                raise CompileError("assignment target must be a variable")
            self.next()
            return ("assign", t, lhs[1], self.expr_assign())
        return lhs

    def ternary(self):
        c = self.binary(0)
        if self.accept("?"):
            a = self.expr()
            self.expect(":")
            return ("cond", c, a, self.ternary())
        return c

    def binary(self, level):
        if level == len(BINPREC):
            return self.unary()
        lhs = self.binary(level + 1)
        while self.peek()[0] == "op" and self.peek()[1] in BINPREC[level]:
            op = self.next()[1]
            lhs = ("bin", op, lhs, self.binary(level + 1))
        return lhs

    def unary(self):
        k, t = self.peek()
        if k == "op":
            if t in ("-", "+", "!", "~"):
                self.next()
                return ("un", t, self.unary())
            if t in ("++", "--"):
                self.next()
                v = self.unary()
                if v[0] != "var":
                    raise CompileError("++/-- needs a variable")
                return ("incdec", t, v[1], True)
        return self.postfix()

    def postfix(self):
        e = self.primary()
        while True:
            k, t = self.peek()
            if k == "op" and t in ("++", "--") and e[0] == "var":
                self.next()
                e = ("incdec", t, e[1], False)
            else:
                return e

    def primary(self):
        k, t = self.next()
        if k == "num":
            return ("num", int(t, 0))
        if k == "char":
            return ("num", unescape(t[1:-1])[0])
        if k == "str":
            data = unescape(t[1:-1])
            while self.peek()[0] == "str":  # adjacent literal concatenation
                data += unescape(self.next()[1][1:-1])
            return ("str", data)
        if k == "id":
            if self.accept("("):
                args = []
                if not self.accept(")"):
                    while True:
                        args.append(self.expr_assign())
                        if self.accept(")"):
                            break
                        self.expect(",")
                return ("call", t, args)
            return ("var", t)
        if t == "(" and k == "op":
            e = self.expr()
            self.expect(")")
            return e
        raise CompileError("unexpected token %r" % t)


ARG_REGS = ["%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"]
CMP = {"==": "e", "!=": "ne", "<": "l", ">": "g", "<=": "le", ">=": "ge"}


class CodeGen:
    def __init__(self, items):
        self.items = items
        self.out = []
        self.strings = []
        self.nlabel = 0
        self.globals = {i[1] for i in items if i[0] == "global"}

    def label(self):
        self.nlabel += 1
        return ".L%d" % self.nlabel

    def emit(self, s):
        self.out.append("\t" + s)

    def put(self, s):
        self.out.append(s)

    def push(self):
        self.emit("pushq %rax")
        self.depth += 1

    def pop(self, reg):
        self.emit("popq " + reg)
        self.depth -= 1

    def generate(self):
        self.put("\t.text")
        for it in self.items:
            if it[0] == "func":
                self.func(it)
        data = [it for it in self.items if it[0] == "global"]
        if data:
            self.put("\t.data")
            for _, name, init in data:
                self.put("\t.globl %s\n\t.align 4\n%s:\n\t.long %d" % (name, name, init & 0xFFFFFFFF))
        if self.strings:
            self.put("\t.section .rodata")
            for i, s in enumerate(self.strings):
                self.put(".LS%d:\n\t.byte %s" % (i, ",".join(map(str, s + [0]))))
        self.put('\t.section .note.GNU-stack,"",@progbits')
        return "\n".join(self.out) + "\n"

    # ---- functions
    def func(self, f):
        _, name, params, body = f
        self.fname = name
        self.scopes = [{}]
        self.nlocals = 0
        self.depth = 0
        self.loops = []
        self.ret_label = self.label()
        saved = self.out
        self.out = []
        for i, p in enumerate(params):
            off = self.new_local(p)
            if i < 6:
                self.emit("movq %s, %d(%%rbp)" % (ARG_REGS[i], off))
            else:
                self.emit("movq %d(%%rbp), %%rax" % (16 + 8 * (i - 6)))
                self.emit("movq %%rax, %d(%%rbp)" % off)
        self.stmt(body)
        self.emit("movl $0, %eax")
        body_code = self.out
        self.out = saved
        frame = (self.nlocals * 8 + 15) & ~15
        self.put("\t.globl %s\n\t.type %s, @function\n%s:" % (name, name, name))
        self.emit("pushq %rbp")
        self.emit("movq %rsp, %rbp")
        if frame:
            self.emit("subq $%d, %%rsp" % frame)
        self.out += body_code
        self.put(self.ret_label + ":")
        self.emit("movq %rbp, %rsp")
        self.emit("popq %rbp")
        self.emit("ret")

    def new_local(self, name):
        if name in self.scopes[-1]:
            raise CompileError("redeclaration of %s" % name)
        self.nlocals += 1
        off = -8 * self.nlocals
        self.scopes[-1][name] = off
        return off

    def lookup(self, name):
        for s in reversed(self.scopes):
            if name in s:
                return "%d(%%rbp)" % s[name]
        if name in self.globals:
            return "%s(%%rip)" % name
        raise CompileError("undeclared variable %s" % name)

    # ---- statements
    def stmt(self, s):
        k = s[0]
        if k == "block":
            self.scopes.append({})
            for x in s[1]:
                self.stmt(x)
            self.scopes.pop()
        elif k == "decl":
            for name, init in s[1]:
                if init is not None:
                    self.expr(init)
                off = self.new_local(name)
                if init is not None:
                    self.emit("movq %%rax, %d(%%rbp)" % off)
                else:
                    self.emit("movq $0, %d(%%rbp)" % off)
        elif k == "expr":
            self.expr(s[1])
        elif k == "return":
            if s[1] is not None:
                self.expr(s[1])
            self.emit("jmp " + self.ret_label)
        elif k == "if":
            els, end = self.label(), self.label()
            self.expr(s[1])
            self.emit("cmpl $0, %eax")
            self.emit("je " + els)
            self.stmt(s[2])
            self.emit("jmp " + end)
            self.put(els + ":")
            if s[3]:
                self.stmt(s[3])
            self.put(end + ":")
        elif k == "while":
            top, end = self.label(), self.label()
            self.put(top + ":")
            self.expr(s[1])
            self.emit("cmpl $0, %eax")
            self.emit("je " + end)
            self.loops.append((end, top))
            self.stmt(s[2])
            self.loops.pop()
            self.emit("jmp " + top)
            self.put(end + ":")
        elif k == "do":
            top, cont, end = self.label(), self.label(), self.label()
            self.put(top + ":")
            self.loops.append((end, cont))
            self.stmt(s[1])
            self.loops.pop()
            self.put(cont + ":")
            self.expr(s[2])
            self.emit("cmpl $0, %eax")
            self.emit("jne " + top)
            self.put(end + ":")
        elif k == "for":
            _, init, cond, step, body = s
            self.scopes.append({})
            if init:
                self.stmt(init)
            top, cont, end = self.label(), self.label(), self.label()
            self.put(top + ":")
            if cond:
                self.expr(cond)
                self.emit("cmpl $0, %eax")
                self.emit("je " + end)
            self.loops.append((end, cont))
            self.stmt(body)
            self.loops.pop()
            self.put(cont + ":")
            if step:
                self.expr(step)
            self.emit("jmp " + top)
            self.put(end + ":")
            self.scopes.pop()
        elif k in ("break", "continue"):
            if not self.loops:
                raise CompileError(k + " outside loop")
            self.emit("jmp " + self.loops[-1][0 if k == "break" else 1])
        else:
            raise CompileError("unknown statement " + k)

    # ---- expressions: result in %rax, kept sign-extended from 32 bits
    def expr(self, e):
        k = e[0]
        if k == "num":
            v = ((e[1] + 2**31) % 2**32) - 2**31
            self.emit("movq $%d, %%rax" % v)
        elif k == "str":
            self.strings.append(e[1])
            self.emit("leaq .LS%d(%%rip), %%rax" % (len(self.strings) - 1))
        elif k == "var":
            self.load(e[1])
        elif k == "comma":
            self.expr(e[1])
            self.expr(e[2])
        elif k == "un":
            self.expr(e[2])
            if e[1] == "-":
                self.emit("negq %rax")
                self.emit("cltq")
            elif e[1] == "~":
                self.emit("notq %rax")
            elif e[1] == "!":
                self.emit("cmpl $0, %eax")
                self.emit("sete %al")
                self.emit("movzbl %al, %eax")
        elif k == "bin":
            self.binary(e)
        elif k == "assign":
            self.assign(e)
        elif k == "incdec":
            _, op, name, prefix = e
            self.load(name)
            if not prefix:
                self.emit("movq %rax, %rdx")
            self.emit(("addq" if op == "++" else "subq") + " $1, %rax")
            self.emit("cltq")
            self.store(name)
            if not prefix:
                self.emit("movq %rdx, %rax")
        elif k == "cond":
            els, end = self.label(), self.label()
            self.expr(e[1])
            self.emit("cmpl $0, %eax")
            self.emit("je " + els)
            self.expr(e[2])
            self.emit("jmp " + end)
            self.put(els + ":")
            self.expr(e[3])
            self.put(end + ":")
        elif k == "call":
            self.call(e)
        else:
            raise CompileError("unknown expression " + k)

    def is_local(self, name):
        return any(name in s for s in self.scopes)

    def load(self, name):
        if self.is_local(name):
            self.emit("movq %s, %%rax" % self.lookup(name))
        else:
            self.emit("movslq %s, %%rax" % self.lookup(name))

    def store(self, name):
        if self.is_local(name):
            self.emit("movq %%rax, %s" % self.lookup(name))
        else:
            self.emit("movl %%eax, %s" % self.lookup(name))

    def assign(self, e):
        _, op, name, rhs = e
        if op == "=":
            self.expr(rhs)
        else:
            self.expr(rhs)
            self.push()
            self.load(name)
            self.pop("%rcx")  # lhs in rax, rhs in rcx
            self.arith(op[:-1])
        self.store(name)

    def binary(self, e):
        _, op, a, b = e
        if op in ("&&", "||"):
            short, end = self.label(), self.label()
            self.expr(a)
            self.emit("cmpl $0, %eax")
            self.emit(("je " if op == "&&" else "jne ") + short)
            self.expr(b)
            self.emit("cmpl $0, %eax")
            self.emit("setne %al")
            self.emit("movzbl %al, %eax")
            self.emit("jmp " + end)
            self.put(short + ":")
            self.emit("movl $%d, %%eax" % (0 if op == "&&" else 1))
            self.put(end + ":")
            return
        self.expr(b)
        self.push()
        self.expr(a)
        self.pop("%rcx")  # lhs in rax, rhs in rcx
        self.arith(op)

    def arith(self, op):
        if op in CMP:
            self.emit("cmpl %ecx, %eax")
            self.emit("set%s %%al" % CMP[op])
            self.emit("movzbl %al, %eax")
        elif op == "+":
            self.emit("addq %rcx, %rax"); self.emit("cltq")
        elif op == "-":
            self.emit("subq %rcx, %rax"); self.emit("cltq")
        elif op == "*":
            self.emit("imulq %rcx, %rax"); self.emit("cltq")
        elif op in ("/", "%"):
            self.emit("cltd")
            self.emit("idivl %ecx")
            if op == "%":
                self.emit("movl %edx, %eax")
            self.emit("cltq")
        elif op == "&":
            self.emit("andq %rcx, %rax")
        elif op == "|":
            self.emit("orq %rcx, %rax")
        elif op == "^":
            self.emit("xorq %rcx, %rax")
        elif op == "<<":
            self.emit("shll %cl, %eax"); self.emit("cltq")
        elif op == ">>":
            self.emit("sarl %cl, %eax"); self.emit("cltq")
        else:
            raise CompileError("unknown operator " + op)

    def call(self, e):
        _, name, args = e
        n = len(args)
        extra = max(0, n - 6)
        pad = (self.depth + extra) % 2
        if pad:
            self.emit("subq $8, %rsp")
            self.depth += 1
        for a in reversed(args):
            self.expr(a)
            self.push()
        for i in range(min(n, 6)):
            self.pop(ARG_REGS[i])
        self.emit("movl $0, %eax")
        self.emit("call %s@PLT" % name)
        self.emit("cltq")
        cleanup = extra + pad
        if cleanup:
            self.emit("addq $%d, %%rsp" % (8 * cleanup))
            self.depth -= cleanup


def main(argv):
    src_path, out_path = None, None
    i = 1
    while i < len(argv):
        if argv[i] == "-o":
            out_path = argv[i + 1]
            i += 2
        else:
            src_path = argv[i]
            i += 1
    if not src_path or not out_path:
        sys.stderr.write("usage: main.py input.c -o output.s\n")
        return 2
    try:
        with open(src_path) as f:
            src = f.read()
        asm = CodeGen(Parser(lex(src)).program()).generate()
    except CompileError as e:
        sys.stderr.write("error: %s\n" % e)
        return 1
    with open(out_path, "w") as f:
        f.write(asm)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
