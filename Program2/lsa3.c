#include<stdio.h>
#include<stdlib.h>
#define inf 999
int spath(int,int);
int cost[10][10],n;


//for directed graph - fixed input


void main()
{
int i,j,min,s,d;
int ch;

printf("\n 1 - Auto input ");
printf("\n 2 - Manual input ");
printf("\n Enter choice :");
scanf("%d",&ch);

if(ch == 2)
{
printf("\n the number of nodes Ex:  5 )  \n");
scanf("%d",&n);


printf("\n enter the cost");


for(i=1;i<=n;i++)
{
 for(j=i;j<=n;j++)
  {
    if(i==j)   
    {         //same node - diagonal in cost matrix
       cost[i][j]=0 ;
       continue;  
    }   
       
     
    
   printf("\n Enter cost for edge %c -> %c :  ",i+64,j+64)  ; 
   scanf("%d",&cost[i][j]);
  

 }

}

 printf("\n  Enter the source node  1 )  ");
 s=1;
 scanf("%d",&s);

}  

 if(ch == 1 )
 {
   n=5;

  for(i=1;i<=n;i++)
   {
    for(j=1;j<=n;j++) 
    {
         cost[i][j]=999;     // initially no connection
         if(i==j)            //same node - diagonal in cost matrix
              cost[i][j]=0 ;
    }
  }



  cost[1][2]=10;   // un directed graph
  cost[1][4]=5;
  cost[2][3]=6;
  cost[2][5]=10;
  cost[3][4]=3;
  cost[3][5]=6;
  cost[4][5]=8;
  
  
   printf(" \n The source = 1 \n");
   s=1;
 }


 for(i=1;i<=n;i++)
   {
    for(j=1;j<=n;j++) 
    {
      if(i < j )
         cost[j][i] =  cost[i][j]  ;      // initially no connection
    }
    
    printf("\n"   ); 
  }


printf("The cost matrix is  : \n");

 for(i=1;i<=n;i++)
   {
    for(j=1;j<=n;j++) 
    {
        printf("%5d" ,   cost[i][j] );      // initially no connection
    }
    
    printf("\n"   ); 
  }
  
printf("\nsending hello packets \n");
for(i=1;i<=n;i++)
for(j=1;j<=n;j++)
{
if(cost[i][j]!=0 && cost[i][j]!=inf)
printf("\n sending hello packets from %d to %d node",i,j);
}
//sleep(2);
printf("\nsending echo packets");
for(i=1;i<=n;i++)
for(j=1;j<=n;j++)
{
if(cost[i][j]!=0 && cost[i][j]!=inf)
printf("sending echo packets from %d to %d node \n",i,j);
}
//sleep(2);
printf("constructing link state protocol");
for(i=1;i<=n;i++)
{printf("\n**** from  node = %d****\n",i);
for(j=1;j<=n;j++)
{
if(cost[i][j]!=0 && cost[i][j]!=inf)
printf("to node = %d--> cost = %d\n",j,cost[i][j]);
}
}

for(i=1;i<=n;i++)
{
min=spath(s,i);
printf("min path from %d to %d =%d\n",s,i,min);
}
}
int spath(int s,int d)
{
struct path{
int len;
enum{tentative,confirmed}label;
}state[10];
int i,u,j,num=2,min=inf;
for(i=1;i<=n;i++)
{
state[i].label=tentative;
state[i].len=cost[s][i];
}
state[s].label=confirmed;
while(num<=n)
{
min=inf;
for(i=1;i<=n;i++)
{
if(state[i].label==tentative && state[i].len<min)
{
min=state[i].len;
u=i;
}
}
state[u].label=confirmed;
num++;
for(j=1;j<=n;j++)
{
if(state[u].len + cost[u][j]<state[j].len && state[j].label==tentative)
{
state[j].len=state[u].len+cost[u][j];
}
}
}
return state[d].len;
}
