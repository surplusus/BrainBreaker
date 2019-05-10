#include <cstdio>
#include "BrainBreaker.h"

// Release 할때는(1)빌드 제외 다시 (2)_image 폴더 Release폴더에 추가
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
