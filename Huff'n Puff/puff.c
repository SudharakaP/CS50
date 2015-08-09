/****************************************************************************
 * puff.c
 *
 * Computer Science 50 (Problem Set 6)
 * Sudharaka Palamakumbura
 *
 * Decompresses huffed files.
 ***************************************************************************/

#include<stdio.h>
#include <stdbool.h>
#include<stdlib.h>

#include "huffile.h"
#include "tree.h"
#include "forest.h"

int main(int argc, const char* argv[])
{
    // ensures correct usage
    if (argc != 3)
    {
        printf("Usage: ./puff File_to_puff Name_to_save\n");
        return 1;
    }

    // opens huff file (Huffman encoded file)
    Huffile* huff_file = hfopen(argv[1], "r");
    if (huff_file == NULL)
    {
        printf("Could not open huff file");
        return 1;
    }
    
    // reads the header of huff file    
    Huffeader* huff_header = malloc(sizeof(Huffeader));
    if (!hread(huff_header, huff_file))
    {
        printf("Could not read the huff header");
        free(huff_header);
        hfclose(huff_file);
        return 1;
    }   
        
    int sum_freq = 0;
    for (int i = 0; i < SYMBOLS; i++)
        sum_freq += huff_header -> frequencies[i];     
     
    // checks for correct magic number and checksum   
    if (huff_header -> magic != MAGIC || huff_header -> checksum != sum_freq)
    {
        printf("Not a valid huffed file");
        hfclose(huff_file);
        free(huff_header);        
        return 1;
    }   
    
    Forest* forest = mkforest();
    Tree* temp_tree;
    
    // make trees for each non-zero frequency and plants them in forest
    for (int i = 0; i < SYMBOLS; i++)
        if (huff_header -> frequencies[i] != 0)
        {
            temp_tree = mktree();
            if (temp_tree == NULL)
            {
                printf("Could not build temp_tree");
                rmtree(temp_tree);
                rmforest(forest);
                hfclose(huff_file);
                free(huff_header); 
                return 1;
            }
            temp_tree -> symbol = i;
            temp_tree -> frequency = huff_header -> frequencies[i];
            
            if (!plant(forest, temp_tree))
            {
                printf("Could not plant temp_tree");
                rmtree(temp_tree);
                rmforest(forest);
                hfclose(huff_file);
                free(huff_header);
                return 1;    
            }
        }
        
    Tree* tree_1;    
    Tree* tree_2;
    
    // constructs Huffman tree
    while (true)
    {
        tree_1 = pick(forest);
        if (tree_1 == NULL)
            break;
            
        tree_2 = pick(forest);
        if (tree_2 == NULL)
        {
            plant(forest, tree_1);
            break;
        }
        
        temp_tree = mktree();
        temp_tree -> frequency = (tree_1 -> frequency) + (tree_2 -> frequency);
        temp_tree -> left = tree_1;
        temp_tree -> right = tree_2;
        plant(forest, temp_tree);
    }
    
    // uses temp_tree to point to the finalized forest with one tree
    temp_tree = pick(forest);
    if (temp_tree == NULL)
    {
        printf("Empty huff file");
        rmtree(temp_tree);
        rmforest(forest);
        hfclose(huff_file);
        free(huff_header);
        return 1;
    }
    
    // opens a file to write puffed output
    FILE* output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not create/open puff file");
        rmtree(temp_tree);
        rmforest(forest);
        hfclose(huff_file);
        free(huff_header);
        return 1;
    }
    
    int bit;
    Tree* point = temp_tree;
    
    // writes the output using the temp_tree (finalized forest)
    while ((bit = bread(huff_file)) != EOF)
    {
        if (bit == 0)
            if (point -> left != NULL)
                point = point -> left;
            else
            {
                fputc(point -> symbol, output);
                point = temp_tree;
                point = point -> left;
            }
        else 
            if (point -> right != NULL)
                point = point -> right;
            else
            {
                fputc(point -> symbol, output);
                point = temp_tree;
                point = point -> right;
            }
    }
    
    // writes final character (if "point == NULL" huff file has one character)
    if (point != NULL)
        fputc(point -> symbol, output);
    
    // closes files and frees memory    
    rmtree(temp_tree);
    rmforest(forest);
    free(huff_header);
    hfclose(huff_file);
    fclose(output);
}
