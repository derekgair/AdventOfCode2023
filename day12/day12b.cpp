#include <iostream>
#include <vector>
#include <map>

enum Mode
{
    READ_PATTERN,
    READ_NUMBERS
};
std::map<std::vector<int>,long> memo;

/*
???.### 1,1,3
.??..??...?##. 1,1,3
?#?#?#?#?#?#?#? 1,3,1,6
????.#...#... 4,1,1
????.######..#####. 1,6,5
?###???????? 3,2,1
*/

template<class NIter, class PIter>
long long check(
    NIter nbegin,
    NIter nend,
    PIter pbegin,
    PIter pend );

template<class NIter,class PIter>
long long checkhash(
    NIter nbegin,
    NIter nend,
    PIter pbegin,
    PIter pend){
    if (nbegin == nend)
    {
        return 0;
    }

    int x = *nbegin;
    if (std::distance(pbegin,pend) < x)
    {
        return 0;
    }

    for (int i = 0; i < x; ++i)
    {
        // if any match a . then it cannot match the number
        if (*(pbegin + i) == '.')
            return 0;
    }

    if (std::distance(pbegin,pend) == x)
    {
        // all characters are a ? or a # and length matches the number (at the end)
        if (nbegin+1==nend )
            return 1;
        return 0;
    }
    else if (*(pbegin + x) == '#') // another #, so cannot match.
        return 0;

    // check the rest of the pattern (substring) without the number.
    long long res = check(nbegin + 1, nend, pbegin + x + 1, pend);

    return res;
}

template<class NIter, class PIter>
long long check(
    NIter nbegin,
    NIter nend,
    PIter pbegin,
    PIter pend )
{
    if ( pbegin == pend )
    {
        if (nbegin == nend )
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    long long r = 0;
    if (*pbegin == '.')
    {
        // recurse ignoring the .
        r = check(nbegin,nend,pbegin+1,pend);
    }
    else if (*pbegin == '#')
    {
        // matches #
        std::vector<int> key(nbegin,nend);
        key.insert(key.end(),pbegin,pend);
        auto i = memo.find(key);    

       if ( i == memo.end() )
        {
            r = checkhash(nbegin, nend, pbegin, pend);
            memo[key]=r;
        }
        else
            r = i->second;
   }

    else if (*pbegin == '?')
    {
        {
            // recurse assuming . or check matches #
                
        std::vector<int> key(nbegin,nend);
        key.insert(key.end(),pbegin,pend);
        auto i = memo.find(key);    
        if ( i == memo.end() ) {
            r = checkhash(nbegin, nend, pbegin, pend);
            memo[key]=r;
        }
        else {
            r = i->second;
        }
            r += check(nbegin, nend, pbegin + 1, pend );
        }
    }
    return r;
}

int main()
{
    int STRLEN = 1024;
    FILE *file = fopen("data.txt", "r");
    char line[STRLEN];
    long long result = 0;
    while (fgets(line, sizeof(line), file))
    {
        enum Mode mode = READ_PATTERN;
        
        std::vector<char> tmp;
        std::vector<int> numbers;
        
        int c = 0;
        int n = 0;
        for (int i = 0; i < strlen(line); ++i)
        {

            if (line[i] == ' ')
            {
                mode = READ_NUMBERS;
            }
            if (mode == READ_PATTERN)
            {
                tmp.push_back( line[i]);
            }
            else if (line[i] >= '0' && line[i] <= '9')
            {
                n = n * 10 + line[i] - '0';
            }
            else if (n > 0)
            {
                numbers.push_back(n);
                n = 0;
            }
        }
        std::vector<char> new_pattern;
        new_pattern.insert(new_pattern.end(),tmp.begin(),tmp.end());
        new_pattern.push_back('?');
        new_pattern.insert(new_pattern.end(),tmp.begin(),tmp.end());
        new_pattern.push_back('?');
        new_pattern.insert(new_pattern.end(),tmp.begin(),tmp.end());
        new_pattern.push_back('?');
        new_pattern.insert(new_pattern.end(),tmp.begin(),tmp.end());
        new_pattern.push_back('?');
        new_pattern.insert(new_pattern.end(),tmp.begin(),tmp.end());
        
        std::vector<int> new_numbers;

        new_numbers.insert(new_numbers.end(),numbers.begin(),numbers.end());
        new_numbers.insert(new_numbers.end(),numbers.begin(),numbers.end());
        new_numbers.insert(new_numbers.end(),numbers.begin(),numbers.end());
        new_numbers.insert(new_numbers.end(),numbers.begin(),numbers.end());
        new_numbers.insert(new_numbers.end(),numbers.begin(),numbers.end());
        // line by line processing
        std::cout << std::string(new_pattern.begin(),new_pattern.end()) << ":";
        for (auto const& i : new_numbers ) {
            std::cout << i;
        }
        std::cout << std::endl;
        
        long long r = check(new_numbers.begin(), new_numbers.end(), new_pattern.begin(), new_pattern.end());

        result += r;
        printf("%lld\n", r);
        
    }
    printf("Result: %lld\n", result);

    return 0;
}