#include <cs50.h>
#include <stdio.h>

int main(void)

{
    // n indicates to the height of the pyramid
    // i indiactes to generating a new line
    // k indicates the the symbol #

    // Asking the user to put an interger number for Height which is not less than 0 and not more than 8
    int n = 0;
    do
    {
        n = get_int("Height:  \n ");
    }
    while (n <= 0 || n > 8);

    // Outer loop: i indicates to the number of rows which increases by 1
    for (int i = 0; i < n ; i++)
    {
        //Print dots
        for (int d = 1; d < n - i ; d++)
        {
            printf(" ");
        }

        //Print hashes
        // Inner loop: k indicates to # which increases by 1 after making a new line
        //The number of dots printed is equal to the difference between the height 'n'and the current row number 'i'.
        //The number of hashes printed is equal to the current row number 'i'.
        for (int k = 0 ; k <= i  ; k++)
        {
            printf("#");
        }

        printf("\n");

    }

    return 0;
}