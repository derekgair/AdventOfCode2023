#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include "../aoc.h"
#include <vector>
#include <utility>
#include <iostream>
/*
Determine the ASCII code for the current character of the string.
Increase the current value by the ASCII code you just determined.
Set the current value to itself multiplied by 17.
Set the current value to the remainder of dividing itself by 256.
*/
int HASH(const char *c, int len)
{
    int ret = 0;
    int i = 0;
    printf("[hash]");
    while (*c != '\0' && i++ < len)
    {
        char d = *c;
        ret += d;
        ret *= 17;
        ret %= 256;
        ++c;
        printf("%c", d);
    }
    printf("=%d\n", ret);

    return ret;
}

void printboxes( std::vector<std::pair<std::string, int> > * boxes) {
    int result = 0;
    for (int i = 0; i < 256; ++i)
    {
        auto node = (boxes)[i];
        if ( !node.empty() ) {
            printf("Box %d: ", i);
        
        int j = 1;
        for (auto iter = node.begin(); iter != node.end(); ++iter)
        {
            result += (i + 1) * j * iter->second;                
            std::cout << "[" << iter->first << " " << iter->second <<"] ";
            ++j;
        }
        std::cout << std::endl;
        }
    }
}
int main()
{
    int STRLEN = 102400;
    FILE *file = fopen("data.txt", "r");
    char line[STRLEN];
    int result = 0;
    std::vector<std::pair<std::string, int> > boxes[256];

    while (fgets(line, sizeof(line), file))
    {

        char *sp1 = NULL;
        char *token = strtok_r(line, ",", &sp1);
        while (token != NULL)
        {
            std::cout<< "token:" << token << std::endl;

            for (int i = 0; i < strlen(token); ++i)
            {
                std::string t(token, 0, i);
                if (token[i] == '-')
                {
                    int hash = HASH(token, i);
                    auto *node = &(boxes[hash]);
                    for (auto iter = node->begin(); iter != node->end(); ++iter)
                    {
                        if ( t == iter->first)
                        {
                            node->erase(iter);
                            break;
                        }
                    }
                }
                if (token[i] == '=')
                {
                    int hash = HASH(token, i);
                    auto *node = &(boxes[hash]);
                    bool found = false;
                    int number = token[i + 1] - '0';
                    for (auto iter = node->begin(); iter != node->end(); ++iter)
                    {
                        if (t == iter->first)
                        {
                            found = true;
                            iter->second = number;
                            break;
                        }
                    }
                    if (!found)
                    {
                        auto p = std::make_pair(t, number);
                        boxes[hash].push_back(p);
                    }
                }
            }
            token = strtok_r(0, ",", &sp1);
        printboxes(boxes);
        printsep();
        
       }
    }

    for (int i = 0; i < 256; ++i)
    {
        auto node = boxes[i];
        if ( !node.empty() ) {
            printf("Box %d: ", i);
        
        int j = 1;
        for (auto iter = node.begin(); iter != node.end(); ++iter)
        {
            result += (i + 1) * j * iter->second;                
            std::cout << "[" << iter->first << " " << iter->second <<"] ";
            ++j;
        }
        std::cout << std::endl;
        }
    }

    printf("Result:%d\n", result);
}
