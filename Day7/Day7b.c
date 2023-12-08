#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>

#define DIM (5)
#define DIM2 (1000)

struct Node {
    int hand[5];
    int uhand[5];
    int rank; 
    int bid;   
    char* desc;
};

struct Node nodes[DIM2];


int sequence( int* hand,int len ) {
    for ( int i = 0; i< len-1; ++i )
        if( hand[i] != hand[i+1]) {
            return 0;
        }
    return hand[0];

}
int addrank(struct Node *rank, int *hand, int *uhand, int calcRank, int bid,char* desc) {
    for ( int i = 0; ; ++i) {
        if ( rank[i].rank==-1 )
        {
            rank[i].rank=calcRank;
            rank[i].bid = bid;
            rank[i].desc = desc;
            
            for ( int k = 0;k < 5;++k)
                    rank[i].hand[k] = hand[k];
            for ( int k = 0;k < 5;++k)
                    rank[i].uhand[k] = uhand[k];
            return i;
        }    
        else if ( calcRank<rank[i].rank){
            for ( int j = DIM2 - 1; j > i; --j)
            {     
                rank[j].rank = rank[j-1].rank;
                rank[j].bid = rank[j-1].bid;
                rank[j].desc = rank[j-1].desc;
                for ( int k = 0;k < 5;++k)
                    rank[j].hand[k] = rank[j-1].hand[k];
                for ( int k = 0;k < 5;++k)
                    rank[j].uhand[k] = rank[j-1].uhand[k];
            }
            rank[i].rank=calcRank;
            rank[i].bid=bid;
            rank[i].desc=desc;
            for ( int k = 0;k < 5;++k)
                rank[i].hand[k] = hand[k];
            for ( int k = 0;k < 5;++k)
                rank[i].uhand[k] = uhand[k];
            return i;
        }
    }
    return 0;
}

int addhand(int a[5], int u[5], int b)
{
    for (int i = 0; i < DIM; ++i)
    {
        if ( u[i] == -1 ){
            u[i] = b;
            break;
        }
    }
    for (int i = 0; i < DIM; ++i)
    {
        if (a[i] == -1)
        {
            a[i] = b;
            return i;
        }
        else if (b>a[i]) {
            for ( int j = DIM-1; j > i; --j ) {
                a[j] = a[j-1];
            }
            a[i] = b;
            return i;
        }
      
    }
    return -1;
}
int fiveOfAKind( int* hand ) {
    return sequence(hand,5);
}
int fourOfAKind( int* hand ) {
    int i1 = sequence(hand,4);
    if ( i1>0) return hand[0]*15 + hand[4];
    i1 = sequence(hand+1,4);
    if ( i1>0) return hand[1]*15 + hand[0];
    return 0;

}
int fullHouse( int * hand) {
    int i1 = sequence(hand,3);
    int i2 = sequence(hand+3,2);
    int i3 = sequence(hand,2);
    int i4 = sequence(hand+2,3);
    if ( i1>0 && i2>0) return hand[0]*15 + hand[3];
    if ( i3>0 && i4>0) return hand[3]*15 + hand[0];
    return 0;
}
int threeKind( int * hand) {
    int i1 = sequence(hand,3);
    if (i1) return hand[0]*15*15 + hand[3]*15+hand[4];
    int i2 = sequence(hand+1,3);
    if ( i2) return hand[1]*15*15 + hand[0]*15 + hand[4];
    int i3 = sequence(hand+2,3);
    if (i3) return hand[2]*15*15 + hand[0]*15 + hand[1] ;
    return 0;
}
int twoPair( int * hand) {
    int i = sequence(hand,2);
    int i1 = sequence(hand+1,2);
    int i2 = sequence(hand+2,2);
    int i3 = sequence(hand+3,2);
    if ( i > 0 && i2 > 0) {
        return hand[0]*15*15 + hand[2]*15 + hand[4];
    }
    if ( i > 0 && i3 > 0) {
        return hand[0]*15*15 + hand[3]*15 + hand[2];
    }
    if ( i1 > 0 && i3 > 0) {
        return hand[1]*15*15 + hand[3]*15 + hand[0];
    }
    return 0;
}
int onePair( int * hand) {
    int i = sequence(hand,2);
    if (i) return hand[0]*15*15*15 + hand[2]*15*15 + hand[3]*15 + hand[4];
    i = sequence(hand+1,2);
    if ( i) return hand[1]*15*15*15+ hand[0]*15*15 + hand[3]*15 + hand[4];
    i = sequence(hand+2,2);
    if (i) return hand[2]*15*15*15+ hand[0]*15*15 + hand[1]*15 + hand[4];
    i = sequence(hand+3,2);
    if (i) return hand[3]*15*15*15+ hand[0]*15*15 + hand[1]*15 + hand[2];
    return 0;
}
int high( int * hand) {
    return hand[0]*15*15*15*15 + hand[1]*15*15*15 + hand[2]*15*15 + hand[3]*15 + hand[4];
}

