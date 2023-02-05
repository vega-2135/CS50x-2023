#include <cs50.h>
#include <stdio.h>

int is_valid(long card_number);
int get_num_digits(long card_number);
int get_first_two_digits(long card_number);

int main(void)
{
    long card_number = get_long("Credit card number: ");

    int validity = is_valid(card_number);

    if (validity == 0)
    {
        printf("INVALID\n");
        return 0;
    }

    int first_two_digits = get_first_two_digits(card_number);
    int num_digits = get_num_digits(card_number);

    int first_digit = first_two_digits / 10;

    if (num_digits == 15 && (first_two_digits == 34 || first_two_digits == 37))
    {
        printf("AMEX\n");
    }
    else if (num_digits == 16 && first_two_digits > 50 && first_two_digits < 56)
    {
        printf("MASTERCARD\n");
    }
    else if (first_digit == 4 && (num_digits == 13 || num_digits == 16))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

int get_num_digits(long card_number)
{
    int digits = 0;
    while (card_number > 0)
    {
        card_number /= 10;
        digits += 1;
    }
    return digits;
}

int get_first_two_digits(long card_number)
{
    while (card_number > 100)
    {
        card_number /= 10;
    }
    return card_number;
}

// Returns 1 when the card number is valid, else 0
int is_valid(long card_number)
{
    int position = 0;
    int sum = 0;

    while (card_number > 0)
    {
        // Divide by 10 to extract last digit of credit card number.
        int reminder = card_number % 10;

        // If digit is in an odd position, then first multiply by two and then added to sum.
        if (position % 2 != 0)
        {
            reminder *= 2;
            // If digit is compose of two numbers calculate the sum of those two numbers.
            if (reminder > 9)
            {
                int last_digit = reminder % 10;
                int first_digit = reminder / 10;
                reminder = last_digit + first_digit;
            }
        }

        sum += reminder;
        position += 1;
        card_number /= 10;
    }
    // Check for validity of credit card number if the modulo 10 of the resulting number
    // from above calculations is = or != to 0.
    if (sum % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}