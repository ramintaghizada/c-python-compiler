// Funksiya prototiplərinin (declarations) yoxlanışı
void process_data(int count);
int calculate(int base);

void process_data(int count) {
    int i = 0;
    // Boş başlanğıc və artım hissəsi olan for dövrü
    for (; i < count; ) {
        i++;
    }
    puts("Loop completed successfully."); // puts istifadəsi
}

int calculate(int base) {
    return base * 3;
}

int main() {
    int start = 5;
    process_data(start);
    int result = calculate(start);
    printf("Result: %d\n", result);
    return result & 255;
}