int rank ( int* hand) {
    const int M = 15*15*15*15*15*15;
    int i = fiveOfAKind(hand);
    if ( i ) return M*10 + i;
    i = fourOfAKind(hand);
    if ( i ) return M*9 + i;
    i = fullHouse(hand);
    if ( i ) return M*8 + i;
    i = threeKind(hand);
    if ( i ) return M*7 + i;
    i = twoPair(hand);
    if ( i ) return M*6 + i;
    i = onePair(hand);
    if ( i ) return M*5 + i;
    i = high(hand);
    if ( i ) return M*4 + i;
    return 0;
}

int dumber_rank( int* hand ){
    int r= 0;
    for ( int i = 0; i < 5; ++i )
        r+=15*r + hand[i];
    return r;
}
int dumb_rank ( int* hand, int* uhand) {
    const int M = 15*15*15*15*15*15;
    int i = fiveOfAKind(hand);
    if ( i ) return M*10 + dumber_rank(uhand);
    i = fourOfAKind(hand);
    if ( i ) return M*9 + dumber_rank(uhand);
    i = fullHouse(hand);
    if ( i ) return M*8 + dumber_rank(uhand);
    i = threeKind(hand);
    if ( i ) return M*7 + dumber_rank(uhand);
    i = twoPair(hand);
    if ( i ) return M*6 + dumber_rank(uhand);
    i = onePair(hand);
    if ( i ) return M*5 + dumber_rank(uhand);
    i = high(hand);
    if ( i ) return M*4 + dumber_rank(uhand);
    return 0;
}

int main()
{
    FILE *file = fopen("data.txt", "r");
    char line[2560];



struct Node nodes[DIM2];
memset(nodes,-1,DIM2*sizeof(struct Node));
    //int hand[DIM];
    int hands[1000][DIM];
    memset( hands,-1,1000*DIM*sizeof(int));
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
        int hand[5] = {-1,-1,-1,-1,-1};
        int uhand[5] = {-1,-1,-1,-1,-1};
        int bid = 0;
        int n = -1;;
        //int* hand = hands[i];
        for ( char* pos = line ; (*pos)!='\0'; ++pos) {
            if ( *pos == ' ')
               mode = READ_BID;
            else if ( mode ==READ_HAND ) {
                if ( *pos <= '9' && *pos > '0' ) {
                    addhand(hand,uhand,*pos-'0');
                   }
                else if ( *pos == 'T' ) addhand(hand,uhand, 10);
                else if ( *pos == 'J' ) addhand(hand,uhand, 11);
                else if ( *pos == 'Q' ) addhand(hand,uhand, 12);
                else if ( *pos == 'K' ) addhand(hand,uhand, 13);
                else if ( *pos == 'A' ) addhand(hand,uhand, 14);                
            }
            else if ( mode== READ_BID ) {
                if ( *pos <= '9' && *pos >= '0' ) {
                    n=(n==-1?0:n)*10 + (*pos-'0');
                }
            }
        }

        //int calcRank = rank(hand);
        int calcRank = dumb_rank(hand,uhand);
        addrank(nodes,hand,uhand,calcRank,n,"");
    }
    int res = 0;
    for ( int i = 0; i < DIM2;  i++ ) {
        if ( nodes[i].rank==-1) break;
        res = res + nodes[i].bid*(i+1);
        printf("%d*%d+",nodes[i].bid,(i+1));
    }
    printf("=%d\n",res);

    for ( int i = 0; i < DIM2;  i++ ) {
        if ( nodes[i].rank==-1) break;
        for ( int j = 0; j < 5; ++j)
            printf("%d-",nodes[i].uhand[j]);
        printf(" (%d)", nodes[i].rank);
    }
    printf("\n");
    
    printf("%d\n",INT_MAX);
    printf("%d\n",15*15*15*15*15*15*10);

    return 0;
}
