#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float n;
    do
    {
        n = get_float("Change Owed: ");
    }
    while(n < 0);

    int cents = round(n * 100);
    int coins = 0;

    coins += cents/25;
    cents = cents % 25;

    coins += cents/10;
    cents = cents % 10;

    coins += cents/5;
    cents = cents % 5;

    coins += cents;

    printf("%i\n", coins);
}