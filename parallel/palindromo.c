#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <pthread.h>

unsigned long long num_to_bin(unsigned long long result){
    unsigned long long binary = 0;
    unsigned long long base = 1;

    while (result > 0) {
        int digit = result % 2;
        binary += digit * base;
        base *= 10;
        result /= 2;
    }
    return binary;
    
}

unisgned long long num_hex (unsinged long long result){
    unsigned long long hex = 0;
    unsigned long long base = 1;

    while (result > 0) {
        int digit = result % 16;
        hex += digit * base;
        base *= 10;
        result /= 16;
    }

    return hex;
    
}

// unsigned long long Palindrome_hex
//     hex = sprintf("%llu", hex);


unsigned long long Palindrome_bin(binary)
    char binary = sprintf("%llu", binary);

    int size = strlen(binary)



#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool Palindrome_bin(unsigned long long binary)
{
    char str[100];

    sprintf(str, "%llu", binary);

    int size = strlen(str);

    for (int i = 0; i < size / 2; i++) {
        if (str[i] != str[size - 1 - i]) {
            return false;
        }
    }

    return true;
}



