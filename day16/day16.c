#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include "../aoc.h"

typedef struct DirPos
{
    int x;
    int y;
    int d;
} dirpos_t;

int xdir[] = {0, 1, 0, -1};
int ydir[] = {-1, 0, 1, 0};

dirpos_t nextpos(dirpos_t pos, int dir)
{
    dirpos_t ret;
    ret.d = dir;
    ret.x = pos.x + xdir[dir];
    ret.y = pos.y + ydir[dir];
    return ret;
}

int recurse(grid_t grid, grid_t copy, dirpos_t pos, int depth)
{
    
    int ret = 0;
    if (pos.x >= grid.maxx)
        return 0;
    else if (pos.y >= grid.maxy)
        return 0;
    else if (pos.x < 0)
        return 0;
    else if (pos.y < 0)
        return 0;
    else
    {

        char passed = getgrid(copy, pos.x, pos.y);
        if (passed == '.')
        {
            ret = 1;
            passed = 0;
        }
        else
            passed = passed - 'A';

        if (TEST_BIT(passed, pos.d))
        {
            // we have passed this way before in the same direction.
            return 0;
        }
        SET_BIT(passed, pos.d);

        setgrid(copy, pos.x, pos.y, passed + 'A');

        char c = getgrid(grid, pos.x, pos.y);
        if (c == '.') // continue in same direction.
            ret += recurse(grid, copy, nextpos(pos, pos.d), depth + 1);
        else if (c == '\\')
        {
            int dir = pos.d;
            if (dir == 0)
                dir = 3;
            else if (dir == 1)
                dir = 2;
            else if (dir == 2)
                dir = 1;
            else if (dir == 3)
                dir = 0;
            ret += recurse(grid, copy, nextpos(pos, dir), depth + 1);
        }
        else if (c == '/')
        {
            int dir = pos.d;
            if (dir == 0)
                dir = 1;
            else if (dir == 1)
                dir = 0;
            else if (dir == 2)
                dir = 3;
            else if (dir == 3)
                dir = 2;
            ret += recurse(grid, copy, nextpos(pos, dir), depth + 1);
        }
        else if (c == '|')
        {
            int dir = pos.d;
            if (dir == 1 || dir == 3)
            {
                ret += recurse(grid, copy, nextpos(pos, 0), depth + 1);
                ret += recurse(grid, copy, nextpos(pos, 2), depth + 1);
            }
            else
            {
                ret += recurse(grid, copy, nextpos(pos, dir), depth + 1);
            }
        }
        if (c == '-')
        {
            int dir = pos.d;
            if (dir == 0 || dir == 2)
            {
                ret += recurse(grid, copy, nextpos(pos, 1), depth + 1);
                ret += recurse(grid, copy, nextpos(pos, 3), depth + 1);
            }
            else
            {
                ret += recurse(grid, copy, nextpos(pos, dir), depth + 1);
            }
        }
    }
    return ret;
}

int main()
{
    grid_t grid = readgrid("data.txt");
    grid_t copy = copygrid(grid);
    cleargrid(copy, '.');
    dirpos_t pos;
    pos.x = 0;
    pos.y = 0;
    pos.d = 1;

    // Part A
    int result = recurse(grid, copy, pos, 0);
    // start at 0,0 direction = 1;
    printf("Result=%d\n", result);

    // Part B
    for (int x = 0; x < grid.maxx; ++x)
    {
        for (int y = 0; y < grid.maxy; ++y)
        {
            //I reallised later that we are only interested in the edges... so I just added
            // the following line... I feel dirty...
            if (y == 0 || x == 0 || y == grid.maxy - 1 || x == grid.maxx - 1)
            {
                for (int d = 0; d < 4; ++d)
                {
                    dirpos_t start;
                    start.x = x;
                    start.y = y;
                    start.d = d;
                    cleargrid(copy, '.');
                    int r = recurse(grid, copy, start, 0);
                    if (result < r)
                    {
                        printsep();
                        printf("Result (%d,%d,%d) with %d", x, y, d, r);
                        printgrid(copy);
                    }
                    result = max(result, r);
                }
            }
        }
    }
    
    freegrid(grid);
    freegrid(copy);

    printf("Result=%d\n", result);
}