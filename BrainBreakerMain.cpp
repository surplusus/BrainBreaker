#include <cstdio>
#include "BrainBreaker.h"

// Release �Ҷ���(1)���� ���� �ٽ� (2)_image ���� Release������ �߰�
int main(void)
{
	system("mode con cols=132 lines=42 | title BrainBreaker");
	CursorView(0);
	PrologueScene();
RESTART:
	
	User user;
	user = StartScene(); system("cls");
	if (user.point == -1) return 0;
	MonTalkScene();

	user = ShowdownScene(); system("cls");
goto RESTART;

    return 0;
}
