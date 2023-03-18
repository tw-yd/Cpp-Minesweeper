#include <stdio.h>
#include <windows.h>

#define NOTSEE 35
#define BUMB 37

int main()
{
    char Map_Value[50][50] = {0};
    char Map_Watch[50][50] = {0};

    while(1){
        int i, x, y, t;
        int seed = time(0);
        srand(seed);

        print("please choose mode:\n", -1, -1, -1);
        print("1.simple\n", -1, -1, 14);
        print("2.generally\n", -1, -1, -1);
        print("3.hard\n", -1, -1, -1);
        print("4.custom\n", -1, -1, -1);
        print("5.end\n", -1, -1, -1);
        print("Enter choose number:", -1, -1, 7);

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
                while(1){
                    print("chose size (x,y):", -1, -1, 7);
                    scanf("%d,%d", &x, &y);
                    if(x<51 && y<51) break;
                }
                while(1){
                    printf("chose number of bombs(1~%d):", x*y);
                    scanf("%d,%d", &t);
                    if(t<x*y) break;
                }
                while(1){
                    printf("enter seed:");
                    scanf("%d", &seed);
                    if(seed<2147483648) break;
                }
                break;
            case 5:
                system("cls");
                print("Thank you for playing", -1, -1, 7);
                return 0;
            default:
                system("cls");
                continue;
        }

        system("cls");
        printf("Minesweeper\nsize:%d*%d, bombs:%d, seed:%d\n\n", x, y, t, seed);
        build(Map_Value, y, x, t);
        draw(Map_Value, y, x);

        int Choose_X = 0, Choose_Y = 0;
        for(int i=0;;i++){
            printf("Enter coordinates(x,y):%d,%d\n", Choose_X, Choose_Y);
            char input = getch();

            if (toupper(input)=='W' && 0<Choose_Y) Choose_Y--;
            if (toupper(input)=='A' && 0<Choose_X) Choose_X--;
            if (toupper(input)=='S' && Choose_Y<y-1) Choose_Y++;
            if (toupper(input)=='D' && Choose_X<y-1) Choose_X++;
            if (input == ' ') ;

            print("@", Choose_X*4+2, Choose_Y*2+4, 10);
            print("", 0, 2*y+4,  7);
        }
    }
}

int print(char s[], int x, int y, int c)
{
    if(x!=-1&&y!=-1){
        COORD a;
        a.X=x;
        a.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),a);
    }
    if(c!=-1){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
    }
    printf("%s", s);
}

void build(int Map_Value[50][50], int y,int x, int t)
{
    //依範圍遍歷成空白
    for(int i=0; i<y; i++){
        for(int j=0; j<x; j++){
            //Map_Value[i][j] = 32;
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

void draw(int Map_Value[50][50], int y, int x)
{
    for(int i=0; i<y; i++){
        for(int j=0; j<4*x+1; j++){
            printf("-");
        }
        printf("\n");
        for(int j=0; j<x; j++){
            printf("|   ");
        }
        printf("|\n");
    }
    for(int j=0; j<4*x+1; j++){
        printf("-");
    }
    printf("\n");
}
