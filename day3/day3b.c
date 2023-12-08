#include <stdio.h>
#include <stddef.h>
#include <string.h>

#define DIM (200)
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MAX_ARRAY_SIZE (DIM * DIM)

void addarray(int *a, int b)
{
    for (int i = 0; i < MAX_ARRAY_SIZE; ++i)
    {
        if (a[i] == b || a[i] == -1)
        {
            a[i] = b;
            break;
        }
    }
}
void cleararray(int *a)
{
    memset(a, -1, MAX_ARRAY_SIZE);
}

struct Pos
{
    int x;
    int y;
};

void getGears(char array[DIM][DIM], int maxx, int maxy, int x, int y, int gears[MAX_ARRAY_SIZE])
{

    for (int x1 = MAX(x - 1, 0); x1 <= MIN(maxx - 1, x + 1); x1++)
    {
        for (int y1 = MAX(y - 1, 0); y1 <= MIN(maxy - 1, y + 1); y1++)
        {
            if (x1 >= 0 && y1 >= 0)
            {
                if (array[y1][x1] == '*')
                {
                    // map 2d co-ordinates to 1d as follows:
                    int gear = y1 * DIM + x1;
                    addarray(gears, gear);
                }
            }
        }
    }
}

struct Pos
{
    int x;
    int y;
};

struct Pos read2darray(char *filename, char array[DIM][DIM])
{

    FILE *file = fopen("data2.txt", "r");
    int x = 0, y = 0;
    while (fgets(array[y], DIM, file))
    {
        x = strlen(array[y]);
        y++;
    }
    struct Pos ret = {x, y};
    return ret;
}

int main()
{
    FILE *file = fopen("data2.txt", "r");
    char array[DIM][DIM];

    struct Pos max = read2darray("data2.txt", array);

    int sum = 0;
    int gears[MAX_ARRAY_SIZE];
    int numgears[MAX_ARRAY_SIZE];
    int prodgears[MAX_ARRAY_SIZE];

    cleararray(gears);

    for (int i = 0; i < max.y; i++)
        printf("%s\n", array[i]);

    for (int y = 0; y < max.y; ++y)
    {
        int n = 0;
        char symbol = 0;
        for (int x = 0; x < max.x + 1; ++x)
        {
            if (array[y][x] >= '0' && array[y][x] <= '9')
            {
                n = 10 * n + (array[y][x] - '0');
                // count the number of gears around this digit.
                // the found gears are returned in the "gears" array.
                getGears(array, max.x, max.y, x, y, gears);
            }
            else if (n > 0)
            {
                printf("%d:", n);

                for (int i = 0; i < MAX_ARRAY_SIZE; ++i)
                {
                    if (gears[i] == -1)
                        break;
                    printf("x:%d,y:%d", gears[i] / DIM, gears[i] % DIM);
                    if (numgears[gears[i]] == 0)
                    {
                        prodgears[gears[i]] = n;
                    }
                    else
                    {
                        prodgears[gears[i]] *= n;
                    }
                    numgears[gears[i]]++;
                }

                printf("\n");

                cleararray(gears);
                n = 0;
                if (array[y][x] == '\0')
                    break;
            }
        }
    }

    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        if (numgears[i] == 2)
            sum += prodgears[i];
    }
    printf("Sum is %d", sum);

    return 0;
}