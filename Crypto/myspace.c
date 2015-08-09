/*****************************************************
 * myspace.c
 *
 * Computer Science 50 (EdX)
 * Sudharaka Palamakumbura
 *
 * Prompts the user for a message, and then outputs 
 * the message with its first letter capitalized, with 
 * all other letters in alternating case. Assumes that 
 * user inputs lower case letters and spaces only.
 *
 *****************************************************/
 
#include<stdio.h>
#include<cs50.h>
#include<string.h>

int main(void)
{
    string input = GetString(); // gets input from user
    
    int count = 0; // counts lower case letters
    
    /* 
     * Capitalizes first letter with all other letters 
     * in alternating case. 
     */     
    for (int i = 0, length = strlen(input); i < length; i++)
    {
        // checks for lower case letters
        if ('a' <= input[i] && input[i] <= 'z')
        {
            // checks for even letters
            if (count % 2 == 0)
            {
                printf("%c", input[i] - ('a' - 'A'));
            }
            else 
            {
                printf("%c", input[i]);
            }
            count++;
        }
        else
        {
            printf("%c", input[i]);
        }
    }
    printf("\n");
}
