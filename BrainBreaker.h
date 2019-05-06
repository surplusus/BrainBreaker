#pragma once
#ifndef __BRAIN_BREAKER_H__
#define __BRAIN_BREAKER_H__

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

#define TRUE 1
#define FALSE 0

#    define __SLASH(x) /##x
#    define __DOUBLE_SLASH __SLASH(/)
#ifdef _DEBUG
#    define _D
#    define _R __DOUBLE_SLASH
#else
#    define _D __DOUBLE_SLASH
#    define _R
#endif

// ����Ű
typedef int Arrow;
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_LEFT 75
#define ARROW_RIGHT 77
// monster,user LIFE
#define MAX_LIFE 100
// default text color
#define DEFAULT_TEXTCOLOR
typedef struct _UserCharacter
{
	char name[21];
	int life;
	int point;
}User;

typedef struct _MonsterCharacter
{
	char name[20];
	int life;
	int level;
	Arrow attack[8];
	int death;  // 1:�� 0:����
} Monster;

// �⺻ �Է�, ���
int InputKey();
void CursorView(char show);  //Ŀ������� 0:����� 1:���̱�
void Gotoxy(int x, int y);
void TextColor(int color_number = 15);  // default color�� ���
int ReadTxt(int startCol, int countCol, int x, int y); // ����κ� startCol ���� �ټ� countCol
User LoadUser(const char *_Source);
void SaveUser(User user);

// Scene ��� ����
User StartScene(void);
User InitUser(void);
void PrintTitle(void);
void PrintArrow(Arrow direction, int x, int y);
int PrintMenu(void);
void SelCurser(int sel);

int PrologueScene(void);
int MawangScene(void);
int MonTalkScene(void);
void ShowdownScene(void);

void PrintMonAtt(Arrow direction);

// �ºΰ��� �Լ�
Monster AddMonster(int countMonster);
Monster KillMonster(Monster monster, int userAttack, int *countMonster);
void Showdown(void);

#endif // !__BRAIN_BREAKER_H__
