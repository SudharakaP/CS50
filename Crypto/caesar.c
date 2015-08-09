/*******************************************************
 * caesar.c
 *
 * Computer Science 50 (EdX)
 * Sudharaka Palamakumbura
 *
 * Encrypts messages using Caesar's cipher. Accept a 
 * single command-line argument: a non-negative integer. 
 *
 *******************************************************/
 
#include<stdio.h>
#include<cs50.h>
#include<stdlib.h>
#include <string.h>
 
int main(int argc, string argv[])
{
    // checks wheather number of arguements is exactly two
    if (argc == 2) 
    {
        string text = GetString(); // obtain plaintext
        
        // iterates over each character of plaintext
        for (int i = 0, n = strlen(text), key = atoi(argv[1]); i < n; i++)
        {
            // converts only alphabatic characters into cipher text
            if ((text[i] <= 'Z') && (text[i] >= 'A'))
            {
                printf("%c", (((text[i] - 'A') + key) % 26)+'A');        
            }
            else if ((text[i] <= 'z') && (text[i] >= 'a'))
            {
                printf("%c", (((text[i] - 'a') + key) % 26)+'a');
            }
            else 
            {
                printf("%c", text[i]); 
            }
        }
        printf("\n");         
    }
    else
    {
        // yells if number of arguements not equal to two
        printf("Invalid Input\n");
        return 1;
    }         
}
