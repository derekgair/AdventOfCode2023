#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include "../aoc.h"

int findReflect(char *array, int dimx, int dimy, int maxx, int maxy, int oldr)
{
    int result = 0;
    int x;
    for (int x = 0; x < maxx - 1; ++x)
    {
        // skip previous result.
        if (oldr != -1 && oldr % 100 == x + 1)
            continue;

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
        }
        if (reflects)
        {
            result += (x + 1);
            break;
        }
    }

    for (int y = 0; y < maxy - 1; ++y)
    {
        if (oldr != -1 && oldr / 100 == y + 1)
            continue;

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
    FILE *file = fopen("data.txt", "r");
    char line[STRLEN];
    int result = 0;

    char array[DIM][DIM];
    char copy[DIM][DIM];

    int maxx = 0, maxy = 0;
    while (fgets(line, sizeof(line), file))
    {
        if (strlen(line) < 2)
        {
            printf("----------------------------------------------------------\n");
            print(array, maxx, maxy, DIM);
            printf("\n");
            // We are just brute forcing it... switch an element of the array and try...
            int r = 0;
            int oldr = findReflect(array, DIM, DIM, maxx, maxy, -1);
            memcpy(copy, array, DIM * DIM);
            for (int x = 0; x < maxx && !r; ++x)
            {
                for (int y = 0; y < maxy && !r; ++y)
                {
                    if (copy[y][x] == '.')
                        copy[y][x] = '#';
                    else
                        copy[y][x] = '.';

                    int newr = findReflect(copy, DIM, DIM, maxx, maxy, oldr);

                    if (newr != 0 && oldr != newr)
                    {
                        r = newr;
                        // we mark the change in the grid before displaying it. 
                        copy[y][x] = 'O';
                        print(copy, maxx, maxy, DIM);
                        printf("(%d,%d) Changes symetry r=%d->%d\n", x, y, oldr, r);
                    }
                    // revert copy
                    copy[y][x] = array[y][x];
                }
            }

            result += r;
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