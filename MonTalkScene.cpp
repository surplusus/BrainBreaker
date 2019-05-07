#include "BrainBreaker.h"

int MonTalkScene(void)
{
	// 몬스터 그림 출력
	FILE *fp;
	char buf[200] = { 0, };
	int i = 0;
	TextColor(120);
	if ((fp = fopen("_image/monster.txt", "r+")) != NULL)
	{
		fseek(fp, 0, SEEK_SET);
		while (true)
		{
			if (feof(fp)) break;
			fscanf(fp, "%s", buf);
			Gotoxy(20, 15+i);  printf("%s\n", buf);
			i++;
		}

		fclose(fp);
	}


	int wait = _getch();
	// 몬스터 대사 출력
	TextColor(112);
	ReadTxt(19, 9, 40, 15);
	TextColor();
	wait = _getch();
	wait = _getch();
	return 0;
}