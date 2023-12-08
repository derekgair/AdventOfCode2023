#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>

#define DIM (26 * 26 * 26)
#define STRLEN (2048)

enum Mode
{
    READ_DIRECTIONS = 0,
    READ_NODE = 1,
    READ_LEFT = 2,
    READ_RIGHT = 3,
};

int main()
{
    enum Mode mode = READ_DIRECTIONS;
    char directions[STRLEN];
    int nodes[DIM];
    int ZZZ = ('Z' - 'A') * 26 * 26 + ('Z' - 'A') * 26 + 'Z' - 'A';
    int AAA = 0;

    FILE *file = fopen("data.txt", "r");
    char line[STRLEN];
    while (fgets(line, sizeof(line), file))
    {
        int v = -1;
        int node = -1;
        int left = -1;
        for (int i = 0; i < STRLEN; ++i)
        {
            char c = line[i];

            if (mode == READ_DIRECTIONS)
            {
                strncpy(directions, line, STRLEN);
                mode++;
                break;
            }
            else if (c >= 'A' && c <= 'Z')
            {
                v = (v == -1 ? 0 : v) * 26 + (c - 'A');
            }
            else if (c == '\0' || c == '\n')
                break;
            else
            {
                if (v > -1)
                {
                    if (mode == READ_NODE)
                    {
                        node = v;
                        mode++;
                    }
                    else if (mode == READ_LEFT)
                    {
                        left = v;
                        mode++;
                    }
                    else if (mode == READ_RIGHT)
                    {
                        nodes[node] = left * 26 * 26 * 26 + v;
                        mode = READ_NODE;
                        node = -1;
                        left = -1;
                    }
                    v = -1;
                }
            }
        }
    }

    int len = 0;
    int node = AAA;
    while (1)
    {
        for (int j = 0; j < strlen(directions); ++j)
        {
            if (directions[j] == 'R')
            {
                node = nodes[node] % DIM;
                len++;
            }
            else if (directions[j] == 'L')
            {
                node = nodes[node] / DIM;
                len++;
            }

            if (node == ZZZ)
            {
                printf("\nResult=%d\n", len);
                return 0;
            }
        }
    }
    return 0;
}
