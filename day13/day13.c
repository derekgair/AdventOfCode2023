#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include "../aoc.h"

int findReflect(char *array, int dimx, int dimy, int maxx, int maxy)
{
    int result = 0;
    int x;
    for (int x = 0; x < maxx - 1; ++x)
    {
        int reflects = 1;
        // check that each col reflects...
        for (int x1 = 0; x - x1 >= 0 && x + x1 + 1 < maxx && reflects; ++x1)
        {
            for (int y = 0; y < maxy && reflects; ++y)
            {
                if (*(array + y * dimx + x - x1) != *(array + y * dimx + x + x1 + 1))
                {
                    reflects = 0;
                }
            }
            printf("Comparing col %d with %d = %d\n", x - x1, x + x1 + 1, reflects);
        }
        if (reflects)
        {
            result += (x + 1);
            break;
        }
    }
    for (int y = 0; y < maxy - 1; ++y)
    {
        int reflects = 1;
        // check that each col reflects...
        for (int y1 = 0; y - y1 >= 0 && y + y1 + 1 < maxy && reflects; ++y1)
        {
            for (int x = 0; x < maxx && reflects; ++x)
            {
                if (*(array + (y - y1) * dimx + x) != *(array + (y + y1 + 1) * dimx + x))
                {
                    reflects = 0;
                }
            }
            printf("Comparing row %d with %d = %d\n", y - y1, y + y1 + 1, reflects);
        }
        if (reflects)
        {
            result += (y + 1) * 100;
            break;
        }
    }

    return result;
}
int main()
{

    int STRLEN = 1024;
    int DIM = 100;
    // remember to add a couple of new lines at the end of the file.  I was too lazy to fix this.
    FILE *file = fopen("data.txt", "r");
    char line[STRLEN];
    int result = 0;

    char array[DIM][DIM];

    int maxx = 0, maxy = 0;
    while (fgets(line, sizeof(line), file))
    {
        if (strlen(line) < 2)
        {
            print(array, maxx, maxy, DIM);
            int x = findReflect(array, DIM, DIM, maxx, maxy);
            printf("%d\n", x);
            result += x;
            maxy = 0;
            maxx = 0;
        }
        else
        {

            for (maxx = 0; maxx < strlen(line) - 1; ++maxx)
            {
                array[maxy][maxx] = line[maxx];
            }
            maxy++;
        }
    }
    printf("Result:%d\n", result);
}