#pragma once
#ifndef __BRAIN_BREAKER_H__
#define __BRAIN_BREAKER_H__

// 방향키
typedef int Arrow;
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_LEFT 75
#define ARROW_RIGHT 77

typedef struct _UserCharacter
{
	char name[20];
	int life = 100;
	int defenceSeq;
	int attack;
	int point;
}User;

typedef struct _MonsterCharacter
{
	char name[20];
	int life;
	int level;
	Arrow attack[8];
} Monster;

// Scene 출력
void SceneMain(void);
void SceneMonster(void);

// 승부관련 함수
Monster AddMonster(int inning);
int KillMonster(Monster monster, int userAttack, int chooseInn);

#endif // !__BRAIN_BREAKER_H__
