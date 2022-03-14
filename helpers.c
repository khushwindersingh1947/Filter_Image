#include "helpers.h"
#include <math.h>
#include <cs50.h>
    // Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // values for colors
    float r = 0;
    float g = 0;
    float b = 0;
    //loop for formula
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            r = image[i][j].rgbtRed;
            b = image[i][j].rgbtBlue;
            g = image[i][j].rgbtGreen;

            float average = (r + b + g) / 3;
            int ave = round(average);

            image[i][j].rgbtRed = ave;
            image[i][j].rgbtBlue = ave;
            image[i][j].rgbtGreen = ave;
        }
    }
    return;
}

