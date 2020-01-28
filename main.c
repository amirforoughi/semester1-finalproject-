#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include"myheaders.h"

int main()
{
    int n=4,xp,yp;
    FILE *fpb1;
    srand(time(0));
    fpb1 = fopen("test2.bin","rb");
    fread(&n , sizeof(n) , 1 , fpb1);
    char *buff = malloc( n*n );
    fread(*buff , n*n , 1 , fpb1);
    struct mapEl **map = creat_map(n);
    Mapinit(buff , n, map);
    char *rndname1=rand_string();
    for( int i = 0; i == 0 ; ){
         xp= rand()%n ;
         yp= rand()%n ;
        if( map[yp][xp].type != 3)
            i=1;
    }
    //for(int i=0;i<5;i++)
        //printf("%s",rndname1);
    struct cell * head = creat_cellhead(rndname1,xp,yp,0);
    //temp_addend(head);
    //randomInit(head,map,n);
    showMap(n,head,map);
    SetColor(13);
    printf("Hello world!\n");
    SetColor(14);
    return 0;
}
/*
    char rndname1[5]=rand_string();
    char rndname2[5]=rand_string();

BLACK
0

BLUE
1

GREEN
2

CYAN
3

RED
4

MAGENTA
5

BROWN
6

LIGHTGRAY
7

DARKGRAY
8

LIGHTBLUE
9

LIGHTGREEN
10

LIGHTCYAN
11

LIGHTRED
12

LIGHTMAGENTA
13

YELLOW
14

WHITE
15

















printf("x=%d y=%d\n",head->x,head->y);
    printf("x=%d y=%d\n",head->next->x,head->next->y);
    printf("x=%d y=%d\n",head->next->next->x,head->next->next->y);
    printf("map = %d",map[head->y][head->x].room);

printf("x=%d y=%d\n",head->x,head->y);
    printf("x=%d y=%d\n",head->next->x,head->next->y);
    printf("x=%d y=%d\n",head->next->next->x,head->next->next->y);
    printf("map = %d",map[head->y][head->x].room);
*/
