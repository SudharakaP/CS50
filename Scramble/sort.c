/*********************************************************
 * sort.c
 *
 * Computer Science 50 (EdX)
 * Sudharaka Palamakumbura
 *
 * Practice Exercise: Implementation of a sort algorithm.   
 *
 *********************************************************/

#include <stdio.h>

#define SIZE 8

// sort array using selection sort
void sort(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {     
        for (int j = i; j < size; j++)
        {
            if (array[j] < array[i])
            {
                array[i] += array[j];
                array[j] = array[i] - array[j];
                array[i] -= array[j];
            }
        }
    }    
}

int main(void)
{
    int numbers[SIZE] = { 4, 15, 16, 50, 8, 23, 42, 108 };
    for (int i = 0; i < SIZE; i++)
        printf("%d ", numbers[i]);
    printf("\n");
    sort(numbers, SIZE);
    for (int i = 0; i < SIZE; i++)
        printf("%d ", numbers[i]);
    printf("\n");
    return 0;
}
