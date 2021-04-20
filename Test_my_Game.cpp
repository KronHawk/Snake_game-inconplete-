#include <conio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, naveX, naveY, score, bossX, bossY, bossLife, damage, bulletD, bulletX, bulletY;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN, BULLET};
eDirection dir;

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    naveX = rand() % width;
    naveY = rand() % height;
    bossX = rand() % width;
    bossY = rand() % height;
    bossLife = 100;
    score = 0;
    damage = 10;
    bulletY = height / 2;
    bulletX = width / 2;
}

void Draw()
{
    system("cls");
    for (int i = 0; i < width+3; i++)
        cout << "=";
    cout << endl;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (j == 0)
                cout << "||";
            if (i == y && j == x)
            {
                cout << "^";
                if (i == bulletY && j == bulletX)
                    cout << ".";
            }
            else if(i == bossY && j == bossX && score == 20)
                cout << "B";
            else if(i == naveY && j == naveX)
                cout << "P";
            else  
                cout << " ";
            if (j == width - 1)
                cout << "||";
        }
        cout << endl; 
    }
    for (int i = 0; i < width+3; i++)
        cout << "=";
    cout << endl;
    cout << "Score: " << score << endl;
    cout << "Damage: " << damage << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        case '5':
            dir = BULLET;
            break;
        }
    }
}

void Logic()
{
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case DOWN:
        y++;
        break;
    case UP:
        y--;
        break;
    case BULLET:
        bulletY = bulletY - 3;
        break;
    }
    if (x == bossX && y == bossY)
    {
        score -= 10;
        bossY = rand() % height;
        bossX = rand() % width;
    }
    if (bulletX == naveX && bulletY == naveY)
    {
        damage += 10;
        bulletD = damage;
        score += 10;
        naveY = rand() % height;
        naveX = rand() % width;
    }
    
    if (x > width || x < 0 || y > height || y < 0)
        gameOver = true;

    if (x == naveX && y == naveY)
    {
        damage += 10;
        score += 10;
        naveX = rand() % width;
        naveY = rand() % height;
    }
}

int main(int argc, char *argv[])
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
    }
    
    return 0;
}
