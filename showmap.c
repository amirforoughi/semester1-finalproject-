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
    int n = 3 * n2 +2;
    int sum = score(head);
    printf("                                                    score = %d\n", sum);
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
                        printf("|       |_______");
                     }
                     // printf("I");
                        printf("\n");
                        continue;
            }

            if (i == n-1){
                printf("        |_______");
                     for(j=0;j<m-1;j++){
                        printf("|       |_______");
                     }
                      printf("|");
                        printf("\n");
                        continue;
            }
            if (i%3 == 1){
                     char s[8] = "       ";
                     char s2[8] = "keepout";
                     int perr=0;
                     //perr = function;
                     if( perr == 1)
                        strcpy( s , s2 );
                     for(j=0;j<m;j++){
                        printf("|%s|_______", s);
                     }
                      printf("|");
                        printf("\n");
            }
            if (i%3 == 2){
                     for(j=0;j<m;j++){
                        c=check_block(head , (n-2)/3 , (i+1)/3 , 2*j+1);
                        char X= check_blockX(map,(n-2)/3,(i+1)/3,2*j+1);
                        char Y;
                        char Z;
                        if( X == 'B'){
                            X=' ';Y=' ';Z=' ';
                        }
                        else if( X == 'c'){
                            X=' '; Y=5; Z=' ';
                        }
                        else if( X == 'b'){
                            X = 3505; Y=3505; Z =3505;
                        }
                        else if( X == 'A'){
                            X='0';Y=' ';Z=' ';
                        }
                        else{
                            Y= check_blockX(map,(n-2)/3,(i+1)/3,2*j+1);
                            if ( Y == '0'){
                                Z = '1';
                            }
                            else{
                                Z = ' ';
                            }

                        }
                        printf("|  %c %c%c%c|       ",c,Z,Y,X);

                     }
                      printf("|");
                        printf("\n");
            }
            if (i%3 == 0){
                     for(j=0;j<m;j++){
                        c=check_block(head ,  (n-2)/3  , (i+2)/3 , 2*j+2);

                        char X= check_blockX(map,(n-2)/3,(i+2)/3,2*j+2);
                        char Y;
                        char Z;
                        if( X == 'B'){
                            X= ' '; Y=' '; Z=' ';
                        }
                        else if( X == 'c'){
                            X=' '; Y=5; Z=' ';
                        }
                        else if( X == 'b'){
                            X = 3505; Y=3505; Z =3505;
                        }
                        else if( X == 'A'){
                            X='0';Y=' ';Z=' ';
                        }
                        else{
                            Y= check_blockX(map,(n-2)/3,(i+2)/3,2*j+2);
                            if ( Y == '0'){
                                Z = '1';
                            }
                            else{
                                Z = ' ';
                            }

                        }

                        printf("|_______|  %c %c%c%c",c,Z,Y,X);
                     }
                      printf("|");
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
    //SetColor(11);
    struct cell * current = head ;

    //struct cell * current2 = head ;
    //static int j = 0;
    int yp , xp = row-1;
    for( yp = n-column , xp = row-1 ; current != NULL  ; current = current->next ){
        if( current->x == xp && current->y == yp ){
            return 'X';
        }

    }
    return ' ';
}


char check_block2( struct cell * head , int n , int column , int row){
    //SetColor(11);
    struct cell * current = head ;

    //struct cell * current2 = head ;
    //static int j = 0;
    int yp , xp = row-1;
    for( yp = n-column , xp = row-1 ; current != NULL  ; current = current->next ){
        if( current->x == xp && current->y == yp ){
            return 'Y';
        }

    }
    return ' ';
}




char check_blockX( struct mapEl **map,int n ,int  column , int row){
    static int counter4 =0;
    int yp = n - column;
    int xp = row - 1;
    if(counter4 == 0){
        if( map[yp][xp].type >4 ){
           int i = (map[yp][xp].type)%10 ;
           char c = i + '0';
           //printf("%c",c);
           counter4++;
           return c;
        }
        else if( map[yp][xp].type == 0 ){
            counter4 = 0;
            return 'A';
        }
        else{
            counter4 = 0;
            if( map[yp][xp].type == 3){
                return 'b';
            }
            if( map[yp][xp].type == 2){
                return 'c';
            }
            return 'B';
        }
    }


   else if( counter4 == 1 ){

            int i = ( ( map[yp][xp].type - (  (map[yp][xp].type)%10) )/10 ) %10;
            if( i == 0 ){
                counter4 = 0;
                return '0';
            }
            counter4 = 0;
            char c = i + '0';
            return c;

    }
    //else
        //exit(-7);
}




