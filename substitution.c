#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <stdlib.h>
//bool isUpper(string key []);

int main(int argc, string argv[])
{

    // upper and lowercase alphabet arrays
    string abc_U [] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    string abc_L [] = {"abcdefghijklmnopqrstuvwxyz"};

    // instantiation of original, upper-, and lower-case keys
    string key = "";
    string sub, sub_U, sub_L;


    // if two arguments passed in command-line, set the second argument (aka key) to variable key
    if (argc != 2)
    {
        printf("Error, check argument length.");
        return 1;
    }


    key = argv[1];

    // copy strings to upper- and lower-case variables
    string key_L = malloc(strlen(key) * 1);
    string key_U = malloc(strlen(key) * 1);
    strcpy(key_L, key);
    strcpy(key_U, key);
    // set sub to first element of abc_U array (all the letters in the alphabet)
    sub_U = abc_U[0];

    // set sub to first element of abc_L array (all the letters in the alphabet)
    sub_L = abc_L[0];


    if (strlen(key) != strlen(sub_U))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < strlen(sub_U); i++)
    {
        if (!((key[i] >= 'A' && key[i] <= 'Z') || (key[i] >= 'a' && key[i] <= 'z')))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }

    for (int i = 0; i < strlen(sub_U); i++)
    {
        for (int j = i + 1; j < strlen(sub_U); j++)
        {
            if (key[i] == key[j])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    //printf("%lu\n", strlen(key));

    // make all characters uppercase and set to uppercase key variable
    for (int i = 0; i < strlen(key); i++)
    {
        //printf("%c", key[i]);
        if (key[i] >= 'a' && key[i] <= 'z')
        {
            key_U[i] -= 32;
            //printf("%c\n", key_U[i]);
        }
    }


    // make all characters lowercase and set to lowercase key variable
    for (int i = 0; i < strlen(key); i++)
    {
        if (key[i] >= 'A' && key[i] <= 'Z')
        {
            //printf("%c", key[i]);
            //printf("%c ", key_L[i]);
            key_L[i] += 32;
            //printf("%c\n", key_L[i]);
        }
    }

    // input string for plaintext
    string plain = get_string("plaintext: ");

    // duplicates string, plaintext is unchanged; stylistic choice
    string dup = plain;

    //printf("%c\n", plain[1]);
    //printf("%c\n", dup[1]);


    // outer for-loop for iterating through each character in the plaintext string
    for (int i = 0; i < strlen(plain); i++)
    {
        // inner for-loop for iterating through the alphabet array in order to find the matching index
        for (int j = 0, count = 0; j < strlen(sub_U); j++)
        {

            // if the character being iterated through is uppercase
            if (plain[i] >= 'A' && plain[i] <= 'Z')
            {

                // find its matching index in the uppercase alphabet array
                if (plain[i] == sub_U[j])
                {

                    //set the ciphertext character to its encrypted uppercase counterpart
                    dup[i] = key_U[j];
                    count++;
                    if (count == 1)
                    {
                        break;
                    }
                }

            }

            // if the character being iterated through is lowercase
            else if (plain[i] >= 'a' && plain[i] <= 'z')
            {

                // find its matching index in the lowercase alphabet array
                if (plain[i] == sub_L[j])
                {

                    //set the ciphertext character to its encrypted lowercase counterpart
                    dup[i] = key_L[j];
                    count++;
                    if (count == 1)
                    {
                        break;
                    }

                }
            }



        }
    }

    printf("ciphertext: %s\n", dup);
    return 0;

}


