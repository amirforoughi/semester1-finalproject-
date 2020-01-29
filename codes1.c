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
#include<time.h>
#include"myheaders.h"
#define size 4
/*
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
    char name[9];
    int energy;
    int x;
    int y;
    struct cell* next ;
};
struct mapEl{
    //to know which of the 4 it is
    int type;
    //to know whether there is a cell in it or not
    int room;
};

*/

struct mapEl** creat_map(int n){
    struct mapEl** map=(struct mapEl**)malloc( sizeof(struct mapEl*) * n );
    for(int i = 0 ; i < n ; i++){
        map[i]=(struct mapEl*)malloc( sizeof(struct mapEl) * n);
    }
    return map;
}
struct cell * creat_cellhead(char *namep, int xp , int yp , int energyp){
    struct cell * newhead =(struct cell*)malloc( sizeof(struct cell) );
    newhead->next = NULL;
    newhead->x = xp ;
    newhead->y = yp ;
    newhead->energy = energyp;
    strcpy(newhead->name,namep);
    return newhead;
}
void addend( struct cell* head , char * newname , int xp , int yp , int energyp){
    struct cell *newcell= malloc( sizeof(struct cell) );
    if( newcell == NULL ){
        exit(-1);
    }
    strcpy(newcell->name,newname);
    newcell->next = NULL;
    newcell->x = xp;
    newcell->y = yp;
    newcell->energy = energyp;
    struct cell * current = head ;
    for( ; current->next != NULL ;  ){
        current = current->next;
    }
    current->next = newcell ;
    return ;
}
struct cell* deletecell(struct cell * head , char * namep , int xp, int yp){
    struct cell *current = head;
    struct cell *prev = head;
    //if it is at the beginning
    if( strcmp(current->name,namep) == 0 ){
        head = current->next;
        return head;
    }
    //if it is at the middle
    for( ; current->next != NULL ; current = current->next ){
        if( strcmp(current->name,namep) == 0 ){
            prev->next = current->next;
            return head;
        }
        prev = current;
    }
    //what if it is at the end
    if( strcmp(current->name,namep)== 0 ){
        prev->next=NULL;
        return head;
    }
    else{
        printf("error");
        exit(-1);
    }
}
char * rand_string1(void) {
    static int differ = 1;// reserves a place for NULL
    srand(time(0));
   // printf("1-%d",rand());
    char *str = malloc( (size+1) * sizeof(char) );
    //printf("%s",str);
    const char charset[52] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for ( int  i = 0 ; i < size ; i++ ) {
        int key = (rand()*differ-2) % (sizeof(charset) / sizeof(char) - 1);
        str[i] = charset[key];
    }
    differ++;
    //printf("%s",str);
    str[size] = '\0';
    return str;
}


char * rand_string2(void) { // reserves a place for NULL
    srand(time(0));
    //printf("2-%d",rand());
    char *sbr = malloc( (size+1) * sizeof(char) );
    //printf("%s",str);
    const char charset[52] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for ( int  i = 0 ; i < size ; i++ ) {
        int key = (rand()*5/8+2) % (sizeof(charset) / sizeof(char) - 1);
        sbr[i] = charset[key];
    }
    //printf("%s",str);
    sbr[size] = '\0';
    return sbr;
}


