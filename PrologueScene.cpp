#include "BrainBreaker.h"

int PrologueScene(void)
{
	// 배경음악 출력
	PlaySound(TEXT("./_sound/prologue.wav"), NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
	// 스토리 그림 출력
	FILE *fp;
	char buf[200] = { 0, };

	if ((fp = fopen("_image/mawang1.txt", "r+")) != NULL)
	{
		fseek(fp, 0, SEEK_SET);
		while (true)
		{
			if (feof(fp)) break;
			fgets(buf, 200, fp);
			printf("%s", buf);
		}

		fclose(fp);
	}

	int wait = _getch();
	// 스토리 대사 출력
	TextColor(112);
	ReadTxt(9, 9, 6, 5);
	TextColor();
	wait = _getch();
	wait = _getch();
	system("cls");
	PlaySound(NULL, NULL, 0);
	return 0;
}