/*
    A library that is used to draw Grayscale and RGB colored Images.
    imagemagick is required to display the images, if you do not have it
    install it on Linux with "sudo apt install imagemagick".

    Author: Umar Alkafaween
    https://github.com/umar221b
*/

#include <stdio.h>
#include <stdlib.h>

int validateGrayscaleImage(int rows, int columns, int array[rows][columns]) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (array[i][j] < 0 || array[i][j] > 255)
                return 1;
        }
    }
    return 0;
}

int writeGrayscaleImageToTempFile(int rows, int columns, int array[rows][columns]) {
    FILE* tempFile = tmpfile();
    tempFile = fopen("image.pgm", "w");
    if (tempFile == NULL) {
        return 1;
    }
    fprintf(tempFile, "P2");
    fprintf(tempFile, "%d %d\n", columns, rows);
    fprintf(tempFile, "255\n");
    for (int i = 0; i < rows; ++i) {            
        for (int j = 0; j < columns; ++j) {
            if (j != 0)
                fprintf(tempFile, " ");
            fprintf(tempFile, "%d", array[i][j]);
            if (j < columns - 1)
                fprintf(tempFile, " ");
        }
        fprintf(tempFile, "\n");
    }
    fclose(tempFile);
    return 0;
}

void drawGrayscaleImage(int rows, int columns, int array[rows][columns]) {
    if (system("which display > /dev/null 2>&1")) {
        puts("Please install imagemagick then try again.\nTo install imagemagick, run the command \"sudo apt install imagemagick\".\n");
    }
    else {
        int status = validateGrayscaleImage(rows, columns, array);
        if (status != 0) {
            if (status == 1) {
                puts("Something is wrong with the values in your image. Make sure they are all between 0 and 255.");
            }
            return;
        }
        status = writeGrayscaleImageToTempFile(rows, columns, array);
        if (status != 0) {
            if (status == 1) {
                puts("There was an issue creating your image.");
            }
            return;
        }
        // all good
        system("display image.pgm");
    }
}

int validateRGBImage(int rows, int columns, int array[rows][columns][3]) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            for (int k = 0; k < 3; ++k) {
                if (array[i][j][k] < 0 || array[i][j][k] > 255)
                    return 1;
            }
        }
    }
    return 0;
}

int writeRGBImageToTempFile(int rows, int columns, int array[rows][columns][3]) {
    FILE* tempFile = tmpfile();
    tempFile = fopen("image.ppm", "w");
    if (tempFile == NULL) {
        return 1;
    }
    fprintf(tempFile, "P3");
    fprintf(tempFile, "%d %d\n", columns, rows);
    fprintf(tempFile, "255\n");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            fprintf(tempFile, "%d %d %d\n", array[i][j][0], array[i][j][1], array[i][j][2]);
        }
        printf("\n");
    }
    fclose(tempFile);
    return 0;
}

void drawRGBImage(int rows, int columns, int array[rows][columns][3]) {
    if (system("which display > /dev/null 2>&1")) {
        puts("Please install imagemagick then try again.\nTo install imagemagick, run the command \"sudo apt install imagemagick\".\n");
    }
    else {
        int status = validateRGBImage(rows, columns, array);
        if (status != 0) {
            if (status == 1) {
                puts("Something is wrong with the values in your image. Make sure they are all between 0 and 255.");
            }
            return;
        }
        status = writeRGBImageToTempFile(rows, columns, array);
        if (status != 0) {
            if (status == 1) {
                puts("There was an issue creating your image.");
            }
            return;
        }
        // all good
        system("display image.ppm");
    }
}
