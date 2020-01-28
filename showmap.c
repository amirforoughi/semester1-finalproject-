#include<stdio.h>
int main(){
    int i = 0 , j = 0 , n = 5 ,k=n=11;

        for( i=0 ; i<n ; i++ ){
            if ( i == 0){
                    for(j=3;j>0;j--){
                        printf(" _______        ");
                    }

                        printf("\n");
                        continue;
            }
            if( i == 1){
                for(j=3;j>0;j--){
                        printf("I       I_______");
                     }
                     // printf("I");
                        printf("\n");
                        continue;
            }

            if (i == n-1){
                printf("        I_______");
                     for(j=2;j>0;j--){
                        printf("I       I_______");
                     }
                      printf("I");
                        printf("\n");
                        continue;
            }
            if (i%3 == 1){
                     for(j=3;j>0;j--){
                        printf("I       I_______");
                     }
                      printf("I");
                        printf("\n");
            }
            if (i%3 == 2){
                     for(j=3;j>0;j--){
                        printf("I  P2  0I       ");
                     }
                      printf("I");
                        printf("\n");
            }
            if (i%3 == 0){
                     for(j=3;j>0;j--){
                        printf("I_______I  P2  0");
                     }
                      printf("I");
                        printf("\n");
            }
        }

    /*   _________
        I         I_________I
        I         I Player1 I
        I_________I double  I
        I  keep   I_________I
        I  out!!  I Player3 I
        I_________I  E=100  I
                  I_________I
        */

}
