#include "BrainBreaker.h"

#define INPUTBUFFER_SIZE 300

using namespace std;

typedef struct _Location
{
	int x;
	int y;
}LOCATION;
#pragma region VALUE
LOCATION setLoc[7][5] = { 0 };
int nFlag = 0;
User user;
#pragma endregion

#pragma region Function
void SetPrintLocation();
int SelMonster(int nExistMonster);
void SelRender(int nExistMonster, Monster currMonster, clock_t sclock);
void PrintMonPic(int x, int y, int onoff);
void PrintMonAtt(Arrow direction, Monster currMonster, int attOrder);
#pragma endregion
User ShowdownScene()
{
	// 기준 위치 설정 함수
	SetPrintLocation();
	// 기준시간 관련 (프로세스 구동 시간)
	clock_t sclock = clock();//sclock:기준시작, nclock:현재(1/1000초 시간)

	// 몬스터 맨트 출력
_D	printf("몬스터 등장 입니다.\n");
	// 승부
#pragma region VAL
	int inputKey = 0;
	Monster monster[5];
	int nSelMonster = 0;
	int nStage = user.point/1000+1;
	Monster currMonster;
	int userAttack[7] = { 0, }, attIdx = 0;
	int nExistMonster = 1;  // 몬스터 존재 상황 비트마스킹
#pragma endregion
	monster[0] = AddMonster(nStage); monster[0].numOfMon = 0; // 처음 한번은 무조건 몬스터 출몰
_D	printf("%s, %d, %d, (%d %d),%d,%d번째\n",
_D		monster[0].name, monster[0].life,
_D		monster[0].level, monster[0].attack[0], monster[0].attack[1],
_D		monster[0].death, monster[0].numOfMon);

  	while (true)
	{
		// 존재하는 몬스터 보이기
		MonStatusRender(nExistMonster);

		nSelMonster = SelMonster(nExistMonster);
		currMonster = monster[nSelMonster];
		memset(userAttack, 0, sizeof(int) * 7);
		attIdx = 0;
		while (true)
		{
			// 모든 몬스터 화살표 한번에 그리기
			for (int i = 0; i < 5; i++)
				if (nExistMonster & (1 << i))
					AttRender(monster[i], sclock);

			//선택된 몬스터 그림이 깜빡임(userAttack과 무관한 깜빡임)
			SelRender(nExistMonster, currMonster, sclock);

			// userAttack 배열 만들기 마지막 공격 다음은 -1
			inputKey = InputKey();
			if (inputKey != 0)
			{
				if (currMonster.level > attIdx)
				{
					userAttack[attIdx] = inputKey;
					attIdx++;
				}
			}

			if (currMonster.level == attIdx)
			{
				userAttack[attIdx] = -1;
				break; // 키 입력 배열이 -1 일때

			}

		}
_D		Gotoxy(40, 18); printf("%d/%d/%d/%d/%d/%d", userAttack[0], userAttack[1], userAttack[2], userAttack[3], userAttack[4], userAttack[5]);

		// nSelMonster 죽었나 판별
		monster[nSelMonster] = CheckMonster(currMonster, userAttack);
		if (0 == monster[nSelMonster].death) 
			nExistMonster &= ~(1 << nSelMonster);
		else
		{
			for (int j = 0; j < 5; j++)
				if (!(nExistMonster & (1 << j)))
				{
					nExistMonster += (1 << j);
					monster[j] = AddMonster(nStage);
					monster[j].numOfMon = j;
					break;
				}
		}

		// 시간이 지날수록 스테이지 난이도 증가 nStage
		if (nExistMonster == 0)
		{
			Gotoxy(50, 17); 	printf("Stage Clear!");
			Gotoxy(50, 18);		printf("(자동저장되었습니다");
			user.life = 100, user.point += nStage * 100;
			SaveUser(user);
			Gotoxy(50, 19); 	printf("(아무키나 누르세요)");
			int wait = _getch();
			break;
		}
		else
		{
			if (nExistMonster == 31)
			{
				Gotoxy(50, 17); printf("Game Over");
				Gotoxy(50, 18); 	printf("(아무키나 누르세요)");
				int wait = _getch();
				user = LoadUser("_image/usersave.txt");
				Gotoxy(50, 19); 	printf("%s / %d / %d", user.name, user.life, user.point);
				user = { "Loser", 0,0 };
				return user;
			}
			nStage++;
		}
	}
}

void MonStatusRender(int nExistMonster)
{
	int x = 0, y = 0;
	TextColor();
	// 존재하는 몬스터 보이기
	for (int i = 0; i < 5; i++)
	{
		x = setLoc[6][i].x; y = setLoc[6][i].y;
		if ((1 << i) & nExistMonster)
		{
			PrintMonPic(x, y, 1);
		}
		else
		{
			PrintMonPic(x, y, -1);
		}
	}
	TextColor();
}

void AttRender(Monster monster, clock_t sclock)
{	
	// 죽어있으면 render 안함 // 1:삶 0:죽음 
	if (!(monster.death)) return;
	// 초마다 실행위한 선언
	clock_t nclock = clock();//sclock:시작, nclock:현재
	int timer = (nclock - sclock) % 1000; // (1/1000초 시간)
	int x = 0; int y = 0;
	// 몬스터 어택 그림
	int ranAtt = 0;
	while (true)  // ranAtt = 어택숫자보다 작거나 같은 attack index
	{
		ranAtt = rand() % 7;
		if (monster.attack[ranAtt]) break;
	}
	if (!timer)  //timer % 1000 = 1초 
	{
		if (nFlag == 0)
		{
			nFlag = !nFlag;
			// 몬스터 어택 그림
			TextColor(3);
			for (int i = 0; i < 5; i++)
				PrintMonAtt(monster.attack[i], monster, ranAtt);
			TextColor();
		}
		else
		{
			nFlag = !nFlag;
			// 몬스터 어택 지움
			TextColor(3);
			PrintMonAtt(111, monster, ranAtt);
			TextColor();
		}
	}
}

