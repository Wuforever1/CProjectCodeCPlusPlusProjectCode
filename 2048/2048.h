#pragma once
#ifndef __2048_h__
#define __2048_h__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<conio.h>
#include<Windows.h>

#define UI_WIDE 32
#define UI_HIGH 16
#define BOX_WIDE 4
#define BOX_HIGH 4

int box[BOX_HIGH][BOX_WIDE] = {0};
int Max = 0;

void initUI(void);
void initBox(void);
void initBorder(void);
void initRandomNumber(void);
void playGame(void);
void showMax(void);
boolean isDead(void);
void upMove(void);
void downMove(void);
void leftMove(void);
void rightMove(void);
boolean isMove(char direction);
boolean isFull(void);


#endif