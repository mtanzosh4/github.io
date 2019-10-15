// implement binary search function

#include <cs50.h>
#include <stdio.h>

#define NUMBERS 9

bool bin_search(int value, int values[], int size);

int main(void)
{
    int arr[] = {2, 4, 6, 7, 8, 11, 14, 18, 20};

    int target = get_int("Enter a number: ");

    if (bin_search(target, arr, NUMBERS))
    {
        printf("Found\n");
    }
    else
    {
        printf("Not found!\n");
    }
}

bool bin_search(int value, int values[], int size)
{
    int min = 0;
    int max = size - 1;
    
    while (min <= max)
    {
        int middle = (min + max) / 2; 
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

