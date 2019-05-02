#pragma once
#ifndef __BRAIN_BREAKER_H__
#define __BRAIN_BREAKER_H__

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

// ¹æÇâÅ°
typedef int Arrow;
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_LEFT 75
#define ARROW_RIGHT 77

#define MAX_LIFE 100

typedef struct _UserCharacter
{
	char name[20];
	int life = 100;
	int point;
}User;

typedef struct _MonsterCharacter
{
	char name[20];
	int life;
	int level;
	Arrow attack[8];
	int death;  // 1:»î 0:Á×À½
} Monster;

// Scene Ãâ·Â
void SceneMain(void);
void SceneMonster(void);

// ½ÂºÎ°ü·Ã ÇÔ¼ö
Monster AddMonster(int countMonster);
Monster KillMonster(Monster monster, int userAttack, int *countMonster);
void Showdown(void);

#endif // !__BRAIN_BREAKER_H__
