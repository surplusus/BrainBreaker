#include "BrainBreaker.h"
// int wait = _getch();
Monster AddMonster(int nStage)
{
	// ���� �ʱ�ȭ
	Monster currMonster = { 0, }; // {�̸�, life, level, (Arrow)attack, death,numofmon}
	srand(time(NULL));
	int tmp = rand() % 100;
	sprintf_s(currMonster.name,sizeof(char)*20, "%d���� ����", tmp);
	currMonster.life = 100;
	currMonster.level = (nStage / 3) % 6 + 1;
	currMonster.death = 1;
	// ���� ���ݹ���(�迭) ����
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
	// ���� ���� �Ǻ�
	if (5 >= currMonster.life)
	{
		Gotoxy(50, 17);
		printf("���Ͱ� �׾����ϴ�.");
		Sleep(600);
		Gotoxy(50, 17);
		printf("                                         ");
		currMonster = { 0, };
		return currMonster;
	}
	else
	{
		Gotoxy(50, 17);
		printf("���Ͱ� ������ ������ ���Ḧ �ҷ����ϴ�.");
		Sleep(600);
		Gotoxy(50, 17);
		printf("                                         ");
		currMonster.life = 100;
		return currMonster;
	}
}

Monster KillMonster(Monster monster, int userAttack, int *countMonster)
{
	// attack �Ǻ� ����
	for (int i = 0; i < monster.level; i++)
		if (monster.attack[i] == userAttack) 
			monster.life -= MAX_LIFE / monster.level;


	return monster;
}

int Showdown(int inputKey, int nSelMonster,	Monster *monster)
{
	

	int nStage = 0;
	int countMonster = 0;
	int nExistMonster = 1;  // ���� ���� ��Ȳ ��Ʈ����ŷ
	monster[0] = AddMonster(nStage); // ó�� �ѹ��� ������ ���� ���
	nStage = 1;

	while (true)
	{
		// nStage ��ŭ �ݺ��� ������ ���� �׾����� Ȯ�� // 1:�� 0:����
		for (int i = 0; i < 5; i++)
		{
			if (monster[i].death)
			{
				nExistMonster |= 1 << i;
				countMonster += 1;
			}
		}
		printf("����(�� 72 / �Ʒ� 80 / ���� 75 / ������ 77)�� ���� ����(", nExistMonster);
		for (int i = 0; i < 5; i++)
			if (nExistMonster & (1 << i))
				printf(" %d", i);
		printf(")\n");

		// attack �Է�
		int userAttack = inputKey, nSelectedMon = 0;
		scanf("%d %d", &userAttack, &nSelectedMon);
		nSelectedMon %= 100;

		// �����ϴ� �������� �Ǻ�
		if (monster[nSelectedMon].level == 0)
			printf("�׷� ���� �����ϴ�.\n");
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

