#include <stdio.h>

int main (void)
{
    int n = 50;
    int* p = &n;

    char c = 'A';
    char* p1 = &c;
    

    char* s = "EMMA";
    //char* (pointer(address) to a character)

    printf("%s\n", s);
    //s(string is an array of chars) is a pointer(address). No need to put `&` before it.
}