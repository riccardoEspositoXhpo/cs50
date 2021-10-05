#include "helpers.h"
#include <stdio.h>
#include <math.h>

int min(int x, int y);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    float average;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // compute the average color and set each color to the rounded average value
            average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = average;

        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    float sepiaRed;
    float sepiaGreen;
    float sepiaBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // run the algorithm to compute sepia and assign colors
            sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 *  image[i][j].rgbtBlue);
            sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 *  image[i][j].rgbtBlue);
            sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 *  image[i][j].rgbtBlue);

            image[i][j].rgbtRed = min(sepiaRed, 255);
            image[i][j].rgbtGreen = min(sepiaGreen, 255);
            image[i][j].rgbtBlue = min(sepiaBlue, 255);

        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    // dummy variable used for swap
    RGBTRIPLE swap[0];

    for (int i = 0; i < height; i++)
    {
        // loop until the middle of the picture
        for (int j = 0; j < (width / 2); j++)
        {
            // swap each pixel with the counterpart that is at the same distance from the center
            swap[0] = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = swap[0];
        }

    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    float sumRed;
    float sumBlue;
    float sumGreen;
    int counter;

    // dummy RGBTRIPLE to store image clone
    RGBTRIPLE temp[height][width];

    /*  clone the image - necessary if we want to recursively update the
        pixels of the image without affecting the average calculation
    */
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // reset variables
            counter = 0;
            sumRed = sumBlue = sumGreen = 0;


            // initiate 3x3 box construction from [i][j], we move one box earlier and one box later
            for (int k = i - 1; k < i + 2; k++)
            {
                for (int l = j - 1; l < j + 2; l++)
                {

                    // we only consider the box if it is withing height limits and width limits
                    if (k >= 0 && k < height && l >= 0 && l < width)
                    {

                        // use the unaltered values from temp to compute average
                        sumRed += temp[k][l].rgbtRed;
                        sumBlue += temp[k][l].rgbtBlue;
                        sumGreen += temp[k][l].rgbtGreen;
                        counter++;
                    }

                }
            }

            // compute average and assign each pixel with new rounded value
            image[i][j].rgbtRed = round(sumRed / counter);
            image[i][j].rgbtBlue = round(sumBlue / counter);
            image[i][j].rgbtGreen = round(sumGreen / counter);

        }
    }
    return;

}


// helper function to compute the min between two numbers
int min(int x, int y)
{

    // function does not do error checking but for the purposes of the exercise I assume the numbers are valid
    if (x < y)
    {
        return x;
    }
    else if (x > y)
    {
        return y;
    }
    else
    {
        return x;
    }

}