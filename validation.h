#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdio.h>

// Функція для введення дійсного числа
double val_double_input(const char *prompt) {
    double value = 0;
    int input = 0;
    do {
        printf("%s", prompt);
        input = scanf("%lf", &value);
        if (input != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            value = 0;
        }
        fflush(stdin);
    } while (input != 1);
    return value;
}

// Умовні функції для перевірки dx
char positive_step_check(double value) {
    return value > 0;
}

char negative_step_check(double value) {
    return value < 0;
}

char zero_step_check(double value) {
    return value == 0;
}

// Функція для валідації dx
double validate_dx(const char *prompt, const char *error_message, char (*condition)(double)) {
    double value = 0;
    do {
        value = val_double_input(prompt);
        if (!condition(value)) {
            printf("%s\n", error_message);
        }
        fflush(stdin);
    } while (!condition(value));
    return value;
}

// Основна функція для перевірки dx
double dx_input_validation(char direction_flag) {
    const char *prompt = "Enter the step (dx): ";
    const char *error_message = "Error: Invalid dx value. Please try again.";

    switch (direction_flag) {
        case 1:
            return validate_dx(prompt, error_message, positive_step_check);
        case 2:
            return validate_dx(prompt, error_message, negative_step_check);
        default:
            return validate_dx(prompt, error_message, zero_step_check);
    }
}

#endif
