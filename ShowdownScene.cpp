#include "BrainBreaker.h"

#define INPUTBUFFER_SIZE 300

int SelMonster(int nExistMonster);
void Render(int nExistMonster, Monster currMonster, clock_t sclock);
void PrintMonAtt(Arrow direction);
void ShowdownScene()
{
	// ���ؽð� ����
	clock_t sclock;//sclock:����, nclock:����(1/1000�� �ð�)
	time_t seconds; //�ʴ��� �ð�
	struct tm *now; //date time �ð�   
	sclock = clock();//���� clock�� ���մϴ�.
	time(&seconds);//�ʴ��� �ð��� ���մϴ�.
	now = localtime(&seconds);//date time �ð��� ���մϴ�.

	// ���� ��Ʈ ���
_D	printf("���� ���� �Դϴ�.\n");
	// �º�
	int inputKey = 0;
	Monster monster[5];
	int nSelMonster = 0;
	int nStage = 1;
	Monster currMonster;
	int userAttack[7] = { 0, }, AttIdx = 0;
	int nExistMonster = 1;  // ���� ���� ��Ȳ ��Ʈ����ŷ
	monster[0] = AddMonster(nStage); // ó�� �ѹ��� ������ ���� ���
_D	printf("%s, %d, %d, (%d %d),%d\n",
_D		monster[0].name, monster[0].life,
_D		monster[0].level, monster[0].attack[0], monster[0].attack[1],
_D		monster[0].death);

	while (true)
	{
		nSelMonster = SelMonster(nExistMonster);
		currMonster = monster[nSelMonster];
		while (true)
		{
			Render(nExistMonster, currMonster,sclock);
			inputKey = InputKey();
			// userAttack �迭 ����� ������ ���� ������ -1
			if (0 == userAttack[AttIdx])
				userAttack[AttIdx] = inputKey;
			else
			{
				if (currMonster.level > AttIdx)
				{
					AttIdx++; 				
					userAttack[AttIdx] = inputKey;
				}
				if (currMonster.level == AttIdx)
				{
					userAttack[AttIdx + 1] = -1;
					break;
				}
			}
		}
		// nSelMonster �׾��� �Ǻ�
		monster[nSelMonster] = CheckMonster(currMonster, userAttack);
		if (0 == monster[nSelMonster].death) nExistMonster &= ~(1 << nSelMonster);

		
		//Gotoxy(5, 10); printf("%d", nSelMonster);
		//Gotoxy(5, 20);
		
		



		if (nExistMonster == 0)
		{
			printf("�������� Ŭ����!\n");
			break;
		}
	}
}

int SelMonster(int nExistMonster)
{
	int sel = 0;
	for (int i = 0; i < 5; i++)
		if (nExistMonster & (1 << i))
			printf("%d", nExistMonster);
	while (true)
	{
		switch (sel)
		{
		case 0:
			Gotoxy(0, 4); printf("��");
			Gotoxy(0, 12); printf("  ");
			Gotoxy(0, 20); printf("  ");
			Gotoxy(0, 28); printf("  ");
			Gotoxy(0, 36); printf("  ");
			break;
		case 1:
			Gotoxy(0, 4); printf("  ");
			Gotoxy(0, 12); printf("��");
			Gotoxy(0, 20); printf("  ");
			Gotoxy(0, 28); printf("  ");
			Gotoxy(0, 36); printf("  ");
			break;
		case 2:
			Gotoxy(0, 4); printf("  ");
			Gotoxy(0, 12); printf("  ");
			Gotoxy(0, 20); printf("��");
			Gotoxy(0, 28); printf("  ");
			Gotoxy(0, 36); printf("  ");
			break;
		case 3:
			Gotoxy(0, 4); printf("  ");
			Gotoxy(0, 12); printf("  ");
			Gotoxy(0, 20); printf("  ");
			Gotoxy(0, 28); printf("��");
			Gotoxy(0, 36); printf("  ");
			break;
		case 4:
			Gotoxy(0, 4); printf("  ");
			Gotoxy(0, 12); printf("  ");
			Gotoxy(0, 20); printf("  ");
			Gotoxy(0, 28); printf("  ");
			Gotoxy(0, 36); printf("��");
			break;
		default:
			break;
		}
		int key = _getch();

		switch (key)
		{
		case 72: // up
			sel -= 1;
			break;
		case 80: // down
			sel += 1;
			break;
		case 13:
			// ���� ĳ���� �����̰� �Ҹ��� �����Ѵ�
			return sel;
		default:
			break;
		}
		if (0 > sel) sel = 4;
		if (4 < sel) sel = 0;
	}
}

void Render(int nExistMonster, Monster currMonster, clock_t sclock)
{
	// �ʸ��� ����
	clock_t nclock;//sclock:����, nclock:����(1/1000�� �ð�)
	time_t seconds; //�ʴ��� �ð�
	struct tm *now; //date time �ð�   
	int tail = 0;
	nclock = clock();
	if (nclock - sclock >= (CLOCKS_PER_SEC / 100))//clock/100�ʿ� ũ�ų� ������
	{
		sclock = clock();
		time(&seconds);//�ʴ��� �ð��� ���մϴ�.
		now = localtime(&seconds);//date time �ð��� ���մϴ�.
		if (now->tm_sec % 3 == 0)
		{
			Gotoxy(12, 1);
			printf("as");   // ���� �׸�
		}
		else
		{
			Gotoxy(12, 1);
			printf("  ");   // ���� �׸� ����
		}
	}

	//���� �÷��� ���
	for (int i = 0; i < 5; i++)
		if (nExistMonster & (1 << i))
			printf("%d", nExistMonster);
}

void PrintMonAtt(Arrow direction)
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
	default:
		break;
	}
	// ��� Ŀ�� ��ġ ����
	int x = 60, y = 16;

	if ((fp = fopen(fLocation, "r+")) != NULL) {
		memset(buffer, 0, sizeof(buffer));
		while (fgets(buffer, INPUTBUFFER_SIZE, fp) != NULL)
		{
			Gotoxy(x, ++y);
			printf("%s", buffer);
		}
		fclose(fp);
	}

	TextColor(); //default color
}