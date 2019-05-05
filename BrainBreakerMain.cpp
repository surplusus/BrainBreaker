#include <cstdio>
#include "BrainBreaker.h"

using namespace System;

// Release 할때는(1)빌드 제외 다시 (2)_image 폴더 Release폴더에 추가
int main(array<System::String ^> ^args)
{
	system("mode con cols=132 lines=40 | title BrainBreaker");
	CursorView(0);

	User user;
	//StartScene();
	ShowdownScene();

    return 0;
}
