#include "BrainBreaker.h"

int MonTalkScene(void)
{
	// 몬스터 그림 출력
	FILE *fp;
	char buf[200] = { 0, };
	//fopen("_image/mawang.txt", "w");
	//fclose(fp);
	if ((fp = fopen("_image/monster.txt", "r+")) != NULL)
	{
		fseek(fp, 0, SEEK_SET);
		while (true)
		{
			if (feof(fp)) break;
			fscanf(fp, "%s", buf);
			printf("%s\n", buf);
		}

		fclose(fp);
	}


	int wait = _getch();
	// 몬스터 대사 출력
	TextColor(112);
	ReadTxt(19, 9, 40, 15);
	TextColor();
	return 0;
}