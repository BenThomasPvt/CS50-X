#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            int red = image[i][j].rgbtRed, green = image[i][j].rgbtGreen,
                blue = image[i][j].rgbtBlue;
            float avg = (float) (red + green + blue) / 3;
            // float round(float avg);
            //  Update pixel values
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = (int) round(avg);
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
            // Compute sepia values
            float sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                             .189 * image[i][j].rgbtBlue;
            float sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                               .168 * image[i][j].rgbtBlue;
            float sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                              .131 * image[i][j].rgbtBlue;
            // Update pixel with sepia values
            image[i][j].rgbtRed = (int) round(fmin(sepiaRed, 255));
            image[i][j].rgbtGreen = (int) round(fmin(sepiaGreen, 255));
            image[i][j].rgbtBlue = (int) round(fmin(sepiaBlue, 255));
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels
            RGBTRIPLE t = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = t;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = 0, green = 0, blue = 0;
            int sum = 0;
            for (int ii = i - 1; ii < i + 2; ii++)
            {
                for (int jj = j - 1; jj < j + 2; jj++)
                {
                    if (ii >= 0 && jj >= 0 && ii < height && jj < width)
                    {
                        red = red + copy[ii][jj].rgbtRed;
                        green = green + copy[ii][jj].rgbtGreen;
                        blue = blue + copy[ii][jj].rgbtBlue;
                        sum++;
                    }
                }
            }
            image[i][j].rgbtRed = (int) round((float) red / sum);
            image[i][j].rgbtGreen = (int) round((float) green / sum);
            image[i][j].rgbtBlue = (int) round((float) blue / sum);
        }
    }
    return;
}
