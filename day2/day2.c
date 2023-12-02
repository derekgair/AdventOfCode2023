#include <stdio.h>
#include <stddef.h>
#include <string.h>

int main()
{

    int RED = 12, GREEN = 13, BLUE = 14;
    FILE *file = fopen("data.txt", "r");
    char line[2560];
    int sum = 0;
    while (fgets(line, sizeof(line), file))
    {
        int red = 0, green = 0, blue = 0;
        int n = 0;
        int game = 0;
        int colon = 0;
        for (int x = 0; x < strlen(line); ++x)
        {
            if (line[x] == ':')
            {
                colon = x;
                game = n;
                n = 0;
            }
            if (colon)
            {
                if (line[x] >= '0' && line[x] <= '9')
                {
                    n = n * 10 + (line[x] - '0');
                }
                else if (line[x] == 'g')
                {
                    if (n > green)
                        green = n;
                    n = 0;
                }
                else if (line[x] == 'b')
                {
                    if (n > blue)
                        blue = n;
                    n = 0;
                }
                else if (line[x] == 'd')
                {
                    if (n > red)
                        red = n;
                    n = 0;
                }
            }
            else
            {
                if (line[x] >= '0' && line[x] <= '9')
                {
                    n = n * 10 + (line[x] - '0');
                }
            }
        }
        if (red <= RED && green <= GREEN && blue <= BLUE)
            sum += game;
        printf("%s : game %d, r %d : g %d, b %d, tot %d \n", line, game, red, green, blue, sum);
    }
    printf("Total:%d", sum);
    fclose(file);

    return 0;
}
