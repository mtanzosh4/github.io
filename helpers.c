#include "helpers.h"
#include <math.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gray = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
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

       typedef struct
    {
        int  row;
        int  column;
    }
    CHOICES;

    RGBTRIPLE imageCopy[height][width];
    CHOICES choices[9];
    CHOICES tmp;
    RGBTRIPLE list[9];
    int count = 0;
    float totalred = 0;
    float totalgreen = 0;
    float totalblue = 0;
    int n = 0;


    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            // build RGBstructure list based on the pixels you want to average- array of pairs
            // find the nine pixels
            tmp.row = row - 1;
            tmp.column = column - 1;
            if (tmp.row >= 0 && tmp.row <= height && tmp.column >= 0 && tmp.column <= width)
                {
                choices[n + 1] = tmp;
                }

            tmp.row = row - 1;
            tmp.column = column;
            if (tmp.row >= 0 && tmp.row <= height && tmp.column >= 0 && tmp.column <= width)
                {
                choices[n+1] = tmp;
                n++;
                }

            tmp.row = row - 1;
            tmp.column = column + 1;
            if (tmp.row >= 0 && tmp.row <= height && tmp.column >= 0 && tmp.column <= width)
                {
                choices[n+1] = tmp;
                n++;
                }

            tmp.row = row;
            tmp.column = column - 1;
            if (tmp.row >= 0 && tmp.row <= height && tmp.column >= 0 && tmp.column <= width)
                {
                choices[n+1] = tmp;
                n++;
                }

            tmp.row = row;
            tmp.column = column;
            if (tmp.row >= 0 && tmp.row <= height && tmp.column >= 0 && tmp.column <= width)
                {
                choices[n+1] = tmp;
                n++;
                }

            tmp.row = row;
            tmp.column = column + 1;
            if (tmp.row >= 0 && tmp.row <= height && tmp.column >= 0 && tmp.column <= width)
                {
                choices[n+1] = tmp;
                n++;
                }

            tmp.row = row + 1;
            tmp.column = column - 1;
            if (tmp.row >= 0 && tmp.row <= height && tmp.column >= 0 && tmp.column <= width)
                {
                choices[n+1] = tmp;
                n++;
                }

            tmp.row = row + 1;
            tmp.column = column;
            if (tmp.row >= 0 && tmp.row <= height && tmp.column >= 0 && tmp.column <= width)
                {
                choices[n+1] = tmp;
                n++;
                }

            tmp.row = row + 1;
            tmp.column = column + 1;
            if (tmp.row >= 0 && tmp.row <= height && tmp.column >= 0 && tmp.column <= width)
                {
                choices[n+1] = tmp;
                n++;
                }


            for (int index = 0; index <= 9; index++)
            {
                totalred += image[choices[index].row] [choices[index].column].rgbtRed;
                totalgreen += image[choices[index].row] [choices[index].column].rgbtGreen;
                totalblue += image[choices[index].row] [choices[index].column].rgbtBlue;
            }


            imageCopy[height][width].rgbtRed = round(totalred/count);
            imageCopy[height][width].rgbtGreen = round(totalgreen/count);
            imageCopy[height][width].rgbtBlue = round(totalblue/count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
        image [i][j].rgbtRed = imageCopy [i][j].rgbtRed;
        image [i][j].rgbtGreen  = imageCopy [i][j].rgbtGreen;
        image [i][j].rgbtBlue  = imageCopy [i][j].rgbtBlue;
        }
    }

    return;
}