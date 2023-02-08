#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define NOTSEE 35
#define BUMB 37

char Map_Value[50][50] = {0};
char Map_Watch[50][50] = {0};

void build(int,int,int);
void draw(int,int);
void enter();
void show(int,int);

int Choose_X = 0;
int Choose_Y = 0;
int Choose = 0;

int main()
{
    int x = 10;
    int y = 10;
    int t = 10;

    int seed = time(0);
    srand(seed);
    build(y, x, t);
    for(int i=0;;i++){
        printf("Minesweeper\nsize:%d*%d, bombs:%d, seed:%d\n\n", x, y, t, seed);
        draw(y,x);
        enter(y,x);
        show(y,x);
        system("cls");
    }
}

void build(int y,int x, int t)
{
    //依範圍遍歷成空白
    for(int i=0; i<y; i++){
        for(int j=0; j<x; j++){
            Map_Value[i][j] = 32;
        }
    }
    //生成炸彈與周圍數值
    for(int i=0; i<t; i++){
        int a, b;
        //生成炸彈直到不重複
        while(1){
            a = rand()%y;
            b = rand()%x;
            if(Map_Value[a][b] != BUMB) break;
        }
        //生成周圍數值
        for(int j=-1; j<2; j++){
            for(int k=-1; k<2; k++){
                if((b-k!=-1||x)&&(Map_Value[a-j][b-k] != BUMB)){
                    if(Map_Value[a-j][b-k]>48 && Map_Value[a-j][b-k]<57) Map_Value[a-j][b-k]+=1;
                    else Map_Value[a-j][b-k] = 49;
                }
            }
        }
        Map_Value[a][b] = BUMB;
    }
}

void draw(int y, int x)
{
    for(int i=0; i<y; i++){
        for(int j=0; j<x; j++){
            printf("----");
        }
        printf("-\n");
        for(int j=0; j<x; j++){
            // Map_Watch[i][j]==1
            if(Map_Value[i][j]==2) printf("| @ ");
            else if(Map_Watch[i][j]==1) printf("| %c ", Map_Value[i][j]);
            else printf("| %c ", NOTSEE);
        }
        printf("|\n");
    }
    for(int j=0; j<x; j++){
        printf("----");
    }
    printf("-\n\n");
}

void enter()
{
    int x=0;
    int y=0;

    printf("Enter coordinates(x,y):%d,%d", Choose_X, Choose_Y);

    char input;
    Map_Value[Choose_Y][Choose_X] = Choose;

    input = getch();
    if (input == 'W' || input == 'w') Choose_Y--;
    if (input == 'A' || input == 'a') Choose_X--;
    if (input == 'S' || input == 's') Choose_Y++;
    if (input == 'D' || input == 'd') Choose_X++;
    if (input == ' ' || input == ' ') Map_Watch[Choose_Y][Choose_X] = 1;

    Choose = Map_Value[Choose_Y][Choose_X];
    Map_Value[Choose_Y][Choose_X] = 2;

    printf("%d%d\n", x, y);
}

void show(int h, int w)
{
    for(int i=0; i<h; i++){
        for(int j=0; j<w; j++){
            //上下左右判定
            short run = 0;
            if(0<i-1 && Map_Watch[i-1][j]==1 && Map_Watch[i][j]!=1 && Map_Value[i-1][j]==32) run = 1;
            if(h>i+1 && Map_Watch[i+1][j]==1 && Map_Watch[i][j]!=1 && Map_Value[i+1][j]==32) run = 1;
            if(0<j-1 && Map_Watch[i][j-1]==1 && Map_Watch[i][j]!=1 && Map_Value[i][j-1]==32) run = 1;
            if(w>j+1 && Map_Watch[i][j+1]==1 && Map_Watch[i][j]!=1 && Map_Value[i][j+1]==32) run = 1;

            if(run){
                Map_Watch[i][j] = 1;
                i=0;
                j=0;
            }
        }
    }
}
