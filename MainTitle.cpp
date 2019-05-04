#include "BrainBreaker.h"

#define INPUTBUFFER_SIZE 300
// http://blog.naver.com/PostView.nhn?blogId=sharonichoya&logNo=220875372940
void MainTitle(void)
{
	system("mode con cols=132 lines=40");
_R	for (int i = 0; i < 5; i++)
_R	TitlePrint();
	TextColor();  // default color
	
	MonAttPrint(ARROW_UP);
	MonAttPrint(ARROW_DOWN);
	MonAttPrint(ARROW_LEFT);
	MonAttPrint(ARROW_RIGHT);
}

void TextColor(int color_number)  // 텍스트 색 함수
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

void TitlePrint(void)
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

void MonAttPrint(Arrow direction)
{
	TextColor(12);
	
	FILE *fp;
	char buffer[INPUTBUFFER_SIZE + 1];
	char fLocation[13];

	switch (direction)
	{
	case ARROW_UP :
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
	// 출력 커서 위치 지정
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

void Gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}