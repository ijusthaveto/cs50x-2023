#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digit(string key);
char rotate(char alpha, int key);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Make sure every charactor in argv[1] is a non-negative digit
    if (!only_digit(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert argv[1] from a `string` to an `int`
    int key = atoi(argv[1]);

    // Prompt user for a plaintext
    string plaintext = get_string("plaintext:  ");

    // For each charactor in the plaintext:
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // Rotate the charactor if it's a letter
        plaintext[i] = rotate(plaintext[i], key);
    }

    printf("ciphertext:  %s\n", plaintext);

    return 0;
}

bool only_digit(string key)
{
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (isdigit(key[i]))
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

char rotate(char alpha, int key)
{
    if (!isalpha(alpha))
    {
        return alpha;
    }

    // Find the base
    char base = isupper(alpha) ? 'A' : 'a';

    return (alpha - base + key) % 26 + base;
}