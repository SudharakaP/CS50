/********************************************************************************
 * resize.c
 *
 * Computer Science 50 (Problem Set 4)
 * Sudharaka Palamakumbura
 *
 * Resizes a BMP by a factor of n where n is a positive integer; 1 <= n <= 100 
 *******************************************************************************/
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: resize n infile outfile\n");
        return 1;
    }
    
    if (atoi(argv[1]) < 1 || atoi(argv[1]) > 100 || atoi(argv[1]) == 0)
    {
        printf("n should be an integer: 1 <= n <= 100\n");
        return 1;
    }
       
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // remember the scaling factor
    int scale = atoi(argv[1]);

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // determine padding for output
    int padding_scale =  (4 - (bi.biWidth * scale * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // remember height and width of bitmap
    int biHeight = abs(bi.biHeight);
    int biWidth = bi.biWidth;
    
    // change BITMAPFILEHEADER and BITMAPINFOHEADER info
    bi.biWidth = bi.biWidth * scale;
    bi.biHeight = bi.biHeight * scale;
    bi.biSizeImage = (bi.biWidth * abs(bi.biHeight) * 3) + (padding_scale * abs(bi.biHeight));
    bf.bfSize = bf.bfOffBits + bi.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // set cursor positions
    fpos_t position1;
    fpos_t position2;
    fgetpos(inptr, &position1);   

    // iterate over infile's scanlines
    for (int i = 0; i < biHeight; i++)
    {
        for (int l = 0; l < scale; l++) 
        {   
            // iterate over pixels in scanline
            for (int j = 0; j < biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for (int k = 0; k < scale; k++)            
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
            
            // skip over padding, if any (input file)
            fseek(inptr, padding, SEEK_CUR);
                    
            // add padding, if any (output file)
            for (int k = 0; k < padding_scale; k++)
                fputc(0x00, outptr);
            
            // set cursor back to beginning
            fgetpos(inptr, &position2);
            fsetpos(inptr, &position1);
            
        }
        // set cursor to current line
        position1 = position2;
        fsetpos(inptr, &position1);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
