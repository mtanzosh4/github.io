#include <cs50.h>
#include <stdio.h>

int main(void)
{
    float c = get_float("C: ");
    printf("F: %.1f\n", ((c * 9) / 5) + 32);
}
