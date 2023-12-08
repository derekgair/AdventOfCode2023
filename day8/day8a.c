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

// Utility function to find
// GCD of 'a' and 'b'
long long gcd(long long a, long long b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Returns LCM of array elements
long long findlcm(int arr[], int n)
{
    // Initialize result
    long long ans = arr[0];

    // ans contains LCM of arr[0], ..arr[i]
    // after i'th iteration,
    for (int i = 1; i < n; i++) {
        long long a = arr[i];

        ans = (((a * ans)) /
               (gcd(a, ans)));
    }
    return ans;
}
int main()
{
    enum Mode mode = READ_DIRECTIONS;
    char directions[STRLEN];

    int results[10000];
    for ( int i= 0; i < 10000; ++i)
     results[i] = -1;

    int nodes[DIM];
    for ( int i= 0; i < DIM; ++i) 
        nodes[i] = -1;
    
    int ZZZ = ('Z' - 'A') * 26 * 26 + ('Z' - 'A') * 26 + 'Z' - 'A';
    int XXX = ('X' - 'A') * 26 * 26 + ('X' - 'A') * 26 + 'X' - 'A';
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

    int resultindex = 0;
    for (int i = 0; i < DIM; i += 26)
    {                       // nodes ending with 0
        if (nodes[i] != -1) // skip empty...
        {
            int node = i;
            printf("%c%c%c:",node/(26*26) + 'A',(node/26)%26 + 'A',node%26 + 'A');

            int len = 0;
            int found = 0;
            while (!found)
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
                    if (node % 26 + 'A' == 'Z')
                    {
                        // printf("\nResult=%d\n", len);
                        results[resultindex++] = len;
                        printf("%d\n",len);

                        found = 1;
                        break;
                    }
                }
            }
        }
    }

    // find the LCM of all values.
    printf("Result: %lld", findlcm(results, resultindex));

    return 0;
}
