#include "BrainBreaker.h"

#define INPUTBUFFER_SIZE 300

int SelMonster(int nExistMonster);
void Render(int nExistMonster, Monster currMonster, clock_t sclock);
void PrintMonAtt(Arrow direction);
void ShowdownScene()
{
	// 기준시간 관련
	clock_t sclock;//sclock:시작, nclock:현재(1/1000초 시간)
	time_t seconds; //초단위 시각
	struct tm *now; //date time 시각   
	sclock = clock();//시작 clock을 구합니다.
	time(&seconds);//초단위 시각을 구합니다.
	now = localtime(&seconds);//date time 시각을 구합니다.

	// 몬스터 맨트 출력
_D	printf("몬스터 등장 입니다.\n");
	// 승부
	int inputKey = 0;
	Monster monster[5];
	int nSelMonster = 0;
	int nStage = 1;
	Monster currMonster;
	int userAttack[7] = { 0, }, AttIdx = 0;
	int nExistMonster = 1;  // 몬스터 존재 상황 비트마스킹
	monster[0] = AddMonster(nStage); // 처음 한번은 무조건 몬스터 출몰
_D	printf("%s, %d, %d, (%d %d),%d\n",
_D		monster[0].name, monster[0].life,
_D		monster[0].level, monster[0].attack[0], monster[0].attack[1],
_D		monster[0].death);

	while (true)
	{
		nSelMonster = SelMonster(nExistMonster);
		currMonster = monster[nSelMonster];
		while (true)
		{
			Render(nExistMonster, currMonster,sclock);
			inputKey = InputKey();
			// userAttack 배열 만들기 마지막 공격 다음은 -1
			if (0 == userAttack[AttIdx])
				userAttack[AttIdx] = inputKey;
			else
			{
				if (currMonster.level > AttIdx)
				{
					AttIdx++; 				
					userAttack[AttIdx] = inputKey;
				}
				if (currMonster.level == AttIdx)
				{
					userAttack[AttIdx + 1] = -1;
					break;
				}
			}
		}
		// nSelMonster 죽었나 판별
		monster[nSelMonster] = CheckMonster(currMonster, userAttack);
		if (0 == monster[nSelMonster].death) nExistMonster &= ~(1 << nSelMonster);

		
		//Gotoxy(5, 10); printf("%d", nSelMonster);
		//Gotoxy(5, 20);
		
		



		if (nExistMonster == 0)
		{
			printf("스테이지 클리어!\n");
			break;
		}
	}
}

int SelMonster(int nExistMonster)
{
	int sel = 0;
	for (int i = 0; i < 5; i++)
		if (nExistMonster & (1 << i))
			printf("%d", nExistMonster);
	while (true)
	{
		switch (sel)
		{
		case 0:
			Gotoxy(0, 4); printf("●");
			Gotoxy(0, 12); printf("  ");
			Gotoxy(0, 20); printf("  ");
			Gotoxy(0, 28); printf("  ");
			Gotoxy(0, 36); printf("  ");
			break;
		case 1:
			Gotoxy(0, 4); printf("  ");
			Gotoxy(0, 12); printf("●");
			Gotoxy(0, 20); printf("  ");
			Gotoxy(0, 28); printf("  ");
			Gotoxy(0, 36); printf("  ");
			break;
		case 2:
			Gotoxy(0, 4); printf("  ");
			Gotoxy(0, 12); printf("  ");
			Gotoxy(0, 20); printf("●");
			Gotoxy(0, 28); printf("  ");
			Gotoxy(0, 36); printf("  ");
			break;
		case 3:
			Gotoxy(0, 4); printf("  ");
			Gotoxy(0, 12); printf("  ");
			Gotoxy(0, 20); printf("  ");
			Gotoxy(0, 28); printf("●");
			Gotoxy(0, 36); printf("  ");
			break;
		case 4:
			Gotoxy(0, 4); printf("  ");
			Gotoxy(0, 12); printf("  ");
			Gotoxy(0, 20); printf("  ");
			Gotoxy(0, 28); printf("  ");
			Gotoxy(0, 36); printf("●");
			break;
		default:
			break;
		}
		int key = _getch();

		switch (key)
		{
		case 72: // up
			sel -= 1;
			break;
		case 80: // down
			sel += 1;
			break;
		case 13:
			// 몬스터 캐릭을 움직이고 소리가 나게한다
			return sel;
		default:
			break;
		}
		if (0 > sel) sel = 4;
		if (4 < sel) sel = 0;
	}
}

void Render(int nExistMonster, Monster currMonster, clock_t sclock)
{
	// 초마다 실행
	clock_t nclock;//sclock:시작, nclock:현재(1/1000초 시간)
	time_t seconds; //초단위 시각
	struct tm *now; //date time 시각   
	int tail = 0;
	nclock = clock();
	if (nclock - sclock >= (CLOCKS_PER_SEC / 100))//clock/100초와 크거나 같으면
	{
		sclock = clock();
		time(&seconds);//초단위 시각을 구합니다.
		now = localtime(&seconds);//date time 시각을 구합니다.
		if (now->tm_sec % 3 == 0)
		{
			Gotoxy(12, 1);
			printf("as");   // 몬스터 그림
		}
		else
		{
			Gotoxy(12, 1);
			printf("  ");   // 몬스터 그림 지움
		}
	}

	//몬스터 플래그 출력
	for (int i = 0; i < 5; i++)
		if (nExistMonster & (1 << i))
			printf("%d", nExistMonster);
}

void PrintMonAtt(Arrow direction)
{
	TextColor(12);

	FILE *fp;
	char buffer[INPUTBUFFER_SIZE + 1];
	char fLocation[30];

	switch (direction)
	{
	case ARROW_UP:
		strcpy(fLocation, "_image/arrow_up.txt");
		break;
	case ARROW_DOWN:
		strcpy(fLocation, "_image/arrow_down.txt");
		break;
	case ARROW_LEFT:
		strcpy(fLocation, "_image/arrow_left.txt");
		break;
	case ARROW_RIGHT:
		strcpy(fLocation, "_image/arrow_right.txt");
		break;
	default:
		break;
	}
	// 출력 커서 위치 지정
	int x = 60, y = 16;

	if ((fp = fopen(fLocation, "r+")) != NULL) {
		memset(buffer, 0, sizeof(buffer));
		while (fgets(buffer, INPUTBUFFER_SIZE, fp) != NULL)
		{
			Gotoxy(x, ++y);
			printf("%s", buffer);
		}
		fclose(fp);
	}

	TextColor(); //default color
}