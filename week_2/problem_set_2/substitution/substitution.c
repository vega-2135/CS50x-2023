#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

string get_ciphertext(string plaintext, string key);

int main(int argc, string argv[])
{


    // Check if user added an argument in command line, and if if the argument is a positive number.
    if (argc != 2)
    {
        printf("missing command-line argument\n");
        return 1;
    }

    // Check validity of key
    string key = argv[1];
    int key_length = strlen(key);

    // Check if key does not contain 26 characters
    if (key_length != 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }

    // Check if key contains any non alphabetic character
    for (int i = 0; i < key_length; i++)
    {
        if (isalpha(key[i]) == 0)
        {
            printf("Key must only contain alphabetic characters\n");
            return 1;
        }
    }

    // Check that key does not contain repeaded characters
    for (int i = 0; i < key_length; i++)
    {
        for (int j = i + 1; j < key_length; j++)
        {
            if (toupper(key[i]) == toupper(key[j]))
            {
                printf("Key must not contain repeated characters\n");
                return 1;
            }
        }
    }


    // Get plaintext from user and convert it in ciphertext.
    string plaintext = get_string("plaintext: ");
    string ciphertext = get_ciphertext(plaintext, key);

}




string get_ciphertext(string plaintext, string key)
{

    printf("ciphertext: ");

    // Compare characters in plaintext with those in alpha
    for (int i = 0; i < strlen(plaintext); i++)
    {
        // Check if plaintext is in uppercase
        if (isupper(plaintext[i]))
        {
            string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            for (int j = 0; j < strlen(alpha); j++)
            {
                if (plaintext[i] == alpha[j])
                {
                    printf("%c", toupper(key[j]));

                }
            }
        }
        // Check if plaintext is in lowercase
        else if (islower(plaintext[i]))
        {
            string alpha = "abcdefghijklmnopqrstuvwxyz";
            for (int j = 0; j < strlen(alpha); j++)
            {
                if (plaintext[i] == alpha[j])
                {
                    printf("%c", tolower(key[j]));

                }

            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return plaintext;
}