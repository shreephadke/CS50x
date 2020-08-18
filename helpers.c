#include "helpers.h"
#include <math.h>
#include <stdio.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;
            float average = (float)((r + g + b)/3.0);
            int avg = round(average);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int tempR = 0, tempG = 0, tempB = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            tempR = image[i][j].rgbtRed;
            tempG = image[i][j].rgbtGreen;
            tempB = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width-1-j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width-1-j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width-1-j].rgbtBlue;

            image[i][width-1-j].rgbtRed = tempR;
            image[i][width-1-j].rgbtGreen = tempG;
            image[i][width-1-j].rgbtBlue = tempB;

        }
    }

    return;
}

/*
            if (i == 0 && j == 0)
            {
                int r1 = image[i][j].rgbtRed;
                int r2 = image[i + 1][j].rgbtRed;
                int r3 = image[i + 1][j + 1].rgbtRed;
                int r4 = image[i][j + 1].rgbtRed;

                int g1 = image[i][j].rgbtGreen;
                int g2 = image[i + 1][j].rgbtGreen;
                int g3 = image[i + 1][j + 1].rgbtGreen;
                int g4 = image[i][j + 1].rgbtGreen;

                int b1 = image[i][j].rgbtBlue;
                int b2 = image[i + 1][j].rgbtBlue;
                int b3 = image[i + 1][j + 1].rgbtBlue;
                int b4 = image[i][j + 1].rgbtBlue;

                float averageR = (r1+r2+r3+r4)/4;
                float averageG = (g1+g2+g3+g4)/4;
                float averageB = (b1+b2+b3+b4)/4;

                image[i][j].rgbtRed = averageR

            }

*/


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    printf("%d\n", height);
    printf("%d\n", width);
    int red[height][width],green[height][width],blue[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red[i][j] = image[i][j].rgbtRed;
            blue[i][j] = image[i][j].rgbtBlue;
            green[i][j] = image[i][j].rgbtGreen;

        }
    }

    int i = 0, j = 0, r = 0, c = 0;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            double sumR = 0, sumG = 0, sumB = 0;
            int counter = 0;
            for (r = i - 1; r <= i + 1; r++)
            {
                for (c = j - 1; c <= j + 1; c++)
                {
                    if (r >= 0 && c >= 0 && r < height && c < width)
                    {
                        //printf ("%d\n", image[r][c].rgbtRed);
                        sumR += red[r][c];
                        sumG += green[r][c];
                        sumB += blue[r][c];
                        // if(i==2 && j==1) printf("%d %d %d %d %d\n",r,c,red[i][j],green[i][j],blue[i][j]);
                        counter++;
                        //printf("%d\n", counter);

                    }
                }
            }

            image[i][j].rgbtRed = round(sumR/counter);
            image[i][j].rgbtGreen = round(sumG/counter);
            image[i][j].rgbtBlue = round(sumB/counter);

            // if(i==2 && j==1) {
            //     printf("For pixel (%d,%d) sum and new value are %lf , %d\n",i,j,sumR,image[i][j].rgbtRed);
            //     printf("For pixel (%d,%d) sum and new value are %lf , %d\n",i,j,sumG,image[i][j].rgbtGreen);
            //     printf("For pixel (%d,%d) sum and new value are %lf , %d\n",i,j,sumB,image[i][j].rgbtBlue);
            //     printf("%d\n", counter);
            // }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx [3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy [3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE imagecpy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imagecpy[i][j].rgbtRed = image[i][j].rgbtRed;
            imagecpy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            imagecpy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            double sumRX = 0, sumGX = 0, sumBX = 0, sumRY = 0, sumGY = 0, sumBY = 0;
            //int counter = 0;

            for (int r = i - 1, countR = 0; r <= i + 1; r++)
            {
                for (int c = i - 1, countC = 0; c <= i + 1; c++)
                {

                    if (r >= 0 && r < height && c >= 0 && c < width)
                    {
                        sumRX += imagecpy[r][c].rgbtRed * gx[countR][countC];
                        sumGX += imagecpy[r][c].rgbtGreen * gx[countR][countC];
                        sumBX += imagecpy[r][c].rgbtBlue * gx[countR][countC];
                        sumRY += imagecpy[r][c].rgbtRed * gy[countR][countC];
                        sumGY += imagecpy[r][c].rgbtGreen * gy[countR][countC];
                        sumBY += imagecpy[r][c].rgbtBlue * gy[countR][countC];
                        //counter++;
                    }
                    countC++;
                }

                countR++;
            }
            double newRed = round(sqrt((sumRX*sumRX) + (sumRY*sumRY)));
            if (newRed > 255)
                newRed = 255;

            double newGreen = round(sqrt((sumGX*sumGX) + (sumGY*sumGY)));
            if (newGreen > 255)
                newGreen = 255;

            double newBlue = round(sqrt((sumBX*sumBX) + (sumBY*sumBY)));
            if (newBlue > 255)
                newBlue = 255;

            image[i][j].rgbtRed = newRed;
            image[i][j].rgbtGreen = newGreen;
            image[i][j].rgbtBlue = newBlue;

        }
    }

    return;
}
