#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include "../aoc.h"

void roll(struct Grid grid)
{
    for (int x = 0; x < grid.maxx; x++)
    {
        for (int y = 1; y < grid.maxy; y++)
        {
            if (getgrid(grid, x, y) == 'O')
            {

                // simply move it up until we hit rock.
                for (int y1 = y - 1; y1 >= 0; y1--)
                {
                    if (getgrid(grid, x, y1) != '.')
                    {
                        setgrid(grid, x, y, '.');
                        setgrid(grid, x, y1 + 1, 'O');
                        break;
                    }
                    else if (y1 == 0)
                    {
                        setgrid(grid, x, y, '.');
                        setgrid(grid, x, y1, 'O');
                        break;
                    }
                }
            }
        }
    }
}

int main()
{
    int result = 0;

    struct Grid grid = readgrid("data.txt");
    printgrid(&grid);

    int CACHE_SIZE = 200;
    int cycle = -1;
    long COUNT = 1000000000L;
    // check for cycles...
    char cache[CACHE_SIZE * grid.maxx * grid.maxy];

    for (long i = 0; i < COUNT; ++i)
    {
        roll(grid);
        // W
        rotategrid90(grid);
        roll(grid);
        // S
        rotategrid90(grid);
        roll(grid);
        // E
        rotategrid90(grid);
        roll(grid);

        // N -> back to original pos.
        rotategrid90(grid);

        int grid_size = grid.maxx * grid.maxy;
        if (cycle == -1)
        {
            if (i < CACHE_SIZE)
            {
                for (int j = 0; j < grid.maxy * grid.maxx; j++)
                {
                    cache[i * grid_size + j] = grid.grid[j];
                }
            }

            // check if we have a cycle...
            for (int k = 0; k < min(i, CACHE_SIZE); k++)
            {
                int match = 1;
                for (int j = 0; j < grid.maxy * grid.maxx; j++)
                {
                    if (cache[k * grid_size + j] != grid.grid[j])
                    {
                        match = 0;
                        break;
                    }
                }
                if (match == 1)
                {
                    printf("Woohoo!!! we found a cycle, k=%d,i=%ld\n", k, i);
                    printgrid(&grid);
                    struct Grid grid2;
                    grid2.grid = cache + (k * grid.maxx * grid.maxy);
                    grid2.maxx = grid.maxx;
                    grid2.maxy = grid.maxy;
                    printsep();
                    printgrid(&grid);

                    cycle = i - k;

                    i = i + ((COUNT - i) / cycle) * cycle;
                    break;
                }
            }
        }
    }

    // calculate....
    for (int x = 0; x < grid.maxx; x++)
    {
        for (int y = 0; y < grid.maxx; y++)
        {
            if (getgrid(grid, x, y) == 'O')
            {
                printf("(%d,%d)result=%d + %d\n", x, y, result, grid.maxy - y);
                result += (grid.maxy - y);
            }
            
        }
    }
    printsep();

    printf("Result: %d\n", result);

    return 0;
}
