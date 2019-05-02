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