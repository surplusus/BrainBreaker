#include "BrainBreaker.h"

#define INPUTBUFFER_SIZE 300

typedef struct _Location
{
	int x;
	int y;
}LOCATION;
#pragma region VALUE
LOCATION setLoc[7][5] = { 0 };
int nFlag = 0;
#pragma endregion

#pragma region Function
void SetPrintLocation();
int SelMonster(int nExistMonster);
void SelRender(int nExistMonster, Monster currMonster, clock_t sclock);
void PrintMonPic(int x, int y, int onoff);
void PrintMonAtt(Arrow direction, Monster currMonster, int attOrder);
#pragma endregion
void ShowdownScene()
{
	// ���� ��ġ ���� �Լ�
	SetPrintLocation();
	// ���ؽð� ���� (���μ��� ���� �ð�)
	clock_t sclock = clock();//sclock:���ؽ���, nclock:����(1/1000�� �ð�)

	// ���� ��Ʈ ���
_D	printf("���� ���� �Դϴ�.\n");
	// �º�
#pragma region VAL
	int inputKey = 0;
	Monster monster[5];
	int nSelMonster = 0;
	int nStage = 1;
	Monster currMonster;
	int userAttack[7] = { 0, }, AttIdx = 0;
	int nExistMonster = 1;  // ���� ���� ��Ȳ ��Ʈ����ŷ
#pragma endregion
	monster[0] = AddMonster(nStage); // ó�� �ѹ��� ������ ���� ���
_D	printf("%s, %d, %d, (%d %d),%d,%d��°\n",
_D		monster[0].name, monster[0].life,
_D		monster[0].level, monster[0].attack[0], monster[0].attack[1],
_D		monster[0].death, monster[0].numOfMon);

  	while (true)
	{
		// �����ϴ� ���� ���̱�
		MonStatusRender(nExistMonster);

		nSelMonster = SelMonster(nExistMonster);
		currMonster = monster[nSelMonster];
		while (true)
		{
			// ��� ���� ȭ��ǥ �ѹ��� �׸���
			for (int i = 0; i < 5; i++)
				if (nExistMonster & (1 << i))
					AttRender(monster[i], sclock);

			//���õ� ���� �׸��� ������(userAttack�� ������ ������)
			SelRender(nExistMonster, currMonster, sclock);

			// userAttack �迭 ����� ������ ���� ������ -1
			inputKey = InputKey();
			if (InputKey != 0)
			{
				if (currMonster.level > AttIdx)
				{
					userAttack[AttIdx] = inputKey;
					AttIdx++;
				}
			}

			if (currMonster.level == AttIdx)
			{
				userAttack[AttIdx] = -1;
				break; // Ű �Է� �迭�� -1 �϶�

			}

		}
_D		Gotoxy(40, 18); printf("%d/%d/%d/%d/%d/%d", userAttack[0], userAttack[1], userAttack[2], userAttack[3], userAttack[4], userAttack[5]);

		// nSelMonster �׾��� �Ǻ�
		monster[nSelMonster] = CheckMonster(currMonster, userAttack);
		if (0 == monster[nSelMonster].death) 
			nExistMonster &= ~(1 << nSelMonster);
		else
		{
			for (int j = 0; j < 5; j++)
				if (!(nExistMonster & (1 << j)))
				{
					nExistMonster += (1 << j);
					monster[j] = AddMonster(nStage);
					break;
				}
		}

		// �ð��� �������� �������� ���̵� ���� nStage
		if (nExistMonster == 0)
		{
			printf("�������� Ŭ����!\n");
			break;
		}
		else
		{
			nStage++;
		}
	}
}

void MonStatusRender(int nExistMonster)
{
	int x = 0, y = 0;
	TextColor();
	// �����ϴ� ���� ���̱�
	for (int i = 0; i < 5; i++)
	{
		x = setLoc[6][i].x; y = setLoc[6][i].y;
		if ((1 << i) & nExistMonster)
		{
			PrintMonPic(x, y, 1);
		}
		else
		{
			PrintMonPic(x, y, -1);
		}
	}
	TextColor();
}

void AttRender(Monster monster, clock_t sclock)
{	
	// �׾������� render ���� // 1:�� 0:���� 
	if (!(monster.death)) return;
	// �ʸ��� �������� ����
	clock_t nclock = clock();//sclock:����, nclock:����
	int timer = (nclock - sclock) % 1000; // (1/1000�� �ð�)
	int x = 0; int y = 0;
	// ���� ���� �׸�
	int ranAtt = 0;
	while (true)  // ranAtt = ���ü��ں��� �۰ų� ���� attack index
	{
		ranAtt = rand() % 7;
		if (monster.attack[ranAtt]) break;
	}
	if (!timer)  //timer % 1000 = 1�� 
	{
		if (nFlag == 0)
		{
			nFlag = !nFlag;
			// ���� ���� �׸�
			TextColor(3);
			for (int i = 0; i < 5; i++)
				PrintMonAtt(monster.attack[i], monster, ranAtt);
			TextColor();
		}
		else
		{
			nFlag = !nFlag;
			// ���� ���� ����
			TextColor(3);
			PrintMonAtt(111, monster, ranAtt);
			TextColor();
		}
	}
}

