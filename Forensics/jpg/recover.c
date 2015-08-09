/****************************************************************************
 * recover.c
 *
 * Computer Science 50 (Problem Set 4)
 * Sudharaka Palamakumbura
 *
 * Recovers JPEGs from a forensic image.
 ***************************************************************************/
 
#include<stdio.h>
#include <stdint.h>

#define BLOCK_SIZE 512

// function prototypes
int size_of_file(FILE* stream);

int main(void)
{
    // opens card.raw for reading
    FILE* input = fopen("card.raw", "r");
    if (input == NULL)
    {
        fclose(input);
        fprintf(stderr, "Could not open card.raw.\n");
        return 1;
    }
    
    int n = size_of_file(input);

    // reads from card.raw, stores the data in file_content array
    uint8_t file_content[n];
    fread(&file_content, n, 1, input);
    
    int starting_ind = 0;
    
    // declares and array for file names
    char file_names[n / BLOCK_SIZE]; 
    int file_number = 0;
    
    // generates each image
    for (int j = 0; j < n; j++)
    {
        int no_blocks = 0;
        
        if (file_content[j] == 0xff && file_content[j+1] == 0xd8 
            && file_content[j+2] == 0xff && (file_content[j+3] == 0xe0 
            || file_content[j+3] == 0xe1))
        {
            starting_ind = j;

            // calculates the number of blocks in each image
            do
            {
                j = j + BLOCK_SIZE;
                no_blocks++;
            }
            while (!(file_content[j] == 0xff && file_content[j+1] == 0xd8 
            && file_content[j+2] == 0xff && (file_content[j+3] == 0xe0 
            || file_content[j+3] == 0xe1)) && j < n);
            
            // check to see if end of file_content array has reached
            if (j > n)
                no_blocks--;
                
            // stores each image in a temporary array
            uint8_t temp[BLOCK_SIZE * no_blocks];
            for (int k = 0, l = starting_ind; k < BLOCK_SIZE * no_blocks; k++, l++)
                temp[k] = file_content[l];
            
            // assigns filenames    
            sprintf(file_names, "%03d.jpg", file_number);
            file_number++;
            
            // writes output files             
            FILE* output = fopen(file_names, "w");
            fwrite(temp, BLOCK_SIZE * no_blocks, 1, output);
            fclose(output);
                       
            if (j > n)
                break;
                
            j--; 
        }
    }
    fclose(input);
    return 0;
}    

// calculates the size of stream in bytes 
int size_of_file(FILE* stream)
{ 
    int i = 0;
    while (fgetc(stream) != EOF)
        i++;
    
    rewind(stream);    
    return i;
}


    

    






