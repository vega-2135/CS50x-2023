#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt the user for a number between 1 and 8
    int height;

    do
    {
        height = get_int("how tall should the pyramid be (choose a number between 1 and 8): ");
    }
    while (height < 1 || height > 8);

// For every line
    for (int i = 1; i <= height; i++)
    {
        // This is adding first ' 's
        for (int j = height; j > i; j--)
        {
            printf(" ");
        }
        // This is adding lef pyramid's #s
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        // This is for adding gaps between pyramids
        printf("  ");

        //This is for adding right pyramid's #s
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }


        printf("\n");
    }



}