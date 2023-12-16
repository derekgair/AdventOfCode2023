#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include "../aoc.h"

/*
Determine the ASCII code for the current character of the string.
Increase the current value by the ASCII code you just determined.
Set the current value to itself multiplied by 17.
Set the current value to the remainder of dividing itself by 256.
*/
int HASH(  const char* c) {
    int ret = 0;
    while( *c!= '\0') {
        char d = *c;
        ret += d;
        ret *= 17;
        ret %= 256;
        ++c;
    }
    return ret;
}


int main()
{
    int STRLEN = 1024000;
    FILE *file = fopen("data.txt", "r");
    char line[STRLEN];
    int result = 0;

    while (fgets(line, sizeof(line), file))
    {
        int hash = 0;
        int lpos = -1;
        char * token = strtok(line,",");
        while ( token != 0 ) {
            int h = HASH(token);
            printf("%s -> %d\n",token,h);
            token = strtok(0,",");
            result += h;
        
        }
    }
    printf("Result:%d\n", result);
}