#include "stdafx.h"

#include "BrainBreaker.h"


void SceneMain(void)
{
	// MainTitle 출력
	MainTitle();

	// 용사 이름 입력
	char inputName[300] = { 0 };
	User user = { 0,100,0,0,0 };
	printf("매인화면 입니다.\n");
	printf("용사여! 이름을 입력(5자) : ");
	while (true)
	{


		_R		scanf_s("%300s", inputName, sizeof(char) * 300);
		_D		inputName[0] = { '1' };
		_D		inputName[0] = { '3' };
		_D		inputName[0] = { '5' };

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

Monster AddMonster(int countMonster)
{
	// 몬스터 초기화
	Monster currMonster = { 0, }; // {이름, life, level, (Arrow)attack, death}
	srand(time(NULL));
	int tmp = rand() % 100;
	sprintf_s(currMonster.name,sizeof(char)*20, "%d구역 몬스터", tmp);
	currMonster.life = 100;
	currMonster.level = (countMonster / 3) + 1;
	currMonster.death = 1;
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
	printf("%s, %d, %d, (%d %d),%d\n",
		currMonster.name, currMonster.life,
		currMonster.level, currMonster.attack[0], currMonster.attack[1],
		currMonster.death);
	return currMonster;
}

Monster KillMonster(Monster monster, int userAttack, int *countMonster)
{

	
	// attack 판별 루프
	for (int i = 0; i < monster.level; i++)
		if (monster.attack[i] == userAttack) 
			monster.life -= MAX_LIFE / monster.level;
	// 몬스터 생명 판별
	if (monster.life == 0)
	{
		printf("몬스터가 죽었습니다.\n");
		monster = { 0, };
		(*countMonster)--;
	}
	else
	{
		printf("몬스터가 공격을 성공해 동료를 불렀습니다.\n");
		(*countMonster)++;
	}

	return monster;
}

void Showdown(void)
{
	Monster monster[100] = {0,};

	int inning = 0;
	int countMonster = 0;
	long long int unsigned nExistMonster = 1;  // 몬스터 존재 상황 비트마스킹
	monster[countMonster] = AddMonster(inning); // 처음 한번은 무조건 몬스터 출몰
	inning = 1; countMonster = 1;
	while (true)
	{
		// inning 만큼 반복문 돌려서 누가 죽었는지 확인 // 1:삶 0:죽음
		for (int i = inning; i >= 0; i--)
		{
			if (monster[i].death)
				nExistMonster |= 1 << i;
		}
		printf("방향(위 72 / 아래 80 / 왼쪽 75 / 오른쪽 77)과 몬스터 선택(", nExistMonster);
		countMonster = 0;
		for (int i = 0; i < inning; i++)
		{
			if (nExistMonster & (1 << i))
			{
				printf(" %d", i);
				countMonster++;
			}
		}
		printf(")\n");

		// attack 입력
		int userAttack = 0, nSelectedMon = 0;
		scanf("%d %d", &userAttack, &nSelectedMon);
		nSelectedMon %= 100;

		// 존재하는 몬스터인지 판별
		if (monster[nSelectedMon].level == 0)
			printf("그런 몬스터 없습니다.\n");
		else
		{
			monster[nSelectedMon] = KillMonster(monster[nSelectedMon], userAttack, &countMonster);
			if (monster[nSelectedMon].death == 0)
				nExistMonster &= ~(1 << nSelectedMon);
			else
				for (int i = 0; i >= 0; i++)
					if (monster[i].death == 0)
					{
						monster[i] = AddMonster(i);
						nExistMonster |= 1 << i;
						break;
					}
		}
	

		if (countMonster == 0)
		{
			printf("스테이지 클리어!\n");
			break;
		}
		else
		{
			inning++;
		}
	}
}

