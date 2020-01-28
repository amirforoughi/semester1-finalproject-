/*
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include <dos.h>
#include <dir.h>
*/
#include"myheaders.h"
void SetColor(int ForgC)
 {
 WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
                 //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
}

/*struct mapEl** creat_map(int n){
    struct mapEl** map=(struct mapEl**)malloc( sizeof(mapEl*) * n );
    for(int i = 0 ; i < n ; i++){
        map[i]=(struct mapEl*)malloc( sizeof(mapEl) * n);
    }
    return map;
}*/

void showMap(int n2 , struct cell * head , struct mapEl** map){
    char c;
    int n =  int n = 3 * n2 +2;;
    /*
    if( n2 == 3)
        n = 11;
    if( n2 == 4)
        n = 14;
    if( n2 == 2)
        n = 8;
    if( n2 == 8)
        n = 26;
    */
    int i = 0 , j = 0 , k = n ;
    int m= (n-2)/6 ;

        for( i=0 ; i<n ; i++ ){
            if ( i == 0){
                    for(j=0;j<m;j++){
                        printf(" _______        ");
                    }

                        printf("\n");
                        continue;
            }
            if( i == 1){
                for(j=0;j<m;j++){
                        printf("I       I_______");
                     }
                     // printf("I");
                        printf("\n");
                        continue;
            }

            if (i == n-1){
                printf("        I_______");
                     for(j=0;j<m-1;j++){
                        printf("I       I_______");
                     }
                      printf("I");
                        printf("\n");
                        continue;
            }
            if (i%3 == 1){
                     for(j=0;j<m;j++){
                        printf("I       I_______");
                     }
                      printf("I");
                        printf("\n");
            }
            if (i%3 == 2){
                     for(j=0;j<m;j++){
                        c=check_block(head , (n-2)/3 , (i+1)/3 , 2*j+1);
                        printf("I  %c   0I       ",c);

                     }
                      printf("I");
                        printf("\n");
            }
            if (i%3 == 0){
                     for(j=0;j<m;j++){
                        c=check_block(head ,  (n-2)/3  , (i+2)/3 , 2*j+2);
                        printf("I_______I  %c   0",c);
                     }
                      printf("I");
                        printf("\n");
            }
        }
}
    /*   _________
        I         I_________
        I         I Player1 I
        I_________I double  I
        I  keep   I_________I
        I  out!!  I Player3 I int n = 3 * np +2;
        I_________I  E=100  I
                  I_________I
*/
// column does not have a zerro
char check_block( struct cell * head , int n , int column , int row){
    struct cell * current = head ;

    //struct cell * current2 = head ;
    static int j = 0;
    int yp , xp = row-1;
    for( yp = n-column , xp = row-1 ; current != NULL  ; current = current->next ){
        if( current->x == xp && current->y == yp ){
            return 'X';
        }

    }
    return ' ';
}


