#include<stdio.h>
#include <string.h>
#define D (1000)
void a(int*a,int b){for(int i=0;i<D;++i){if(a[i]==-1){a[i]=b;break;}}}
int main(){FILE*f=fopen("data.txt","r");char l[2560];int s=0,t=0;while(fgets(l,sizeof(l),f)){int m[D],o[D],n=0,c=0;memset(m,-1,D);memset(o,-1,D);for(int i=0;i<strlen(l);++i){if(l[i]==':'){c=n;t=1;n=0;}else if(l[i]=='|'){t=2;n=0;}else if(l[i]>='0'&&l[i]<='9'){n=n*10+(l[i]-'0');}else if(n>0){if(t==1)a(m,n);else if(t==2)a(o,n);n=0;}if(l[i]=='\0')break;}int sc=0;for(int i=0;m[i]!=-1;++i)for(int j=0;o[j]!=-1;++j)if(o[j]==m[i])sc=(sc==0?1:sc*2);s+=sc;}printf("Sum: %d\n",s);}
