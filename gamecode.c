#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#define KEO 1
#define BUA 2
#define BAO 3

int set,win_time=0, num_machine, num_gamer,lose_time=0;


void hienthiluachon(){
    printf(" KEO CHON 1 \n BUA CHON 2\n BAO CHON 3\n");
}
// cơ chế chò chơi
int regime(){
    int time=0;
    
    do {    
        num_machine= 1+rand()%3;

        printf("NHAP SO: ");
        scanf("%d", &num_gamer);
        time++;
        if(num_gamer==KEO && num_machine==BUA ){
            printf("BAN CHON KEO VA MAY CHON BUA\n");
            printf("BAN DA THUA!!!\n");
            lose_time++;
        }
        else if(num_gamer==KEO && num_machine==BAO){
            printf("BAN CHON KEO VA MAY CHON BAO\n");
            printf("BAN DA THANG!!!\n");
            win_time++;
        }
        else if(num_gamer==BUA && num_machine==KEO ){
            printf("BAN CHON BUA VA MAY CHON KEO");
            printf("BAN DA THANG!!!\n");
            win_time++;
        }
        else if(num_gamer ==BUA && num_machine== BAO ){
            printf("BAN CHON BUA VA MAY CHON BAO\n");
            printf("BAN DA THUA!!!\n");
            lose_time++;
        }
        else if(num_gamer == BAO && num_machine== KEO ){
            printf("BAN CHON BAO VA MAY CHON KEO\n");
            printf("BAN DA THUA!!!\n");
            lose_time++;
        }
        else if(num_gamer== BAO && num_machine== BUA){
            printf("BAN CHON BAO VA MAY CHON BUA\n");
            printf("BAN DA THANG!!! \n");
            win_time++;
        }
        else {
            printf("BAN CHON %d VA MAY CHON %d\n",num_gamer, num_machine );
            printf("BAN HOA VOI MAY!!!\n");
        }
    }while(time<set);
}
// cơ chế ăn thua
void check_set(){
    if(win_time<lose_time){
        printf("BAN DA THUA TRONG SET NAY !!!\n");
    }
    if(win_time>lose_time){
        printf("BAN DA THANG TRONG SET NAY !!!\n");
    }
    else{
        printf("BAN DA HOA TRONG SET NAY !!!\n");
    }
}
int main(){
    hienthiluachon();
    printf("MOI BAN NHAP SO LAN CHOI: ");
    scanf("%d",&set);
    regime();
    check_set();

}