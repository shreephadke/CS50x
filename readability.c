#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    // takes text as input
    string txt = get_string("Text: ");

    // instantiates variables for number of letters, words, and sentences within the text
    float letters = 0;
    float words = 1;
    float sent = 0;

    // for loop for iterating through the text inputted
    for (int i = 0; i < strlen(txt); i++)
    {
        if ((txt[i] >= 'A') && (txt[i] <= 'z'))
        {
            letters++;
        }

        if ((txt[i] == ' ') && (txt[i - 1] != ' '))
        {
            words++;
        }

        if (((txt[i] == '.') || (txt[i] == '!') || (txt[i] == '?')) && ((txt[i - 1] >= 'A') && (txt[i - 1] <= 'z')))
        {
            sent++;
        }

    }

    //printf("Number of letters: %f\n", letters);
    //printf("Number of words: %f\n", words);
    //printf("Number of sentences: %f\n", sent);

    // converting letters/words to proportion of letters per every 100 words
    float L = letters / words * 100;

    // converting sentences/words to proportion of sentences per every 100 words
    float S = sent / words * 100;

    // Coleman-Liau index formula
    float in = 0.0588 * L - 0.296 * S - 15.8;

    // Coleman-Liau index casted to an integer (floored value)
    int index = (int) in;

    // rounds up
    if (in >= index + 0.5)
    {
        index++;
    }

    // if index is greater than or equal to 16, prints this statement
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }

    // if index is less than 1, prints this statement
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    else
    {
        printf("Grade %i\n", index);
    }


}