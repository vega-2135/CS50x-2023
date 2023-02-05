#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    int cents;

    do
    {
        cents = get_int("Number of cents: ");
    }
    while (cents < 0);

    return cents;
}

int calculate_quarters(int cents)
{
    int quarters = 25;
    int quarters_to_return = cents / quarters;
    return quarters_to_return;
}

int calculate_dimes(int cents)
{
    int dimes = 10;
    int dimes_to_return = cents / dimes;
    return dimes_to_return;
}

int calculate_nickels(int cents)
{
    int nickels = 5;
    int nickels_to_return = cents / nickels;
    return nickels_to_return;
}

int calculate_pennies(int cents)
{
    int pennies = 1;
    int pennies_to_return = cents / pennies;
    return pennies_to_return;
}
