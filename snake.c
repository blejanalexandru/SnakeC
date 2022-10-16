/// SNAKE by Blejan Alexandru
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define DIM 1000
#define POW 42
#define ORZ 205
#define VER 186

void SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    //We use csbi for the wAttributes word.
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        //Mask out all but the background attribute, and add in the forgournd color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

/*
Name         | Value
             |
Black        |   0
Blue         |   1
Green        |   2
Cyan         |   3
Red          |   4
Magenta      |   5
Brown        |   6
Light Gray   |   7
Dark Gray    |   8
Light Blue   |   9
Light Green  |   10
Light Cyan   |   11
Light Red    |   12
Light Magenta|   13
Yellow       |   14
White        |   15

186 - vertical
205 - orizontal
187 - colt st-jos
188 - colt st-sus
200 - colt dr-sus
201 - colt dr-jos
254 - power
*/

void MapInit(char map[DIM][DIM], int *n, int snake[DIM][2], int *m)
{
    int i, j, px, py;
    char x;

    srand(time(NULL)); // initialize random seed

    system("cls");
    SetColor(9);
    printf("Dimensiunile mapei: \n");
    SetColor(15);

    printf("1 - mare\n2 - mediu\n3 - mic\n");
    x = getch();
    switch(x)
    {
    case '1' :
    {
        *n = 30;    ///range 1-28
        px = rand() % 27 + 1;
        py = rand() % 27 + 1;
        break;
    }
    case '2' :
    {
        *n = 20;    ///range 1-18
        px = rand() % 17 + 1;
        py = rand() % 17 + 1;
        break;
    }
    case '3' :
    {
        *n = 10;    ///range 1-8
        px = rand() % 7 + 1;
        py = rand() % 7 + 1;
        break;
    }
    default :
    {
        printf("nu ai introdus corespunzator");
        exit(1);
    }
    }
    system("cls");
    for(i = 0; i < *n; i++)
        for(j = 0; j < *n; j++)
            if(j == 0  || j == *n-1)
                map[i][j] = '|';
            else if(i == 0 || i == *n-1)
                map[i][j] = '-';
            else
                map[i][j] = ' ';

    map[*n/2][*n/2] = VER;
    map[*n/2-1][*n/2] = VER;
    snake[1][0] = *n/2-1;
    snake[1][1] = *n/2;
    snake[0][0] = *n/2;
    snake[0][1] = *n/2; //coordonates of snake in map
    *m = 2;
    //map[*n/2-3][*n/2] = '*';
    map[px][py] = POW;
}

int verify(char map[DIM][DIM], int vx, int vy)
{
    if(map[vx][vy] == POW)
        return 1;
    else if(map[vx][vy] == ' ')
            return 1;
         else
            return 0;
}

void randpower(char map[DIM][DIM], int n)
{
    int px, py;

    //srand(time(NULL)); /// nu se stie

    switch(n)
    {
    case 30: {px = rand() % 27 + 1; py = rand() % 27 + 1; break;}
    case 20: {px = rand() % 17 + 1; py = rand() % 17 + 1; break;}
    case 10: {px = rand() % 7 + 1; py = rand() % 7 + 1; break;}
    }

    map[px][py] = POW;
}

void moveW(char map[DIM][DIM], int n, int *m, int snake[DIM][2])
{
    int i;

    if(map[snake[*m-1][0]-1][snake[*m-1][1]] == POW) // daca are power
    {
        *m = *m + 1;
        snake[*m-1][0] = snake[*m-2][0]-1;
        snake[*m-1][1] = snake[*m-2][1];
        map[snake[*m-1][0]][snake[*m-1][1]] = VER;
        randpower(map, n);
    }
    else // daca e liber
    {
        map[snake[0][0]][snake[0][1]] = ' ';
        for(i = 0; i < *m-1; i++)
        {
            snake[i][0] = snake[i+1][0];
            snake[i][1] = snake[i+1][1];
        }
        snake[*m-1][0] = snake[*m-1][0]-1;
        map[snake[*m-1][0]][snake[*m-1][1]] = VER;
    }
}

void moveA(char map[DIM][DIM], int n, int *m, int snake[DIM][2])
{
    int i;

    if(map[snake[*m-1][0]][snake[*m-1][1]-1] == POW) // daca are power
    {
        *m = *m + 1;
        snake[*m-1][0] = snake[*m-2][0];
        snake[*m-1][1] = snake[*m-2][1]-1;
        map[snake[*m-1][0]][snake[*m-1][1]] = ORZ;
        randpower(map, n);
    }
    else // daca e liber
    {
        map[snake[0][0]][snake[0][1]] = ' ';
        for(i = 0; i < *m-1; i++)
        {
            snake[i][0] = snake[i+1][0];
            snake[i][1] = snake[i+1][1];
        }
        snake[*m-1][1] = snake[*m-1][1]-1;
        map[snake[*m-1][0]][snake[*m-1][1]] = ORZ;
    }
}

void moveS(char map[DIM][DIM], int n, int *m, int snake[DIM][2])
{
    int i;

    if(map[snake[*m-1][0]+1][snake[*m-1][1]] == POW) // daca are power
    {
        *m = *m + 1;
        snake[*m-1][0] = snake[*m-2][0]+1;
        snake[*m-1][1] = snake[*m-2][1];
        map[snake[*m-1][0]][snake[*m-1][1]] = VER;
        randpower(map, n);
    }
    else // daca e liber
    {
        map[snake[0][0]][snake[0][1]] = ' ';
        for(i = 0; i < *m-1; i++)
        {
            snake[i][0] = snake[i+1][0];
            snake[i][1] = snake[i+1][1];
        }
        snake[*m-1][0] = snake[*m-1][0]+1;
        map[snake[*m-1][0]][snake[*m-1][1]] = VER;
    }
}

