// Implementation of the 4 filters 

#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0, n = height; i < n; i++)
    {
        for (int j = 0, m = width; j < m; j++)
        {
            // Find the average value of Red, Green and Blue
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/ 3.00);

            // Set the new values
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Set limit to RGB 255
int limit(int RGB)
{
    if (RGB > 255)
    {
        RGB = 255;
    }
    return RGB;
}

// Convert image to sepia (works with "limit" function from above)
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // For every row
    for (int i = 0, n = height; i < n; i++)
    {
        // For every RGBTRIPLE (a pixel)
        for (int j = 0, m = width; j < m; j++)
        {
            // Use the Sepia Red Formula
            int sepiaRed = limit(round(0.393 * image[i][j].rgbtRed
            + 0.769 * image[i][j].rgbtGreen
            + 0.189 * image[i][j].rgbtBlue));

            //Use the Sepia Green Formula
            int sepiaGreen = limit(round(0.349 * image[i][j].rgbtRed
            + 0.686 * image[i][j].rgbtGreen
            + 0.168 * image[i][j].rgbtBlue));

            // Use the Sepia Blue Formula
            int sepiaBlue = limit(round(0.272 * image[i][j].rgbtRed
            + 0.534 * image[i][j].rgbtGreen
            + 0.131 * image[i][j].rgbtBlue));

            // Apply new shades
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}
