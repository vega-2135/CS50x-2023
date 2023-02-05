#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Prompt user to say his name and say hi
    string username = get_string("What is your name? ");
    printf("hello, %s\n", username);

}