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

// 방향키
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
	int death;  // 1:삶 0:죽음
	int numOfMon;
} Monster;

// 기본 입력, 출력
void print_time(struct tm *now, int tail);
int InputKey();
void CursorView(char show);  //커서숨기기 0:숨기기 1:보이기
void Gotoxy(int x, int y);
void TextColor(int color_number = 15);  // default color는 흰색
int ReadTxt(int startCol, int countCol, int x, int y); // 제목부분 startCol 본문 줄수 countCol
User LoadUser(const char *_Source);
void SaveUser(User user);
int InputKey_stay();

// Scene 출력 관련
User StartScene(void);
User InitUser(void);
void PrintTitle(void);
void PrintArrow(Arrow direction, int x, int y);
int PrintMenu(void);
void SelCurser(int sel);

int PrologueScene(void);
int MawangScene(void);
int MonTalkScene(void);
User ShowdownScene(void);


// 승부관련 함수
void MonStatusRender(int nExistMonster);
Monster AddMonster(int countMonster);
Monster KillMonster(Monster monster, int userAttack, int *countMonster);
int Showdown(int inputKey, int nSelMonster, Monster *monster);
Monster CheckMonster(Monster currMonster, int *userAttack);
void PrintMonAtt(Arrow direction, Monster currMonster, int attOrder);
void AttRender(Monster monster, clock_t sclock);
#endif // !__BRAIN_BREAKER_H__
