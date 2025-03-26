#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int count_grades(string text);

int letters = 0 ;
int sentences = 0;
int words = 0;
int grade = 0 ;


int main(void)
{
    string name = get_string("Text:\n");
    int num_letters = count_letters(name);
    int num_sentences = count_sentences(name);
    int num_words = count_words(name);

    count_grades(name); // Calculate the grade

    int num_grades = (int) round(grade); //Round the grade and assign it to num_grades


    if (num_grades >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (num_grades < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", num_grades);
    }

}

int count_letters(string text)

{
    int letter = 0;
    //int length = strlen(letter);

    for (int i = 0,   length = strlen(text)   ; i < length ; i ++)
    {
        if (islower(text[i]) || isupper(text[i]))
        {
            letter ++;
        }

        //  else
        // {
        //Non-alphabetical charcter, do nothing
        // }

    }

    return letter ;
}



int count_words(string text)


{
    int word = 0;

    for (int i = 0,  length = strlen(text); i < length ; i ++)

    {

        if (text[i] == ' ')
            //or '.'
        {
            word ++;
        }

        else if (text[i] == '-')
        {
            word --;
        }

    }

    return word + 1 ;

}

int count_sentences(string text)

{
    int sentence = 0 ;
    for (int i = 0, length = strlen(text); i < length ; i ++)
        if (text[i] == '.' || text[i] == '!' || text [i] == '?')
        {
            sentence ++;
        }
        else if (text[i] == ',' || text[i] == ';')
        {
            //Do not count it as a sentence // Do nothing
        }

    return sentence;


}

int count_grades(string text)
{
    letters = count_letters(text);
    sentences = count_sentences(text);
    words = count_words(text);


    int L = letters;
    int S = sentences;
    int W = words;

    // float X = L/W*100 ;
    // float Y = S/W*100 ;

    //  grade = (int)((0.0588 * X) - (0.296 * Y) - 15.8);


    // Calculate the grade using the provided formula

    grade = round(0.0588 * ((float)L / W * 100) - 0.296 * ((float)S / W * 100) - 15.8);
    // grade = S;


    return grade;


}