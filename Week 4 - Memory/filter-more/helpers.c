#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    double average = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0;
            average = round (average);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
       }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE buffer;
    for (int i = 0; i < height; i++)
    {
        if ( width % 2 == 0)
        {
            for (int j = 0; j < width/2; j++)
            {
                buffer = image [i][j];
                image [i][j] = image [i][width-(j + 1)];
                image [i][width - (j + 1)] = buffer;
            }
        }
        else
        {
            for (int j = 0; j < (width-1)/2; j++)
            {
                buffer = image [i][j];
                image [i][j] = image [i][width-( j + 1)];
                image [i][width - (j + 1)] = buffer;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float average [3] = {0,0,0};
    RGBTRIPLE buffer[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average [0] = 0;
            average [1] = 0;
            average [2] = 0;
            int count = 0;
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                average [0] = average [0] + image [i-1][j-1].rgbtRed;
                average [1] = average [1] + image [i-1][j-1].rgbtBlue;
                average [2] = average [2] + image [i-1][j-1].rgbtGreen;
                count++;
            }
            if (i - 1 >= 0)
            {
                average [0] = average [0] + image [i-1][j].rgbtRed;
                average [1] = average [1] + image [i-1][j].rgbtBlue;
                average [2] = average [2] + image [i-1][j].rgbtGreen;
                count++;
            }
            if(i - 1 >= 0 && j + 1 <= width-1)
            {
                average [0] = average [0] + image [i-1][j+1].rgbtRed;
                average [1] = average [1] + image [i-1][j+1].rgbtBlue;
                average [2] = average [2] + image [i-1][j+1].rgbtGreen;
                count++;
            }
            if(j - 1 >= 0)
            {
                average [0] = average [0] + image [i][j-1].rgbtRed;
                average [1] = average [1] + image [i][j-1].rgbtBlue;
                average [2] = average [2] + image [i][j-1].rgbtGreen;
                count++;
            }
            average [0] = average [0] + image [i][j].rgbtRed;
            average [1] = average [1] + image [i][j].rgbtBlue;
            average [2] = average [2] + image [i][j].rgbtGreen;
            count++;
            if(j + 1 <= width-1)
            {
                average [0] = average [0] + image [i][j+1].rgbtRed;
                average [1] = average [1] + image [i][j+1].rgbtBlue;
                average [2] = average [2] + image [i][j+1].rgbtGreen;
                count++;
            }
            if(i + 1 <= height-1 && j - 1 >= 0)
            {
                average [0] = average [0] + image [i+1][j-1].rgbtRed;
                average [1] = average [1] + image [i+1][j-1].rgbtBlue;
                average [2] = average [2] + image [i+1][j-1].rgbtGreen;
                count++;
            }
            if(i + 1 <= height-1)
            {
                average [0] = average [0] + image [i+1][j].rgbtRed;
                average [1] = average [1] + image [i+1][j].rgbtBlue;
                average [2] = average [2] + image [i+1][j].rgbtGreen;
                count++;
            }
            if(i + 1 <= height-1 && j + 1 <= width-1)
            {
                average [0] = average [0] + image [i+1][j+1].rgbtRed;
                average [1] = average [1] + image [i+1][j+1].rgbtBlue;
                average [2] = average [2] + image [i+1][j+1].rgbtGreen;
                count++;
            }

            average [0] = round( average [0] / count);
            average [1] = round( average [1] / count);
            average [2] = round( average [2] / count);
            buffer [i][j].rgbtRed = average [0];
            buffer [i][j].rgbtBlue = average [1];
            buffer [i][j].rgbtGreen = average [2];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = buffer[i][j].rgbtBlue;
            image[i][j].rgbtGreen = buffer[i][j].rgbtGreen;
            image[i][j].rgbtRed = buffer[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer[height][width];
    int GX [3][3] = {{-1, 0, 1} , {-2, 0, 2} , {-1, 0, 1}};
    int GY [3][3] = {{-1, -2, -1} , {0, 0, 0} , {1, 2, 1}};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int GXRed = 0;
            int GYRed = 0;
            int GXBlue = 0;
            int GYBlue = 0;
            int GXGreen = 0;
            int GYGreen = 0;
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                GXRed = GXRed + image [i - 1][j - 1].rgbtRed * GX [0][0];
                GXBlue = GXBlue + image [i - 1][j - 1].rgbtBlue * GX[0][0];
                GXGreen = GXGreen + image [i - 1][j - 1].rgbtGreen * GX[0][0];
                GYRed = GYRed + image [i - 1][j - 1].rgbtRed * GY[0][0];
                GYBlue = GYBlue + image [i - 1][j - 1].rgbtBlue * GY[0][0];
                GYGreen = GYGreen + image [i - 1][j - 1].rgbtGreen * GY[0][0];
            }
            if (i - 1 >= 0)
            {
                GXRed = GXRed + image [i-1][j].rgbtRed * GX [0][1];
                GXBlue = GXBlue + image [i-1][j].rgbtBlue * GX[0][1];
                GXGreen = GXGreen + image [i-1][j].rgbtGreen * GX[0][1];
                GYRed = GYRed + image [i-1][j].rgbtRed * GY[0][1];
                GYBlue = GYBlue + image [i-1][j].rgbtBlue * GY[0][1];
                GYGreen = GYGreen + image [i-1][j].rgbtGreen * GY[0][1];
            }
            if(i - 1 >= 0 && j + 1 <= width-1)
            {
                GXRed = GXRed + image [i-1][j+1].rgbtRed * GX [0][2];
                GXBlue = GXBlue + image [i-1][j+1].rgbtBlue * GX[0][2];
                GXGreen = GXGreen + image [i-1][j+1].rgbtGreen * GX[0][2];
                GYRed = GYRed + image [i-1][j+1].rgbtRed * GY[0][2];
                GYBlue = GYBlue + image [i-1][j+1].rgbtBlue * GY[0][2];
                GYGreen = GYGreen + image [i-1][j+1].rgbtGreen * GY[0][2];
            }
            if(j - 1 >= 0)
            {
                GXRed = GXRed + image [i][j-1].rgbtRed * GX [1][0];
                GXBlue = GXBlue + image [i][j-1].rgbtBlue * GX[1][0];
                GXGreen = GXGreen + image [i][j-1].rgbtGreen * GX[1][0];
                GYRed = GYRed + image [i][j-1].rgbtRed * GY[1][0];
                GYBlue = GYBlue + image [i][j-1].rgbtBlue * GY[1][0];
                GYGreen = GYGreen + image [i][j-1].rgbtGreen * GY[1][0];
            }
            GXRed = GXRed + image [i][j].rgbtRed * GX [1][1];
            GXBlue = GXBlue + image [i][j].rgbtBlue * GX[1][1];
            GXGreen = GXGreen + image [i][j].rgbtGreen * GX[1][1];
            GYRed = GYRed + image [i][j].rgbtRed * GY[1][1];
            GYBlue = GYBlue + image [i][j].rgbtBlue * GY[1][1];
            GYGreen = GYGreen + image [i][j].rgbtGreen * GY[1][1];
            if(j + 1 <= width-1)
            {
                GXRed = GXRed + image [i][j+1].rgbtRed * GX [1][2];
                GXBlue = GXBlue + image [i][j+1].rgbtBlue * GX[1][2];
                GXGreen = GXGreen + image [i][j+1].rgbtGreen * GX[1][2];
                GYRed = GYRed + image [i][j+1].rgbtRed * GY[1][2];
                GYBlue = GYBlue + image [i][j+1].rgbtBlue * GY[1][2];
                GYGreen = GYGreen + image [i][j+1].rgbtGreen * GY[1][2];
            }
            if(i + 1 <= height-1 && j - 1 >= 0)
            {
                GXRed = GXRed + image [i+1][j-1].rgbtRed * GX [2][0];
                GXBlue = GXBlue + image [i+1][j-1].rgbtBlue * GX[2][0];
                GXGreen = GXGreen + image [i+1][j-1].rgbtGreen * GX[2][0];
                GYRed = GYRed + image [i+1][j-1].rgbtRed * GY[2][0];
                GYBlue = GYBlue + image [i+1][j-1].rgbtBlue * GY[2][0];
                GYGreen = GYGreen + image [i+1][j-1].rgbtGreen * GY[2][0];
            }
            if(i + 1 <= height-1)
            {
                GXRed = GXRed + image [i+1][j].rgbtRed * GX [2][1];
                GXBlue = GXBlue + image [i+1][j].rgbtBlue * GX[2][1];
                GXGreen = GXGreen + image [i+1][j].rgbtGreen * GX[2][1];
                GYRed = GYRed + image [i+1][j].rgbtRed * GY[2][1];
                GYBlue = GYBlue + image [i+1][j].rgbtBlue * GY[2][1];
                GYGreen = GYGreen + image [i+1][j].rgbtGreen * GY[2][1];
            }
            if(i + 1 <= height-1 && j + 1 <= width-1)
            {
                GXRed = GXRed + image [i+1][j+1].rgbtRed * GX [2][2];
                GXBlue = GXBlue + image [i+1][j+1].rgbtBlue * GX[2][2];
                GXGreen = GXGreen + image [i+1][j+1].rgbtGreen * GX[2][2];
                GYRed = GYRed + image [i+1][j+1].rgbtRed * GY[2][2];
                GYBlue = GYBlue + image [i+1][j+1].rgbtBlue * GY[2][2];
                GYGreen = GYGreen + image [i+1][j+1].rgbtGreen * GY[2][2];
            }
            int blue = round(sqrt((GXBlue * GXBlue) + (GYBlue * GYBlue)));
            int green = round(sqrt((GXGreen * GXGreen) + (GYGreen * GYGreen)));
            int red = round(sqrt((GXRed * GXRed) + (GYRed * GYRed)));
            if (blue > 255)
            {
                blue = 255;
            }
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            buffer [i][j].rgbtRed = red;
            buffer [i][j].rgbtBlue = blue;
            buffer [i][j].rgbtGreen = green;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = buffer[i][j].rgbtBlue;
            image[i][j].rgbtGreen = buffer[i][j].rgbtGreen;
            image[i][j].rgbtRed = buffer[i][j].rgbtRed;
        }
    }
    return;
}
