#include <stdio.h>

void bitmask()
{

	unsigned long long int nExistMonster = 1;
	// (nExistMonster & (1 << (n - 1))) ? 1 : 0
	(nExistMonster & (1 << (2))) ? 1 : 0;
	//nExistMonster = 1 << 2;
	//nExistMonster |= 1 << 0;
	//nExistMonster |= 1 << 4;
	//nExistMonster &= ~(1 << 4);
	printf("%d", nExistMonster);
}

//몬스터 플래그 출력
for (int i = 0; i < 5; i++)
	if (nExistMonster & (1 << i))
		printf("%d", nExistMonster);

// 방향성을 가진 함수로 for문 안에 두가지 판별식을 두기. 커서를 만들때 쓰면 좋다
int dir(1, -1);
i += dir;
for (int i = 0; i < 5 || i >0; i += dir)
if (nExistMonster & (1 << i))
printf("%d", nExistMonster);



