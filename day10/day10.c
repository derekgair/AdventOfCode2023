#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>

int STRLEN = 1024;
int DIM = 150;
int x = 0;

char ALL_PIPES[] = "|-7LFJ";

struct Pos {
    int x;
    int y;
};

int map(int prev, int current, char c, int x) {
    int next = -1;
    int sign = 1;
    if ( prev > current) 
        sign = -1;
    if ( c=='|') {
        if ( prev == current -x ){
            return current + x;
        }
        if ( prev == current + x ) {
            return current - x;
        }
    }
    if ( c == '-')  {
        if ( prev == current - 1 ) {
            return current + 1;
        }

        if ( prev == current + 1 ) {
            return current - 1;
        }
    }
    if ( c == 'J') {
        if ( prev == current - x ) {
            return current - 1;
        }
        if ( prev == current -1 ) {
            return current - x;
        }
    }
    if ( c == 'L') {
        if ( prev == current - x ) {
            return current + 1;
        }
        if ( prev == current +1 )
            return current - x;
    }
    if ( c == 'F') {
        if ( prev == current + 1 ) {
            return current + x;
        }
        if ( prev == current + x ) {
            return current + 1;
        }        
    }
    if ( c == '7') {
        if ( prev == current - 1 ) {
            return current + x;
        }
        if ( prev == current + x ) {
            return current - 1;
        }        
    }
    return -1;
}
int max( int a, int b) {
    if ( a>b) return a;
    return b;
}

int min( int a, int b) {
    if ( a<b) return a;
    return b;
}

int pos( int x, int y, int maxx) {
    return y*maxx + x;
} 

int main()
{
    FILE *file = fopen("data.txt", "r");
    char line[DIM];
    char array[DIM][DIM];
    int size = 0;
    
    int maxx = -1;
    int maxy = 0;
    int startx = -1,starty=-1;
    while (fgets(line, sizeof(line), file))
    {
        for ( int i = 0; i < STRLEN;++i)
        {
            if ( line[i] == '\0' ) {
                if ( maxx == -1 ) maxx = i;
                break;
            }
            else if ( line[i]!='\n' ) {
                if ( line[i] == 'S' ) {
                    startx = i;
                    starty = maxy;
                }
                array[maxy][i] = line[i];
            }
        }
        maxy++;
    }

    int prevx = startx;
    int prevy = starty;
    int prev = pos(prevx,prevy,maxx);
    int currentx = -1;
    int currenty = -1;
    int currentdir = 0;
    int current = pos(currentx,currenty,maxx);
    
    for ( int x = max(0,prevx-1); x <= min(maxx,prevx+1) && currenty==-1;++x) {
        for ( int y = max(0,prevy-1); y <= min(maxy,prevy+1) && currenty==-1;++y ){
            char c = array[y][x];
            current = y*maxx + x;
            if ( map(prev, current, c, maxx) != -1 ) {
                    currentx = x;
                    currenty = y;
                    if ( c == 'J' || c == '_' || c == '7') {
                        currentdir=0;
                    }

                    if ( c == 'F' || c == '|' || c == 'L') {
                        currentdir=-1;
                    }

                }
            //}
        }
    }
    
    //prev = prevy*maxx + prevx;
    int start = prev;
    current = pos(currentx,currenty,maxx);
    
    int length = 1;
    
    do {
        char c = array[currenty][currentx];
        
        int tmp =  map( prev,current, c, maxx );
        prev = current;
        current = tmp;
        currentx = current%maxx;
        currenty = current/maxx;
        printf("(%d,%d)[%c][%d]\n",currentx,currenty,c,current);
        length++;
    } while ( current != start );

    printf( "Result: %d",length/2);

}

