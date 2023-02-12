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

void main()
{
    while(1){
        int i, x, y, t;

        printf("please choose mode:\
                \n1.Simple\
                \n2.Generally\
                \n3.Hard\
                \n4.Custom\
                \n5.End\
                \n\nEnter choose number:");
        scanf("%d", &i);
        switch(i){
            case 1:
                x = 5, y = 5, t = 1;
                break;
            case 2:
                x = 10, y = 10, t = 10;
                break;
            case 3:
                x = 20, y = 20, t = 50;
                break;
            case 4:
                printf("chose size(x,y)");
                scanf("%d,%d", &x, &y);
                printf("chose number of bombs(1~%d)", x*y);
                scanf("%d,%d", &t);
                break;
            case 5:
                printf("Thank you for playing");
                return 0;
            default:
                system("cls");
                continue;
        }

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
}

void build(int y,int x, int t)
{
    //�̽d��M�����ť�
    for(int i=0; i<y; i++){
        for(int j=0; j<x; j++){
            Map_Value[i][j] = 32;
        }
    }
    //�ͦ����u�P�P��ƭ�
    for(int i=0; i<t; i++){
        int a, b;
        //�ͦ����u���줣����
        while(1){
            a = rand()%y;
            b = rand()%x;
            if(Map_Value[a][b] != BUMB) break;
        }
        //�ͦ��P��ƭ�
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
            //�W�U���k�P�w
            short run = 0;
            if(0<i-1 && Map_Watch[i-1][j]==1 && Map_Value[i-1][j]==32) run = 1;
            if(h>i+1 && Map_Watch[i+1][j]==1 && Map_Value[i+1][j]==32) run = 1;
            if(0<j-1 && Map_Watch[i][j-1]==1 && Map_Value[i][j-1]==32) run = 1;
            if(w>j+1 && Map_Watch[i][j+1]==1 && Map_Value[i][j+1]==32) run = 1;

            if(Map_Watch[i][j]!=1 && run){
                Map_Watch[i][j] = 1;
                i=0, j=0;
            }
        }
    }
}
