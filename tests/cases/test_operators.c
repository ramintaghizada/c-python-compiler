int main() {
    int x = 0x1A; // Hex literal (26)
    int y = 0x0F; // Hex literal (15)
    
    x--; // Azaltma operatoru (25)
    
    x <<= 2; // Shift assignment (100)
    x %= y;  // Modulo assignment (10)
    
    int dummy = 98; // char 'b' əvəzinə ASCII int dəyəri
    
    printf("%d %d %d\n", x, y, dummy);
    return x & 127;
}