void movecell(struct cell *head , int xp , int yp , int coor_number , struct mapEl **map){
    struct cell * current = head;
    map[yp][xp].room = 0;
    for(; current != NULL ; current = current->next){
        if( current->x == xp && current->y == yp )
            break;
    }
    if( current == NULL )
        exit(-2);
    if( xp%2 == 0){
        switch(coor_number){
        case 1 :
            (current->y)++;
            map[yp+1][xp].room = 1;
            break;
        case 2 :
            (current->y)--;
            map[yp-1][xp].room = 1;
            break;
        case 3 :
            (current->y)++;
            (current->x)++;
            map[yp+1][xp+1].room = 1;
            break;
        case 4 :
            (current->x)++;
            map[yp][xp+1].room = 1;
            break;
        case 5 :
            (current->y)++;
            (current->x)--;
            map[yp+1][xp-1].room = 1;
            break;

        case 6 :
            (current->x)--;
            map[yp][xp-1].room = 1;
            break;
        }
    }
    else{
        switch(coor_number){
        case 1 :
            (current->y)++;
            map[yp+1][xp].room = 1;
            break;
        case 2 :
            (current->y)--;
            map[yp-1][xp].room = 1;
            break;
        case 3 :
            //(current->y)++;
            (current->x)++;
            map[yp][xp+1].room = 1;
            break;
        case 4 :
            (current->y)--;
            (current->x)++;
            map[yp-1][xp+1].room = 1;
            break;
        case 5 :
            //(current->y)++;
            (current->x)--;
            map[yp][xp-1].room = 1;
            break;

        case 6 :
            (current->y)--;
            (current->x)--;
            map[yp-1][xp-1].room = 1;
            break;
        }

    }
  //  printf("function moveccell done");
}
int checkmove1( int xp , int yp , int n){
    int evalue_result;
        //do not want to make this function complicated thats why I use checkmove2 and checkmove3
    if(xp == 0){
        evalue_result = checkmove2( xp , yp , n );
        return evalue_result;
    }
    else if(xp == n-1){
        evalue_result = checkmove3( xp , yp , n );
        return evalue_result;
    }
    else{
        //what if it is at the bottom
        if( yp == 0 ){
            if( xp%2 == 0 ){
                return 9;
            }
            else{
                return 10;
            }
        }
        //what if it is at the top
        else if( yp == n-1 ){
                if( xp%2 == 0 ){

                    return 5;
                }
                else{
                    return 4;
                }
        }
        //what if it is in the middle;
        else{
            return 11;
        }
    }
}

int checkmove2(int xp, int yp , int n){
    // what if x is 0 and y is 0
    if( yp == 0 ){
        return 1;
    }
    // what if x is 0 and y is n-1
    else if( yp == n-1 ){
        return 3;
    }
    // what if x is 0 and y is not both of them
    else{
        return 2;
    }
}
int checkmove3(int xp, int yp , int n){
    // what if x is n-1 and y is 0
    if( yp == 0 ){
        return 8;
    }
    // what if x is n-1 and y is n-1
    else if( yp == n-1 ){
        return 6;
    }
    // what if x is n-1 and y is not both of them
    else{
        return 7;
    }
}
   // sum=result.direct1+result.direct2*10+result.direct3*100+result.direct4*1000+result.direct5*10000+result.direct6*100000;

