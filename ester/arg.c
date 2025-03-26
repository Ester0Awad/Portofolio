// Prints a command-linw argument

#include <stdio.h>
#include <cs50.h>

int main (int argc, string argv[])
{
    if (argc == 2)
    {
        printf("hello, %c\n", argv[1][0]);

    }
    else
    {
        printf("hello, world\n");
    }
   // printf("%s\n", argv[0]);
}