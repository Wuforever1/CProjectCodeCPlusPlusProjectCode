#include"snake.h"

int main()
{
    // 去除光标
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = sizeof(cci);
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

    kbhit();
    srand(time(NULL)); // 随机数种子

    initSnake();
    initFood();

    initWall();
    initUI();

    playGame();

    showScore();

    system("pause");

    return 0;
}

void showScore(void)
{
    COORD coord;

    coord.X = 0;
    coord.Y = HIGH + 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    printf("Game Over\n");
    printf("Score: %d\n", score);
}

void initWall(void)
{
    for(size_t i = 0; i <= HIGH; i++)
    {
        for(size_t j = 0; j <= WIDE; j++)
        {
            if(j == WIDE) printf("|");
            else if(i == HIGH) printf("_");
            else printf(" ");
        }
        printf("\n");
    }
}

void playGame(void)
{
    char key = 'd';
    // 判断蛇撞墙
    while(snake.body[0].X >= 0 && snake.body[0].X < WIDE
        && snake.body[0].Y >= 0 && snake.body[0].Y < HIGH)
    {
        // 更新蛇
        initUI();

        // 接收用户输入 asdw
        if(kbhit())
        {
            char temp = getch();
            if(temp == 'w' && key == 's');
            else if(temp == 's' && key == 'w');
            else if(temp == 'a' && key == 'd');
            else if(temp == 'd' && key == 'a');
            else key = temp;
        }
        switch(key)
        {
            case 'w': kx = 0; ky = -1; break;
            case 's': kx = 0; ky = 1; break;
            case 'd': kx = 1; ky = 0; break;
            case 'a': kx = -1; ky = 0; break;
            default:
                break;
        }

        // 蛇头撞身体
        for(size_t i = 1; i < snake.size; i++)
        {
            if(snake.body[0].X == snake.body[i].X
                && snake.body[0].Y == snake.body[i].Y)
            {
                return;
            }
        }

        // 蛇头撞食物
        if(snake.body[0].X == food.X && snake.body[0].Y == food.Y)
        {
            initFood();     // 食物消失 
            snake.size++;   // 身体增长
            score += 10;    // 加分
            if(speed > 50) speed -= 10;    // 加速
        }

        lastX = snake.body[snake.size - 1].X;
        lastY = snake.body[snake.size - 1].Y;

        // 蛇移动，前一节身体给后一节身体
        for(size_t i = snake.size - 1; i > 0; i--)
        {
            snake.body[i].X = snake.body[i - 1].X;
            snake.body[i].Y = snake.body[i - 1].Y;
        }

        snake.body[0].X += kx;  // 蛇头坐标根据输入修改
        snake.body[0].Y += ky;

        Sleep(speed);

    }

    return;
}

// 初始化蛇函数
void initSnake(void)
{
    snake.size = 2;
    snake.body[0].X = WIDE / 2;
    snake.body[0].Y = HIGH / 2;

    snake.body[1].X = WIDE / 2 - 1;
    snake.body[1].Y = HIGH / 2;

    return;
}


void initUI(void)
{
    // 画蛇
    COORD coord;

    for(size_t i = 0; i < snake.size; i++)
    {
        coord.X = snake.body[i].X;
        coord.Y = snake.body[i].Y;

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        if(i == 0) putchar('@');
        else putchar('*');
    }
    // 去除蛇尾
    coord.X = lastX;
    coord.Y = lastY;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    putchar(' ');

    // 画食物
    coord.X = food.X;
    coord.Y = food.Y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    putchar('#');

    return;
}

// 初始化食物
void initFood(void)
{
    food.X = rand() % WIDE / 2 + WIDE / 4;
    food.Y = rand() % HIGH / 2 + HIGH / 4;
}