int   checkcell(int xp , int yp , int locate , struct mapEl** map , int n ){
    int sum=0;
    struct map_evalue result;
    if( locate == 1 ){
        //because we know where it is and where can it go...
        result.direct1 = 1;
        result.direct2 = 0;
        result.direct3 = 1;
        result.direct4 = 1;
        result.direct5 = 0;
        result.direct6 = 0;
        //if there are cells in other locations
        if( map[0][1].room == 1 ){
            result.direct4 = 0;
        }
        if( map[1][1].room == 1 ){
            result.direct3 = 0;
        }
        if( map[1][0].room == 1 ){
            result.direct1 = 0;
        }
        //what if it is forbidden
        if( map[0][1].type == 3){
            result.direct4=0;
        }
        if( map[1][1].type == 3){
            result.direct3=0;
        }
        if( map[1][0].type == 3){
            result.direct1=0;
        }
        ///return result;
        sum=result.direct1+result.direct2*10+result.direct3*100+result.direct4*1000+result.direct5*10000+result.direct6*100000;
        return sum;
    }
    if( locate == 3 ){
        //because we know where it is and where can it go...
        result.direct1 = 0;
        result.direct2 = 1;
        result.direct3 = 0;
        result.direct4 = 1;
        result.direct5 = 0;
        result.direct6 = 0;
        //if there are cells in other locations
        if( map[n-1][1].room == 1 ){
            result.direct4 = 0;
        }
        if( map[n-2][0].room == 1 ){
            result.direct2 = 0;
        }
        //what if it is forbidden
        if( map[n-1][1].type == 3){
            result.direct4 = 0;
        }
        if( map[n-2][0].type == 3){
            result.direct2 = 0;
        }
        ///return result;
        sum=result.direct1+result.direct2*10+result.direct3*100+result.direct4*1000+result.direct5*10000+result.direct6*100000;
    }
     if( locate == 6 ){
        //because we know where it is and where can it go...
		if( n%2 ==0 ){
			result.direct1 = 0;
			result.direct2 = 1;
			result.direct3 = 0;
			result.direct4 = 0;
			result.direct5 = 1;
			result.direct6 = 1;
			//if there are cells in other locations
			if( map[n-2][n-1].room == 1 ){
				result.direct2 = 0;
			}
			if( map[n-2][n-2].room == 1 ){
				result.direct6 = 0;
			}
			if( map[n-1][n-2].room == 1 ){
				result.direct5 = 0;
			}
			//what if it is forbidden
			if( map[n-2][n-1].type == 3){
				result.direct2 = 0;
			}
			if( map[n-2][n-2].type == 3){
				result.direct6 = 0;
			}
			if( map[n-1][n-2].type == 3){
				result.direct5 = 0;
			}
			///return result;
			sum=result.direct1+result.direct2*10+result.direct3*100+result.direct4*1000+result.direct5*10000+result.direct6*100000;
			return sum;
		}

		else{
			result.direct1 = 0;
			result.direct2 = 1;
			result.direct3 = 0;
			result.direct4 = 0;
			result.direct5 = 0;
			result.direct6 = 1;
			//considering full places
			if( map[yp-1][xp].room == 1 ){
				result.direct2 = 0;
			}
			if( map[yp][xp-1].room == 1 ){
				result.direct6 = 0;
			}
			//forbidden places
			if( map[yp-1][xp].type == 3 ){
				result.direct2 = 0;
			}
			if( map[yp][xp-1].type == 3 ){
				result.direct6 = 0;
			}
			sum=result.direct1+result.direct2*10+result.direct3*100+result.direct4*1000+result.direct5*10000+result.direct6*100000;
			return sum;
		}
	}
    if( locate == 8 ){
		if( n%2 == 0 ){
			//because we know where it is and where can it go without considering the probable exceptions ...
			result.direct1 = 1;
			result.direct2 = 0;
			result.direct3 = 0;
			result.direct4 = 0;
			result.direct5 = 1;
			result.direct6 = 0;
			//if there are cells in other locations
			if( map[0][n-2].room == 1 ){
				result.direct5 = 0;
			}
			if( map[1][n-1].room == 1 ){
				result.direct1 = 0;
			}
			//what if it is forbidden
			if( map[0][n-2].type == 3){
				result.direct5 = 0;
			}
			if( map[1][n-1].type == 3){
				result.direct1 = 0;
			}
			///return result;
			sum=result.direct1+result.direct2*10+result.direct3*100+result.direct4*1000+result.direct5*10000+result.direct6*100000;
			return sum;
		}
		else{
			result.direct1 = 1;
			result.direct2 = 0;
			result.direct3 = 0;
			result.direct4 = 0;
			result.direct5 = 1;
			result.direct6 = 1;
			//considering full rooms
			if( map[yp+1][xp].room == 1 ){
				result.direct1 = 0;
			}
			if( map[yp+1][xp-1].room == 1 ){
				result.direct5 = 0;
			}
			if( map[yp][xp-1].room == 1 ){
				result.direct6 = 0;
			}
			//forbidden places
			if( map[yp+1][xp].type == 3 ){
				result.direct1 = 0;
			}
			if( map[yp+1][xp-1].type == 3 ){
				result.direct5 = 0;
			}
			if( map[yp][xp-1].type == 3 ){
				result.direct6 = 0;
			}
			sum=result.direct1+result.direct2*10+result.direct3*100+result.direct4*1000+result.direct5*10000+result.direct6*100000;
			return sum;
		}
	}
//same thing I do for the rest
    if( locate == 2 ){
        result.direct1 = 1;
        result.direct2 = 1;
        result.direct3 = 1;
        result.direct4 = 1;
        result.direct5 = 0;
        result.direct6 = 0;
        //there are cells
        if( map[yp+1][xp].room == 1 ){
            result.direct1 = 0;
        }
        if( map[yp-1][xp].room == 1 ){
            result.direct2 = 0;
        }
        if( map[yp+1][xp+1].room == 1 ){
            result.direct3 = 0;
        }
        if( map[yp][xp+1].room == 1 ){
            result.direct4 = 0;
        }
        //forbidden places
        if( map[yp+1][xp].type == 3 ){
            result.direct1 = 0;
        }
        if( map[yp-1][xp].type == 3){
            result.direct2 = 0;
        }
        if( map[yp+1][xp+1].type == 3 ){
            result.direct3 = 0;
        }
        if( map[yp][xp+1].type == 3 ){
            result.direct4 = 0;
        }
       /// return result;
       sum=result.direct1+result.direct2*10+result.direct3*100+result.direct4*1000+result.direct5*10000+result.direct6*100000;
       return sum;
    }
    if( locate == 7 ){

		if( n%2 == 0 ){
			result.direct1 = 1;
			result.direct2 = 1;
			result.direct3 = 0;
			result.direct4 = 0;
			result.direct5 = 1;
			result.direct6 = 1;
			//there are cells
			if( map[yp+1][xp].room == 1 ){
				result.direct1 = 0;
			}
			if( map[yp-1][xp].room == 1 ){
				result.direct2 = 0;
			}
			if( map[yp-1][xp-1].room == 1 ){
				result.direct6 = 0;
			}
			if( map[yp][xp-1].room == 1 ){
				result.direct5 = 0;
			}
			//forbidden places
			if( map[yp+1][xp].type == 3 ){
				result.direct1 = 0;
			}
			if( map[yp-1][xp].type == 3){
				result.direct2 = 0;
			}
			if( map[yp-1][xp-1].type == 3 ){
				result.direct3 = 0;
			}
			if( map[yp][xp-1].type == 3 ){
				result.direct4 = 0;
			}
			sum=result.direct1+result.direct2*10+result.direct3*100+result.direct4*1000+result.direct5*10000+result.direct6*100000;
			return sum;
		}

		else{
			result.direct1 = 1;
			result.direct2 = 1;
			result.direct3 = 0;
			result.direct4 = 0;
			result.direct5 = 1;
			result.direct6 = 1;
			//there are cells
			if( map[yp+1][xp].room == 1 ){
				result.direct1 = 0;
			}
			if( map[yp-1][xp].room == 1 ){
				result.direct2 = 0;
			}
			if( map[yp+1][xp-1].room == 1 ){
				result.direct5 = 0;
			}
			if( map[yp][xp-1].room == 1 ){
				result.direct6 = 0;
			}
			//forbidden places
			if( map[yp+1][xp].type == 3 ){
				result.direct1 = 0;
			}
			if( map[yp-1][xp].type == 3 ){
				result.direct2 = 0;
			}
			if( map[yp+1][xp-1].type == 3 ){
				result.direct5 = 0;
			}
			if( map[yp][xp-1].type == 3 ){
				result.direct6 = 0;
			}
			sum=result.direct1+result.direct2*10+result.direct3*100+result.direct4*1000+result.direct5*10000+result.direct6*100000;
			return sum;
		}
    }
    if( locate == 10 ){
        result.direct1 = 1;
        result.direct2 = 0;
        result.direct3 = 1;
        result.direct4 = 0;
        result.direct5 = 1;
        result.direct6 = 0;
        if( map[yp+1][xp].room == 1){
            result.direct1 = 0;
        }
        if( map[yp][xp+1].room == 1){
            result.direct3 = 0;
        }
        if( map[yp][xp-1].room == 1){
            result.direct5=0;
        }
        //what if it is forbidden
        if( map[yp+1][xp].type == 3){
            result.direct1 = 0;
        }
        if( map[yp][xp+1].type == 3){
            result.direct3 = 0;
        }
        if( map[yp][xp-1].type == 3){
            result.direct5=0;
        }
        sum=result.direct1+result.direct2*10+result.direct3*100+result.direct4*1000+result.direct5*10000+result.direct6*100000;
        return sum;
    }
    if( locate == 5 ){
        result.direct1 = 0;
        result.direct2 = 1;
        result.direct3 = 0;
        result.direct4 = 1;
        result.direct5 = 0;
        result.direct6 = 1;
        if( map[yp-1][xp].room == 1){
            result.direct2 = 0;
        }
        if( map[yp][xp+1].room == 1){
            result.direct4 = 0;
        }
        if( map[yp][xp-1].room == 1){
            result.direct6=0;
        }
        //what if it is forbidden
        if( map[yp-1][xp].type == 3){
            result.direct2 = 0;
        }
        if( map[yp][xp+1].type == 3){
            result.direct4 = 0;
        }
        if( map[yp][xp-1].type == 3){
            result.direct6=0;
        }
        sum=result.direct1+result.direct2*10+result.direct3*100+result.direct4*1000+result.direct5*10000+result.direct6*100000;
        return sum;
    }
    if( locate == 9){
        result.direct1 = 1;
        result.direct2 = 0;
        result.direct3 = 1;
        result.direct4 = 1;
        result.direct5 = 1;
        result.direct6 = 1;
        if( map[yp+1][xp].room == 1){
            result.direct1 = 0;
        }
        if( map[yp+1][xp+1].room == 1){
            result.direct3 = 0;
        }
        if( map[yp+1][xp-1].room == 1){
            result.direct5 = 0;
        }
        if( map[yp][xp+1].room == 1){
            result.direct4 = 0;
        }
        if( map[yp][xp-1].room == 1 ){
            result.direct6 = 0;
        }
        //what if it is forbidden
        if( map[yp+1][xp].type == 3){
            result.direct1 = 0;
        }
        if( map[yp+1][xp+1].type == 3){
            result.direct3 = 0;
        }
        if( map[yp+1][xp-1].type == 3){
            result.direct5 = 0;
        }
        if( map[yp][xp+1].type == 3){
            result.direct4 = 0;
        }
        if( map[yp][xp-1].type == 3 ){
            result.direct6 = 0;
        }
        sum=result.direct1+result.direct2*10+result.direct3*100+result.direct4*1000+result.direct5*10000+result.direct6*100000;
        return sum;
    }
    if( locate == 4){
        result.direct1 = 0;
        result.direct2 = 1;
        result.direct3 = 1;
        result.direct4 = 1;
        result.direct5 = 1;
        result.direct6 = 1;
        if( map[yp-1][xp].room == 1){
            result.direct2 = 0;
        }
        if( map[yp][xp+1].room == 1){
            result.direct3 = 0;
        }
        if( map[yp][xp-1].room == 1){
            result.direct5 = 0;
        }
        if( map[yp-1][xp+1].room == 1){
            result.direct4 = 0;
        }
        if( map[yp-1][xp-1].room == 1 ){
            result.direct6 = 0;
        }
        //what if it is forbidden
        if( map[yp-1][xp].type == 3){
            result.direct2 = 0;
        }
        if( map[yp][xp+1].type == 3){
            result.direct3 = 0;
        }
        if( map[yp][xp-1].type == 3){
            result.direct5 = 0;
        }
        if( map[yp-1][xp+1].type == 3){
            result.direct4 = 0;
        }
        if( map[yp-1][xp-1].type == 3 ){
            result.direct6 = 0;
        }
        sum=result.direct1+result.direct2*10+result.direct3*100+result.direct4*1000+result.direct5*10000+result.direct6*100000;
        return sum;
    }
    if( locate == 11 ){
        //what if it is at the middle with even x
        if( xp%2 == 0 ){
            //empty place checking
            result.direct1=1;
            result.direct2=1;
            result.direct3=1;
            result.direct4=1;
            result.direct5=1;
            result.direct6=1;
            if( map[yp+1][xp].room == 1 ){
                result.direct1=0;
            }
            if( map[yp-1][xp].room == 1 ){
                result.direct2=0;
            }
            if( map[yp+1][xp+1].room == 1 ){
                result.direct3=0;
            }
            if( map[yp][xp+1].room == 1 ){
                result.direct4=0;
            }
            if( map[yp+1][xp-1].room == 1 ){
                result.direct5=0;
            }
            if( map[yp][xp-1].room == 1 ){
                result.direct6=0;
            }
            //forbidden checking
            if( map[yp+1][xp].type == 3 ){
                result.direct1=0;
            }
            if( map[yp-1][xp].type == 3 ){
                result.direct2=0;
            }
            if( map[yp+1][xp+1].type == 3 ){
                result.direct3=0;
            }
            if( map[yp][xp+1].type == 3 ){
                result.direct4=0;
            }
            if( map[yp+1][xp-1].type == 3 ){
                result.direct5=0;
            }
            if( map[yp][xp-1].type == 3 ){
                result.direct6=0;
            }
            sum=result.direct1+result.direct2*10+result.direct3*100+result.direct4*1000+result.direct5*10000+result.direct6*100000;
            return sum;
        }
        //what if it is at the middle with odd x
        else{
            result.direct1=1;
            result.direct2=1;
            result.direct3=1;
            result.direct4=1;
            result.direct5=1;
            result.direct6=1;
            if( map[yp+1][xp].room == 1 ){
                result.direct1=0;
            }
            if( map[yp-1][xp].room == 1 ){
                result.direct2=0;
            }
            if( map[yp][xp+1].room == 1 ){
                result.direct3=0;
            }
            if( map[yp-1][xp+1].room == 1 ){
                result.direct4=0;
            }
            if( map[yp][xp-1].room == 1 ){
                result.direct5=0;
            }
            if( map[yp-1][xp-1].room == 1 ){
                result.direct6=0;
            }
            //forbidden checking
            if( map[yp+1][xp].type == 3 ){
                result.direct1=0;
            }
            if( map[yp-1][xp].type == 3 ){
                result.direct2=0;
            }
            if( map[yp][xp+1].type == 3 ){
                result.direct3=0;
            }
            if( map[yp-1][xp+1].type == 3 ){
                result.direct4=0;
            }
            if( map[yp][xp-1].type == 3 ){
                result.direct5=0;
            }
            if( map[yp-1][xp-1].type == 3 ){
                result.direct6=0;
            }
            sum=result.direct1+result.direct2*10+result.direct3*100+result.direct4*1000+result.direct5*10000+result.direct6*100000;
            return sum;
        }
    }
    exit(-3);
}
int split_permission(char * namep , struct cell * head , struct mapEl **map){
    struct cell * current = head ;
    for( ;current != NULL  ; current = current->next ){
        if( strcmp( current->name , namep ) == 0 ){
            break;
        }
    }
    if(  map[current->y][current->x].type == 2 && current->energy > 80){
        return 1;
    }
    else
        return 0;
}
int energy_permission(char * namep , struct cell * head , struct mapEl **map){
    struct cell * current = head ;
    for( ;current != NULL  ; current = current->next ){
        if( strcmp( current->name , namep ) == 0 ){
            break;
        }
    }
     //if it is an energy place
     if(  map[current->y][current->x].type > 4 ){
             //if energy is more than 15
            if(   map[current->y][current->x].type > 15  ){
                 (map[current->y][current->x].type) -= 15;
                    return 1;
            }
             //if energy is less than 15
            else{
                    int hold = map[current->y][current->x].type;
                    map[current->y][current->x].type = 0;
                    return hold;
            }
     }
     //if it is not an energy place
    else
        return 0;
}
int  checksplit(struct cell * head , char * namep , int n , struct mapEl** map){
    struct cell * current = head;
    struct map_evalue result;
    int sum=0;
    for( ; current != NULL ; current = current->next ){
        if( strcmp(current->name,namep) == 0 ){
           sum=checkcell( current->x , current->y , checkmove1(current->x , current->y , n), map , n);

            result.direct1 = sum%10; sum-=sum%10; sum/=10;
            result.direct2 = sum%10; sum-=sum%10; sum/=10;
            result.direct3 = sum%10; sum-=sum%10; sum/=10;
            result.direct4 = sum%10; sum-=sum%10; sum/=10;
            result.direct5 = sum%10; sum-=sum%10; sum/=10;
            result.direct6 = sum%10; sum-=sum%10; sum/=10;
            break;
        }
    }
    //can be changed to anything e.g making places random
    if( result.direct1 )
        return 1;
    else if( result.direct2 )
        return 2;
    else if( result.direct3 )
        return 3;
    else if( result.direct4 )
        return 4;
    else if( result.direct5 )
        return 5;
    else if( result.direct6 )
        return 6;
    else
        return 0;
}
void split( struct cell * head , char * namep , int direct , struct mapEl **map){
	char * randName1 , * randName2 ;
	srand(time(0));
	randName1=rand_string1();
	struct cell * current = head ;
	for( ; current != NULL ; current = current->next ){
		if( strcmp( current->name , namep ) == 0 )
			break;
	}

	randName2=rand_string2();
	//printf("%s",randName1);
	//printf("%s",randName2);
	//printf("random-> %d",rand());
	//printf("random-> %d",rand());
	int xp = current->x;
	int yp = current->y;
	strcpy(current->name , randName1 );
	//addend( head , randName1 , xp , yp , 40 );
    //head = deletecell(head , namep , current->x , current->y);
    //puts("reached");
   // addend( head , randName1 , xp , yp , 40 );
    if( direct == 1 ){
        addend( head , randName2 , xp , yp+1 , 40 );
        map[yp+1][xp].room = 1;
    }
    else if( direct == 2 ){
        addend( head , randName2 , xp , yp-1 , 40 );
        map[yp-1][xp].room = 1;
    }
    else{
        if( xp%2 == 0 ){
            if( direct == 3 ){
                addend( head , randName2 , xp+1 , yp+1 , 40 );
                map[yp+1][xp+1].room = 1;
            }
            else if( direct == 4 ){
                addend( head , randName2 , xp+1 , yp , 40 );
                map[yp][xp+1].room = 1;
            }
            else if( direct == 5 ){
                addend( head , randName2 , xp-1 , yp+1 , 40 );
                map[yp+1][xp-1].room = 1;
            }
            else if( direct == 6 ){
                addend( head , randName2 , xp-1 , yp , 40 );
                map[yp][xp-1].room = 1;
            }
        }
        else{
            if( direct == 3 ){
                addend( head , randName2 , xp+1 , yp , 40 );
                map[yp][xp+1].room = 1;
            }
            else if( direct == 4 ){
                addend( head , randName2 , xp+1 , yp-1 , 40 );
                map[yp-1][xp+1].room = 1;
            }
            else if( direct == 5 ){
                addend( head , randName2 , xp-1 , yp , 40 );
                map[yp][xp-1].room = 1;
            }
            else if( direct == 6 ){
                addend( head , randName2 , xp-1 , yp-1 , 40 );
                map[yp-1][xp-1].room = 1;
            }
        }
    }
    return head;
}



