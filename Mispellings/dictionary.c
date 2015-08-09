/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

/**
 * Defines the structure of a trie.
 */

typedef struct node
{
    bool is_word;
    struct node* children[27];
}
node;
 
/**
 * Declares a node pointer to first node of the trie
 */
node* first_node = NULL;

/**
 * Size of Dictionary.
 */
int num_words;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO 
    
    char array[strlen(word) + 1];
    
    node* node_point = first_node;
    node** point;
    
    // converts each character in word to lowercase and stores in array.
    for (int i = 0, n = strlen(word); i <= n; i++)
        if (isupper(word[i]))
            array[i] = tolower(word[i]);
        else
            array[i] = word[i];
    
    // search for each character of array in the trie 
    for (int i = 0; array[i] != '\0'; i++)
    {   
        // looks at the relavant index of children in current node     
        if (array[i] != '\'')
            point = &(node_point -> children[array[i] % 'a']);
        else if (array[i] == '\'')
            point = &(node_point -> children[26]);
        
        // checks if current character is the final    
        if (array[i+1] == '\0')
            if (*point == NULL)
                return false;
            else
            {
                node_point = *point; 
                if (node_point -> is_word == true)
                    return true;
                else
                    return false;
            }
        
        if (*point == NULL)
            return false;
        
        // moves to next node    
        node_point = *point;
    }
    
    /* If all ends well true or false should be returned within 
     * the above for loop.
     */
    exit(1);
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO 
    
    // initializes variables used throughout this function
    int size_node = sizeof(node);
    char array[LENGTH + 1];
    num_words = 0;
    
    // opens the dictionary
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
        return false;
    
    // initializes the first node of the trie
    first_node = calloc(1, size_node);
    first_node -> is_word = false;
    
    // loads each word until end of dictionary    
    while (fscanf(fp, "%s\n", array) != EOF)
    {
        int n = strlen(array);
        
        // "node_point" points to the node and "point" points to inserted character 
        node* node_point = first_node;
        node** point;
        
        // keeps track of how many words in dictionary        
        num_words++;
        
        // iterates over each character of array, inserts in the trie      
        for (int i = 0; i < n; i++)
        {
            // checks for apostrophes and make pointers        
            if (array[i] != '\'')
                point = &(node_point -> children[array[i] % 'a']);
            else 
                point = &(node_point -> children[26]);
            
            // checks for end of word in next character
            if (array[i + 1] != '\0')
            {
                // updates pointers
                if (*point == NULL)
                {
                    *point = calloc(1, size_node);
                    node_point = *point;
                    
                    node_point -> is_word = false;
                }
                else
                    node_point = *point;
            }
            else 
            {
                // if end of word, sets "is_word" to true
                if (*point != NULL)
                {   
                    node_point = *point;
                    node_point -> is_word = true;
                }
                else 
                {
                    *point = calloc(1, size_node);
                    node_point = *point;
                    
                    node_point -> is_word = true;
                } 
            }         
        }        
    }
    // close the file 
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return num_words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    // checks to see if dictionary is loaded 
    if (first_node == NULL)
        return false;
    
    // frees each node
    while (true)
    {
        node* unload_point = first_node;           
        node** temp_point;
        
        while(true)
        {
            int i = 0;
            // checks for the first pointer in "children" array which is not null 
            while (i < 27)
                if (unload_point -> children[i] == NULL)
                    i++;
                else
                    break;
            
            // enters the next node pointed by the current node (if any)    
            if (i < 27)
            {
                temp_point = &(unload_point -> children[i]);
                unload_point = unload_point -> children[i];
            }
            // otherwise (all pointers null) frees the node
            else
            {
                if (first_node == unload_point)
                {
                    free(unload_point);
                    unload_point = NULL;
                    return true;
                }
                else
                {
                    free(unload_point);
                    *temp_point = NULL;
                    break;
                }
            }
        }
    }
}
