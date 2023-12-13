#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include "../aoc.h"

enum Mode {
    READ_PATTERN,
    READ_NUMBERS
};

int match(char * a, char * b) {

    while( *a != '\0' ) {
        if ( *a != *b || *b !='?' ) {
            return 0;
        }
    } 
    return 1;
}
/*
???.### 1,1,3
.??..??...?##. 1,1,3
?#?#?#?#?#?#?#? 1,3,1,6
????.#...#... 4,1,1
????.######..#####. 1,6,5
?###???????? 3,2,1
*/

int check(
	int* numbers,
    int numbers_size,
    char* pattern,
    int pattern_size );

int checkhash(
	int * numbers,
    int numbers_size,
    char* pattern,
    int pattern_size
)
{
	if (numbers_size == 0) {
		return 0;
	}

	int x = *numbers;
	if (pattern_size < x) 
        return 0;
	
    for (int i = 0; i < x; ++i ) {
        // if any match a . then it cannot match the number
    	if (*(pattern+i) == '.') 
            return 0;
	}
    
	if (pattern_size == x)
    {   
        // all characters are a ? or a # and length matches the number (at the end)
        if (numbers_size == 1)
             return 1;
		return 0;
	}
	else if ( *(pattern+x) == '#') // another #, so cannot match.
        return 0;
    
    // check the rest of the pattern (substring) without the number.
    return check( numbers+1, numbers_size -1, pattern + x + 1, pattern_size -x -1);
}


int check(
	int* ix,
    int numbers_size,
    char* pattern,
    int pattern_size )
{
	if (pattern_size == 0) {
		if (numbers_size == 0) {
			return 1;
		} else {
			return 0;
		}
	}

int r = 0;
	if ( *pattern == '.' ) {
            // recurse ignoring the .
			r = check(ix, numbers_size, pattern + 1,pattern_size-1);
		}
        else if ( *pattern == '#' ) {
            // matches #
			r =  checkhash(ix, numbers_size, pattern, pattern_size); //.also{mem[ix to pattern] = it} // NOTE the 'also' part was added during PART 2
	    }
        else if ( *pattern == '?') {
		{
            // recurse assuming . or check matches #
            r =  check(ix, numbers_size, pattern+1,pattern_size-1) + checkhash(ix, numbers_size, pattern,pattern_size); //.also{mem[ix to pattern] = it}
             //printf("[?]%d\n",r);
    
        }
	}
    //printf("%d\n",r);
    return r;
}

int main() {

    int STRLEN=1024;    
    FILE *file = fopen("data.txt", "r");
    char line[STRLEN];
    int result = 0;
    while (fgets(line, sizeof(line), file))
    {
        enum Mode mode = READ_PATTERN;
        char pattern[STRLEN];
        int numbers[STRLEN];
        int c= 0;
        int n = 0;
        for ( int i = 0; i < strlen(line); ++i ){
            
            if ( line[i] == ' ' ) {
                mode = READ_NUMBERS;
                pattern[i] = '\0';
            }
            if ( mode == READ_PATTERN){
                pattern[i] = line[i];
            }
            else if ( line[i] >= '0' && line[i] <='9') {
                n = n*10 + line[i] - '0';
            }
            else if ( n>0) {
                numbers[c++] = n;
                n=0;
            }
        }
        
        for ( int i = c; i < c*5 ; ++i) {
            numbers[i] = numbers[i%c];
        }
        // line by line processing
        printf("%s:",pattern);
        for ( int i = 0; i<c;++i)
        {
            printf("%d,",numbers[i]);
        }
        printf("->");

        int r = check(numbers,c,pattern,strlen(pattern));

        result +=r;
        printf("%d\n",r);
    }
        printf("Result: %d\n", result);

    return 0;
}