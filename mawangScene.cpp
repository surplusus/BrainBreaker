#include "BrainBreaker.h"

int MawangScene(void)
{
	// ���丮 �׸� ���
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
	// ���丮 ��� ���
	TextColor(112);
	ReadTxt(9, 9, 6, 5);
	TextColor();
	wait = _getch();
	return 0;
}