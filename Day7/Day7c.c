    #include <stdio.h>
    #include <stddef.h>
    #include <string.h>
    #include <limits.h>

    #define MAX_BID (10000)
    #define DIM (MAX_BID)

    int insertarray(long* a, int rank, int bid) {
        int i = 0;
        for ( ; a[i]!=0; ++i ){
            if ( a[i] == -1 ) {
                long v = (long)rank*(long)MAX_BID + bid;
                a[i] = v;
                break;
            }
            else if ( rank < a[i]/(long)MAX_BID ) {
                for ( int j = DIM-1; j>i; --j) {
                    a[j] = a[j-1];
                }
                a[i] = (long)rank*(long)MAX_BID + bid;
                break;
            }
        }
        return i;
    }
    int addarray(int* a, int b) {
        int i = 0; 
        for ( ; a[i]!=-1; ++i );
        a[i] = b;
        return i;
    }
    int addhand(char* a, char b) {
        int i = 0; 
        for ( ; a[i]!=-1; ++i );
        a[i] = b;
        return i;
    }
    int add_sorted_hand(char* a, char b) {
        int i= 0;
        for ( ; i< 5; ++i ){
            if ( a[i] == -1 ) {
                a[i] = b;
                break;
            }
            else if ( b > a[i] ) {
                for ( int j = 4;j>i;--j) {
                    a[j]=a[j-1];
                }
                a[i] = b;
                break;
            }
        }
        return i;
    }
    enum Type {
        FIVE_KIND = 6,
        FOUR_KIND = 5,
        FULL_HOUSE = 4,
        THREE_KIND = 3,
        TWO_PAIR = 2,
        ONE_PAIR = 1,
        HIGH = 0,
    };

    enum Type recognize(char* sorted_hand) {
        char temp[6];
        temp[5]='\0';
        char v = 'A';
        temp[0] = v;
        for ( int i = 1;i< 5;++i) {
            if ( sorted_hand[i] != sorted_hand[i-1]) {
                v++;
            }
            if ( sorted_hand[i] == '1')
                v='1';
            temp[i] = v;
        }
        if ( strcmp(temp,"ABCDE") ==0) {
            return HIGH;
        }
        else if ( 
            strcmp(temp,"ABCDD") ==0 || 
            strcmp(temp,"ABCCD") ==0 || 
            strcmp(temp,"ABBCD") ==0 || 
            strcmp(temp,"AABCD") ==0 || 
            strcmp(temp,"ABCD1") ==0 || 
            1==0) {
            return ONE_PAIR;
        }
        else if ( 
            strcmp(temp,"AABBC") ==0 || 
            strcmp(temp,"ABBCC") ==0 || 
            strcmp(temp,"AABCC") ==0 || 
            1==0) {
            return TWO_PAIR;
        }
        else if ( 
            strcmp(temp,"AAABC") ==0 ||
            strcmp(temp,"ABBBC") ==0 ||
            strcmp(temp,"ABCCC") ==0 ||
            strcmp(temp,"AABC1") ==0 ||
            strcmp(temp,"ABBC1") ==0 ||
            strcmp(temp,"ABCC1") ==0 ||
            strcmp(temp,"ABC11") ==0 ||
            1==0) {
            return THREE_KIND;
        }
        else if ( 
            strcmp(temp,"AAABB") ==0 ||
            strcmp(temp,"AABBB") ==0 ||
            strcmp(temp,"AABB1") ==0 ||
            1==0) {
            return FULL_HOUSE;
        }
        else if ( 
            strcmp(temp,"AAAAB") ==0 ||
            strcmp(temp,"ABBBB") ==0 ||
            strcmp(temp,"AAAB1") ==0 ||
            strcmp(temp,"ABBB1") ==0 ||
            strcmp(temp,"AAB11") ==0 ||
            strcmp(temp,"ABB11") ==0 ||
            strcmp(temp,"AB111") ==0 ||
            1==0) {
            return FOUR_KIND;
        }
        else if ( 
            strcmp(temp,"AAAAA") ==0 ||
            strcmp(temp,"AAAA1") ==0 ||
            strcmp(temp,"AAA11") ==0 ||
            strcmp(temp,"AA111") ==0 ||
            strcmp(temp,"A1111") ==0 ||
            strcmp(temp,"11111") ==0 ||
            1==0) {
            return FIVE_KIND;
        } 
        //else if ( strcmp(temp,"ABCDE") ==0) {
            return HIGH;
        //}
    }

    int card_rank( char a ) {
        if ( a >= '0' && a<='9' ) {
            return a-'0';
        }
        return a-'A'+10;
    }
    int simple_rank( char* hand ){
        int rank = 0;
        for ( int i = 0; i < 5; ++i ) {
            rank = rank * 15 + card_rank(hand[i]);
        }
        return rank;
    }
    int rank( char* hand, char* shand ) {
        int M = (15*15*15*15*15);

        int s = simple_rank(hand);
        int type = recognize(shand);
        return M*type + s;
    }

    int main()
    {
        FILE *file = fopen("data.txt", "r");
        char line[2560];
        long nodes[DIM];
        char hands[DIM][6];

        for ( int i = 0 ; i < DIM; ++i ) {
            nodes[i] = -1L;
        }
        enum Mode
        {
            READ_HAND = 0,
            READ_BID = 1
        };

        enum Mode mode = READ_HAND;

        int i = 0;
        while (fgets(line, sizeof(line), file))
        {
            mode = READ_HAND;
            char hand[6] = {-1,-1,-1,-1,-1,0};
            char shand[6] = {-1,-1,-1,-1,-1,0};
            
            int n = -1;;
            
            for ( char* pos = line ; (*pos)!='\0'; ++pos) {
                if ( *pos == ' ')
                mode = READ_BID;
                else if ( mode == READ_HAND ) {
                    if ( *pos <= '9' && *pos >= '0' ) {
                        addhand(hand,*pos);
                        add_sorted_hand(shand,*pos);
                    }
                    else if ( *pos == 'T' ) {
                        addhand(hand, 'A');
                        add_sorted_hand(shand,'A');
                    }
                    else if ( *pos == 'J' ) 
                    {
                        addhand(hand, '1');
                        add_sorted_hand(shand,'1');
                    }
                    else if ( *pos == 'Q' ) {
                        addhand(hand, 'C');
                        add_sorted_hand(shand,'C');
                    }
                    else if ( *pos == 'K' ) {
                        addhand(hand, 'D');
                        add_sorted_hand(shand,'D');
                    }
                    else if ( *pos == 'A' ) {
                        addhand(hand, 'E');
                        add_sorted_hand(shand,'E');
                    }                
                }
                else if ( mode== READ_BID ) {
                    if ( *pos <= '9' && *pos >= '0' ) {
                        n=(n==-1?0:n)*10 + (*pos-'0');
                    }
                }
            }
            insertarray(nodes,rank(hand,shand),n);
            strcpy(hands[n],hand);
            printf("%s:%s:%d:%d:%d\n",hand,shand,n,recognize(shand),rank(hand,shand));
        }

        long res = 0;
        for ( int i = 0; i < DIM; ++i ) {
            if ( nodes[i] == -1) break;
            res = res + nodes[i]%MAX_BID * (i+1);
            printf( "+%ld*%d  [%s]\n",nodes[i]%MAX_BID,(i+1),hands[nodes[i]%MAX_BID]);
        }
        printf("=%ld\n",res);
    }
