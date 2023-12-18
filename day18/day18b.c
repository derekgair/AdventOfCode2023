#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include "../aoc.h"

int main()
{
    FILE *file = fopen("data.txt", "r");
    char line[1024];
    
    long long x1 = 0;
    long long y1 = 0;
    long long a = 0;
    long long p =0;
    while (fgets(line, sizeof(line), file))
    {
        char* pos = strchr(line,'#');
        long long h = 0;
        pos++;
        for ( int i = 0; i < 5; ++i)
        {
            if ( *pos >='0' && *pos <='9' ) {
                h = h*16 + *pos -'0';
            }
            else if ( *pos >='a' && *pos <='f' ) {
                h = h*16 + *pos -'a' + 10 ;
            }
            pos++;
        }
        char dir = *pos;

        long long x2 = x1;
        long long y2 = y1;    
        if ( dir == '0')
            x2= x1 + (h);
        if ( dir == '2')
            x2= x1 - (h);
        if ( dir == '3')
            y2= y1 - (h);
        if ( dir == '1')
            y2 = y1 + (h);

        a += (y1+y2) * (x1-x2);
        
        p += h;
        
        x1=x2;
        y1=y2;

        printf("%lld\n",a);
    }

    printf("Result:%lld,%lld\n", a/2 + p/2 + 1,p);
    


}