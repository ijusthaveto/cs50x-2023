#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = 0;

    do
    {
        number = get_long("Number: ");
    } while (number <= 0);

    long number_backup = number;
    int underline_sum = 0;
    int other_sum = 0;
    bool is_even = false;
    int counter = 0;

    while (number)
    {

        if (is_even)
        {
            int current_digit = number % 10 * 2;
            if (current_digit >= 10)
            {
                underline_sum += current_digit % 10 + current_digit / 10;
            }
            else
            {
                underline_sum += number % 10 * 2;
            }
            is_even = false;
        }
        else
        {
            other_sum += number % 10;
            is_even = true;
        }
        number /= 10;
        counter++;
    }

    int total_sum = underline_sum + other_sum;

    if (total_sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        number = number_backup;
        for (int i = 1; i <= counter - 2; i++)
        {
            number /= 10;
        }

        if ((number == 34 || number == 37) && counter == 15)
        {
            printf("AMEX\n");
        }
        else if (number >= 51 && number <= 55 && counter == 16)
        {
            printf("MASTERCARD\n");
        }
        else if (number >= 40 && number <= 49 && (counter == 13 || counter == 16))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}
