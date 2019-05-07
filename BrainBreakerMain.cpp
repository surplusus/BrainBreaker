#include <cstdio>
#include "BrainBreaker.h"


// Release 할때는(1)빌드 제외 다시 (2)_image 폴더 Release폴더에 추가
int main(void)
{
	system("mode con cols=132 lines=42 | title BrainBreaker");
	CursorView(0);

	//PrologueScene();
		
	User user;
	//StartScene();
	//MawangScene();
	//MonTalkScene();

	ShowdownScene();

    return 0;
}
