#include <stdio.h>
#include <cs50.h>

int main(void)
{

    // do-while loop for input
    int x;
    do
    {
        x = get_int("Height: ");
    }
    while (x < 1 || x >= 9);

    //outer for loop for each row
    for (int i = 1; i <= x; i++)
    {
        // inner for loop for printing out x - i spaces per row
        for (int s = x - i; s > 0; s--)
        {
            printf(" ");
        }

        // inner for loop for printing out i pound signs for i rows
        for (int h = i; h > 0; h--)
        {
            printf("#");
        }

        //two spaces between the pyramids
        printf("  ");

        // inner for loop to print out the right pyramid
        for (int h = i; h > 0; h--)
        {
            printf("#");
        }

        // netx line statement to distinguish between each row
        printf("\n");
    }



}