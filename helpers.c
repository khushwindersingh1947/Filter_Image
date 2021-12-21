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
bool valid_pixal(int k,int l,int height,int width)
{
    return k>=0 && k<height && l>=0 && l<width;

}

RGBTRIPLE get_blurred(int i,int j,int height, int width,RGBTRIPLE image[height][width])
{
    int count=0;
    int r,b,g; r=b=g=0;
    for(int k=i-1;k<=i+1;k++)
    {
        for(int l=j-1;l<=j+1;l++)
        {
            if(valid_pixal(k,l,height,width))
            {
                count++;
                r+=image[k][l].rgbtRed;
                b+=image[k][l].rgbtBlue;
                g+=image[k][l].rgbtGreen;
            }

        }
    }
    RGBTRIPLE pixal;
    pixal.rgbtRed=round( (float)r/count);
    pixal.rgbtBlue=round( ( float)b/count);
    pixal.rgbtGreen=round( (float)g/count);
    return pixal;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //copy variable for storing pixals
    RGBTRIPLE copy[height][width];
    // two loops for picking a pixal
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
          copy[i][j]=get_blurred(i,j,height,width,image);

        }

    }
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            image[i][j]=copy[i][j];
        }
    }

    return;
}

RGBTRIPLE get_edge(int i,int j,int height,int width,RGBTRIPLE image[height][width])
{
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int gxi[3]={0}; int gyi[3]={0};
    int m,n; m=n=0;
    for(int k=i-1;k<i+2;k++)
    {
        for(int l=j-1;l<j+2;l++)
        {
            if(valid_pixal(k,l,height,width))
            {
                gxi[0]+=gx[m][n]*image[k][l].rgbtRed;
                gyi[0]+=gy[m][n]*image[k][l].rgbtRed;

                gxi[1]+=gx[m][n]*image[k][l].rgbtBlue;
                gyi[1]+=gy[m][n]*image[k][l].rgbtBlue;

                gxi[2]+=gx[m][n]*image[k][l].rgbtGreen;
                gyi[2]+=gy[m][n]*image[k][l].rgbtGreen;
            }
            n++;
        }
        m++;
        n=0;
    }
    RGBTRIPLE pixal;
    pixal.rgbtRed=round(sqrt(gxi[0]*gxi[0]+gyi[0]*gyi[0])>255?255:sqrt(gxi[0]*gxi[0]+gyi[0]*gyi[0]));
    pixal.rgbtBlue=round(sqrt(gxi[1]*gxi[1]+gyi[1]*gyi[1])>255?255:sqrt(gxi[1]*gxi[1]+gyi[1]*gyi[1]));
    pixal.rgbtGreen=round(sqrt(gxi[2]*gxi[2]+gyi[2]*gyi[2])>255?255:sqrt(gxi[2]*gxi[2]+gyi[2]*gyi[2]));
    return pixal;

}



// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //matrix declarations


    RGBTRIPLE copy[height][width];
    //two loops for picking up pixal
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

        copy[i][j]=get_edge(i,j,height,width,image);

        }
    }

    // loop for putting values back to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }


    return;
}