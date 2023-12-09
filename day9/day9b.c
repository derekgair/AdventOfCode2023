#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>

int STRLEN = 1000;
int DIM = 100;

int all_zero(int *a, int s)
{
    for (int i = 0; i < s - 1; ++i)
    {
        if (a[i] != 0)
            return 0;
    }
    return 1;
}

int main()
{

    FILE *file = fopen("data.txt", "r");
    char line[STRLEN];
    int array[DIM];
    long sum = 0;
    while (fgets(line, sizeof(line), file))
    {
        int c = 0;
        int n = INT_MAX;
        int minus = 0;
        for (int i = 0; i < STRLEN; ++i)
        {
            if (line[i] == '-')
                minus = 1;
            else if (line[i] >= '0' && line[i] <= '9')
                n = (n == INT_MAX ? 0 : n) * 10 + line[i] - '0';
            else if (n != INT_MAX)
            {
                array[c++] = (minus ? -1 : 1) * n;
                n = INT_MAX;
                minus = 0;
            }
            if (line[i] == '\0')
                break;
        }
        int j = 0;
        for (; j < c; ++j)
        {
            if (all_zero(array + j, c - j - 1))
            {
                break;
            }
            for (int i = c - 2; i >= j; --i)
            {
                array[i + 1] = array[i] - array[i + 1];
            }
        }
        for (int i = 0; i < c; ++i)
        {
            sum += array[i];
            printf("%d+", array[i]);
        }
        printf("\n");
        c = 0;
    }
    printf("Result:%ld", sum);

    return 0;
}