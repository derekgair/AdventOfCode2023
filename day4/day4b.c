#include <stdio.h>
#include <stddef.h>
#include <string.h>

#define DIM (1000)
void addarray(int *a, int b)
{
    for (int i = 0; i < DIM; ++i)
    {
        if (a[i] == b || a[i] == -1)
        {
            a[i] = b;
            break;
        }
    }
}
enum state_enum
{
    READING_CARD_NO,
    READING_MY_CARD,
    READING_OTHER_CARD
};

int main()
{

    FILE *file = fopen("data.txt", "r");
    char line[2560];

    int extracards[DIM];
    memset(extracards, 0, DIM);

    int totcards = 0;
    while (fgets(line, sizeof(line), file))
    {
        totcards++;
        enum state_enum state = READING_CARD_NO;
        int mycards[DIM];
        int othercards[DIM];
        int n = 0;
        int card = 0;
        memset(mycards, -1, DIM);
        memset(othercards, -1, DIM);
        for (int i = 0; line[i] != '\0'; ++i)
        {
            if (line[i] == ':')
            {
                card = n;
                state = READING_MY_CARD;
                n = 0;
                // reading first card
            }
            else if (line[i] == '|')
            {
                // reading second card.
                state = READING_OTHER_CARD;
                n = 0;
            }
            else if (line[i] >= '0' && line[i] <= '9')
            {
                n = n * 10 + (line[i] - '0');
            }
            else if (n > 0)
            {
                if (state == READING_MY_CARD)
                    addarray(mycards, n);
                else if (state == READING_OTHER_CARD)
                    addarray(othercards, n);
                // reset...
                n = 0;
            }
        }

        for (int x = 0; x < extracards[card - 1] + 1; ++x)
        {
            int score = 0;
            for (int i = 0; mycards[i] != -1; ++i)
            {
                for (int j = 0; othercards[j] != -1; ++j)
                {
                    if (othercards[j] == mycards[i])
                    {
                        score++;
                    }
                }
            }

            for (int i = card; i < card + score; ++i)
            {
                extracards[i]++;
                totcards++;
            }
        }
    }
    fclose(file);
    printf("Sum: %d\n", totcards);
}