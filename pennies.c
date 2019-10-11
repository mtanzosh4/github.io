#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //prompts the user for an amount of days in between 28 and 31
    int daysInMonth;    
    do
    {
        daysInMonth = get_int("How many days are in the month? \n");  
    }
    while (daysInMonth > 31 || daysInMonth < 28);

    //prompts the user for a positive number of pennies earned on the first day
    long penniesOnFirstDay;    
    do
    {
        penniesOnFirstDay = get_long("How many pennies will you get on the first day? \n");  
    }
    while (penniesOnFirstDay < 1);
    
    //declaring variables to be used in the for loop
    int dayOfMonth;
    long numberOfPennies = penniesOnFirstDay;
    
    //this will perform the algorithm and add the value for each day in the month
    for (dayOfMonth = 1; dayOfMonth < daysInMonth; dayOfMonth++)
    {
        numberOfPennies += penniesOnFirstDay * pow(2, dayOfMonth);
        
    }
    
    //converting from pennies to dollars
    double total = (double) numberOfPennies / 100;
    
    //printing the number of dollars earned
    printf("$%.2f\n", total);
    
}
