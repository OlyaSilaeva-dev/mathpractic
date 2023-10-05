#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

long long int parseNumber(char* str, int base) {
    long long int result = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        char c = str[i];
        int digit;
        if (isdigit(c)) {
            digit = c - '0';
        } else {
            digit = 10 + (tolower(c) - 'a');
        }
        result = result * base + digit;
    }
    return result;
}

void toBase(long long int number, int base) {
    char result[100]; 
    int index = 99;
    result[index] = '\0';

    while (number > 0) {
        int digit = number % base;
        if (digit < 10) {
            result[--index] = '0' + digit;
        } else {
            result[--index] = 'a' + (digit - 10);
        }
        number /= base;
    }

    printf("%s\n", &result[index]);
}

char *inputString(FILE* fp, size_t size){
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(*str) * size); 
    if (!str) return str;
    while (EOF != (ch = fgetc(fp)) && ch != '\n') {
        str[len++] = ch;
        if (len == size) {
            str = realloc(str, sizeof(*str) * (size += 16));
            if (!str) return str;
        }
    }
    str[len++] = '\0';
    return realloc(str, sizeof(*str) * len);
}

int main() {
    int base;
    char *input;

    printf("Введите основание системы счисления (от 2 до 36): ");
    input = inputString(stdin, 10);
    if (input == NULL) {
        printf("Wrong base\n");
        return 1;
    }
    base = strtol(input, NULL, 10); 
    free(input);
    if(base < 2 || base > 36){
        printf("Wrong base");
        return 1;
    }
    
    long long int maxNumber = 0;
    char maxNumberStr[50];

    printf("Введите число (или 'Stop' для завершения ввода):\n");

    while ((input = inputString(stdin, 10)) != NULL) {
        if (strcmp(input, "Stop") == 0) {
            free(input);
            break;
        }

        long long int number = parseNumber(input, base);

        if (llabs(number) > llabs(maxNumber)) {
            maxNumber = number;
            strcpy(maxNumberStr, input);
        }

        free(input);
    }

    printf("Максимальное по модулю число: %lld\n", maxNumber);
    printf("В системе счисления с основанием 9: ");
    toBase(maxNumber, 9);
    printf("В системе счисления с основанием 18: ");
    toBase(maxNumber, 18);
    printf("В системе счисления с основанием 27: ");
    toBase(maxNumber, 27);
    printf("В системе счисления с основанием 36: ");
    toBase(maxNumber, 36);

    return 0;
}
