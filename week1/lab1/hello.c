#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("Please type your name: ");
    printf("hello, %s\n", name);
    return 0;
}