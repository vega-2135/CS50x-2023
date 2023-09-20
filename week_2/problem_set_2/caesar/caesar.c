#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

string get_ciphertext(string plaintext, int key_number);

int main(int argc, string argv[])
{


    // Check if user added an argument in command line, and if if the argument is a positive number.
    if (argc != 2)
    {
        printf("missing command-line argument\n");
        return 1;
    }

    // Check that the input is a decimal digit
    string key = argv[1];
    int key_length = strlen(key);
    for (int i = 0; i < key_length; i++)
    {
        if (isdigit(key[i]) == 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Convert the string input into an int
    int key_number = atoi(key);

    // Check that the number inputted is positive
    if (key_number < 0)
    {
        printf("missing command-line argument\n");
        return 1;
    }

    // Get plaintext from user and convert it in ciphertext.
    string plaintext = get_string("plaintext: ");
    string ciphertext = get_ciphertext(plaintext, key_number);

}



string get_ciphertext(string plaintext, int key_number)
{

    int plaintext_length = strlen(plaintext);
    printf("ciphertext: ");

    for (int i = 0; i < plaintext_length; i++)
    {
        // Check for lower and uppercase and make conversion into corresponding character.

        if (isupper(plaintext[i]))
        {
            printf("%c", (((plaintext[i] + key_number - 'A') % 26) + 'A'));
        }

        else if (islower(plaintext[i]))
        {
            printf("%c", (((plaintext[i] + key_number - 'a') % 26) + 'a'));
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return plaintext;
}

