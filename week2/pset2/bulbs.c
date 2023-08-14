#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    string message = get_string("Message: ");

    for (int i = 0, n = strlen(message); i < n; i++)
    {
        int bulb_array[8] = {0}, idx = 7;

        while (message[i])
        {
            bulb_array[idx--] = message[i] % 2;
            message[i] /= 2;
        }

        for (int j = 0; j < 8; j++)
        {
            print_bulb(bulb_array[j]);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
