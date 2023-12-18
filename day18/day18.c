#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include "../aoc.h"

int main()
{
    FILE *file = fopen("data.txt", "r");
    char line[1024];
    
    int x1 = 0;
    int y1 = 0;
    int a = 0;
    int p =0;
    while (fgets(line, sizeof(line), file))
    {
        char dir = line[0];
        int d = line[2] - '0';
        if ( line[3] != ' ') d = d*10 + line[3] -'0';
        int x2 = x1;
        int y2 = y1;    
        if ( dir == 'R')
            x2= x1 + (d);
        if ( dir == 'L')
            x2= x1 - (d);
        if ( dir == 'U')
            y2= y1 - (d);
        if ( dir == 'D')
            y2 = y1 + (d);

        a += (y1+y2) * (x1-x2);
        
        p += d;
        
        x1=x2;
        y1=y2;
    }

    printf("Result:%d,%d", a/2 + p/2 + 1,p);
    


}