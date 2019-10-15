// implement binary search function

#include <cs50.h>
#include <stdio.h>

#define SIZE 9

bool bin_search(int value, int values[], int n);

int main(void)
{
    int arr[] = {2, 4, 6, 7, 8, 11, 14, 18, 20};

    int target = get_int("Enter a number: ");

    if (bin_search(target, arr, SIZE))
    {
        printf("Found\n");
    }
    else
    {
        printf("Not found!\n");
    }
}

bool bin_search(int value, int values[], int n)
{
    int min = 0, max =  n - 1;
    while (min <= max)
    {
//         printf("min: %i max: %i\n", min, max);
        int middle = (min + max) / 2;
//         printf("middle: %i values[middle]: %i\n", middle, values[middle]);
        if (value < values[middle])
        {
            max = middle - 1;
        }
        else if (value > values[middle])
        {
            min = middle + 1;
        }
        else if (value == values[middle])
        {
            return true;
        }
    }
    return false;
}
