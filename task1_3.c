#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_number(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (i == 0 && str[i] == '-' && str[i+1] != '\0') continue;
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int is_operator(const char *str) {
    return strcmp(str, "+") == 0 || strcmp(str, "-") == 0 || 
           strcmp(str, "*") == 0 || strcmp(str, "%") == 0;
}

int calculate(int a, char *op, int b) {
    if (strcmp(op, "+") == 0) return a + b;
    if (strcmp(op, "-") == 0) return a - b;
    if (strcmp(op, "*") == 0) return a * b;
    if (strcmp(op, "%") == 0) return a % b;
    return 0;
}

int main(int argc, char* argv[]) {
    int results[20];
    int count = 0;
    int key = 0;
    int found_k = 0;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-k") == 0 && i + 1 < argc) {
            key = atoi(argv[i + 1]);
            found_k = 1;
            break;
        }
        
        if (i + 2 < argc && is_number(argv[i]) && is_operator(argv[i+1]) && is_number(argv[i+2])) {
            int a = atoi(argv[i]);
            char *op = argv[i+1];
            int b = atoi(argv[i+2]);
            
            results[count] = calculate(a, op, b);
            count++;
            i += 2;
        }
    }
    
    if (!found_k) {
        printf("Ошибка: флаг -k не найден!\n");
        return 1;
    }
    
    for (int i = 0; i < count; i++) {
        printf("Ответ №%d: %d\n", i + 1, results[i]);
    }
    
    printf("Результирующая строка: ");
    for (int i = 0; i < count; i++) {
        printf("%c", results[i] - key);
    }
    printf("\n");
    
    return 0;
}
