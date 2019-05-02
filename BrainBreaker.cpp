#include "BrainBreaker.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int primeNumber[100] = { 2, 3, 5, 7,
11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,
101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,
211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293,
307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397,
401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499,
503, 509, 521, 523, 541 }; // 100번째 소수는 541

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
		printf("용사여! 이름을 입력(5자) : ");
	}
}

void SceneMonster()
{
	// 몬스터 맨트 출력
	printf("몬스터 등장 입니다.\n");
	// 승부
	Showdown();
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

Monster KillMonster(Monster monster, int userAttack, int nSelectedMon)
{
	
	// attack 판별 루프
	for (int i = 0; i < monster.level; i++)
		if (monster.attack[i] == userAttack) 
			monster.life -= MAX_LIFE / monster.level;
	// 몬스터 생명 판별
	if (monster.life == 0)
		monster = { 0, };

	return monster;
}

void ExistMonPrint(int nExistMonster, int inning)
{
	char chExistMonster[200] = { 0, };  // 몬스터 존재 상황 출력 변수
	int checkExMon = 0;
	for (int i = inning; i >=0; i--)
	{
		checkExMon = nExistMonster % primeNumber[i]; // 값이 0이면 존재
		if (!checkExMon)
		{
			sprintf(chExistMonster, "%s %d", chExistMonster, primeNumber[i]);
			
		}

	}

	// Attack 입력
	printf("방향(위 72 / 아래 80 / 왼쪽 75 / 오른쪽 77)과 몬스터 선택(%s)\n", chExistMonster);
}


void Showdown(void)
{
	Monster monster[100] = {0,};
	int inning = 1;
	int countMonster = 1;
	int nExistMonster = primeNumber[0]; // primeNumber의 곱

	monster[countMonster] = AddMonster(inning); // 처음 한번은 무조건 몬스터 출몰

	while (true)
	{

		

		ExistMonPrint(nExistMonster, inning);

		// attack 입력
		int attack = 0, nSelectedMon = 0;
		scanf("%d %d", &attack, &nSelectedMon);

		// 몬스터 킬 판정
		if (KillMonster(monster[nSelectedMon-1], attack, nSelectedMon).death)
		{
			printf("몬스터가 공격을 성공해 동료를 불렀습니다.\n");
			countMonster++;
			nExistMonster = nExistMonster * primeNumber[countMonster];
			monster[countMonster] = AddMonster(inning); // inning을 입력받아 level 결정
		}
		else
		{
			printf("몬스터가 죽었습니다.\n");
			countMonster--;
			nExistMonster = nExistMonster / primeNumber[nSelectedMon];
		}
		
		if (countMonster == 0)
		{
			printf("스테이지 클리어!\n");
			break;
		}
		else
		{
			inning++; // 회차 증가
		}
	}
}