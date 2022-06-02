#include "Texture.h"

int windowWidth;
int windowHeight;

pixel** InputImage(char* fileName, int width, int height)
{
    FILE * inFile;
    int input;

    printf("Width: %d, Height: %d\n", width, height);

        pixel** image = (pixel**)malloc(height * sizeof(pixel*));
        for (int i = 0; i < height; i++)
            image[i] = (pixel*)malloc(width * sizeof(pixel));


    /* try to open file for reading (r) in binary (b) mode */
    if ((inFile = fopen(fileName, "rb")) == NULL)  /* open failed */
    {
        puts("*** Can't open input file - please check file name typed!\n ");
        input = getchar();
        exit(1);   /* terminate execution */
    }

    /* reaching this line of code means file opened successfully,
    now read file contents into image array */
    for (int r = 0; r < width; r++) {
        for (int c = 0; c < height; c++) {
           
            for (size_t p = 0; p < 3; p++)
            {
                if ((input = fgetc(inFile)) == EOF)   /* read failed */
                {
                    printf("***file reading failed! at r: %d, c: %d \n", r, c);
                    input = getchar();
                    exit(1);    /* terminate execution */
                }
                image[r][c][p] = input;
            }
            
        }
    }

    /* reaching this line of code means all of file read successfully */
    printf("\nImage input completed!\n");
    fclose(inFile);    /* close input file  */
    return image;
}

void displayImage(pixel** imageData, int w,int h,int x, int y) {
    int	offset;
    unsigned char* imageBuffer = (pixel*)malloc(sizeof(pixel) * w * h);

    /* flip image - 1st row becomes last - before calling glDrawPixels
    to display original image*/
    //offset = 0;
    //int r = h - 1; r >= 0; r--

    /* loading image buffer before displaying it*/
    for (int r = 0; r < w;r++) {
        for (int c = 0; c < h; c++) {
           for (int p = 0; p < 3; p++)
            {
                imageBuffer[h * r * 3 + c * 3 + p] = imageData[r][c][p];
            }
        }
        //offset++;
    }

    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, windowWidth, windowHeight, 0.0, -1.0, 10);

    //back to model view
    glMatrixMode(GL_MODELVIEW);
    //save state
    glPushMatrix();
    glLoadIdentity();

    //has issues when not in smooth shading
    unsigned int shadeMode;
    glGetIntegerv(GL_SHADE_MODEL, &shadeMode);
    glShadeModel(GL_SMOOTH);

    //glDisable(GL_CULL_FACE);//not sure...
    glClear(GL_DEPTH_BUFFER_BIT);




    /* set raster position for displaying image in graphics image buffer*/
    glRasterPos2i(x, y);
    glDrawPixels(w, h, GL_RGB, GL_UNSIGNED_BYTE, imageBuffer); //image_buf


    free(imageBuffer);

    glShadeModel(shadeMode);//switch back to old shade mode
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glEnable(GL_LIGHTING);

}

void reshapeTexture(int w, int h) {
    windowWidth = w;
    windowHeight = h;
}