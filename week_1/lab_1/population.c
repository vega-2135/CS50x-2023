#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int starting_population_size;

    do
    {
        starting_population_size = get_int("Enter starting population size(minimum allowed population size = 9): ");
    }
    while (starting_population_size < 9);

    // TODO: Prompt for end size
    int ending_population_size;

    do
    {
        ending_population_size = get_int("Enter ending population size(must be equal or greater than starting population size ): ");
    }
    while (ending_population_size < starting_population_size);


    // TODO: Calculate number of years until we reach threshold
    int current_population = starting_population_size;

    int years = 0;
    while (current_population < ending_population_size)
    {
        int born = current_population / 3;
        int deaths = current_population / 4;
        current_population += born - deaths;
        years += 1;
    }

    // TODO: Print number of years
    printf("Years: %i", years);
}
