#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>



bool only_digits(string s);
char rotate(char c, int n);


int main(int argc, string argv[])
{
    // Program runs with just one command-line argument // DONE :)

    if (argc == 2 && only_digits(argv[1]))
    {
        // Convert argv[1] from a `string` to an `int`
        int k = atoi(argv[1]);

        // Ask the user for plaintext
        string plain = get_string("plaintext:\n");

        int length = strlen(plain);
        char cipher[length] ;
        for (int i = 0 ; i < length ; i ++)
        {
            char rotated = rotate(plain[i], k);
            cipher[i] = rotated;
        }

        cipher[length]  = '\0';
        printf("ciphertext: %s\n", cipher);

        return 0;
    }
    else
    {
        printf("Usage: %s Key\n", argv[0]);
        return 1;
    }
}


// Make sure every character in argv[1] is a digit
bool only_digits(string s)
{
    int digits = 0;

    for (int i = 0, length = strlen(s); i < length; i++)
    {
        if (!isdigit(s[i])) // If a non-digit character is found
        {
            return false;
        }
    }
    return true;
}


// Rotate the character if it's a letter
char rotate(char c, int k)
{
    if (isalpha(c))
    {
        if (isupper(c))
        {

            int p = (char) c - 'A' ;
            //p is a non ascii value//قيمة الحرف الغير مشفر  بس مش بال اسكي
            int z = ((int)p + (int)k)   % 26 ;
            //z is a non ascii value//قيمة الحرف المشفر بس مش بالل اسكي
            int o = (int)z + 'A' ;

            return o ;
        }

        else if (islower(c))
        {

            int p = (char) c - 'a' ;
            //p is a non ascii value//قيمة الحرف الغير مشفر  بس مش بال اسكي
            int z = ((int)p + (int)k)   % 26 ;
            //z is a non ascii value//قيمة الحرف المشفر بس مش بالل اسكي

            int o = (int)z + 'a' ;

            return o ;

        }

    }

    return c;
}