#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int get_number_of_letters(string text);

int get_number_words(string text);

int get_number_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    int number_characters = get_number_of_letters(text);
    int number_words = get_number_words(text);
    int number_sentences = get_number_sentences(text);
    float L = (number_characters / (float) number_words) * 100;
    float S = (number_sentences / (float) number_words) * 100;
    int index = (int) round(0.0588 * L - 0.296 * S - 15.8);

    printf("number_characters: %d, number_words: %d, number_sentences: %d\n",
           number_characters, number_words, number_sentences);

    //printf("L: %d, S: %d\n", L, S);
    printf("L: %f, S: %f\n", L, S);

    if (index >= 16)
    {
        printf("%s\n", "Grade 16+");
    }
    else if (index < 1)
    {
        printf("%s\n", "Before Grade 1");
    }
    else
    {
        printf("%s %i\n", "Grade", index);
    }

}

int get_number_of_letters(string text)
{
    int length_text = strlen(text);
    int length = 0;
    for (int i = 0; i < length_text; i++)
    {
        if (isalpha(text[i]))
        {
            length += 1;
        }
    }
    return length;
}

int get_number_words(string text)
{
    int length_text = strlen(text);
    int words_count = 0;

    for (int i = 0; i < length_text; i++)
    {
        if (text[i] == ' ')
        {
            words_count += 1;
        }
    }
    return words_count + 1;
}

int get_number_sentences(string text)
{
    int length_text = strlen(text);
    int sentence_count = 0;

    for (int i = 0; i < length_text; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentence_count += 1;
        }
    }
    return sentence_count;

}

