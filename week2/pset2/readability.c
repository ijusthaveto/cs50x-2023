#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int count_grade(int words, int sentences, int letters);

int main(void)
{
    string prompt = get_string("Text: ");
    int words = count_words(prompt);
    int sentences = count_sentences(prompt);
    int letters = count_letters(prompt);
    int grade = count_grade(words, sentences, letters);
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }
    return 0;
}

int count_grade(int words, int sentences, int letters)
{
    double L = 100.0 * letters / words;
    double S = 100.0 * sentences / words;
    return round(0.0588 * L - 0.296 * S - 15.8);
}

int count_letters(string text)
{
    int counter = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            counter++;
        }
    }
    return counter;
}

int count_words(string text)
{
    int counter = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isspace(text[i]))
        {
            counter++;
        }
    }
    return counter + 1;
}

int count_sentences(string text)
{
    int counter = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            counter++;
        }
    }
    return counter;
}
