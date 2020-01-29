#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include"myheaders.h"
int counter5 =1;
void printsplitname(struct cell * head , char * namep , struct mapEl **map , int n ){
    //static int counter5 = 1;
    int spltpermission = split_permission(namep,head,map);
    int spltcheck = checksplit(head,namep,n,map);
    if(spltpermission != 0  && spltcheck !=0 ){
        SetColor(14);
        printf(" [%d]%s\n",counter5,namep);
    }
    else{
        SetColor(8);
        printf(" [%d]%s\n",counter5,namep);
    }
    counter5++;
}

int main()
{
    //system(color(5));
    srand(time(0));
    int n=3,xp,yp;
    FILE *fpb1;
    fpb1 = fopen("test2.bin","rb");
    if(fpb1 == NULL)
        exit(8);
    fread(&n , sizeof(n) , 1 , fpb1);
    char *buff = malloc( n*n );
    fread( buff , n*n , 1 , fpb1);
    struct mapEl **map = creat_map(n);
    Mapinit(buff , n, map);
    char *rndname1=rand_string1();
    for( int i = 0; i == 0 ; ){
         xp= rand()%n ;
         yp= rand()%n ;
        if( map[yp][xp].type != 3)
            i=1;
    }
    struct cell * head = creat_cellhead(rndname1,xp,yp,0);
    SetColor(15);
    showMap(n,head,map);
    SetColor(13);
    //show_mainmenu();
    int input=0 ;
    int laterinput;
    int spltpermission;
    int spltcheck , source;
    struct cell * current2 = head;
    while(laterinput != 3){
        int count2=0 , count3=0;
        for( current2 = head ; current2 != NULL ; current2 = current2->next , count2++ ){
            spltpermission=split_permission( current2->name , head , map );
            if( spltpermission == 1){
                spltcheck = checksplit(head,current2->name,n,map);
                if( spltcheck != 0){
                    source = 1;
                    break;
                }
                else
                    source = 0;
            }
            else
                source = 0;
        }
        if( source != 0){
            SetColor(14);
            puts("[1]split\n[2]move");
        }
        else{
            SetColor(8);
            puts("[1]split");
            SetColor(14);
            puts("[2]move");
        }
       scanf("%d",&laterinput);
       if( laterinput == 1){
           for( current2 = head ; current2 != NULL ; current2 = current2->next){
                printsplitname(head , current2->name , map , n);
           }
           counter5 = 1;
           SetColor(15);
           showMap(n,head,map);
           int number;
           scanf( "%d", &number );
           struct cell * current = head;
           int counter = 1 ;
           while( counter < number ){
              current = current->next;
              counter++;
           }
           split(head , current->name , spltcheck , map);
           SetColor(15);
           showMap(n,head,map);

       }
       if( laterinput == 2){
            int permission;
            permission = checkmove1(head->x,head->y,n);
            if( permission == 0 ){
                puts("cant move");
            }
            struct map_evalue result ;
            int sum = checkcell(head->x , head->y , permission , map , n);
            SetColor(5);
            result.direct1 = sum%10; sum-=sum%10; sum/=10;
            result.direct2 = sum%10; sum-=sum%10; sum/=10;
            result.direct3 = sum%10; sum-=sum%10; sum/=10;
            result.direct4 = sum%10; sum-=sum%10; sum/=10;
            result.direct5 = sum%10; sum-=sum%10; sum/=10;
            result.direct6 = sum%10; sum-=sum%10; sum/=10;
            printf("which direction\n");
            SetColor(14);
            show_moveoptions(result.direct1 , result.direct2 , result.direct3 , result.direct4 , result.direct5 , result.direct6);
            scanf("%d",&input);
            movecell(head , head->x , head->y , input , map);
            SetColor(15);
            showMap(n,head,map);
            printf("Hello world!\n");
            SetColor(3);
       }
    }
        return 0;
}
/*
    if( result.direct1 )
        movecell(head , head->x , head->y , result.direct1 , map );
    else if( result.direct2 )
        movecell(head , head->x , head->y , result.direct2 , map );
    else if( result.direct3 )
        movecell(head , head->x , head->y , result.direct3 , map );
    else if( result.direct4 )
        movecell(head , head->x , head->y , result.direct4 , map );
    else if( result.direct5 )
        movecell(head , head->x , head->y , result.direct5 , map );
    else if( result.direct6 )
        movecell(head , head->x , head->y , result.direct6 , map );
    */
/*
    char rndname1[5]=rand_string();
    char rndname2[5]=rand_string();

BLACKif( dir1 == 1 )
        puts("[1]North");
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
