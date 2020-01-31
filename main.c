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
    show_mainmenu();
    int laterlateinput;
    int loadNumber = 0;
    scanf("%d",&laterlateinput);
    if(laterlateinput == 1){
        Beep(1000,50); // 523 hertz (C5) for 500 milliseconds
        SetColor(14);//make yellow
        puts("which type would you want to load?\n[1]single player\n[2]multiplayer");
        scanf("%d",&loadNumber);
        SetColor(15);//make white
        if(loadNumber == 1){
            laterlateinput=2;
        }
        else{
            laterlateinput=3;
        }
    }
    if(laterlateinput == 2){//////////
    int n=3,xp,yp;
    FILE *fpb1;
    fpb1 = fopen("test2.bin","rb");//*
    if(fpb1 == NULL)
        exit(8);
    fread(&n , sizeof(n) , 1 , fpb1);
    //n=3;///
    char *buff = malloc( n*n );
    fread( buff , n*n , 1 , fpb1);
    struct mapEl **map = creat_map(n);
    Mapinit(buff , n, map);
    char *rndname1=rand_string1();
    fclose(fpb1);
    for( int i = 0; i == 0 ; ){
         xp= rand()%n ;
         yp= rand()%n ;
        if( xp == 0 && yp == n-1)
            continue;
        if( map[yp][xp].type != 3)
            i=1;
    }
    struct cell * head = creat_cellhead(rndname1,xp,yp,0);//*
    if( loadNumber == 1){
        FILE *fp1 ,*fp2 , *fpb1;
        fpb1 = fopen("testmap.bin","rb");
        fp2 = fopen("testmap.txt","r");
        fp1 = fopen("testcell.txt","r");
        fread(&n,sizeof(n),1,fp2);
        //n=3;///
        int * info_bin ;
        int * info_txt ;
        info_bin = mapinfo_bin("testmap.bin");
        n = info_bin[0];
        //n=3;///
        mapinfo_txt("testmap.txt",info_bin);
        MapinitFILE(map,n,info_bin);
        int lines=0;
        char namep[5];
        int xp , yp , energyp;
        fscanf(fp1,"%d\n",&lines);
        fscanf(fp1,"%s %d %d %d\n",namep,&xp,&yp,&energyp);
        strcpy(head->name,namep);
        head->energy = energyp;
        head->x = xp ;
        head->y = yp ;
        head->next = NULL;
        for(int  counter=1 ; counter < lines ; counter++){
            fscanf(fp1,"%s %d %d %d\n",namep,&xp,&yp,&energyp);
            linker(head,namep,xp,yp,energyp);
        }
        fclose(fp1);
        fclose(fpb1);
        fclose(fp2);
    }
    SetColor(15);
    if( n%2 == 0)
        showMap(n,head,map);
    else
        showMapodd(n,head,map);
    SetColor(13);
    int input=0 ;

    int laterinput;
    int spltpermission;
    int spltcheck , source , engypermission;
    struct cell * current2 = head;
    while(laterinput != 5){
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
        engypermission = checkenergy(head,map);

        if( source != 0 && engypermission == 1){
            SetColor(14);
            puts("[1]split\n[2]move\n[3]enrgy\n[4]save\n[5]exit");
        }
        else if( source == 0 && engypermission == 1 ){
            SetColor(8);
            puts("[1]split");
            SetColor(14);
            puts("[2]move\n[3]energy\n[4]save\n[5]exit");
        }
        //( source != 0 && engypermission !=1)
        else if(source !=0 && engypermission != 1){
            SetColor(14);
            puts("[1]split\n[2]move");
            SetColor(8);
            puts("[3]energy");
            SetColor(14);
            puts("[4]save\n[5]exit");
        }
        else if(source ==0 && engypermission != 1){
            SetColor(8);
            puts("[1]split");
            SetColor(14);
            puts("[2]move");
            SetColor(8);
            puts("[3]energy");
            SetColor(14);
            puts("[4]save\n[5]exit");
        }
       scanf("%d",&laterinput);
       if( laterinput == 1){
           for( current2 = head ; current2 != NULL ; current2 = current2->next){
                printsplitname(head , current2->name , map , n);
           }
           counter5 = 1;
           SetColor(15);
          ///* if( n%2 == 0)
              ///*  showMap(n,head,map);
           ///*else
             ///*   showMapodd(n,head,map);
           SetColor(5);
           puts("which cell?");
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
           if( n%2 == 0)
                showMap(n,head,map);
           else
                showMapodd(n,head,map);

       }
       if( laterinput == 2){
            SetColor(5);
            puts("which cell?");
            SetColor(14);
            int sum2;
            int permission , count5;
            struct cell * current = head;
            for( count5=1 ; current != NULL ; current = current->next , count5++ ){
                permission = checkmove1(current->x,current->y,n);
                sum2 = checkcell(current->x,current->y,permission,map,n);
                if( sum2 != 0 ){
                    SetColor(14);
                    printf("[%d]%s\n",count5,current->name);
                }
                else{
                    SetColor(8);
                    printf("[%d]%s\n",count5,current->name);
                }
            }
           // permission = checkmove1(head->x,head->y,n);
           /*
            if( permission == 0 ){
                puts("cant move");
            }
            */
            int inputM; //input move
            scanf("%d",&inputM);
            count5=1;
            current = head;
            while( count5 < inputM ){
              current = current->next;
              count5++;
           }
            struct map_evalue result ;
            permission = checkmove1(current->x,current->y,n);
            int sum = checkcell(current->x , current->y , permission , map , n);
            SetColor(5);
            result.direct1 = sum%10; sum-=sum%10; sum/=10;
            result.direct2 = sum%10; sum-=sum%10; sum/=10;
            result.direct3 = sum%10; sum-=sum%10; sum/=10;
            result.direct4 = sum%10; sum-=sum%10; sum/=10;
            result.direct5 = sum%10; sum-=sum%10; sum/=10;
            result.direct6 = sum%10; sum-=sum%10; sum/=10;
            printf("which direction?\n");
            SetColor(14);
            show_moveoptions(result.direct1 , result.direct2 , result.direct3 , result.direct4 , result.direct5 , result.direct6);
            scanf("%d",&input);
            movecell(head , current->x , current->y , input , map);
            SetColor(15);
            if( n%2 == 0)
                showMap(n,head,map);
            else
                showMapodd(n,head,map);
            //printf("Hello world!\n");
            SetColor(3);
            fclose(fpb1);
       }
       if( laterinput == 3 ){
            SetColor(5);
            puts("which cell?");
            SetColor(14);
            int permission;
            struct cell * current;
            int count4;
            for( current = head , count4 = 1; current != NULL ; current = current->next , count4++){
                permission = energy_permission2(current->name,head,map);
                if( permission != 0){
                    SetColor(14);
                    printf("[%d]%s\n",count4,current->name);
                }
                else{
                    SetColor(8);
                    printf("[%d]%s\n",count4,current->name);
                }
            }
            int inputE;
            scanf("%d",&inputE);
            count4 = 1;
            current = head;
            while( count4 < inputE ){
              current = current->next;
              count4++;
            }
            //puts("here");
            permission = energy_permission(current->name,head,map);
            //puts("here2");
            get_energy(head,permission,current->name);
            SetColor(15);
            if( n%2 == 0)
                showMap(n,head,map);
            else
                showMapodd(n,head,map);
       }


       if( laterinput == 4 ){
            FILE *fp1 , *fp2 , *fpb1;
            int lines=0;
            fpb1 = fopen("testmap.bin","wb");
            fp1 = fopen("testcell.txt","w");
            fp2 = fopen("testmap.txt","w");
            struct cell * current = head ;
            while( current != NULL ){
                lines++;
                current = current->next;
            }
            fprintf(fp1,"%d\n",lines);
            for( current = head ; current != NULL ; current = current->next ){
                fprintf(fp1,"%s %d %d %d\n",current->name,current->x,current->y,current->energy);
            }
            fwrite(&n,sizeof(n),1,fpb1);
            fprintf(fp2,"%d\n",n);
            for( int i=0 ; i<n ; i++ ){
                for( int j=0 ; j<n ; j++ ){
                    int k = map[i][j].type;
                    int k2;
                    int k1=0;
                    if(map[i][j].room == 1)
                        k1=1;
                    else
                        k1=0;
                    fwrite(&(map[i][j].type),sizeof(k1),1,fpb1);
                    fwrite(&i,sizeof(i),1,fpb1);
                    fwrite(&j,sizeof(j),1,fpb1);
                    fwrite(&k1,sizeof(k1),1,fpb1);
                    if( map[i][j].type == 0 || map[i][j].type >4 ){
                        k=1;
                        k2=map[i][j].type;
                    }
                    else{
                        k2=0;
                    }//fprintf(fp2,"block type= %d block energy= %d block location [%d][%d] player%d\n",k,k2,i,j,k1);
                    //if(map[i][j].room == 1)
                        //return 100;
                    fprintf(fp2,"block type= %d block energy= %d block location [%d][%d] player%d\n",k,k2,i,j,map[i][j].room);
                }
            }
            fclose(fp1);
            fclose(fp2);
            fclose(fpb1);
       }
    }
        return 0;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if( laterlateinput == 3){
    static int turn;
    int n=3,xp1,yp1,xp2,yp2;
    FILE *fpb1;
    fpb1 = fopen("test2.bin","rb");//*
    if(fpb1 == NULL)
        exit(8);
    fread(&n , sizeof(n) , 1 , fpb1);
    char *buff = malloc( n*n );
    fread( buff , n*n , 1 , fpb1);
    struct mapEl **map = creat_map(n);
   // n=4;///
    Mapinit(buff , n, map);
    char *rndname1=rand_string1();
    char *rndname2=rand_string2();
    fclose(fpb1);
    for( int i = 0; i == 0 ; ){
         xp1= rand()%n ;
         yp1= rand()%n ;
         if((xp1 == 0 && yp1 == n-1 )|| map[yp1][xp1].room == 1)
            continue;
        if( map[yp1][xp1].type != 3)
            i=1;
    }
    map[yp1][xp1].room=1;
    for( int i = 0; i == 0 ; ){
         xp2= rand()%n ;
         yp2= rand()%n ;
         if((xp2 == 0 && yp2 == n-1 )|| map[yp2][xp2].room == 1)
            continue;
        if( map[yp2][xp2].type != 3)
            i=1;
    }
    struct cell * head1 = creat_cellhead(rndname1,xp1,yp1,0);
    struct cell * head2 = creat_cellhead(rndname2,xp2,yp2,0);

    if( loadNumber == 2 ){


        FILE *fp1 , *fp2 , *fpb1;
        fp1 = fopen("multiplayer_players.txt","r");
        fp2 = fopen("multiplayer_map.txt","r");
        fpb1 = fopen("multiplayer_map.bin","rb");
        int * info_bin;
        int * info_txt;
        info_bin = mapinfo_bin("multiplayer_map.bin");
        for(int i=1;i<=n*n+1;i+=4)
            printf("%d %d %d %d\n",info_bin[i],info_bin[i+1],info_bin[i+2],info_bin[i+3]);
        mapinfo_txt("multiplayer_map.txt" , info_bin );
        n = info_bin[0];
        MapinitFILE(map,n,info_bin);
        fclose(fp2);
        fclose(fpb1);

        int p1Lines=0;
        int p2Lines=0;
        int resumeturn=0;
        fscanf(fp1,"%d\n",&resumeturn);
        if( resumeturn == 1 )
            turn=0;
        else if( resumeturn == 2 )
            turn=1;
        else
            exit(10);
        char namep[5];
        int energyp , xp , yp;
        fscanf(fp1,"%d\n",&p1Lines);
        fscanf(fp1,"%s %d %d %d\n",namep,&xp,&yp,&energyp);
        strcpy(head1->name , namep);
        head1->energy = energyp;
        head1->x = xp;
        head1->y = yp;
        head1->next = NULL;
        for(int counter=1;counter<p1Lines;counter++){
            fscanf(fp1,"%s %d %d %d\n",namep,&xp,&yp,&energyp);
            linker(head1,namep,xp,yp,energyp);
        }
        fscanf(fp1,"%d\n",&p2Lines);
        fscanf(fp1,"%s %d %d %d\n",namep,&xp,&yp,&energyp);
        strcpy(head2->name , namep);
        head2->energy = energyp;
        head2->x = xp;
        head2->y = yp;
        head2->next = NULL;
        for(int counter=1;counter<p2Lines;counter++){
            fscanf(fp1,"%s %d %d %d\n",namep,&xp,&yp,&energyp);
            linker(head2,namep,xp,yp,energyp);
        }
        fclose(fp1);
    }
    if( n%2 == 0)///
        showMap2(n,head1,head2,map);
    else
        showMap2odd(n,head1,head2,map);
    updateMap(head1,head2,map,n);
    int laterinput = 0;
    while(laterinput != 5){
    if( turn%2 == 0 ){
        puts("ready player1...");

        int xp=xp1;
        int yp=yp1;
        struct cell * head = head1;
        int spltpermission;
        int spltcheck , source , engypermission;
        struct cell * current2 = head;
        //while(laterinput != 5){
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
            engypermission = checkenergy(head,map);

            if( source != 0 && engypermission == 1){
            SetColor(14);
            puts("[1]split\n[2]move\n[3]enrgy\n[4]save\n[5]exit");
        }
        else if( source == 0 && engypermission == 1 ){
            SetColor(8);
            puts("[1]split");
            SetColor(14);
            puts("[2]move\n[3]energy\n[4]save\n[5]exit");
        }
        //( source != 0 && engypermission !=1)
        else if(source !=0 && engypermission != 1){
            SetColor(14);
            puts("[1]split\n[2]move");
            SetColor(8);
            puts("[3]energy");
            SetColor(14);
            puts("[4]save\n[5]exit");
        }
        else if(source ==0 && engypermission != 1){
            SetColor(8);
            puts("[1]split");
            SetColor(14);
            puts("[2]move");
            SetColor(8);
            puts("[3]energy");
            SetColor(14);
            puts("[4]save\n[5]exit");
        }
            scanf("%d",&laterinput);
            if( laterinput == 1){
                for( current2 = head ; current2 != NULL ; current2 = current2->next){
                    printsplitname(head , current2->name , map , n);
                }
                counter5 = 1;
                SetColor(15);
              ///*  if( n%2 == 0)///
                  ///*  showMap2(n,head1,head2,map);
               ///* else
                   ///* showMap2odd(n,head1,head2,map);
                SetColor(5);
                puts("which cell?");
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
                updateMap(head1,head2,map,n);
                if( n%2 == 0)///
                    showMap2(n,head1,head2,map);
                else
                    showMap2odd(n,head1,head2,map);

            }
            if( laterinput == 2){
                SetColor(5);
                puts("which cell?");
                SetColor(14);
                int sum2;
                int permission , count5;
                struct cell * current = head;
                for( count5=1 ; current != NULL ; current = current->next , count5++ ){
                    permission = checkmove1(current->x,current->y,n);
                    sum2 = checkcell(current->x,current->y,permission,map,n);
                    if( sum2 != 0 ){
                        SetColor(14);
                        printf("[%d]%s\n",count5,current->name);
                    }
                    else{
                        SetColor(8);
                        printf("[%d]%s\n",count5,current->name);
                    }
                }
           // permission = checkmove1(head->x,head->y,n);
           /*
            if( permission == 0 ){
                puts("cant move");
            }
            */
                int inputM; //input move
                scanf("%d",&inputM);
                count5=1;
                current = head;
                while( count5 < inputM ){
                current = current->next;
                count5++;
                }
                struct map_evalue result ;
                permission = checkmove1(current->x,current->y,n);
                int sum = checkcell(current->x , current->y , permission , map , n);
                SetColor(5);
                result.direct1 = sum%10; sum-=sum%10; sum/=10;
                result.direct2 = sum%10; sum-=sum%10; sum/=10;
                result.direct3 = sum%10; sum-=sum%10; sum/=10;
                result.direct4 = sum%10; sum-=sum%10; sum/=10;
                result.direct5 = sum%10; sum-=sum%10; sum/=10;
                result.direct6 = sum%10; sum-=sum%10; sum/=10;
                printf("which direction?\n");
                int input;
                SetColor(14);
                show_moveoptions(result.direct1 , result.direct2 , result.direct3 , result.direct4 , result.direct5 , result.direct6);
                scanf("%d",&input);
                movecell(head , current->x , current->y , input , map);
                SetColor(15);
                updateMap(head1,head2,map,n);
                if( n%2 == 0)///
                    showMap2(n,head1,head2,map);
                else
                    showMap2odd(n,head1,head2,map);
                //printf("Hello world!\n");
                SetColor(3);
                fclose(fpb1);
            }
            if( laterinput == 3 ){
                SetColor(5);
                puts("which cell?");
                SetColor(14);
                int permission;
                struct cell * current;
                int count4;
                for( current = head , count4 = 1; current != NULL ; current = current->next , count4++){
                    permission = energy_permission2(current->name,head,map);
                    if( permission != 0){
                        SetColor(14);
                        printf("[%d]%s\n",count4,current->name);
                    }
                    else{
                        SetColor(8);
                        printf("[%d]%s\n",count4,current->name);
                    }
                }
                int inputE;
                scanf("%d",&inputE);
                count4 = 1;
                current = head;
                while( count4 < inputE ){
                    current = current->next;
                    count4++;
                }
                //puts("here");
                permission = energy_permission(current->name,head,map);
                //puts("here2");
                get_energy(head,permission,current->name);
                SetColor(15);
                updateMap(head1,head2,map,n);
                if( n%2 == 0)///
                    showMap2(n,head1,head2,map);
                else
                    showMap2odd(n,head1,head2,map);
            }


            if( laterinput == 4 ){
                FILE *fp1 , *fp2 ;
                fp1 = fopen("multiplayer_players.txt","w");
                fp2 = fopen("multiplayer_map.txt","w");
                fpb1 = fopen("multiplayer_map.bin","wb");
                struct cell * current = head1;
                int lines =0;
                while( current != NULL ){
                //fprintf(fp1,"",)
                lines++;
                current = current->next;
                }
                fprintf(fp1,"%d\n",1);
                fprintf(fp1,"%d\n",lines);
                for( current = head1 ; current != NULL ; current = current->next ){
                    fprintf(fp1,"%s %d %d %d\n",current->name,current->x,current->y,current->energy);
                }
                lines =0;
                current = head2;
                while( current != NULL ){
                //fprintf(fp1,"",)
                lines++;
                current = current->next;
                }
                fprintf(fp1,"%d\n",lines);
                for( current = head2 ; current != NULL ; current = current->next ){
                    fprintf(fp1,"%s %d %d %d\n",current->name,current->x,current->y,current->energy);
                }
                fwrite(&n,sizeof(n),1,fpb1);//first write n
                current = head1;
                for(  int i=0 ; i<n ; i++ ){
                    for( int j=0 ; j<n ; j++ ){
                      if( map[i][j].room == 1){
                        int k1 = cellBlocks(head1,map,j,i);
                        if( k1 == 0 ){
                            int k = map[i][j].type;
                            int k2;
                            if( map[i][j].type == 0 || map[i][j].type >4 ){
                                k=1;
                                k2=map[i][j].type;
                            }
                            else{
                                k2=0;
                            }
                            k1=2;

                            fwrite(&(map[i][j].type),sizeof(k1),1,fpb1);
                            fwrite(&i,sizeof(i),1,fpb1);
                            fwrite(&j,sizeof(j),1,fpb1);
                            fwrite(&k1,sizeof(k1),1,fpb1);
                            fprintf(fp2,"block type= %d block energy= %d block location [%d][%d] player%d\n",k,k2,i,j,k1);
                        }
                        else{
                            int k = map[i][j].type;
                            int k2;
                            if( map[i][j].type == 0 || map[i][j].type >4 ){
                                k=1;
                                k2=map[i][j].type;
                            }
                            else{
                                k2=0;
                            }
                            k1=1;

                            fwrite(&(map[i][j].type),sizeof(k1),1,fpb1);
                            fwrite(&i,sizeof(i),1,fpb1);
                            fwrite(&j,sizeof(j),1,fpb1);
                            fwrite(&k1,sizeof(k1),1,fpb1);
                            fprintf(fp2,"block type= %d block energy= %d block location [%d][%d] player%d\n",k,k2,i,j,k1);
                        }
                      }
                      else{
                            int k1 = 0;
                            int k = map[i][j].type;
                            int k2;
                            if( map[i][j].type == 0 || map[i][j].type >4 ){
                                k=1;
                                k2=map[i][j].type;
                            }
                            else{
                                k2=0;
                            }

                            fwrite(&(map[i][j].type),sizeof(k1),1,fpb1);
                            fwrite(&i,sizeof(i),1,fpb1);
                            fwrite(&j,sizeof(j),1,fpb1);
                            fwrite(&k1,sizeof(k1),1,fpb1);
                            fprintf(fp2,"block type= %d block energy= %d block location [%d][%d] player%d\n",k,k2,i,j,k1);
                      }
                    }
                }

                fclose(fp1);
                fclose(fp2);
                fclose(fpb1);
                turn--;
            }
         checkendofgame(map,n);
         turn++;
    }
    else{
        puts("ready player2...");
        //int laterinput = 0;
        int xp=xp2;
        int yp=yp2;
        struct cell * head = head2;
        int spltpermission;
        int spltcheck , source , engypermission;
        struct cell * current2 = head;
        //while(laterinput != 5){
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
            engypermission = checkenergy(head,map);

             if( source != 0 && engypermission == 1){
            SetColor(14);
            puts("[1]split\n[2]move\n[3]enrgy\n[4]save\n[5]exit");
        }
        else if( source == 0 && engypermission == 1 ){
            SetColor(8);
            puts("[1]split");
            SetColor(14);
            puts("[2]move\n[3]energy\n[4]save\n[5]exit");
        }
        //( source != 0 && engypermission !=1)
        else if(source !=0 && engypermission != 1){
            SetColor(14);
            puts("[1]split\n[2]move");
            SetColor(8);
            puts("[3]energy");
            SetColor(14);
            puts("[4]save\n[5]exit");
        }
        else if(source ==0 && engypermission != 1){
            SetColor(8);
            puts("[1]split");
            SetColor(14);
            puts("[2]move");
            SetColor(8);
            puts("[3]energy");
            SetColor(14);
            puts("[4]save\n[5]exit");
        }
            scanf("%d",&laterinput);
            if( laterinput == 1){
                for( current2 = head ; current2 != NULL ; current2 = current2->next){
                    printsplitname(head , current2->name , map , n);
                }
                counter5 = 1;
                SetColor(15);
                updateMap(head1,head2,map,n);
               ///* if( n%2 == 0)///
                   ///* showMap2(n,head1,head2,map);
                ///*else
                    ///*showMap2odd(n,head1,head2,map);
                SetColor(5);
                puts("which cell?");
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
                updateMap(head1,head2,map,n);
                if( n%2 == 0)///
                    showMap2(n,head1,head2,map);
                else
                    showMap2odd(n,head1,head2,map);

            }
            if( laterinput == 2){
                SetColor(5);
                puts("which cell?");
                int sum2;
                int permission , count5;
                struct cell * current = head;
                for( count5=1 ; current != NULL ; current = current->next , count5++ ){
                    permission = checkmove1(current->x,current->y,n);
                    sum2 = checkcell(current->x,current->y,permission,map,n);
                    if( sum2 != 0 ){
                        SetColor(14);
                        printf("[%d]%s\n",count5,current->name);
                    }
                    else{
                        SetColor(8);
                        printf("[%d]%s\n",count5,current->name);
                    }
                }
           // permission = checkmove1(head->x,head->y,n);
           /*
            if( permission == 0 ){
                puts("cant move");
            }
            */
                int inputM; //input move
                scanf("%d",&inputM);
                count5=1;
                current = head;
                while( count5 < inputM ){
                current = current->next;
                count5++;
                }
                struct map_evalue result ;
                permission = checkmove1(current->x,current->y,n);
                int sum = checkcell(current->x , current->y , permission , map , n);
                SetColor(5);
                result.direct1 = sum%10; sum-=sum%10; sum/=10;
                result.direct2 = sum%10; sum-=sum%10; sum/=10;
                result.direct3 = sum%10; sum-=sum%10; sum/=10;
                result.direct4 = sum%10; sum-=sum%10; sum/=10;
                result.direct5 = sum%10; sum-=sum%10; sum/=10;
                result.direct6 = sum%10; sum-=sum%10; sum/=10;
                printf("which direction?\n");
                SetColor(14);
                int input;
                show_moveoptions(result.direct1 , result.direct2 , result.direct3 , result.direct4 , result.direct5 , result.direct6);
                scanf("%d",&input);
                movecell(head , current->x , current->y , input , map);
                updateMap(head1,head2,map,n);
                SetColor(15);
                if( n%2 == 0)///
                    showMap2(n,head1,head2,map);
                else
                    showMap2odd(n,head1,head2,map);
                //printf("Hello world!\n");
                SetColor(3);
                fclose(fpb1);
            }
            if( laterinput == 3 ){
                SetColor(5);
                puts("which cell?");
                SetColor(14);
                int permission;
                struct cell * current;
                int count4;
                for( current = head , count4 = 1; current != NULL ; current = current->next , count4++){
                    permission = energy_permission2(current->name,head,map);
                    if( permission != 0){
                        SetColor(14);
                        printf("[%d]%s\n",count4,current->name);
                    }
                    else{
                        SetColor(8);
                        printf("[%d]%s\n",count4,current->name);
                    }
                }
                int inputE;
                scanf("%d",&inputE);
                count4 = 1;
                current = head;
                while( count4 < inputE ){
                    current = current->next;
                    count4++;
                }
                //puts("here");
                permission = energy_permission(current->name,head,map);
                //puts("here2");
                get_energy(head,permission,current->name);
                updateMap(head1,head2,map,n);
                SetColor(15);
                if( n%2 == 0)///
                    showMap2(n,head1,head2,map);
                else
                    showMap2odd(n,head1,head2,map);
            }

            if( laterinput == 4 ){
                FILE *fp1 , *fp2 ;
                fp1 = fopen("multiplayer_players.txt","w");
                fp2 = fopen("multiplayer_map.txt","w");
                fpb1 = fopen("multiplayer_map.bin","wb");
                struct cell * current = head1;
                int lines =0;
                while( current != NULL ){
                //fprintf(fp1,"",)
                lines++;
                current = current->next;
                }
                fprintf(fp1,"%d\n",2);
                fprintf(fp1,"%d\n",lines);
                for( current = head1 ; current != NULL ; current = current->next ){
                    fprintf(fp1,"%s %d %d %d\n",current->name,current->x,current->y,current->energy);
                }
                lines =0;
                current = head2;
                while( current != NULL ){
                //fprintf(fp1,"",)
                lines++;
                current = current->next;
                }
                fprintf(fp1,"%d\n",lines);
                for( current = head2 ; current != NULL ; current = current->next ){
                    fprintf(fp1,"%s %d %d %d\n",current->name,current->x,current->y,current->energy);
                }
                fwrite(&n,sizeof(n),1,fpb1);
                current = head1;
                for(  int i=0 ; i<n ; i++ ){
                    for( int j=0 ; j<n ; j++ ){
                      if( map[i][j].room == 1){
                        int k1 = cellBlocks(head1,map,j,i);
                        if( k1 == 0 ){
                            int k = map[i][j].type;
                            int k2;
                            if( map[i][j].type == 0 || map[i][j].type >4 ){
                                k=1;
                                k2=map[i][j].type;
                            }
                            else{
                                k2=0;
                            }
                            k1=2;

                            fwrite(&(map[i][j].type),sizeof(k1),1,fpb1);
                            fwrite(&i,sizeof(i),1,fpb1);
                            fwrite(&j,sizeof(j),1,fpb1);
                            fwrite(&k1,sizeof(j),1,fpb1);
                            fprintf(fp2,"block type= %d block energy= %d block location [%d][%d] player%d\n",k,k2,i,j,k1);
                        }
                        else{
                            int k = map[i][j].type;
                            int k2;
                            if( map[i][j].type == 0 || map[i][j].type >4 ){
                                k=1;
                                k2=map[i][j].type;
                            }
                            else{
                                k2=0;
                            }
                            k1=1;

                            fwrite(&(map[i][j].type),sizeof(k1),1,fpb1);
                            fwrite(&i,sizeof(i),1,fpb1);
                            fwrite(&j,sizeof(j),1,fpb1);
                            fwrite(&k1,sizeof(j),1,fpb1);
                            fprintf(fp2,"block type= %d block energy= %d block location [%d][%d] player%d\n",k,k2,i,j,k1);
                        }
                      }
                      else{
                            int k1 = 0;
                            int k = map[i][j].type;
                            int k2;
                            if( map[i][j].type == 0 || map[i][j].type >4 ){
                                k=1;
                                k2=map[i][j].type;
                            }
                            else{
                                k2=0;
                            }

                            fwrite(&(map[i][j].type),sizeof(k1),1,fpb1);
                            fwrite(&i,sizeof(i),1,fpb1);
                            fwrite(&j,sizeof(j),1,fpb1);
                            fwrite(&k1,sizeof(k1),1,fpb1);
                            fprintf(fp2,"block type= %d block energy= %d block location [%d][%d] player%d\n",k,k2,i,j,k1);
                      }
                    }
                }

                fclose(fp1);
                fclose(fp2);
                fclose(fpb1);
                turn--;
            }
            checkendofgame(map,n);
         turn++;
    }
    }
}
if(laterlateinput == 4){
    return 0;
}
/*
if( laterlateinput == 1 ){
    FILE *fp1 , *fp2 , *fpb1;
    fp1 = fopen("multiplayer_players.txt","w");
    fp2 = fopen("multiplayer_map.txt","w");
    fpb1 = fopen("multiplayer_map.bin","wb");
    int * info_bin;
    int * info_txt;
    info_bin = mapinfo_bin("multiplayer_map.bin");
   // info_txt = mapinfo_txt("multiplayer_map.txt" , info_bin );
    n = info_bin[0];
    MapinitFILE(map,n,info_bin);
    //char  namep[];

}

*/
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
