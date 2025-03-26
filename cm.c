#include <stdio.h>
#include <cs50.h>

int main (void)
{
   char* s =  get_string("S? ");
   // s indiactes to the address(pointer which means char*) of first element of an array(first charachter).
   //poniters take different places in meomery that is why when I compared between two adrresses of the same string
   //the addresses were different.
   char* t = get_string("T? ");

   if (s == t)
   {
     printf("same.\n");
   }
   else
   {
    printf("different\n");
   }
   printf("%p\n%p\n", s, t);

}