void get_energy( struct cell * head , int permission , char * namep ){
    struct cell * current = head;
    for( ; current != NULL ; current = current ->next ){
        if( strcmp( current->name , namep ) == 0 ){
            break;
        }
    }
    if( current == NULL )
        exit(-5);
    if( permission == 0 )
        return;
    else if( permission == 1 ){
        (current->energy) += 15;
        return;
    }
    else{
        (current->energy) += permission;
        return;
    }
}
void randomInit(struct cell * head , struct mapEl **map , int n ){
    srand(time(0));
    struct cell * current ;
    int holdx;
    int holdy;
    for( current = head ; current != NULL ; ){
        holdx = rand()%n;
        holdy = rand()%n;
        if( map[holdy][holdx].type != 3 && map[holdy][holdx].room != 1 ){
            map[holdy][holdx].room = 1;
            current->x = holdx;
            current->y = holdy;
            current = current->next;
        }
    }
}
void temp_emptyMapInit(struct mapEl **map , int n){
    int i , j ;
    for( i=0 ; i<n ; i++ ){
        for( j=0;j<n;j++){
            map[i][j].type=4;
            map[i][j].room=0;
        }
    }
}
void temp_addend( struct cell * head ){
    struct cell * current = head;
    for(int  i=0 ; i<3 ; current = current->next , i++){
        if( current->next == NULL ){
            char * rndname=rand_string1();
            current->next = malloc( sizeof( struct cell ) );
            current = current->next ;
            current->next = NULL;
            strcpy( current->name , rndname );
            current = head;
        }
    }
    return;
}
void Mapinit(char * buff , int n , struct mapEl **map){
    int k = 0;
    for( int i=0 ; i<n ; i++ ){
        for( int j=0 ; j<n && k<n*n ; j++ ){
            if( buff[k] == '1'){
                map[i][j].type = 100;
                map[i][j].room = 0;
            }
            else{
                map[i][j].type = buff[k] - '0';
                map[i][j].room = 0;
            }
            k++;
        }
    }
}

