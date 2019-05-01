#include "BrainBreaker.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void SceneMain(void)
{
	// ��� �̸� �Է�
	char inputName[300] = { 0 };
	User user = {0,100,0,0,0};
	printf("����ȭ�� �Դϴ�.\n");
	printf("��翩! �̸��� �Է�(5��) : ");
	while (true)
	{
		scanf_s("%300s", inputName, sizeof(char) * 300);
		int tmp = strlen(inputName);
		if (tmp < 6 && tmp != 0)
		{
			strcpy_s(user.name, inputName);
			break;
		}
		printf("�̸��� �ٽ� �Է��ϼ���\n");
	}
}

void SceneMonster()
{
	// ���� ��Ʈ ���
	printf("���� ���� �Դϴ�.\n");

	// �º�
	Monster monster[100];
	int inning = 0;
	int countMonster = 0;
	while (true)
	{

		// if() Ʋ�ȴٸ�
		// {
			monster[inning] = AddMonster(inning);
			countMonster++;
		// }
		printf("%s, %d, %d, %d", 
			monster[inning].name, 
			monster[inning].life, 
			monster[inning].level,
			monster[inning].attack[0]);
		// �Է�
		int attack = 0, chooseInn = 0;	
		scanf_s("%d &d", &attack,sizeof(int), &chooseInn,sizeof(int));
		// ���� ų
		if (attack == monster[chooseInn].attack[0])
		{
			countMonster -= KillMonster(monster[chooseInn], attack, chooseInn);
		}

		inning++;
	}
}

Monster AddMonster(int inning)
{
	// ���� �ʱ�ȭ
	int i = 0;
	Monster currMonster = { 0, }; // {�̸�, life, level, (Arrow)attack}
	srand(time(NULL));
	int tmp = rand() % 100;
	sprintf_s(currMonster.name,sizeof(char)*20, "%d���� ����", tmp);
	currMonster.life = 100;
	currMonster.level = (inning / 3) + 1;
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

int KillMonster(Monster monster, int userAttack, int chooseInn)
{
	for (int i = 0; i < monster.level; i++)
	{
		if (monster.attack[i] == userAttack) monster.life -= monster.level;
	}


	return 1;
}

