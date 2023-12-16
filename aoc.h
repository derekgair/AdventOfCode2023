#include <stdio.h>
#include <stdlib.h>


#define BIT_MASK(bit)             (1 << (bit))
#define SET_BIT(value,bit)        ((value) |= BIT_MASK(bit))
#define CLEAR_BIT(value,bit)      ((value) &= ~BIT_MASK(bit))
#define TEST_BIT(value,bit)       (((value) & BIT_MASK(bit)) ? 1 : 0)


int pow10(int a, int b) {
    
    for ( int i = 0; i < b;i++) {
        a = a * 10;
    }
    return a;
}
int abs(int a)
{
    if (a < 0)
        return -a;
    return a;
}
int min(int a, int b)
{
    if (b > a)
        return a;
    return b;
}

int max(int a, int b)
{
    if (b > a)
        return b;
    return a;
}

typedef struct Grid {
    char * grid;
    int maxx;
    int maxy;
} grid_t;


void printsep()
{
    printf("--------------------------------------------------\n");
}
void printgrid(struct Grid grid)
{
    for (int y = 0; y < grid.maxy; ++y)
    {
        for (int x = 0; x < grid.maxx ; ++x){
            char c = *(grid.grid + ((y * grid.maxx) + x)*sizeof(char));
            if ( c=='\0') break;
            printf("%c", c);
        }
        printf("\n");
    }
}
char getgrid(struct Grid grid, int x, int y){
    return *(grid.grid + y * grid.maxx + x );
}
void setgrid(struct Grid grid, int x, int y, char c ){
    *(grid.grid + y * grid.maxx + x ) = c;
}
grid_t copygrid(grid_t grid) {
    grid_t ret;
    ret.maxx = grid.maxx;
    ret.maxy = grid.maxy;
    ret.grid=malloc(grid.maxx*grid.maxy);
    for ( int i = 0 ; i < grid.maxx*grid.maxy;++i) {
        *(ret.grid + i) = *(grid.grid+i);
    }
    return ret;
}
void cleargrid(grid_t grid, char c) {
    for ( int i = 0 ; i < grid.maxx*grid.maxy;++i) {
        grid.grid[i] = c;
        
    }

}
struct Grid readgrid(const char* filename) {
    
    struct Grid ret;
    ret.grid = 0;
    ret.maxx = 0;
    ret.maxy = 0;
    char line[1024];
    FILE *file = fopen(filename, "r");
    
    int s = 0;
    while (fgets(line, sizeof(line), file))
    {
        // find maxx;
        int x = 0;
        while ( line[x] != '\n' && line[x] != '\0' ) {
            x++;
        }
        s+=x;
        if ( ret.grid )
            ret.grid = (char*)realloc(ret.grid,s);
        else 
            ret.grid = (char*)malloc(s);

        x = 0;
        while ( line[x] != '\n' && line[x] != '\0' ) {
            *(ret.grid + ret.maxy*ret.maxx +x ) = line[x];
            ++x;
        }
        ret.maxx=x;
        ret.maxy++;
    }
    fclose(file);
    return ret;
    
}
void print(char *a, int maxx, int maxy,int dimx)
{
    for (int y = 0; y < maxy; ++y)
    {
        for (int x = 0; x < maxx ; ++x){
            char c = *(a + ((y * dimx) + x)*sizeof(char));
            if ( c=='\0') break;
            printf("%c", c);
        }
        printf("\n");
    }
}

void rotategrid90(struct Grid  in) {
// assumes it is square for now!!!

    int N=in.maxx;
    char *a = in.grid;
	for (int i = 0; i < N / 2; i++) {
		for (int j = i; j < N - i - 1; j++) {

			// Swap elements of each cycle
			// in clockwise direction
			int temp = a[(i)*N+j];
			a[(i)*N+j] = a[(N - 1 - j)*N+i];
			a[(N - 1 - j)*N+i] = a[(N - 1 - i)*N+N - 1 - j];
			a[(N - 1 - i)*N+N - 1 - j] = a[(j)*N+N - 1 - i];
			a[(j)*N+N - 1 - i] = temp;
		}
	}
}
void rotategrid90AC(struct Grid in) {
// assumes it is square for now!!!
    rotategrid90(in);
    rotategrid90(in);
    rotategrid90(in);

}