#include <cstdio>
#include "BrainBreaker.h"

using namespace System;

// Release �Ҷ���(1)���� ���� �ٽ� (2)_image ���� Release������ �߰�
int main(array<System::String ^> ^args)
{
	system("mode con cols=132 lines=40 | title BrainBreaker");
	CursorView(0);

	//PrologueScene();
		
	User user;
	//StartScene();
	//MawangScene();
	//MonTalkScene();

	ShowdownScene();

    return 0;
}
