#include "BrainBreaker.h"
// int wait = _getch();
Monster AddMonster(int nStage)
{
	// 몬스터 초기화
	Monster currMonster = { 0, }; // {이름, life, level, (Arrow)attack, death}
	srand(time(NULL));
	int tmp = rand() % 100;
	sprintf_s(currMonster.name,sizeof(char)*20, "%d구역 몬스터", tmp);
	currMonster.life = 100;
	currMonster.level = (nStage / 3) % 6 + 1;
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

	return currMonster;
}

Monster CheckMonster(Monster currMonster, int *userAttack)
{
	for (int i = 0; i < currMonster.level; i++)
	{
		if (currMonster.attack[i] == *(userAttack + i))
			currMonster.life -= currMonster.life / currMonster.level;
	}

	// 몬스터 생명 판별
	if (5 >= currMonster.life)
	{
_D		printf("몬스터가 죽었습니다.\n");
		currMonster = { 0, };
		return currMonster;
	}
	else
	{
_D		printf("몬스터가 공격을 성공해 동료를 불렀습니다.\n");
		currMonster.life = 100;
	}
}

Monster KillMonster(Monster monster, int userAttack, int *countMonster)
{
	// attack 판별 루프
	for (int i = 0; i < monster.level; i++)
		if (monster.attack[i] == userAttack) 
			monster.life -= MAX_LIFE / monster.level;


	return monster;
}

int Showdown(int inputKey, int nSelMonster,	Monster *monster)
{
	

	int nStage = 0;
	int countMonster = 0;
	int nExistMonster = 1;  // 몬스터 존재 상황 비트마스킹
	monster[0] = AddMonster(nStage); // 처음 한번은 무조건 몬스터 출몰
	nStage = 1;

	while (true)
	{
		// nStage 만큼 반복문 돌려서 누가 죽었는지 확인 // 1:삶 0:죽음
		for (int i = 0; i < 5; i++)
		{
			if (monster[i].death)
			{
				nExistMonster |= 1 << i;
				countMonster += 1;
			}
		}
		printf("방향(위 72 / 아래 80 / 왼쪽 75 / 오른쪽 77)과 몬스터 선택(", nExistMonster);
		for (int i = 0; i < 5; i++)
			if (nExistMonster & (1 << i))
				printf(" %d", i);
		printf(")\n");

		// attack 입력
		int userAttack = inputKey, nSelectedMon = 0;
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
	

	}
}

