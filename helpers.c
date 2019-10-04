#include "helpers.h"
#include <math.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gray = (image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3;
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtRed = gray;
            image[i][j].rgbtGreen = gray;

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE temp;
            temp.rgbtBlue = image[i][j].rgbtBlue;
            temp.rgbtRed = image[i][j].rgbtRed;
            temp.rgbtGreen = image[i][j].rgbtGreen;

            int red = round(.393 * temp.rgbtRed + .769 * temp.rgbtGreen + .189 * temp.rgbtBlue);
            int green = round(.349 * temp.rgbtRed + .686 * temp.rgbtGreen + .168 * temp.rgbtBlue);
            int blue = round(.272 * temp.rgbtRed + .534 * temp.rgbtGreen + .131 * temp.rgbtBlue);

            image[i][j].rgbtRed  = (red <= 255) ? red : 255;
            image[i][j].rgbtGreen = (green <= 255) ? green : 255;
            image[i][j].rgbtBlue = (blue <= 255) ? blue : 155;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][width - j - 1].rgbtBlue = image[i][j].rgbtBlue ;
            temp[i][width - j - 1].rgbtRed = image[i][j].rgbtRed;
            temp[i][width - j - 1].rgbtGreen = image[i][j].rgbtGreen;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurred[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue = 0;
            int red = 0;
            int green = 0;
            int n = 0;

            // average grid of pixels
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (i + k >= 0 && i + k < height && j + l >= 0 && j + l < width)
                    {
                        blue += image[i + k][j + l].rgbtBlue;
                        red += image[i + k][j + l].rgbtRed;
                        green += image[i + k][j + l].rgbtGreen;
                        n++;
                    }
                }

            }
            if (n)
            {
                blurred[i][j].rgbtBlue = round((float)blue / n);
                blurred[i][j].rgbtRed = round((float)red / n);
                blurred[i][j].rgbtGreen = round((float)green / n);
            }

        }
    }

    // copy blurred to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = blurred[i][j].rgbtBlue;
            image[i][j].rgbtRed = blurred[i][j].rgbtRed;
            image[i][j].rgbtGreen = blurred[i][j].rgbtGreen;
        }
    }
    return;
}

// void average(int i , int j, RGBTRIPLE image[height][width])
// {
//     int average = 0;
//     int n = 0;
//     // average grid of pixels
//     for (int k = 0; k < 9; k++)
//     {
//         if (i - 1 - k >= 0  && i + 1 + k <= height && j - 1 - k  >= 0 && j + 1 + k  <= width)
//         {
//             average += image[i][j];
//             n++;
//         }
//     }

//     image[i][j] = round(average / n);

// }