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

//���� �÷��� ���
for (int i = 0; i < 5; i++)
	if (nExistMonster & (1 << i))
		printf("%d", nExistMonster);

// ���⼺�� ���� �Լ��� for�� �ȿ� �ΰ��� �Ǻ����� �α�. Ŀ���� ���鶧 ���� ����
int dir(1, -1);
i += dir;
for (int i = 0; i < 5 || i >0; i += dir)
if (nExistMonster & (1 << i))
printf("%d", nExistMonster);



