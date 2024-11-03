#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "validation.h"
#include "calculation.h"
#define TO_RADIANS(degree) ((degree) * M_PI / 180.0)

int main()
{
    printf("This program calculates sin/cos from a starting value x1 to an ending value x2 with a step dx.\n");

    do
    {
        const size_t table_size = 4;
        char user_choice = 0, format_type = 0;
        double start_x = 0, end_x = 0, step_dx = 0, tolerance = 0;
        char *table_sin[] = {"Degrees", "Calc_Sin", "Table_Sin", "Diff"};
        char *table_cos[] = {"Degrees", "Calc_Cos", "Table_Cos", "Diff"};
        double data[table_size] = {};

        start_x = val_double_input("Enter starting x (x1): ");
        end_x = val_double_input("Enter ending x (x2): ");

        step_dx = start_x == end_x
                          ? dx_input_validation(0)
                          : start_x < end_x
                                    ? dx_input_validation(1)
                                    : dx_input_validation(2);
        tolerance = fabs(val_double_input("Enter precision (epsilon): "));

        do
        {
            printf("Choose output format: e (exponential) / d (decimal): ");
            format_type = getchar();
            if (format_type != 'e' && format_type != 'd')
            {
                printf("Invalid selection.\n");
            }
            fflush(stdin);
        }
        while (format_type != 'e' && format_type != 'd');

        do
        {
            printf("Choose function to compute (1 - sin, 2 - cos): ");
            user_choice = getchar();
            if (user_choice != '1' && user_choice != '2')
            {
                printf("Invalid option.\n");
            }
            fflush(stdin);
        }
        while (user_choice != '1' && user_choice != '2');

        // Вивід заголовків із більшою шириною
        user_choice == '1'
            ? printf("%-20s %-25s %-25s %-25s\n", table_sin[0], table_sin[1], table_sin[2], table_sin[3])
            : printf("%-20s %-25s %-25s %-25s\n", table_cos[0], table_cos[1], table_cos[2], table_cos[3]);

        double x = start_x;
        int printed_x2 = 0;
        while ((start_x < end_x && x <= end_x) || (start_x > end_x && x >= end_x))
        {
            double radians_x = fabs(x) > 360
                                       ? TO_RADIANS(fmod(x, 360))
                                       : TO_RADIANS(x);
            double computed_val = 0, library_val = 0, delta = 0;

            computed_val = user_choice == '1'
                                       ? taylor_sin(radians_x, tolerance)
                                       : taylor_cos(radians_x, tolerance);
            library_val = user_choice == '1'
                                      ? sin(radians_x)
                                      : cos(radians_x);
            delta = fabs(computed_val - library_val);

            data[0] = x;
            data[1] = computed_val;
            data[2] = library_val;
            data[3] = delta;
            unsigned precision = fabs(log10(tolerance));

            if (format_type == 'e')
            {
                printf("%-20g %-25.*e %-25e %-25.*e\n", data[0], precision, data[1], data[2], precision, data[3]);
            }
            else
            {
                printf("%-20g %-25.*lf %-25e %-25.*lf\n", data[0], precision, data[1], data[2], precision, data[3]);
            }

            if (x == end_x)
            {
                printed_x2 = 1;
            }

            if (step_dx == 0) // зупинити цикл, якщо step_dx дорівнює нулю, щоб уникнути нескінченного циклу
            {
                break;
            }

            x += step_dx; // оновлення значення x для наступної ітерації
        }

        // Додатковий друк x2, якщо воно не було надруковане в циклі
        if (!printed_x2) {
            double radians_x = fabs(end_x) > 360
                                       ? TO_RADIANS(fmod(end_x, 360))
                                       : TO_RADIANS(end_x);
            double computed_val = user_choice == '1'
                                       ? taylor_sin(radians_x, tolerance)
                                       : taylor_cos(radians_x, tolerance);
            double library_val = user_choice == '1'
                                      ? sin(radians_x)
                                      : cos(radians_x);
            double delta = fabs(computed_val - library_val);

            data[0] = end_x;
            data[1] = computed_val;
            data[2] = library_val;
            data[3] = delta;

            unsigned precision = fabs(log10(tolerance));
            if (format_type == 'e') {
                printf("%-20g %-25.*e %-25e %-25.*e\n", data[0], precision, data[1], data[2], precision, data[3]);
            } else {
                printf("%-20g %-25.*lf %-25e %-25.*lf\n", data[0], precision, data[1], data[2], precision, data[3]);
            }
        }

        printf("Press '0' to exit, or any other key to continue: ");
        fflush(stdin);
    }
    while (getchar() != 48);

    return 0;
}
