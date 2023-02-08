#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int i_array[10][10] = {0};

int draw(int,int);
int build(int,int,int);

int main()
{
    int x = 10;
    int y = 10;

    build(y, x, 99);
    for(int i=0;;i++){
        printf("刷新數:%d\n", i);
        draw(x,y);

        sleep(100);
        system("cls");
    }
}

int draw(int x, int y)
{
    for(int i=0; i<y; i++){
        for(int j=0; j<x; j++){
            printf("----");
        }
        printf("-\n");
        for(int j=0; j<x; j++){
            printf("| %d ", i_array[i][j]);
        }
        printf("|\n");
    }
    for(int j=0; j<x; j++){
        printf("----");
    }
    printf("-");
}

int build(int y,int x, int t)
{
    srand(time(0));
    for(int i=0; i<t; i++){
        int a, b;
        while(1){
            a = rand()%y;
            b = rand()%x;
            if(i_array[a][b] != 9) break;
        }
        for(int j=-1; j<2; j++){
            for(int k=-1; k<2; k++){
                if(a-j>=0 && b-k>=0 &&a-j<=x-1 && b-k<=x-1 && i_array[a-j][b-k]!=9) i_array[a-j][b-k] += 1;
            }
        }
        i_array[a][b] = 9;
    }
}
