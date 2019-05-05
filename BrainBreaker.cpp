#include "BrainBreaker.h"

Monster AddMonster(int countMonster)
{
	// ���� �ʱ�ȭ
	Monster currMonster = { 0, }; // {�̸�, life, level, (Arrow)attack, death}
	srand(time(NULL));
	int tmp = rand() % 100;
	sprintf_s(currMonster.name,sizeof(char)*20, "%d���� ����", tmp);
	currMonster.life = 100;
	currMonster.level = (countMonster / 3) + 1;
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
	printf("%s, %d, %d, (%d %d),%d\n",
		currMonster.name, currMonster.life,
		currMonster.level, currMonster.attack[0], currMonster.attack[1],
		currMonster.death);
	return currMonster;
}

Monster KillMonster(Monster monster, int userAttack, int *countMonster)
{

	
	// attack �Ǻ� ����
	for (int i = 0; i < monster.level; i++)
		if (monster.attack[i] == userAttack) 
			monster.life -= MAX_LIFE / monster.level;
	// ���� ���� �Ǻ�
	if (monster.life == 0)
	{
		printf("���Ͱ� �׾����ϴ�.\n");
		monster = { 0, };
		(*countMonster)--;
	}
	else
	{
		printf("���Ͱ� ������ ������ ���Ḧ �ҷ����ϴ�.\n");
		(*countMonster)++;
	}

	return monster;
}

void Showdown(void)
{
	Monster monster[100] = {0,};

	int inning = 0;
	int countMonster = 0;
	long long int unsigned nExistMonster = 1;  // ���� ���� ��Ȳ ��Ʈ����ŷ
	monster[countMonster] = AddMonster(inning); // ó�� �ѹ��� ������ ���� ���
	inning = 1; countMonster = 1;
	while (true)
	{
		// inning ��ŭ �ݺ��� ������ ���� �׾����� Ȯ�� // 1:�� 0:����
		for (int i = inning; i >= 0; i--)
		{
			if (monster[i].death)
				nExistMonster |= 1 << i;
		}
		printf("����(�� 72 / �Ʒ� 80 / ���� 75 / ������ 77)�� ���� ����(", nExistMonster);
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

		// attack �Է�
		int userAttack = 0, nSelectedMon = 0;
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
	

		if (countMonster == 0)
		{
			printf("�������� Ŭ����!\n");
			break;
		}
		else
		{
			inning++;
		}
	}
}

