



struct cell * creat_cellhead(char *namep, int xp , int yp , int energyp){
    struct cell * newhead = malloc( sizeof(struct cell) );
    cell->next = NULL;
    cell->x = xp ;
    cell->y = yp ;
    cell->energy = energyp;
    strcpy(cell->name,namep);
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
    for( ; current->next != NULL ; current = current->next );
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
char * rand_string(void) { // reserves a place for NULL
    char *str = malloc( (size+1) * sizeof(char) );
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for ( size_t i = 0 ; i < size ; i++ ) {
        int key = rand() % (sizeof(charset) / sizeof(char) - 1);
        str[i] = charset[key];
    }
    str[size] = '\0';
    return str;
}
int x_coor(int n){
    int i = rand() % n;
    return i;
}
int y_coor(int n){
    int i = rand() % n;
    return i;
}
void movecell(struct cell *head , int oldx , int oldy , int coor_number){
    struct cell * current = head;
    for(; current != NULL ; current = current->next){
        if( current->x == oldx && current->y == oldy )
            break;
    }
    if( current == NULL )
        exit(-2);
    switch(coor_number){
    case 1 :
        (current->y)++;
        break;
    case 2 :
        (current->y)--;
        break;
    case 3 :
        (current->y)++;
        (current->x)++;
        break;
    case 4 :
        (current->x)++;
        break;
    case 5 :
        (current->y)++;
        (current->x)--;
        break;

    case 6 :
        (current->x)--;
        break;
    }
}
int checkmove1( int xp , int yp , int n){
    int evalue_result;
        //do not want to make this function complicated
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
struct map_evalue checkcell(int xp , int yp , int locate , struct mapEl** map , int n ){
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
        return result;
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
        return result;
    }
     if( locate == 6 ){
        //because we know where it is and where can it go...
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
        return result;
    }
    if( locate == 8 ){
        //because we know where it is and where can it go...
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
        return result;
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
        return result;
    }
    if( locate == 7 ){
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
        return result;
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
        return result;
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
        return result;
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
        return result;
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
        return result;
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
            return result;
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
            return result;
        }
    }
    exit(-3);
}
struct map_evalue checksplit(struct cell * head , char * namep , int n , struct mapEl** map){
    struct cell * current = head;
    struct map_evalue result;
    for( ; current != NULL ; current = current->next ){
        if( strcmp(current->name,namep) == namep ){
            result=checkcell( current->x , current->y , checkmove1(current->x , current->y , n), map , n);
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
        exit(-4); else if( result.direct2 )
        return 2;
}







struct cell * split( struct cell * head , char * namep , int direct){

}
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







