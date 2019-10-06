// complete the selection_sort function

#include <cs50.h>
#include <stdio.h>

// function prototypes
void selection_sort(int arr[], int size);
void print_array(int arr[], int size);

// size of array
#define SIZE 10

int main(void)
{ 
    // initialize array
    int arr[] = {1, 8, 4, 6, 0, 3, 5, 2, 7, 9};
  
    // sort array
    selection_sort(arr, SIZE); 
    
    // print out the array
    print_array(arr, SIZE); 
    
    // done
    return 0; 
} 

// Function to print an array
void print_array(int arr[], int size) 
{ 
    for (int i = 0; i < size; i++) 
    {
        printf("%i ", arr[i]); 
    }
    printf("\n"); 
}

// selection sort
void selection_sort(int arr[], int size) 
{
    // TODO
    
    
    for (int i = 0; i < size; i++)
    {
        int min = i;

        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
        
    }
    
    
}