int SelMonster(int nExistMonster)
{
	int sel = 0;

	while (true)
	{
		switch (sel)
		{
		case 0:
			Gotoxy(127, 5); printf("��");
			Gotoxy(127, 13); printf("  ");
			Gotoxy(127, 21); printf("  ");
			Gotoxy(127, 29); printf("  ");
			Gotoxy(127, 37); printf("  ");
			break;
		case 1:
			Gotoxy(127, 5); printf("  ");
			Gotoxy(127, 13); printf("��");
			Gotoxy(127, 21); printf("  ");
			Gotoxy(127, 29); printf("  ");
			Gotoxy(127, 37); printf("  ");
			break;
		case 2:
			Gotoxy(127, 5); printf("  ");
			Gotoxy(127, 13); printf("  ");
			Gotoxy(127, 21); printf("��");
			Gotoxy(127, 29); printf("  ");
			Gotoxy(127, 37); printf("  ");
			break;
		case 3:
			Gotoxy(127, 5); printf("  ");
			Gotoxy(127, 13); printf("  ");
			Gotoxy(127, 21); printf("  ");
			Gotoxy(127, 29); printf("��");
			Gotoxy(127, 37); printf("  ");
			break;
		case 4:
			Gotoxy(127, 5); printf("  ");
			Gotoxy(127, 13); printf("  ");
			Gotoxy(127, 21); printf("  ");
			Gotoxy(127, 29); printf("  ");
			Gotoxy(127, 37); printf("��");
			break;
		default:
			break;
		}
		int key = _getch();

		switch (key)
		{
		case ARROW_UP: // up
			sel -= 1;
			break;
		case ARROW_DOWN: // down
			sel += 1;
			break;
		case 13:
			if (nExistMonster & (1 << (sel)))
			{
				return sel;
			}
			{
				Gotoxy(50, 17);
				printf("���͸� �� �� �����ϼ̽��ϴ�");
				Sleep(400);
				Gotoxy(50, 17);
				printf("                              ");
				break;
			}
		default:
			break;
		}
		if (0 > sel) sel = 4;
		if (4 < sel) sel = 0;
	}
}

void SetPrintLocation()
{
	int relY = 2, relX = 1; // ���� ��������
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			setLoc[i][j] = { relY + 18 * i, relX + 8 * j };
		}
	}
}

void SelRender(int nExistMonster, Monster currMonster, clock_t sclock)
{
	// �ʸ��� ����
	clock_t nclock = clock();//sclock:���ؽð�, nclock:����(1/1000��)
	int timer = (nclock - sclock) % 1000;
	int x = 0; int y = 0;
	nclock = clock();
	
	// �����̴� ���ͱ׸�
	if (timer==0 || timer == 300 || timer == 400)  // timer ���� 0�϶� �ѹ�
	{
		if (0 == nFlag)
		{
			nFlag = 1;
			// ���� �׸�
			TextColor(12);
			for (int i = 0; i < 5; i++)
				if (nExistMonster & (1 << i))
				{
					x = setLoc[6][i].x; y = setLoc[6][i].y; PrintMonPic(x, y, 1);
				}
			TextColor();
		}
		else
		{
			nFlag = 0;
			// ���� �׸� ����
			TextColor(12);
			for (int i = 0; i < 5; i++)
				if (nExistMonster & (1 << i))
				{
					x = setLoc[6][i].x; y = setLoc[6][i].y; PrintMonPic(x, y, 0);
				}
			TextColor();
		}
	}
}

void PrintMonPic(int x, int y,int onoff) // onoff 1 : �׸� 0 : ��׸� -1 : ����
{
	FILE *fp;
	char buffer[20];
	if (1 == onoff)
	{
		if ((fp = fopen("_image/monster.txt", "r+")) != NULL) {
			memset(buffer, 0, sizeof(buffer));
			while (fgets(buffer, INPUTBUFFER_SIZE, fp) != NULL)
			{
				Gotoxy(x, ++y);
				printf("%s", buffer);
			}
			fclose(fp);
		}
	}
	if (0 == onoff)
	{
		for (int i = 0; i < 7; i++)
		{
			Gotoxy(x, ++y);
			printf("���������");
		}
	}
	if (-1 == onoff)
		for (int i = 0; i < 7; i++)
		{
			Gotoxy(x, ++y);
			printf("                ");
		}
}

void PrintMonAtt(Arrow direction, Monster currMonster, int attOrder)
{
	TextColor(12);
	FILE *fp;
	char buffer[INPUTBUFFER_SIZE + 1];
	char fLocation[30];
	switch (direction)
	{
	case ARROW_UP:
		strcpy(fLocation, "_image/arrow_up.txt");
		break;
	case ARROW_DOWN:
		strcpy(fLocation, "_image/arrow_down.txt");
		break;
	case ARROW_LEFT:
		strcpy(fLocation, "_image/arrow_left.txt");
		break;
	case ARROW_RIGHT:
		strcpy(fLocation, "_image/arrow_right.txt");
		break;
	case 111: // ȭ��ǥ ����� �Է�
		strcpy(fLocation, "_image/arrow_blank.txt");
	default:
		break;
	}
	// ��� Ŀ�� ��ġ ����
	int numMon = currMonster.numOfMon;
	int wCount = 0;
	//if (currMonster.attack[i] != 0)
		
	if ((fp = fopen(fLocation, "r+")) != NULL) {
		memset(buffer, 0, sizeof(buffer));
		while (fgets(buffer, INPUTBUFFER_SIZE, fp) != NULL)
		{
			Gotoxy(setLoc[numMon][attOrder].x, setLoc[numMon][attOrder].y+wCount);
			printf("%s", buffer);
			wCount++;
		}
		fclose(fp);
	}
	TextColor(); //default color
}