int SelMonster(int nExistMonster)
{
	int sel = 0;

	while (true)
	{
		switch (sel)
		{
		case 0:
			Gotoxy(127, 5); printf("●");
			Gotoxy(127, 13); printf("  ");
			Gotoxy(127, 21); printf("  ");
			Gotoxy(127, 29); printf("  ");
			Gotoxy(127, 37); printf("  ");
			break;
		case 1:
			Gotoxy(127, 5); printf("  ");
			Gotoxy(127, 13); printf("●");
			Gotoxy(127, 21); printf("  ");
			Gotoxy(127, 29); printf("  ");
			Gotoxy(127, 37); printf("  ");
			break;
		case 2:
			Gotoxy(127, 5); printf("  ");
			Gotoxy(127, 13); printf("  ");
			Gotoxy(127, 21); printf("●");
			Gotoxy(127, 29); printf("  ");
			Gotoxy(127, 37); printf("  ");
			break;
		case 3:
			Gotoxy(127, 5); printf("  ");
			Gotoxy(127, 13); printf("  ");
			Gotoxy(127, 21); printf("  ");
			Gotoxy(127, 29); printf("●");
			Gotoxy(127, 37); printf("  ");
			break;
		case 4:
			Gotoxy(127, 5); printf("  ");
			Gotoxy(127, 13); printf("  ");
			Gotoxy(127, 21); printf("  ");
			Gotoxy(127, 29); printf("  ");
			Gotoxy(127, 37); printf("●");
			break;
		default:
			break;
		}
		int key = _getch();

		switch (key)
		{
		case ARROW_UP: // up
			sel -= 1;
			break;
		case ARROW_DOWN: // down
			sel += 1;
			break;
		case 13:
			if (nExistMonster & (1 << (sel)))
			{
				return sel;
			}
			{
				Gotoxy(50, 17);
				printf("몬스터를 잘 못 선택하셨습니다");
				Sleep(400);
				Gotoxy(50, 17);
				printf("                              ");
				break;
			}
		default:
			break;
		}
		if (0 > sel) sel = 4;
		if (4 < sel) sel = 0;
	}
}

void SetPrintLocation()
{
	int relY = 2, relX = 1; // 기준 시작지점
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			setLoc[i][j] = { relY + 18 * i, relX + 8 * j };
		}
	}
}

void SelRender(int nExistMonster, Monster currMonster, clock_t sclock)
{
	// 초마다 실행
	clock_t nclock = clock();//sclock:기준시각, nclock:현재(1/1000초)
	int timer = (nclock - sclock) % 1000;
	int x = 0; int y = 0;
	nclock = clock();
	int selX = currMonster.numOfMon;
	// 깜빡이는 몬스터그림
	if (timer==0 || timer == 300 || timer == 400)  // timer 값이 0일때 한번
	{
		if (0 == nFlag)
		{
			nFlag = 1;
			// 몬스터 그림
			TextColor(12);
			x = setLoc[6][selX].x; y = setLoc[6][selX].y; PrintMonPic(x, y, 1);
		}
		else
		{
			nFlag = 0;
			// 몬스터 그림 지움
			TextColor(12);
			for (int i = 0; i < 5; i++)
				if (nExistMonster & (1 << i))
				{
					x = setLoc[6][i].x; y = setLoc[6][i].y; PrintMonPic(x, y, 0);
				}
		}
	}
	TextColor();
}

void PrintMonPic(int x, int y,int onoff) // onoff 1 : 그림 0 : 흰그림 -1 : 공백
{
	FILE *fp;
	char buffer[20];
	if (1 == onoff)
	{
		if ((fp = fopen("_image/monster.txt", "r+")) != NULL) {
			memset(buffer, 0, sizeof(buffer));
			while (fgets(buffer, INPUTBUFFER_SIZE, fp) != NULL)
			{
				Gotoxy(x, ++y);
				printf("%s", buffer);
			}
			fclose(fp);
		}
	}
	if (0 == onoff)
	{
		for (int i = 0; i < 7; i++)
		{
			Gotoxy(x, ++y);
			printf("□□□□□□□□");
		}
	}
	if (-1 == onoff)
		for (int i = 0; i < 7; i++)
		{
			Gotoxy(x, ++y);
			printf("                ");
		}
}

void PrintMonAtt(Arrow direction, Monster currMonster, int attOrder)
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
	case 111: // 화살표 지우기 입력
		strcpy(fLocation, "_image/arrow_blank.txt");
	default:
		break;
	}
	// 출력 커서 위치 지정
	int numMon = currMonster.numOfMon;
	int wCount = 0;
	//if (currMonster.attack[i] != 0)
		
	if ((fp = fopen(fLocation, "r+")) != NULL) {
		memset(buffer, 0, sizeof(buffer));
		while (fgets(buffer, INPUTBUFFER_SIZE, fp) != NULL)
		{
			Gotoxy(setLoc[numMon][attOrder].x, setLoc[numMon][attOrder].y+wCount);
			printf("%s", buffer);
			wCount++;
		}
		fclose(fp);
	}
	TextColor(); //default color
}