void moveD(char map[DIM][DIM], int n, int *m, int snake[DIM][2])
{
    int i;

    if(map[snake[*m-1][0]][snake[*m-1][1]+1] == POW) // daca are power
    {
        *m = *m + 1;
        snake[*m-1][0] = snake[*m-2][0];
        snake[*m-1][1] = snake[*m-2][1]+1;
        map[snake[*m-1][0]][snake[*m-1][1]] = ORZ;
        randpower(map, n);
    }
    else // daca e liber
    {
        map[snake[0][0]][snake[0][1]] = ' ';
        for(i = 0; i < *m-1; i++)
        {
            snake[i][0] = snake[i+1][0];
            snake[i][1] = snake[i+1][1];
        }
        snake[*m-1][1] = snake[*m-1][1]+1;
        map[snake[*m-1][0]][snake[*m-1][1]] = ORZ;
    }
}

int move(char map[DIM][DIM], int snake[DIM][2], int *m, int n)
{
    int ok, i, j, aux;
    char x;

    x = getch();

    switch(x)
    {
    case 'w':
    {
        if(verify(map, snake[*m-1][0]-1, snake[*m-1][1]) == 0) return 0;
        break;
    }
    case 'a':
    {
        if(verify(map, snake[*m-1][0], snake[*m-1][1]-1) == 0) return 0;
        break;
    }
    case 's':
    {
        if(verify(map, snake[*m-1][0]+1, snake[*m-1][1]) == 0) return 0;
        break;
    }
    case 'd':
    {
        if(verify(map, snake[*m-1][0], snake[*m-1][1]+1) == 0) return 0;
        break;
    }
    default :
    {
        printf("tasta gresita!");
        return 1;
    }
    }

    switch(x)
    {
    case 'w':
    {
        moveW(map, n, m, snake);
        /*if(map[snake[*m-1][0]][snake[*m-1][1]] == VER) //de jos in sus
        {
            moveW(map, n, m, snake);/// m are & ?
        }
        else if(map[snake[*m-1][0]][snake[*m-1][1]] == ORZ) // din lateral in sus
        {
            moveW(map, n, m, snake);/// m are & ?
            if(snake[*m-1][1] > snake[*m-2][1])//din stanga
                map[snake[*m-2][0]][snake[*m-2][1]] = 188;
            else // din dreapta
                map[snake[*m-2][0]][snake[*m-2][1]] = 200;
        }*/
        break;
    }

    case 'a':
    {
        moveA(map, n, m, snake);
        break;
    }

    case 's':
    {
        moveS(map, n, m, snake);
        break;
    }

    case 'd':
    {
        moveD(map, n, m, snake);
        break;
    }
    }

    return 1;
}

void MapShow(char map[DIM][DIM], int n)
{
    int i, j;

    system("cls");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            if(i == 0 && i == n-1)
                printf("%c", map[i][j]);
            else
                printf("%c", map[i][j]);
        printf("\n");
    }
}

void verificare(int snake[DIM][2], int m)
{
    int i;
    for(i = 0; i < m; i++)
            printf("%i %i\n", snake[i][0], snake[i][1]);
}

void score (int k)
{
    FILE *p;
    int ok = 0, i = 0, nr, poz = 0;
    char nume[DIM], s[DIM];

    p = fopen("score.txt", "r");
    if(p == NULL)
    {
        printf("Fisierul nu s-a deschis");
        exit(1);
    }

    i = 0;
    while(i < 5 && ok == 0)
    {
        fflush(stdin);
        fgets(s, DIM, p);

        nr = (int)(s[strlen(s)-1]);
        nr = nr * 10 + (int)(s[strlen(s)-2]);
        if(k > nr)
            ok = 1;
        poz = poz + strlen(s);
        i++;
    }
    poz = poz - strlen(s);

    if(ok == 1)
    {
        fclose(p);

        p = fopen("score.txt", "a");
        if(p == NULL)
        {
            printf("Fisierul nu s-a deschis");
            exit(1);
        }

        /// trebuie adaugat pe pozitia POZ
        fseek(p, poz, SEEK_SET);


        fclose(p);

        p = fopen("score.txt", "r");
        if(p == NULL)
        {
            printf("Fisierul nu s-a deschis");
            exit(1);
        }
    }

    fseek(p, 0L, SEEK_SET);
    printf("\n");
    for(i = 0; i < 5; i++)
    {
        fflush(stdin);
        fgets(s, DIM, p);
        puts(s);
        puts("\n");
    }
    fclose(p);
}

void main()
{

    char map[DIM][DIM];
    int n, m, ok, snake[DIM][2] = {0};

    SetColor(10);
    printf("\b\tWelcome to SNAKE");
    SetColor(15);
    printf("\npress ENTER");
    getch();

    MapInit(map, &n, snake, &m);

    do
    {
        ok = move(map, snake, &m, n); /// greseala la IF & primire power
        MapShow(map, n);
    }
    while(ok == 1);

    SetColor(4);
    printf("\b\tGAME OVER");
    SetColor(15);

    getch();

    //score()

    getch();
}
