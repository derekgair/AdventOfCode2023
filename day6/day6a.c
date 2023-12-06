#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>

#define DIM (1000)

int addarray(long *a, long b)
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

    long time[DIM];
    memset(time, -1, DIM * sizeof(1L));
    long distance[DIM];
    memset(distance, -1, DIM * sizeof(1L));

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
        long n = -1;

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
            else if (*pos == ' ')
            {
                // ignore
            }
            else if (n > -1)
            {
                if (mode == READ_DISTANCE)
                    addarray(distance, n);
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
    long res = 1;

    // d = (t-s)*s
    for (int race = 0; race < races; ++race)
    {
        long sum = 0;
        long t = time[race];
        long d = distance[race];
        for (long s = 0; s < t; ++s)
        {
            long d2 = (t - s) * s;
            if (d2 > d)
                sum++;
        }
        printf("%ld,%ld,%ld ", t, d, sum);
        res = res * sum;
    }
    printf("\nResult:%ld\n", res);
}