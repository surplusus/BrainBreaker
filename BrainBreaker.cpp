#include "BrainBreaker.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void SceneMain(void)
{
	// 용사 이름 입력
	char inputName[300] = { 0 };
	User user = {0,100,0,0,0};
	printf("매인화면 입니다.\n");
	printf("용사여! 이름을 입력(5자) : ");
	while (true)
	{
		scanf_s("%300s", inputName, sizeof(char) * 300);
		int tmp = strlen(inputName);
		if (tmp < 6 && tmp != 0)
		{
			strcpy_s(user.name, inputName);
			break;
		}
		printf("이름을 다시 입력하세요\n");
	}
}

void SceneMonster()
{
	// 몬스터 맨트 출력
	printf("몬스터 등장 입니다.\n");

	// 승부
	Monster monster[100];
	int inning = 0;
	int countMonster = 0;
	while (true)
	{

		// if() 틀렸다면
		// {
			monster[inning] = AddMonster(inning);
			countMonster++;
		// }
		printf("%s, %d, %d, %d", 
			monster[inning].name, 
			monster[inning].life, 
			monster[inning].level,
			monster[inning].attack[0]);
		// 입력
		int attack = 0, chooseInn = 0;	
		scanf_s("%d &d", &attack,sizeof(int), &chooseInn,sizeof(int));
		// 몬스터 킬
		if (attack == monster[chooseInn].attack[0])
		{
			countMonster -= KillMonster(monster[chooseInn], attack, chooseInn);
		}

		inning++;
	}
}

Monster AddMonster(int inning)
{
	// 몬스터 초기화
	int i = 0;
	Monster currMonster = { 0, }; // {이름, life, level, (Arrow)attack}
	srand(time(NULL));
	int tmp = rand() % 100;
	sprintf_s(currMonster.name,sizeof(char)*20, "%d구역 몬스터", tmp);
	currMonster.life = 100;
	currMonster.level = (inning / 3) + 1;
	// 몬스터 공격방향(배열) 생성
	for (int i = 0; i < currMonster.level; i++)
	{
		tmp = rand() % 4;
		switch (tmp)
		{
		case 0:
			currMonster.attack[i] = ARROW_UP;
			break;
		case 1:
			currMonster.attack[i] = ARROW_DOWN;
			break;
		case 2:
			currMonster.attack[i] = ARROW_LEFT;
			break;
		case 3:
			currMonster.attack[i] = ARROW_RIGHT;
			break;
		default:
			break;
		}
	}

	return currMonster;
}

int KillMonster(Monster monster, int userAttack, int chooseInn)
{
	for (int i = 0; i < monster.level; i++)
	{
		if (monster.attack[i] == userAttack) monster.life -= monster.level;
	}


	return 1;
}

