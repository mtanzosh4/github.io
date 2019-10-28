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

    n = n * 100;

    int coins = 0;
    while (n >= 25)
    {
        n = n - 25;
        coins++;
    }
    while (n >= 10)
    {
        n = n - 10;
        coins++;
    }
    while (n >= 5)
    {
        n = n - 5;
        coins++;
    }
    while (n >= 1)
    {
        n = n - 1;
        coins++;
    }

    printf("%i\n", coins);
}