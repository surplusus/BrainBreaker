#include "BrainBreaker.h"

#define INPUTBUFFER_SIZE 300
void Update();
void Render();
void ShowdownScene()
{
	// ���� ��Ʈ ���
_D	printf("���� ���� �Դϴ�.\n");
	// �º�
	int inputKey = 0;
	while (true)
	{
		inputKey = InputKey();
		Update();
		Render();
	}

	Showdown();
}


void Update(void)
{

}
void Render(void)
{

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