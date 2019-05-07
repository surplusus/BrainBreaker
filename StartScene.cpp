#include "BrainBreaker.h"

#define INPUTBUFFER_SIZE 100

void PrintProgrammer(void);

User StartScene(void)
{
	// MainTitle 출력
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
	// 용사 이름 입력
	User user;
	if (0 == sel) user = InitUser(); // 새로하기
	if (1 == sel) user = LoadUser("_image/usersave.txt");
	if (2 == sel) PrintProgrammer(); // 크래딧
	if (3 == sel)  // 종료
	{
		user.point = -1;
		return user;  
	}

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
	int wait = _getch();
	wait = _getch();
	while (true)
	{
		Gotoxy(60, 25);
		scanf_s("%300s", inputName, sizeof(char) * 300);
		int tmp = strlen(inputName);
		if (tmp < 21 && tmp != 0)
		{
			strcpy_s(user.name, inputName);
			break;
		}
		Gotoxy(50, 17); printf("이름을 다시 입력하세요\n");
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
		TextColor(112);	Gotoxy(60, 17);	printf("새로하기");
		TextColor(7);	Gotoxy(60, 19);	printf("이어하기");
		TextColor(7);	Gotoxy(59, 21);	printf("개발자 보기");
		TextColor(7);	Gotoxy(60, 23);	printf("종    료");
	}
	else if (1 == sel)
	{
		TextColor(7);	Gotoxy(60, 17);	printf("새로하기");
		TextColor(112);	Gotoxy(60, 19);	printf("이어하기");
		TextColor(7);	Gotoxy(59, 21);	printf("개발자 보기");
		TextColor(7);	Gotoxy(60, 23);	printf("종    료");
	}
	else if (2 == sel)
	{
		TextColor(7);	Gotoxy(60, 17);	printf("새로하기");
		TextColor(7);	Gotoxy(60, 19);	printf("이어하기");
		TextColor(112);	Gotoxy(59, 21);	printf("개발자 보기");
		TextColor(7);	Gotoxy(60, 23);	printf("종    료");
	}
	else
	{
		TextColor(7);	Gotoxy(60, 17);	printf("새로하기");
		TextColor(7);	Gotoxy(60, 19);	printf("이어하기");
		TextColor(7);	Gotoxy(59, 21);	printf("개발자 보기");
		TextColor(112);	Gotoxy(60, 23);	printf("종    료");
	}
}

void PrintProgrammer(void)
{
	TextColor(112);	Gotoxy(60, 16);	printf("기    획");
	TextColor(7);	Gotoxy(60, 17);	printf("윤 구 현");
	TextColor(7);	Gotoxy(60, 18);	printf("        ");
	TextColor(112);	Gotoxy(59, 19);	printf("프로그래밍");
	TextColor(7);	Gotoxy(60, 20);	printf("윤 구 현");
	TextColor(7);	Gotoxy(58, 21);	printf("             ");
	TextColor(112);	Gotoxy(60, 22);	printf("스 토 리");
	TextColor(7);	Gotoxy(60, 23);	printf("윤 구 현");


	// wipe out
	int anykey = _getch();
	for (int i = 0; i < 11; i++)
	{
		TextColor(7);	Gotoxy(58, 16 + i);	printf("           ");
	}
	StartScene();
}

