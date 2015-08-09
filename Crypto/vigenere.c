/*******************************************************
 * vigenere.c
 *
 * Computer Science 50 (EdX)
 * Sudharaka Palamakumbura
 *
 * Encrypts messages using Vigenere's cipher. Accepts a 
 * single command-line argument: a keyword, k, composed 
 * entirely of alphabetical characters.  
 *
 *******************************************************/
 
#include<stdio.h>
#include<cs50.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // checks wheather number of arguements is exactly two
    if (argc == 2)
    {
        // checks wheather key contains non alphabetic characters
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isalpha(argv[1][i]) == 0)
            {
                printf("Invalid Key\n");
                return 1;
            }
        }
        
        // change upper case letters in key to lower case letters
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isupper(argv[1][i]) != 0)
            {
                argv[1][i] = argv[1][i] + ('a' - 'A');
            }
        } 
    
        string text = GetString(); // obtain plaintext
        
        // iterates over each character of plaintext
        for (int i = 0, m = strlen(text), l = strlen(argv[1]),
             j = 0; i < m; i++, j++)
        {
            // converts only alphabetic characters into cipher text
            if ((text[i] <= 'Z') && (text[i] >= 'A'))
            {
                printf("%c", ((((text[i]-'A') + 
                       (argv[1][j % l] - 'a')) % 26)) + 'A');        
            }
            else if ((text[i] <= 'z') && (text[i] >= 'a'))
            {
                printf("%c", ((((text[i]-'a') + 
                       (argv[1][j % l] - 'a')) % 26)) + 'a');
            }
            else 
            {
                printf("%c", text[i]);
                j--; 
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


