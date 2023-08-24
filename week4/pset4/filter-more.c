#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            uint8_t rgbtGrey = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = rgbtGrey;
            image[i][j].rgbtGreen = rgbtGrey;
            image[i][j].rgbtBlue = rgbtGrey;
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
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    int dx[] = {0, 1, 1, 1, 0, -1, -1, -1, 0};
    int dy[] = {1, 1, 0, -1, -1, -1, 0, 1, 0};
    int n = sizeof(dx) / sizeof(int);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float cnt = 0;
            uint16_t red_sum = 0, green_sum = 0, blue_sum = 0;

            for (int k = 0; k < n; k++)
            {
                int new_x = i + dx[k], new_y = j + dy[k];
                if (new_x >= 0 && new_y >= 0 && new_x < height && new_y < width)
                {
                    red_sum += image[new_x][new_y].rgbtRed;
                    green_sum += image[new_x][new_y].rgbtGreen;
                    blue_sum += image[new_x][new_y].rgbtBlue;
                    cnt++;
                }
            }

            copy[i][j].rgbtRed = round(red_sum / cnt);
            copy[i][j].rgbtGreen = round(green_sum / cnt);
            copy[i][j].rgbtBlue = round(blue_sum / cnt);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    int dx[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
    int dy[] = {1, 1, 1, 0, 0, 0, -1, -1, -1};
    float gx[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    float gy[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    int n = sizeof(dx) / sizeof(int);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int x = 0, y = 1;
            float sobel_red[2] = {0};
            float sobel_green[2] = {0};
            float sobel_blue[2] = {0};

            for (int k = 0; k < n; k++)
            {
                int new_x = i + dx[k], new_y = j + dy[k];
                if (new_x >= 0 && new_y >= 0 && new_x < height && new_y < width)
                {
                    sobel_red[x] += image[new_x][new_y].rgbtRed * gx[k];
                    sobel_red[y] += image[new_x][new_y].rgbtRed * gy[k];
                    sobel_green[x] += image[new_x][new_y].rgbtGreen * gx[k];
                    sobel_green[y] += image[new_x][new_y].rgbtGreen * gy[k];
                    sobel_blue[x] += image[new_x][new_y].rgbtBlue * gx[k];
                    sobel_blue[y] += image[new_x][new_y].rgbtBlue * gy[k];
                }
            }

            uint16_t cur_red = round(sqrt(sobel_red[x] * sobel_red[x] + sobel_red[y] * sobel_red[y]));
            uint16_t cur_green = round(sqrt(sobel_green[x] * sobel_green[x] + sobel_green[y] * sobel_green[y]));
            uint16_t cur_blue = round(sqrt(sobel_blue[x] * sobel_blue[x] + sobel_blue[y] * sobel_blue[y]));

            copy[i][j].rgbtRed = cur_red > 255 ? 255 : cur_red;
            copy[i][j].rgbtGreen = cur_green > 255 ? 255 : cur_green;
            copy[i][j].rgbtBlue = cur_blue > 255 ? 255 : cur_blue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
    return;
}
