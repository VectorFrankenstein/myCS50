#include "math.h"
#include "helpers.h"
#include "stdio.h"

// for calloc
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){

            int avg = (image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3;

            image[i][j].rgbtBlue = avg;

            image[i][j].rgbtRed = avg;

            image[i][j].rgbtGreen = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int mid_point = ceil(width / 2); // This is index of image around which we mill pivot the image.

    for(int i = 0; i < height; i++){
        for(int j = 0; j < mid_point ; j++){

            int comp = width - j;

            RGBTRIPLE temp = image[i][j];

            image[i][j] = image[i][comp];

            image[i][comp] = temp;

            printf("J is %d, width -j is %d, and comp is %d\n",j,width - j ,comp+j);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*placeholder)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (placeholder == NULL)
    {
        printf("Not enough memory to store image.\n");
    }

    for(int i = 0; i < height;i++){
        for(int j = 0; j < width;j++){

            int tally = 0;

            // Now we need to find the range of pixels to average.
            int height_low = i - 1; // one around the pixel

            if(height_low <= 0 ){
                height_low = i; // if the height_low goes below the valid point reset it to i
            }

            int height_high = i + 1;

            if(height_high >= height){
                height_high = i; // making sure you do not go out of bounds
            }

            int width_left = j - 1;

            if(width_left <= 0 ){
                width_left = j; // making sure you do not go out of bounds
            }

            int width_right = j + 1;

            if(width_right >= width){
                width_right = j;
            }

            RGBTRIPLE temp;

            int totalRed = 0;

            int totalBlue = 0;

            int totalGreen = 0;

            for(int vertical_index = height_low; vertical_index <= height_high; vertical_index++){
                for(int horizontal_index = width_left; horizontal_index <= width_right;horizontal_index++){

                    totalRed += image[vertical_index][horizontal_index].rgbtRed;

                    totalBlue += image[vertical_index][horizontal_index].rgbtBlue;

                    totalGreen += image[vertical_index][horizontal_index].rgbtGreen;

                    tally++;
                }
            }

            placeholder[i][j].rgbtRed = totalRed / tally;

            placeholder[i][j].rgbtGreen = totalGreen / tally;

            placeholder[i][j].rgbtBlue = totalBlue / tally;


        }
    }

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            image[i][j] = placeholder[i][j];
        }
    }

    free(placeholder);

    return;
}

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Sobel operator kernels
    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };
    RGBTRIPLE(*placeholder)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (placeholder == NULL)
    {
        printf("Not enough memory to store image.\n");
        return;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int xtotalRed = 0, xtotalGreen = 0, xtotalBlue = 0;

            int ytotalRed = 0, ytotalGreen = 0, ytotalBlue = 0;

            // Now we need to find the range of pixels to average.
            int height_low = (i - 1 < 0) ? i : i - 1;
            int height_high = (i + 1 >= height) ? i : i + 1;
            int width_left = (j - 1 < 0) ? j : j - 1;
            int width_right = (j + 1 >= width) ? j : j + 1;

            for (int vertical_index = height_low, gv = 0; vertical_index <= height_high && gv < 3; vertical_index++, gv++)
            {
                for (int horizontal_index = width_left, gh = 0; horizontal_index <= width_right && gh < 3; horizontal_index++, gh++)
                {
                    xtotalRed += image[vertical_index][horizontal_index].rgbtRed * Gx[gv][gh];
                    xtotalGreen += image[vertical_index][horizontal_index].rgbtGreen * Gx[gv][gh];
                    xtotalBlue += image[vertical_index][horizontal_index].rgbtBlue * Gx[gv][gh];

                    ytotalRed += image[vertical_index][horizontal_index].rgbtRed * Gy[gv][gh];
                    ytotalGreen += image[vertical_index][horizontal_index].rgbtGreen * Gy[gv][gh];
                    ytotalBlue += image[vertical_index][horizontal_index].rgbtBlue * Gy[gv][gh];
                }
            }

            double prefinalRed = sqrt(xtotalRed * xtotalRed + ytotalRed * ytotalRed);
            double prefinalBlue = sqrt(xtotalBlue * xtotalBlue + ytotalBlue * ytotalBlue);
            double prefinalGreen = sqrt(xtotalGreen * xtotalGreen + ytotalGreen * ytotalGreen);

            int finalRed = (prefinalRed < 255) ? prefinalRed : 255;
            int finalBlue = (prefinalBlue < 255) ? prefinalRed : 255;
            int finalGreen = (prefinalGreen < 255) ? prefinalGreen : 255;

            placeholder[i][j].rgbtRed = finalRed;
            placeholder[i][j].rgbtGreen = finalGreen;
            placeholder[i][j].rgbtBlue = finalBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = placeholder[i][j];
        }
    }

    free(placeholder);
    return;
}

