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
