#include <stdio.h>
#include <cs50.h>

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
    while (cents >= 25)
    {
        cents = cents - 25;
        coins++;
    }
    while (cents >= 10)
    {
        cents = cents - 10;
        coins++;
    }
    while (cents >= 5)
    {
        cents = cents - 5;
        coins++;
    }
    while (cents >= 1)
    {
        cents = cents - 1;
        coins++;
    }

    printf("%i\n", coins);
}