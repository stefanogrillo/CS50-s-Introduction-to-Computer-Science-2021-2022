// Write some filters for images: Grayscale, Reflect, Blur and Edges 

#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // For each column
    for (int i = 0, n = height; i < n; i++)
    {
        // For each row (i.e. with the above code: for each pixel)
        for (int j = 0, m = width; j < m; j++)
        {
            // Find the average value
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.00);

            // Set RGB values to avg (makes the shade of b/w)
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0, n = height; i < n; i++)
    {
        for (int j = 0, m = (width / 2); j < m; j++)
        {
            // Create a temporary value for Left pixels
            RGBTRIPLE temp = image[i][j];

            // Move Right pixels to Left (till center)
            image[i][j] = image[i][width - j - 1];

            // Move temporary into Right pixels
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a picture's copy
    RGBTRIPLE copy[height][width];
    for (int i = 0, n = height; i < n; i++)
    {
        for (int j = 0, m = width; j < m; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Read from copy, make calculations, paste to image
    for (int i = 0, n = height; i < n; i++)
    {
        for (int j = 0, m = width; j < m; j++)
        {
            // Create counters
            float sumRed = 0, sumGreen = 0, sumBlue = 0;
            int counter = 0;

            // Nest another loop to average out the values in the surrouding pixels
            for (int k = (i - 1); k < (i + 2); k++)
            {
                for (int l = (j - 1); l < (j + 2); l++)
                {
                    // When surrounding pixels are outside the image
                    if (k < 0 || k >= height)
                    {
                        continue;
                    }
                    if (l < 0 || l >= width)
                    {
                        continue;
                    }

                    // Keep track
                    sumRed += copy[k][l].rgbtRed;
                    sumGreen += copy[k][l].rgbtGreen;
                    sumBlue += copy[k][l].rgbtBlue;
                    counter++;
                }
            }
            // Calculate
            image[i][j].rgbtRed = round(sumRed / counter);
            image[i][j].rgbtGreen = round(sumGreen / counter);
            image[i][j].rgbtBlue = round(sumBlue / counter);
        }
    }
    return;
}

// Set upper limit to RGB 255 (the maximum RGB value possible)
int limit(int RGB)
{
    if (RGB > 255)
    {
        RGB = 255;
    }
    return RGB;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary copy
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Create Sobel 2D arrays [n][m] where n is row, m is column
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Loop through rows
    for (int i = 0; i < height; i++)
    {
        // Loop through columns
        for (int j = 0; j < width; j++)
        {
            // Create counters to be reset after having considered the single pixel
            float GxRed = 0;
            float GxGreen = 0;
            float GxBlue = 0;
            float GyRed = 0;
            float GyGreen = 0;
            float GyBlue = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Check if pixel is outside rows
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    // Check if pixel is outside columns
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }

                    // Otherwise add to sums
                    // Meant to calculate how much the colors R, G, B change in horizontal && vertical
                    GxRed += copy[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                    GxGreen += copy[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                    GxBlue += copy[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];
                    GyRed += copy[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                    GyGreen += copy[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                    GyBlue += copy[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
                }
            }
            // Update the image with the calculated values
            image[i][j].rgbtRed = limit(round(sqrt(pow(GxRed, 2) + pow(GyRed, 2))));
            image[i][j].rgbtGreen = limit(round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2))));
            image[i][j].rgbtBlue = limit(round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2))));
        }
    }
}
