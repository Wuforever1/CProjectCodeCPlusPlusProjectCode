#pragma once
#ifndef __SNAKE_H__
#define __SNAKE_H__

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

#define WIDE 60
#define HIGH 20

// 定义蛇对象
struct BODY
{
    /* data */
    int X;
    int Y;
};

struct SNAKE
{
    /* data */
    struct BODY body[WIDE * HIGH];
    int size;
} snake;

// 定义食物对象
struct FOOD
{
    /* data */
    int X;
    int Y;
} food;

int score = 0; // 分数
int kx = 0;     // 用户按下asdw所得到的坐标值
int ky = 0;
int lastX = 0;
int lastY = 0;
int speed = 150;

void initSnake(void);
void initFood(void);
void initUI(void);
void playGame(void);
void initWall(void);
void showScore(void);

#endif