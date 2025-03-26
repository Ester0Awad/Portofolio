#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main (void)
{
    typedef struct
    {
        string name;
        string number;
    }
    person;

     
    person people[3];

    people[0].name = "Ahmad";
    people[0].number = "012123";

    people[1].name = "Khaled";
    people[1].number = "010111";

    people[2].name = "Hasan";
    people[2]. number = "011666";


    //string names[] = {"Ahmad" , "Khaled" , "Hasan"} ;
    //string numbers[] = {"012123", "010111", "011666"};
              //[3]
    for (int i = 0 ; i < 3 ; i ++)
    {
        if (strcmp("Hasan", people[i].name) == 0)
       // if (!strcmp("Khaled", names[i]) )                             // ! means "not"
        {
               printf("FOUND! %s\n", people[i].number);
               return 0;
        }

    }
     printf("NOT FOUND!\n");

}