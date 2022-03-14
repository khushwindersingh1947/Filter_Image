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

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // temp variable for storage
    RGBTRIPLE temp;
    //loop for changing pixals
    for (int i = 0; i < height; i++)
    {
        int k = width - 1;

        if (width % 2 == 0)
        {
            for (int j = 0; j < width / 2; j++)
            {
                temp = image[i][j];
                image[i][j] = image[i][k];
                image[i][k] = temp;
                k--;
            }
        }
        else
        {
            for (int j = 0; j < (width - 1) / 2; j++)
            {
                temp = image[i][j];
                image[i][j] = image[i][k];
                image[i][k] = temp;
                k--;
            }

        }
    }
    return;
}
