#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>

#define DIM (1000)

int addarray(int *a, int b)
{
    for (int i = 0; i < DIM; ++i)
    {
        if (a[i] == -1)
        {
            a[i] = b;
            return i;
        }
    }
    return -1;
}

int main()
{
    FILE *file = fopen("data.txt", "r");
    char line[2560];

    int time[DIM];
    memset(time, -1, DIM);
    int distance[DIM];
    memset(distance, -1, DIM);

    enum Mode
    {
        UNSET = 0,
        READ_DISTANCE = 2,
        READ_TIME = 1,
    };

    enum Mode mode = UNSET;

    int races;
    while (fgets(line, sizeof(line), file))
    {

        char *pos = line;
        int n = -1;

        for (;; ++pos)
        {
            if (*pos == ':')
            {
                mode++;
                n = -1;
            }
            else if (*pos >= '0' && *pos <= '9')
            {
                n = n == -1 ? 0 : n;
                n = n * 10 + *pos - '0';
            }
            else if (n > -1)
            {
                if (mode == READ_DISTANCE)
                    races = addarray(distance, n);
                else if (mode == READ_TIME)
                {
                    addarray(time, n);
                    races++;
                }
                n = -1;
            }
            if (*pos == '\0')
            {
                n = -1;
                break;
            }
        }
    }
    int res = 1;

    // d = (t-s)*s
    for (int race = 0; race <= races; ++race)
    {
        int sum = 0;
        int t = time[race];
        int d = distance[race];
        for (int s = 0; s < t; ++s)
        {
            int d2 = (t - s) * s;
            if (d2 > d)
                sum++;
        }
        printf("%d,%d,%d ", t, d, sum);
        res = res * sum;
    }
    printf("\nResult:%d\n", res);
}