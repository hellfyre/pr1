/*##################################
#                                  #
#  Author:  Marcell Kehmstedt      #
#  Email:   marcell@kehmstedt.com  #
#  Website: www.kehmstedt.com      #
#                                  #
##################################*/
 

#include <stdio.h>

/*
 Saves bitmap images as Windows Bitmap files.
 
 Parameters:
    pathToFile - path to the file to which to save the bitmap to
    pixeldata  - pointer to array containing unsigned 24bit pixel data
    width      - width of the image
    height     - height of the image
    invertY    - whether to invert the Y-axis of the target image
 
 Returns:
    0 - an error occured, the image was not saved
    1 - ok
 
 Details:
    The pixeldata is expected to hold continues pixels row-wise.
    The first pixel is assumed to be located in the lower left corner of the image.
    To put the first pixel in the upper left corner, the Y-axis can be inverted by setting
    the invertY parameter to 1 (TRUE).
 
    Every pixel shall consist of three consecutive unsigned 8bit color components.
    The ordering is: blue, green, red
*/
int saveBMP(const char* pathToFile, unsigned char *pixeldata, unsigned int width, unsigned int height, int invertY)
{
    FILE *file = fopen(pathToFile, "wb");
    if (!file)
        return 0;
    
    const int linefill = (4-(3*width)%4)%4;

    unsigned char fileheader[14];
    fileheader[0] = 'B';        // magic
    fileheader[1] = 'M';        // magic
    *(int*)&fileheader[2]  = 54+3*width*height+height*linefill;  // filesize 
    *(int*)&fileheader[6]  = 0;  // reserved
    *(int*)&fileheader[10] = 54; // offset to data

    unsigned char infoheader[40];
    *(int*)&infoheader[0]  = 40;  // size of this header
    *(int*)&infoheader[4]  = width;
    *(int*)&infoheader[8]  = (invertY ? -height : height);
    *(short*)&infoheader[12] = (short)1;
    *(short*)&infoheader[14] = (short)24;   // bits per pixel
    *(int*)&infoheader[16] = 0;  // compression
    *(int*)&infoheader[20] = 3*width*height;
    *(int*)&infoheader[24] = 0;
    *(int*)&infoheader[28] = 0;
    *(int*)&infoheader[32] = 0;
    *(int*)&infoheader[36] = 0;
    
    if (fwrite(fileheader, 14, 1, file) != 1) { fclose(file); return 0; } 
    if (fwrite(infoheader, 40, 1, file) != 1) { fclose(file); return 0; }
    
    int row, i;
    for (row = 0; row < height; row++)
    {
        if (fwrite(&pixeldata[row*width*3], 3, width, file) != width) { fclose(file); return 0; }
        for (i = 0; i < linefill; i++) if (fputc((char)0, file) == EOF) { fclose(file); return 0; }
    }
    
    fclose(file);
    
    return 1;
}
