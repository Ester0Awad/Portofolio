#include <stdio.h>
#include <stdlib.h>


int main (void)
{
   int* list = malloc (sizeof(int)* 3);
   if (list == NULL)
   {
       return 1;
   }

     list[0] = 1;
     list[1] = 2;
     list[2] = 3;

     //....

     int* tmp = realloc (list, sizeof(int)* 4);

     //list = the chunck of memory that I want to grow or shrink
     //to re allocate memory

     if (tmp == NULL)
     {
          free(list);
          return 1;
     }
     list = tmp;

     list[3] = 4;

     for (int i = 0; i < 3; i ++)
     {
        printf("%i\n", list[i]);
     }

     free(list);
     return 0;
}