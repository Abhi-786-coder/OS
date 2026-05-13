#include<stdio.h>
#include "lib_mylib.h"
#include "lib_mylib1.h"


int main() {
    int num = 12345;
    
    printf("Original number: %d\n", num);
    printf("Reversed number: %d\n", reverse(num));
    printf("Sum of digits: %d\n", sumofdigits(num));
    printf("Fibonacci of 10: %d\n", fibonacci(10));
    printf("Count of digits in %d: %d\n", num, countdigits(num));
    
    return 0;
}