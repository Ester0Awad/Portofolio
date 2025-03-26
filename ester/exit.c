// Returns explicit value from main

#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("incorrect command-line argument - expected ./exit <name>\n");
        return 123;
    }
    printf("hello, %s\n", argv[1]);
    return 0;
}