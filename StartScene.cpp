#include "BrainBreaker.h"
// int wait = _getch();
#define INPUTBUFFER_SIZE 100

void PrintProgrammer(void);

User StartScene(void)
{
	// MainTitle ���
_R	for (int i = 0; i < 4; i++)
	{
		PrintTitle();
		PrintArrow(ARROW_LEFT, 20, 16);
		PrintArrow(ARROW_RIGHT, 132 - 20 - 16, 16);
	}
		
	// default color
	TextColor();  
	// menu
	int sel = PrintMenu();
	// ��� �̸� �Է�
	User user;
	if (0 == sel) user = InitUser(); // �����ϱ�
	if (1 == sel) user = LoadUser("_image/usersave.txt");
	if (2 == sel) PrintProgrammer(); // ũ����
	if (3 == sel) system("exit");  // ����

	//test
_D	printf("%s\n%d\n%d\n", user.name, user.life, user.point);
	return user;
}

User InitUser(void)
{
	// wipe out
	int anykey = _getch();
	for (int i = 0; i < 11; i++)
	{
		TextColor(7);	Gotoxy(58, 16 + i);	printf("           ");
	}
	// initiate user
	char inputName[300] = { 0 };
	User user = { 0,100,0 };

	// print
	ReadTxt(4, 4, 50, 18);

	while (true)
	{
_R		scanf_s("%300s", inputName, sizeof(char) * 300);
_D		strcpy(inputName, "��!������!����������");
		int tmp = strlen(inputName);
		if (tmp < 21 && tmp != 0)
		{
			strcpy_s(user.name, inputName);
			break;
		}
		printf("�̸��� �ٽ� �Է��ϼ���\n");
	}
	return user;
}

void PrintTitle(void)
{
	srand(time(NULL));
	int nColorChanger = rand() % 14 +1;
	system("cls");
	TextColor(nColorChanger);

	FILE *fp;
	char buffer[INPUTBUFFER_SIZE + 1];

	if ((fp = fopen("_image/maintitle.txt", "r+")) != NULL) {
		memset(buffer, 0, sizeof(buffer));
		while (fgets(buffer, INPUTBUFFER_SIZE, fp) != NULL)
			printf("%s", buffer);
		fclose(fp);
	}
	printf("\n\n\n\n");
	Sleep(400);
}

void PrintArrow(Arrow direction, int x, int y)
{
	TextColor(12);

	FILE *fp;
	char buffer[INPUTBUFFER_SIZE + 1];
	char fLocation[13];

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

int PrintMenu(void)
{
	int sel = 100;
	SelCurser(sel);
	while (true)
	{
		int key = _getch();

		switch (key)
		{
		case 72: // up
			sel -= 1;
			SelCurser(sel);
			PrintArrow(ARROW_UP, 20, 16);
			PrintArrow(ARROW_UP, 132 - 20 - 16, 16);
			break;
		case 75: // left
			PrintArrow(ARROW_LEFT, 20, 16);
			PrintArrow(ARROW_LEFT, 132 - 20 - 16, 16);
			break;
		case 77: // right
			PrintArrow(ARROW_RIGHT, 20, 16);
			PrintArrow(ARROW_RIGHT, 132 - 20 - 16, 16);
			break;
		case 80: // down
			sel += 1;
			SelCurser(sel);
			PrintArrow(ARROW_DOWN, 20, 16);
			PrintArrow(ARROW_DOWN, 132 - 20 - 16, 16);
			break;
		case 13:
			sel %= 4;
			return sel;
		default:
			break;
		}
		if (0 == sel) sel = 100;
	}
}

void SelCurser(int sel)
{
	sel %= 4;
	if (0 == sel)
	{
		TextColor(112);	Gotoxy(60, 17);	printf("�����ϱ�");
		TextColor(7);	Gotoxy(60, 19);	printf("�̾��ϱ�");
		TextColor(7);	Gotoxy(59, 21);	printf("������ ����");
		TextColor(7);	Gotoxy(60, 23);	printf("��    ��");
	}
	else if (1 == sel)
	{
		TextColor(7);	Gotoxy(60, 17);	printf("�����ϱ�");
		TextColor(112);	Gotoxy(60, 19);	printf("�̾��ϱ�");
		TextColor(7);	Gotoxy(59, 21);	printf("������ ����");
		TextColor(7);	Gotoxy(60, 23);	printf("��    ��");
	}
	else if (2 == sel)
	{
		TextColor(7);	Gotoxy(60, 17);	printf("�����ϱ�");
		TextColor(7);	Gotoxy(60, 19);	printf("�̾��ϱ�");
		TextColor(112);	Gotoxy(59, 21);	printf("������ ����");
		TextColor(7);	Gotoxy(60, 23);	printf("��    ��");
	}
	else
	{
		TextColor(7);	Gotoxy(60, 17);	printf("�����ϱ�");
		TextColor(7);	Gotoxy(60, 19);	printf("�̾��ϱ�");
		TextColor(7);	Gotoxy(59, 21);	printf("������ ����");
		TextColor(112);	Gotoxy(60, 23);	printf("��    ��");
	}
}

void PrintProgrammer(void)
{
	TextColor(112);	Gotoxy(60, 16);	printf("��    ȹ");
	TextColor(7);	Gotoxy(60, 17);	printf("�� �� ��");
	TextColor(7);	Gotoxy(60, 18);	printf("        ");
	TextColor(112);	Gotoxy(59, 19);	printf("���α׷���");
	TextColor(7);	Gotoxy(60, 20);	printf("�� �� ��");
	TextColor(7);	Gotoxy(58, 21);	printf("             ");
	TextColor(112);	Gotoxy(60, 22);	printf("�� �� ��");
	TextColor(7);	Gotoxy(60, 23);	printf("�� �� ��");
	TextColor(7);	Gotoxy(60, 24);	printf("        ");
	TextColor(112);	Gotoxy(60, 25);	printf("��    ��");
	TextColor(7);	Gotoxy(60, 26);	printf("�� �� ��");

	// wipe out
	int anykey = _getch();
	for (int i = 0; i < 11; i++)
	{
		TextColor(7);	Gotoxy(58, 16 + i);	printf("           ");
	}
	StartScene();
}

