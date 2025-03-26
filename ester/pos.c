#include<stdio.h>
#include<cs50.h>

int getpos(void);

int main (void)
{
    int i  = getpos(); //do the below code and the output put it as an input in the "i" variable////int is the kind of output//
    int j  = getpos();
    int k  = getpos();
    printf("%i - %i - %i\n", i, j, k);
}


int getpos(void)
{
    int x;
    do
    {
        x = get_int("Please enter a positive integer: ");
    }
    while (x <=0 );
    return x;

}