/*******************************************************
 * binarysearch.c
 *
 * Computer Science 50 (EdX)
 * Sudharaka Palamakumbura
 *
 * Practice Exercise: Implementation of Binary Search.   
 *
 *******************************************************/

#include <cs50.h>
#include <stdio.h>

#define SIZE 8

// return true iff needle is in haystack, using binary search
bool search(int needle, int haystack[], int size)
{   
    int begin = 0, end = size - 1;
    
    while (!(end < begin))
    {    
        int middle = (begin + end) / 2;

        if (haystack[middle] < needle)
            begin = middle + 1;
        else if (haystack[middle] > needle)
            end = middle - 1;
        else
            return true;
    }
    return false;
}

int main(void)
{
    int numbers[SIZE] = { 4, 8, 15, 16, 23, 42, 50, 108 };
    printf("> ");
    int n = GetInt();
    if (search(n, numbers, SIZE))
        printf("YES\n");
    return 0;
}
