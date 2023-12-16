#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include "../aoc.h"

int main()
{
    int result = 0;

    struct Grid grid = readgrid("example.txt");
    struct Grid copy = readgrid("example.txt");

    printgrid(grid);

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
            // else
            // break;
        }
    }
    printsep();

    printf("Result: %d\n", result);

    return 0;
}
