/*
These extra lines are just for caution.
If you include this file from multiple files that are being compiled together,
these lines (and the #endif in the end) will make sure it gets included only once.
*/
#ifndef DRAW_LIB_FOC
#define DRAW_LIB_FOC

/*
Draws a grayscale image
A grayscale image is a 2D array, each element in the array describes the color of a pixel in the image.
The value of any element must be between 0 (black) and 255 (white).
*/
void drawGrayscaleImage(int rows, int columns, int array[rows][columns]);

/*
Draws a colored image
A colored image is a 3D array, each element in the array describes the intensity of one of the channels of the RGB system.
The value of any element must be between 0 (no intensity) and 255 (high intensity).
The first 2 dimensions of the 3D array specify the location of the pixel in the image, and
the last dimension (which is always 3) specifies the RGB channel that is being filled.
The first value array[i][j][0] is for the Red channel.
The second value array[i][j][1] is for the Green channel.
The third value array[i][j][2] is for the Blue channel.
*/
void drawRGBImage(int rows, int columns, int array[rows][columns][3]);


#endif