#include "BrainBreaker.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int primeNumber[100] = { 1, 2, 3, 5, 7,
11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,
101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,
211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293,
307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397,
401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499,
503, 509, 521, 523 }; // 100��° �Ҽ��� 541

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
		printf("��翩! �̸��� �Է�(5��) : ");
	}
}

void SceneMonster()
{
	// ���� ��Ʈ ���
	printf("���� ���� �Դϴ�.\n");
	// �º�
	Showdown();
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

int KillMonster(Monster monster, int userAttack, int nSelectedMon)
{
	// attack �Ǻ� ����
	for (int i = 0; i < monster.level; i++)
		if (monster.attack[i] == userAttack) 
			monster.life -= MAX_LIFE / monster.level;
	// ���� ���� �Ǻ�
	if (monster.life == 0)
		return TRUE;
	else
		return FALSE;
}

void Showdown(void)
{
	Monster monster[100] = {0,};
	int inning = 0;
	int countMonster = 1;
	int nExistMonster = 1; // primeNumber�� ��

	monster[countMonster] = AddMonster(inning); // ó�� �ѹ��� ������ ���� ���
	while (true)
	{
		inning++;
		char *chExistMonster = NULL;
		chExistMonster = (char*)calloc(100, sizeof(char));
		int tmp = 6;  // tmp = nExistMonster
		for (int i = 0; i < 100; i++)
		{
			sprintf(chExistMonster, "%s %d", chExistMonster, primeNumber[i]);
			if ((tmp / primeNumber[i]) == 1)
				break;
			else
				tmp /= primeNumber[i];
			
		}
		
		// Attack �Է�
		printf("����(�� 72 / �Ʒ� 80 / ���� 75 / ������ 77)�� ���� ����(%s)",chExistMonster);
		int attack = 0, nSelectedMon = 0;
		scanf_s("%d &d", &attack, sizeof(int), &nSelectedMon, sizeof(int));
		free(chExistMonster); // ���� ���� ��Ȳ ��� ���� ����


		// ���� ų ����
		if (KillMonster(monster[nSelectedMon], attack, nSelectedMon))
		{
			printf("���Ͱ� �׾����ϴ�.\n");
			countMonster--;
		}
		else
		{
			printf("���Ͱ� ������ ������ ���Ḧ �ҷ����ϴ�.\n");
			countMonster++;
			monster[countMonster] = AddMonster(inning); // inning�� �Է¹޾� level ����
		}
		
		if (countMonster == 0)
		{
			printf("�������� Ŭ����!\n");
			break;
		}
	}
}