#include "2048.h"

int main()
{
    // 去除光标
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = sizeof(cci);
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

    srand(time(NULL)); // 随机数种子

    initBox();

    initBorder();

    initUI();

    playGame();

    showMax();

    printf("点击回车结束游戏");

    while(getch() != '\n');

    return 0;
}

void showMax(void)
{
    COORD coord;

    coord.X = 0;
    coord.Y = UI_HIGH + 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    for(size_t i = 0; i < BOX_HIGH; i++)
    {
        for(size_t j = 0; j < BOX_WIDE; j++)
        {
            Max = box[i][j] > Max ? box[i][j] : Max;
        }
    }
    printf("Game Over\n");
    printf("MAX SCORE: %d\n", Max);
}

void initBox(void)
{
    int x1;
    int y1;
    int x2;
    int y2;
    while(1)
    {
        x1 = rand() % 4;
        y1 = rand() % 4;
        x2 = rand() % 4;
        y2 = rand() % 4;
        if(!(x1 == x2 && y1 == y2)) break;
    }

    box[x1][y1] = 2;
    box[x2][y2] = 2;

    return;
}

void initUI(void)
{
    COORD coord;
    for(size_t i = 0; i < BOX_HIGH; i++)
    {
        for(size_t j = 0; j < BOX_WIDE; j++)
        {
            coord.X = j * 8 + 3;
            coord.Y = i * 4 + 2;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            printf("    ");
            if(box[i][j] != 0)
            {
                coord.X = j * 8 + 3;
                coord.Y = i * 4 + 2;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                printf("%d", box[i][j]);
            }
        }
    }
}

void initBorder(void)
{
    for(size_t i = 0; i <= UI_HIGH; i++)
    {
        for(size_t j = 0; j <= UI_WIDE; j++)
        {
            if(j % 8 == 0) printf("|");
            else if(i % 4 == 0) printf("_");
            else printf(" ");
        }
        printf("\n");
    }
}

void initRandomNumber(void)
{
    int x;
    int y;
    int tof = rand() % 6 + 1;
    size_t i = 0;
    while(!isFull())
    {
        x = rand() % 4;
        y = rand() % 4;
        if (box[x][y] == 0)
        {
            if(tof == 6) box[x][y] = 4;
            else box[x][y] = 2;
            break;
        }
    }
    return;
}

void playGame(void)
{
    char key = 0;
    boolean move = TRUE;
    // 判断是否还有能够合并的可能
    while(1)
    {
        // 更新
        initUI();

        if(isDead()) break;

        // 接收用户输入 asdw
        key = getch();

        switch(key)
        {
            case 'w': move = isMove('w'); break;
            case 's': move = isMove('s'); break;
            case 'd': move = isMove('d'); break;
            case 'a': move = isMove('a'); break;
            default:
                move = FALSE;
                break;
        }
        if(move) initRandomNumber();
        key = 0;
    }

    return;
}

boolean isDead(void)
{
    // 没有满的话直接返回
    if(!isFull()) return FALSE;

    for(size_t i = 0; i < BOX_HIGH; i++)
        for(size_t j = 0; j < BOX_WIDE - 1; j++)
            if(box[i][j] == box[i][j + 1]) return FALSE;

    for(size_t i = 0; i < BOX_HIGH - 1; i++)
        for(size_t j = 0; j < BOX_WIDE; j++)
            if(box[i][j] == box[i + 1][j]) return FALSE;

    return TRUE;
}

void upMove(void)
{
    for (int col = 0; col < BOX_WIDE; col++) {
        int nonZeroIndex = 0; // 跟踪下一非零元素的位置

        for (int row = 0; row < BOX_HIGH; row++) {
            if (box[row][col] != 0) {
                if (nonZeroIndex > 0 && box[nonZeroIndex - 1][col] == box[row][col]) {
                    // 合并相同元素
                    box[nonZeroIndex - 1][col] *= 2;
                    box[row][col] = 0;
                } else {
                    if (row != nonZeroIndex) {
                        // 上移非零元素
                        box[nonZeroIndex][col] = box[row][col];
                        box[row][col] = 0;
                    }
                    nonZeroIndex++;
                }
            }
        }
    }
}

void downMove(void)
{
    for (int col = 0; col < BOX_WIDE; col++) {
        int nonZeroIndex = BOX_HIGH - 1; // 跟踪下一非零元素的位置

        for (int row = BOX_HIGH - 1; row >= 0; row--) {
            if (box[row][col] != 0) {
                if (nonZeroIndex < BOX_HIGH - 1 && box[nonZeroIndex + 1][col] == box[row][col]) {
                    // 合并相同元素
                    box[nonZeroIndex + 1][col] *= 2;
                    box[row][col] = 0;
                } else {
                    if (row != nonZeroIndex) {
                        // 下移非零元素
                        box[nonZeroIndex][col] = box[row][col];
                        box[row][col] = 0;
                    }
                    nonZeroIndex--;
                }
            }
        }
    }
}

void leftMove(void)
{
    for (int row = 0; row < BOX_HIGH; row++) {
        int nonZeroIndex = 0; // 跟踪下一非零元素的位置

        for (int col = 0; col < BOX_WIDE; col++) {
            if (box[row][col] != 0) {
                if (nonZeroIndex > 0 && box[row][nonZeroIndex - 1] == box[row][col]) {
                    // 合并相同元素
                    box[row][nonZeroIndex - 1] *= 2;
                    box[row][col] = 0;
                } else {
                    if (col != nonZeroIndex) {
                        // 左移非零元素
                        box[row][nonZeroIndex] = box[row][col];
                        box[row][col] = 0;
                    }
                    nonZeroIndex++;
                }
            }
        }
    }
}

void rightMove(void)
{
    for (int row = 0; row < BOX_HIGH; row++) {
        int nonZeroIndex = BOX_WIDE - 1; // 跟踪下一非零元素的位置

        for (int col = BOX_WIDE - 1; col >= 0; col--) {
            if (box[row][col] != 0) {
                if (nonZeroIndex < BOX_WIDE - 1 && box[row][nonZeroIndex + 1] == box[row][col]) {
                    // 合并相同元素
                    box[row][nonZeroIndex + 1] *= 2;
                    box[row][col] = 0;
                } else {
                    if (col != nonZeroIndex) {
                        // 右移非零元素
                        box[row][nonZeroIndex] = box[row][col];
                        box[row][col] = 0;
                    }
                    nonZeroIndex--;
                }
            }
        }
    }
}

boolean isMove(char direction)
{
    int b[BOX_HIGH][BOX_WIDE];
    for(size_t i = 0; i < BOX_HIGH; i++)
        for(size_t j = 0; j < BOX_WIDE; j++)
            b[i][j] = box[i][j];

    switch (direction)
    {
    case 'w':
        upMove();
        break;
    case 's':
        downMove();
        break;
    case 'a':
        leftMove();
        break;
    case 'd':
        rightMove();
        break;
    default:
        break;
    }
    for(size_t i = 0; i < BOX_HIGH; i++)
        for(size_t j = 0; j < BOX_WIDE; j++)
            if(b[i][j] != box[i][j]) return TRUE;
    return FALSE;
}

boolean isFull(void)
{
    for(size_t i = 0; i < BOX_HIGH; i++)
        for(size_t j = 0; j < BOX_WIDE; j++)
            if(box[i][j] == 0) return FALSE;

    return TRUE;
}