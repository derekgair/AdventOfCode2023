#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>

#define DIM (10000)
void addarray(long *a, long b)
{
    for (long i = 0; i < DIM; ++i)
    {
        if (a[i] == -1)
        {
            a[i] = b;
            break;
        }
    }
}


struct Range {
    long from;
    long to;
    long size;
};
void addarrayrange(struct Range *a, struct Range b)
{
    for (long i = 0; i < DIM; ++i)
    {
        if (a[i].from == -1)
        {
            a[i] = b;
            break;
        }
    }
}

int main()
{

    FILE *file = fopen("data.txt", "r");
    char line[2560];
    long sum = 0;

    
    long seeds[DIM];
    memset(seeds,-1,DIM);
    struct Range seeds_to_soil_map[DIM];
    memset(seeds_to_soil_map,-1,DIM*sizeof(*seeds_to_soil_map));
    struct Range soil_to_fertilizer_map[DIM];
    memset(soil_to_fertilizer_map,-1,DIM*sizeof(*seeds_to_soil_map));
    struct Range fertilizer_to_water_map[DIM];
    memset(fertilizer_to_water_map,-1,DIM*sizeof(*seeds_to_soil_map));
    struct Range water_to_light_map[DIM];
    memset(water_to_light_map,-1,DIM*sizeof(*seeds_to_soil_map));
    struct Range light_to_temperature_map[DIM];
    memset(light_to_temperature_map,-1,DIM*sizeof(*seeds_to_soil_map));
    struct Range temperature_to_humidity_map[DIM];
    memset(temperature_to_humidity_map,-1,DIM*sizeof(*seeds_to_soil_map));
    struct Range humidity_to_location_map[DIM];
    memset(humidity_to_location_map,-1,DIM*sizeof(*seeds_to_soil_map));

    struct Range *mapmap[] = {seeds_to_soil_map,soil_to_fertilizer_map,fertilizer_to_water_map,water_to_light_map,light_to_temperature_map,temperature_to_humidity_map,humidity_to_location_map};
       
    enum Mode { SOIL=0, FERT=1,WATER=2,LIGHT=3,TEMP=4,HUMIDITY=5,LOCATION=6,SEEDS=-1 };
    enum NumberMode {FROM, TO, RANGE};

    enum Mode mode = SEEDS;
    while (fgets(line, sizeof(line), file))
    {
        long n = -1;
        char name[DIM];
        char *pos = name;
        memset(name,'\0',DIM);
        long from = -1,to = -1, range = -1;
            
        for (long i = 0; i < strlen(line); ++i)
        {
           if (line[i] == ':')
            {
                if( strcmp(name,"seeds")==0 ) {
                    mode=SEEDS;
                }
                else if( strcmp(name,"seed-to-soil map")==0 ) {
                    mode=SOIL;
                }
                else if( strcmp(name,"soil-to-fertilizer map")==0 ) {
                    mode=FERT;
                }
                else if( strcmp(name,"fertilizer-to-water map")==0 ) {
                    mode=WATER;
                }
                else if( strcmp(name,"water-to-light map") ==0) {
                    mode=LIGHT;
                }
                else if( strcmp(name,"light-to-temperature map") ==0) {
                    mode=TEMP;
                }
                else if( strcmp(name,"temperature-to-humidity map") ==0) {
                    mode=HUMIDITY;
                }
                else if( strcmp(name,"humidity-to-location map") ==0) {
                    mode=LOCATION;
                }
                pos = name;
                memset(name,'\0',DIM);                
            }
            else if (line[i] >= '0' && line[i] <= '9')
            {
                if ( n==-1) n=0;
                n = n * 10 + (line[i] - '0');
                // check fo
            }
            else if (n!=-1)
            {
                if ( mode == SEEDS ) {
                    addarray(seeds,n);
                }
                else if ( to >=0 ) {
                    struct Range r = { from,to,n };
                    addarrayrange(mapmap[mode],r);
                    from=-1;
                    to=-1;
                }
                else if ( from>=0 ) {
                    to = n;
                }
                else
                    from = n;
                n=-1;
            }
            *pos++ = line[i];
            if (line[i] == '\0')
            {
                break;
            }
        }
    }
    
    long lowest = LONG_MAX; // BIG NUMBER
    for ( long i = 0; seeds[i] != -1; i+=2) {
        printf("%ld...%ld\n",seeds[i],seeds[i+1]);
        for ( long l = seeds[i]; l < seeds[i] + seeds[i+1]; ++l )
        {
            long n = l;
        for ( long j = 0; j< 7; ++j){
            int found = 0;
            for ( int k = 0; (mapmap[j])[k].from != -1; ++k)
            {
                struct Range r = (mapmap[j])[k];
                if ( n >= r.to && n < r.to+r.size ) {
                    found = 1;                
                    n = (n-r.to) + r.from;
                    break;
                }    
            }
           
      //      printf("->%ld",n);
        }
        if ( l %100000000==0 ) 
                printf( "%ld percent complete\n",(100*(l-seeds[i]))/seeds[i+1] );            

        if ( n<lowest) lowest = n;
        
       // printf("\n");
        }
    }
    printf("\nLowest:%ld\n",lowest);

}