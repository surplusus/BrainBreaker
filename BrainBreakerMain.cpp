#include <cstdio>
#include "BrainBreaker.h"


// Release �Ҷ���(1)���� ���� �ٽ� (2)_image ���� Release������ �߰�
int main(void)
{
	system("mode con cols=132 lines=42 | title BrainBreaker");
	CursorView(0);

	PrologueScene();
	system("cls");
	User user;
	user = StartScene(); system("cls");
	if (user.point == -1) return 0;
	MonTalkScene(); system("cls");

	user = ShowdownScene(); system("cls");

    return 0;
}
