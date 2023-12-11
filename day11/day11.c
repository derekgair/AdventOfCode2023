#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>

#define DIM (300)
#define STRLEN (2048)

// Part 1
//#define EXPANSION (2L)
// Part 2
#define EXPANSION (1000000L)

void print( char a[DIM][DIM], int maxx,int maxy ) {
        for (int y = 0; y < maxy; ++y)
    {
    for (int x = 0; x < maxx; ++x)
        {  
            char c = a[y][x];
        
            printf("%c", c);
        }
        printf("\n");
    }
}
int abs(int a) {
    if ( a<0) return -a;
    return a;
}
int min(int a,int b)
{
    if ( b>a )
    return a;
    return b;
}

int max( int a, int b)
{
    if ( b>a) 
    return b;
    return a;
}
int main()
{

    char array[DIM][DIM];

    FILE *file = fopen("data.txt", "r");
    char line[STRLEN];
    int maxy = 0;
    int maxx = 0;
    while (fgets(line, sizeof(line), file))
    {
        for (maxx = 0; maxx < strlen(line); ++maxx)
        {
            array[maxy][maxx] = line[maxx];    
        }

        maxy++;
    }

    print( array,maxy,maxx);


    long xexpansion[DIM];
    long yexpansion[DIM];
    
    for (int y = 0; y < maxy; ++y)
    {
        int found = 0;
        for (int x = 0; x < maxx; ++x)
        {
            if (array[y][x] == '#')
            {
                found = 1;
                break;
            }
        }
        if ( !found ) {
            yexpansion[y]=EXPANSION;
        }
        else {
            yexpansion[y]=1;
        }
        /*
            for ( int y1 = maxy; y1>y; --y1)
            {
                for ( int x1 = 0; x1< maxx; ++x1) {
                        array[y1][x1] = array[y1-1][x1];
                    }
            }
            y++;
            maxy++;
        }
        */
    }

    
    print(array,maxx,maxy);
    // insert column
    for (int x = 0; x < maxx; ++x)
    {
        int found = 0;
        for (int y = 0; y < maxy; ++y)
        {
            if (array[y][x] == '#')
            {
                found = 1;
                break;
            }
        }
        if ( !found ) {
            xexpansion[x] = EXPANSION;
        }
        else {
            xexpansion[x]=1;
        }   
        /* for ( int x1 = maxx; x1>x; --x1)
            {
                for ( int y1 = 0; y1< maxy; ++y1) {
                        array[y1][x1] = array[y1][x1-1];
                }
            }
            x++;
            maxx++;
        }
        */
        //print(array,maxx,maxy);

    }

    
    print(array,maxx,maxy);



    long sum = 0L;
    // for each galaxy, find the distance to the others
    for (int y = 0; y < maxy; ++y)
    {
        for (int x = 0; x < maxx; ++x)
        {
            if (array[y][x] == '#')
            {
                // find distances to next galaxies and add to sum
                for (int y1 = 0; y1 < maxy; ++y1)
                {
                    for (int x1 = 0; x1 < maxx; ++x1)
                    {
                        // skip those before current position (removes dupes)
                        if (y1 * maxy + x1 > y * maxy + x)
                        {
                            if (array[y1][x1] == '#')
                            {
                                printf("#(%d,%d)->#(%d,%d)=%d\n",x,y,x1,y1, ( abs(y1 - y) + abs(x1 - x)));
                            
                                for ( int i = min(y,y1); i< max(y,y1); ++i )
                                {
                                    sum+=yexpansion[i];
                                }
                                for ( int i = min(x,x1); i< max(x,x1); ++i )
                                {
                                    sum+=xexpansion[i];
                                }
                                
                        }
                        }
                    }
                }
            }
        }
    }
    
    printf("result: %ld", sum);

    return 0;
}
