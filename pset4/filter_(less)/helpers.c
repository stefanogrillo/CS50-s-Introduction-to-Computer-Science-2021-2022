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
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.00);

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

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0, n = height; i < n; i++)
    {
        for (int j = 0, m = width / 2; j < m; j++)
        {
            // Create a temporary value to save RGB values on the Left
            RGBTRIPLE temp = image[i][j];

            // Copy and paste Right-to-Left
            image[i][j] = image[i][width - j - 1];

            // Copy and paste Left-to-Right
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create an operative copy to read from
    RGBTRIPLE copy[height][width];
    for (int i = 0, n = height; i < n; i++)
    {
        for (int j = 0, m = width; j < m; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Read from copy[i][j] and write to image[i][j]
    for (int i = 0, n = height; i < n; i++)
    {
        for (int j = 0, m = width; j < m; j++)
        {
            // Initialize counters (needed to make the averages)
            float sumRed = 0, sumGreen = 0, sumBlue = 0;
            int counter = 0;
            
            // To Blur the image, we must average the RGB values of local pixels; we do so considering a square around the pixel[i][j]
            // Loop for the surrounding pixels (the square around the pixel[i][j]: i && i +/- 1; j && j +/- 1)
            for (int k = (i - 1); k < (i + 2); k++)
            {
                for (int l = (j - 1); l < (j + 2); l++)
                {
                    // If pixel is out of the column
                    if (k < 0 || k >= height)
                    {
                        continue;
                    }

                    // If pixel is out of the row
                    if (l < 0 || l >= width)
                    {
                        continue;
                    }

                    // Otherwise
                    sumRed += copy[k][l].rgbtRed;
                    sumGreen += copy[k][l].rgbtGreen;
                    sumBlue += copy[k][l].rgbtBlue;
                    counter++;
                }
            }
            // Calculate the average value per color, then blur
            image[i][j].rgbtRed = round(sumRed / counter);
            image[i][j].rgbtGreen = round(sumGreen / counter);
            image[i][j].rgbtBlue = round(sumBlue / counter);
        }
    }
    return;
}
