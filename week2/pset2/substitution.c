#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool validate(string plaintext);
string encrypt(string plaintext, string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (!validate(argv[1]))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string plaintext = get_string("plaintext:  ");

    plaintext = encrypt(plaintext, argv[1]);

    printf("ciphertext:  %s\n", plaintext);

    return 0;
}

bool validate(string plaintext)
{
    // Contain 26 charactors
    int length = strlen(plaintext);
    if (length != 26)
    {
        return false;
    }

    // Contain any non-alphabetic charactors
    int cnt[26] = {0};
    for (int i = 0; i < length; i++)
    {
        if (!isalpha(plaintext[i]))
        {
            return false;
        }
        char base = isupper(plaintext[i]) ? 'A' : 'a';
        cnt[plaintext[i] - base]++;
    }

    // Contain each letter exactly once
    for (int i = 0; i < 26; i++)
    {
        if (!cnt[i] || cnt[i] > 1)
        {
            return false;
        }
    }
    return true;
}

string encrypt(string plaintext, string key)
{
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            int offset = toupper(plaintext[i]) - 'A';
            bool is_upper = isupper(plaintext[i]);
            if (is_upper)
            {
                plaintext[i] = toupper(key[offset]);
            }
            else
            {
                plaintext[i] = tolower(key[offset]);
            }
        }
    }
    return plaintext;
}