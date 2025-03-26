//Print string char by char

#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main (void)
{
    string s = get_string("Input: ");
    printf("Output: ");


    for(int i = 0,  int x = strlen(s);        i < x      ; i++)
    {
        printf("%c", s[i]);
    }
    printf("\n");
}