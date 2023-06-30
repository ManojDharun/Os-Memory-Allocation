#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
bool found(int,int[],int);
void firstfit(int,int,int*,int*,int*);
void worstfit(int,int,int*,int*,int*);
void bestfit(int,int,int*,int*,int*);
int main()
{
do{
int blocks,process,*arr,*arr1,*arr2;
int *block,*pr,i,j;
printf("ENTER THE NUMBER OF BLOCKS :\n");
scanf("%d",&blocks);
printf("ENTER THE BLOCKS :");
block = (int*)malloc(blocks*sizeof(int));
for(i=0;i<blocks;i++)
{
scanf("%d",&block[i]);
}
printf("ENTER THE NUMBER OF PROCESSES :\n");
scanf("%d",&process);
printf("ENTER THE PROCESSES :");
pr = (int*)malloc(process * sizeof(int));
arr = (int*)malloc(blocks * sizeof(int));
arr1 = (int*)malloc(blocks * sizeof(int));
arr2 = (int*)malloc(blocks * sizeof(int));
for(i=0;i<process;i++)
{
        arr[i] = -1;
}
for(i=0;i<process;i++)
{
scanf("%d",&pr[i]);
}
printf("\n-------MEMORY MANAGEMENT SCHEME ==> FIRST FIT---------------------\n");
firstfit(process,blocks,pr,block,arr);
        printf("\n-------MEMORY MANAGEMENT SCHEME ==> BEST FIT---------------------\n");
bestfit(process,blocks,pr,block,arr1);
printf("\n-------MEMORY MANAGEMENT SCHEME ==> WORST FIT---------------------\n");
worstfit(process,blocks,pr,block,arr2);
}while(0);
}

bool found(int n,int *arr,int process)
{
int i;
for(i=0;i<process;i++)
{
if(n == arr[i])
{
return true;
}
}
return false;
}

void bestfit(int process,int blocks,int *pr,int *block,int *arr)
{
        int s,min,i,j,k,s1 = 0,s2 = 0,s3=0,sum = 0;
        bool visited;
        for(i=0;i<blocks;i++)
        {
                arr[i] = -1;
        }
        for(i=0;i<process;i++)
        {
                min = 999;
                j = 0;
                k = -1;
                while(j<blocks)
                {
                        visited = found(j,arr,blocks);
                        if(block[j] >= pr[i] &&  min>block[j] && visited == false){
                                min = block[j];
                                k = j;
                        }
                        j++;
                }
                printf("\n%d\n",k);
                if(min!=999){
                        printf("BLOCK : %d  PROCESS :  %d\n",min,pr[i]);
                        s = min - pr[i];
                        s1 = s1 + s;
                }
                arr[i] = k;
                if(min == 999)
                {
                        printf("PROCESS %d CANNOT BE ALLOCATED",pr[i]);
                }
        }
        for(i=0;i<blocks;i++)
        {
                if(arr[i]!=-1){
                        s2 = s2 + block[arr[i]];
                }
                sum = sum + block[i];
        }
        s3 = sum - s2;
        printf("\nTOTAL INTERNAL FRAGMENTATION  %d\n",s1);
        printf("\nTOTAL EXTERNAL FRAGMENTATION  %d\n",s3);
}

void firstfit(int process,int blocks,int *pr,int *block,int *arr)
{
        int s,s1 = 0,s2 = 0;
        int i,j,count;
        bool visited;
        for(i=0;i<process;i++)
        {
                j = 0;
                count = 0;
                while(j<blocks)
                {
                        visited = found(j,arr,process);
                        if(block[j]>=pr[i] && visited == false)
                        {
                                printf("BLOCK : %d  PROCESS :  %d\n",block[j],pr[i]);
                                s = block[j] - pr[i];
                                s1 = s1 + s;
                                printf("\nREMAINING MEMORY  %d\n",s);
                                arr[i] = j;
                                count = 1;
                                break;
                        }
                        j++;
                }
                if(count == 0)
                {
                        printf("PROCESS %d NOT ALLOCATED\n",pr[i]);
                        s2 = s2 + block[i];
                }

        }
        printf("\nTOTAL INTERNAL FRAGMENTATION  %d\n",s1);
        printf("\n TOTAL EXTERNAL FRAGMENTATION %d\n",s2);
}

void worstfit(int process,int blocks,int *pr,int *block,int *arr)
{
        int s,maxi,count,k,i,j,s1 = 0,sum = 0,s2 = 0,s3 = 0;
        bool visited;
        for(i=0;i<blocks;i++)
        {
                arr[i] = -1;
        }
        for(i=0;i<process;i++)
        {
                visited = false;
                maxi = 0;
                j = 0;
                k = -1;
                while(j<blocks)
                {
                        visited = found(j,arr,blocks);
                        if(block[j] >= pr[i] &&  maxi<block[j] && visited == false){
                                maxi = block[j];
                                k = j;
                        }
                        j++;
                }
                if(maxi == 0)
                {
                        printf(" PROCESS : %d cannot be allocated\n",pr[i]);
                }
                printf("\n%d\n",k);
                printf("\nBLOCK : %d  PROCESS :  %d\n",maxi,pr[i]);
                s =  maxi - pr[i];
                s1 = s1 + s;
                arr[i] = k;
        }
        for(i=0;i<blocks;i++)
        {
                if(arr[i]!=-1){
                        s2 = s2 + block[arr[i]];
                }
                sum = sum + block[i];
        }
        s3 = sum - s2;
        printf("\nTOTAL INTERNAL FRAGMENTATION  %d\n",s1);
        printf("\nTOTAL EXTERNAL FRAGMENTATION  %d\n",s3);
}
