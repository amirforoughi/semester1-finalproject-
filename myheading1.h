#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include <dos.h>
#include <dir.h>
#define size 4
struct map_evalue{
    //these are the directions which cell can move
    int direct1;
    int direct2;
    int direct3;
    int direct4;
    int direct5;
    int direct6;
};
struct cell{
    char name[5];
    int energy;
    int x;
    int y;
    struct cell* next;
};
struct mapEl{
    //to know which of the 4 it is
    int type;
    //to know whether there is a cell in it or not
    int room;
};
void addend( struct cell* head , char * newname , int xp , int yp , int energyp );
struct cell* deletecell( struct cell * head , char * namep , int xp, int yp );
struct cell * creatcell(char *namep, int xp , int yp);
char *rand_string(void);
struct mapEl** creat_map(int n);
int energy_permission(char * name , struct cell * head , struct mapEl** map);
void SetColor(int ForgC);
void randomInit(struct cell * head , struct mapEl **map , int n );
char check_block( struct cell * head , int n , int column , int row);
void showMap(int n2 , struct cell * head , struct mapEl** map);
/*
int x_coor(int n);
int y_coor(int n);
*/