/*
char * rand_number(void){

}
*/


/*
DUPLICATED
int x_coor(int n){
    int i = rand() % n;
    return i;
}
int y_coor(int n){
    int i = rand() % n;
    return i;
}
*/
/*
struct cell * slpit(struct cell *head , char *namep , int xp , int yp , int n){
    struct cell * current = head;
    char *randName1,*randName2;
    randName1=rand_string();
    randName2=rand_string();
    int evalue_result = checkmove1( xp , yp , n );
    if( strcmp(current->name,namep) == 0 ){
        switch(evalue_result){
        case 1 :
            addend(head , randName1 , 1 , 1 , 40);
            addend(head , randName1 , 0 , 1 , 40);
            head=deletecell( head , current->name , current->x , current->y );
            break;
        case 2 :

        }
    }
}
*/
/*
int energy_permission(char * namep , struct cell * head , struct mapEl **map){
    struct cell * current = head ;
    for( ;current != NULL  ; current = current->next ){
        if( strcmp( current->name , namep ) == 0 ){
            break;
        }
    }
     //if it is an energy place
     if(  map[current->y][current->x].type > 4 ){
             //if energy is more than 15
            if(   map[current->y][current->x].type > 15  ){
                    return 1;
                 ///(map[current->y][current->x].type) -= 15;
            }
             //if energy is less than 15
            else{
                /// map[current->y][current->x].type = 0;
                    return 2;
            }
     }
     //if it is not an energy place
    else
        return 0;
}
*/








