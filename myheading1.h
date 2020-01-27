#define size 9
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
    struct cell* next = NULL;
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
int x_coor(int n);
int y_coor(int n);
struct mapEl** creat_map(int n);
