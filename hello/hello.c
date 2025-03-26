#include<stdio.h>
#include<cs50.h>
int main(void)

{
    //Assigning a value to a variable called name which is a string type
    string name = get_string("What is your name?\n");
    //Greeting the user after entering his/her name
    printf("Hello, %s", name);
}
