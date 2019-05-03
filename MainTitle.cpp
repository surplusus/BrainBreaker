#include "BrainBreaker.h"

#define INPUTBUFFER_SIZE 300

void MainTitle(void)
{
	system("mode con cols=132 lines=50");
	printf("출력 테스트\n");
	//for (int i = 0; i < 5; i++)
	TitlePrint();
	TextColor();  // default color
	
	Arrow n= ARROW_UP;
	MonAttPrint(n);
	n = ARROW_DOWN;
	MonAttPrint(n);
	n = ARROW_LEFT;
	MonAttPrint(n);
	n = ARROW_RIGHT;
	MonAttPrint(n);
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

	switch (direction)
	{
	case ARROW_UP :
		if ((fp = fopen("_image/dager_up.txt", "r+")) != NULL) {
			memset(buffer, 0, sizeof(buffer));
			while (fgets(buffer, INPUTBUFFER_SIZE, fp) != NULL)
				printf("%s", buffer);
			fclose(fp);
		}
		break;
	case ARROW_DOWN:
		if ((fp = fopen("_image/dager_down.txt", "r+")) != NULL) {
			memset(buffer, 0, sizeof(buffer));
			while (fgets(buffer, INPUTBUFFER_SIZE, fp) != NULL)
				printf("%s", buffer);
			fclose(fp);
		}
		break;
	case ARROW_LEFT:
		if ((fp = fopen("_image/shord_left.txt", "r+")) != NULL) {
			memset(buffer, 0, sizeof(buffer));
			while (fgets(buffer, INPUTBUFFER_SIZE, fp) != NULL)
				printf("%s", buffer);
			fclose(fp);
		}
		break;
	case ARROW_RIGHT:
		if ((fp = fopen("_image/shord_right.txt", "r+")) != NULL) {
			memset(buffer, 0, sizeof(buffer));
			while (fgets(buffer, INPUTBUFFER_SIZE, fp) != NULL)
				printf("%s", buffer);
			fclose(fp);
		}
		break;
	default:
		break;
	}

	if ((fp = fopen("_txt/shord_left.txt", "r+")) != NULL) {
		memset(buffer, 0, sizeof(buffer));
		while (fgets(buffer, INPUTBUFFER_SIZE, fp) != NULL)
			printf("%s", buffer);
		fclose(fp);
	}

	TextColor(); //default color
}