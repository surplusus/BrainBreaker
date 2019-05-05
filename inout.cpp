#define _CTR_SECURE_NO_WARNINGS
#include "BrainBreaker.h"

int InputKey()
{
	int key;
	while (true)
	{
		if (_kbhit())
		{
			key = _getch();
			switch (key)
			{
			case 72: // up
_D				printf("up\n");
				return true;
			case 75: // left
_D				printf("left\n");
				return true;
			case 77: // right
_D				printf("right\n");
				return true;
			case 80: // down
_D				printf("down\n");
				return true;
			default:
				break;
			}
		}
		else
		{
			return false;
		}
	}
}

void TextColor(int color_number)  // 텍스트 색 함수
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

void Gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

int ReadTxt(int startCol, int countCol, int x, int y)
{
#define LINE_SIZE 50
#define LINE_INDEX 100
	FILE *fp;
	char buffer[LINE_SIZE];
	int fileSize;
	int bcount = 0;
	int indexCol[LINE_INDEX];
	if ((fp = fopen("_image/script.txt", "r+")) != NULL) {
		fseek(fp, 0, SEEK_END);    // 파일 포인터를 파일의 끝으로 이동시킴
		fileSize = ftell(fp);          // 파일 포인터의 현재 위치를 얻음
		memset(buffer, 0, sizeof(char) * LINE_SIZE);
		memset(indexCol, 0, sizeof(int) * LINE_INDEX);
		fseek(fp, 0, SEEK_SET);

		while (TRUE)
		{
			bcount++;
			if (feof(fp)) break;
			fgets(buffer, LINE_SIZE, fp);
			indexCol[bcount] = ftell(fp);
			if (startCol + countCol == bcount)
				for (int i = 0; i < countCol; i++)
				{
					fseek(fp, indexCol[startCol + i], SEEK_SET);
					fgets(buffer, LINE_SIZE, fp);
					Gotoxy(x, y + i);	printf("%s", buffer);
				}
		}
		fclose(fp);
	}
	return 0;
}

User LoadUser(const char *_Source)
{
	User loadUser = { '0',0,0 };
	char textbuffer[20] = { 0, };
	int intbuffer = 0;

	FILE *fp;
	if ((fp = fopen(_Source, "r+")) != NULL)
	{
		fseek(fp, 0, SEEK_SET);
		fgets(textbuffer, 20, fp);
		strcpy(loadUser.name, textbuffer);
		fscanf(fp, "%d", &intbuffer);
		loadUser.life = intbuffer;
		fscanf(fp, "%d", &intbuffer);
		loadUser.point = intbuffer;
		fclose(fp);
	}
	else
	{
		TextColor(160);	Gotoxy(53, 19);	printf("저장한 데이터가 없습니다");
		TextColor();
		int asdf = _getch();
		StartScene();
	}
	return loadUser;
}

void SaveUser(User user)
{
	user = { "test",0,0 };

	FILE *fp;
	if ((fp = fopen("_image/usersave.txt", "w")) != NULL)
	{
		fseek(fp, 0, SEEK_SET);
		fprintf(fp, "%s\n", user.name);
		fprintf(fp, "%d\n", user.life);
		fprintf(fp, "%d\n", user.point);
		fclose(fp);
	}
}