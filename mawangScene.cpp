#include "BrainBreaker.h"

int MawangScene(void)
{
	// 스토리 그림 출력
	FILE *fp;
	char buf[200] = { 0, };

	if ((fp = fopen("_image/mawang2.txt", "r+")) != NULL)
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
	return 0;
}