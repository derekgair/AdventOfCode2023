#include <stdio.h>
#include <stddef.h>
#include <string.h>

#define DIM (200)
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

char hasSymbol(char grid[DIM][DIM], int maxx, int maxy, int x, int y)
{
    for (int x1 = MAX(x - 1, 0); x1 <= MIN(maxx - 1, x + 1); x1++)
        for (int y1 = MAX(y - 1, 0); y1 <= MIN(maxy - 1, y + 1); y1++)
            if (x1 >= 0 && y1 >= 0)
                if ((grid[y1][x1] > '9' || grid[y1][x1] < '0') && grid[y1][x1] != '.')
                    return grid[y1][x1];        
    return 0;
}

int main()
{
    FILE *file = fopen("data2.txt", "r");

    char grid[DIM][DIM];
    int sum = 0;
    int maxx = 0, maxy = 0;

    while (fgets(grid[maxy], DIM, file))
        maxx = strlen(grid[maxy++]);

    for (int y = 0; y < maxy; ++y)
    {
        int n = 0;
        char symbol = 0;
        for (int x = 0; x < maxx + 1; ++x)
        {
            if (grid[y][x] >= '0' && grid[y][x] <= '9')
            {
                n = 10 * n + (grid[y][x] - '0');
                char s = hasSymbol(grid, maxx, maxy, x, y);
                if (s)
                    symbol = s;
            }
            else if (n > 0)
            {
                if (symbol)
                    sum += n;
                else
                    printf("%d has no symbol\n", n);
 
                n = 0;
                symbol = 0;
            }
        }
    }
    printf("Sum is %d", sum);

    return 0;
}