void show_mainmenu(void){
    SetColor(12);
    printf("[1]Load\n");
    SetColor(5);
    printf("[2]New single player game\n");
    SetColor(11);
    printf("[3]New multiplayer game\n");
    SetColor(4);
    printf("[4]Exit\n");
}
void show_moveoptions(int dir1 , int dir2 , int dir3 , int dir4 , int dir5 , int dir6 ){
    if( dir1 == 1 ){
        SetColor(14);
        puts("[1]North");
    }
    else{
        SetColor(8);
        puts("[1]North");
    }
    if( dir2 == 1 ){
        SetColor(14);
        puts("[2]South");
    }
    else{
        SetColor(8);
        puts("[2]South");
    }
    if( dir3 == 1 ){
        SetColor(14);
        puts("[3]NorthEast");
    }
    else{
        SetColor(8);
        puts("[3]NorthEast");
    }
    if( dir4 == 1 ){
        SetColor(14);
        puts("[4]SouthEast");
    }
    else{
        SetColor(8);
        puts("[4]SouthEast");
    }
    if( dir5 == 1 ){
        SetColor(14);
        puts("[5]NorthWest");
    }
    else{
        SetColor(8);
        puts("[5]NorthWest");
    }
    if( dir6 == 1 ){
        SetColor(14);
        puts("[6]SouthWest");
    }
    else{
        SetColor(8);
        puts("[6]SouthWest");
    }
}
void printlistname(struct cell * head){
    struct cell * current =head;
    for(int i=0 ; current!=NULL ; current = current->next , i++){
        printf("i)%s\n",current->name);
    }
}
int score(struct cell * head ){
    struct cell *current = head;
    int sum=0;
    for( ; current != NULL ; current = current->next){
        //printf("%d\n",sum);
        sum = sum + current->energy ;
    }
    return sum;
}













void showMap2(int n2 , struct cell * head , struct cell * head2 , struct mapEl** map){
    char c;
    int n = 3 * n2 +2;
    int sum1 = score(head);
    int sum2 = score(head2);
    printf("                                                    score = %d\n", sum1);
    printf("                                                    score = %d\n", sum2);
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
                        printf("|       |_______");
                     }
                     // printf("I");
                        printf("\n");
                        continue;
            }

            if (i == n-1){
                printf("        |_______");
                     for(j=0;j<m-1;j++){
                        printf("|       |_______");
                     }
                      printf("|");
                        printf("\n");
                        continue;
            }
            if (i%3 == 1){
                     char s[8] = "       ";
                     char s2[8] = "keepout";
                     int perr=0;
                     //perr = function;
                     if( perr == 1)
                        strcpy( s , s2 );
                     for(j=0;j<m;j++){
                        printf("|%s|_______", s);
                     }
                      printf("|");
                        printf("\n");
            }
            if (i%3 == 2){
                     for(j=0;j<m;j++){
                        c=check_block(head , (n-2)/3 , (i+1)/3 , 2*j+1);
                        if( c != 'X'){
                            c = check_block2(head2,(n-2)/3 , (i+1)/3 , 2*j+1);
                            if( c != 'Y')
                                c=' ';
                        }
                        char X= check_blockX(map,(n-2)/3,(i+1)/3,2*j+1);
                        char Y;
                        char Z;
                        if( X == 'B'){
                            X=' ';Y=' ';Z=' ';
                        }
                        else if( X == 'c'){
                            X=' '; Y=5; Z=' ';
                        }
                        else if( X == 'b'){
                            X = 3505; Y=3505; Z =3505;
                        }
                        else if( X == 'A'){
                            X='0';Y=' ';Z=' ';
                        }
                        else{
                            Y= check_blockX(map,(n-2)/3,(i+1)/3,2*j+1);
                            if ( Y == '0'){
                                Z = '1';
                            }
                            else{
                                Z = ' ';
                            }

                        }
                        printf("|  %c %c%c%c|       ",c,Z,Y,X);

                     }
                      printf("|");
                        printf("\n");
            }
            if (i%3 == 0){
                     for(j=0;j<m;j++){
                        c=check_block(head ,  (n-2)/3  , (i+2)/3 , 2*j+2);
                        if( c != 'X'){
                            c = check_block2(head2,(n-2)/3 , (i+2)/3 , 2*j+2);
                            if( c != 'Y')
                                c=' ';
                        }
                        char X= check_blockX(map,(n-2)/3,(i+2)/3,2*j+2);
                        char Y;
                        char Z;
                        if( X == 'B'){
                            X= ' '; Y=' '; Z=' ';
                        }
                        else if( X == 'c'){
                            X=' '; Y=5; Z=' ';
                        }
                        else if( X == 'b'){
                            X = 3505; Y=3505; Z =3505;
                        }
                        else if( X == 'A'){
                            X='0';Y=' ';Z=' ';
                        }
                        else{
                            Y= check_blockX(map,(n-2)/3,(i+2)/3,2*j+2);
                            if ( Y == '0'){
                                Z = '1';
                            }
                            else{
                                Z = ' ';
                            }

                        }

                        printf("|_______|  %c %c%c%c",c,Z,Y,X);
                     }
                      printf("|");
                        printf("\n");
            }
        }
}


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
