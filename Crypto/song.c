/*****************************************************
 * myspace.c
 *
 * Computer Science 50 (EdX)
 * Sudharaka Palamakumbura
 *
 * Sings "This Old Man".
 *
 *****************************************************/
 
#include<stdio.h>
#include<cs50.h>

void verse(string word_one, string word_two);
 
int main(void)
{
    // line one words
    string line_one[] = {"one", "two", "three", "four", 
                         "five", "six", "seven", "eight",
                         "nine", "ten"};
 
    // line two words                     
    string line_two[] = {"on my thumb", "on my shoe", 
                         "on my knee", "on my door", 
                         "on my hive", "on my sticks",
                         "up in heaven", "on my gate", 
                         "on my spine", "once again"};
    
    // put the words in corresponding lines                     
    for (int i = 0; i < 10; i++)
    {
        verse(line_one[i], line_two[i]);
    }
}

/*
 * Prints the verses taking given words 
 * as inputs.
 */  
void verse(string word_one, string word_two)
{
    printf("This old man, he played %s\n", word_one);
    printf("He played knick-knack %s\n", word_two);
    printf("Knick-knack paddywhack, give your dog a bone\n");
    printf("This old man came rolling home\n");
    printf("\n");
}
