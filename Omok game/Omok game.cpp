#include<iostream>
#include<windows.h>

using namespace std;

int pan[19][19] = { 0, };		// 바둑 판

typedef struct coor {
	int x = 0;					// 마우스 x 좌표
	int y = 0;					// 마우스 y 좌표
}xy;

void gotoxy(int xx, int yy)	// 좌표 함수
{
	COORD pos = { xx,yy };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void draw()
{
	gotoxy(0, 0);
	for (int a = 0; a < 19; a++)			// 바둑 판 첫번째 줄
	{
		if (a == 0)
			cout << "┏ ";
		else if (a == 18)
			cout << "┓" << endl;
		else
			cout << "╋ ";
	}
	for (int a = 0; a < 17; a++)			// 바둑판 2번쨰 ~ 18번째 줄
	{
		for (int r = 0; r < 19; r++)
		{
			cout << "╋ ";
		}
		cout << endl;
	}
	for (int a = 0; a < 19; a++)			// 바둑판 마지막 줄
	{
		if (a == 0)
			cout << "┗ ";
		else if (a == 18)
			cout << "┛" << endl;
		else
			cout << "╋ ";
	}
	cout << endl;
}
void doll()
{
	for (int a = 0; a < 19; a++)
	{
		for (int b = 0; b < 19; b++)
		{
			if (pan[b][a] == 1)
			{
				gotoxy(a * 2, b);
				cout << "○";
			}
			else if (pan[b][a] == 2)
			{
				gotoxy(a * 2, b);
				cout << "●";
			}
		}
	}
}

void check_mouse(xy co, int turn)
{
	DWORD        dwNOER;
	INPUT_RECORD rec;
	COORD        pos = { 0,1 };
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	while (1)
	{
		co.x = 0;
		co.y = 0;
		ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &rec, 1, &dwNOER);
		if (rec.EventType == MOUSE_EVENT)										// 마우스 이벤트
		{
			if (rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)	//마우스 이벤트 + 왼쪽 클릭
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				co.x = rec.Event.MouseEvent.dwMousePosition.X;			// x의 좌표값
				co.y = rec.Event.MouseEvent.dwMousePosition.Y;			// y의 좌표값
				if (co.x % 2 != 0)										// x가 홀수
				{
					co.x = ((co.x + 1) / 2) - 1;
				}
				else													// x가 짝수
				{
					co.x /= 2;
				}

				if (co.x > 18 || co.y > 18 || pan[co.y][co.x] != 0)
				{
					gotoxy(5, 21);
					cout << " 잘못된 입력입니다. 다시 입력하세요";
				}
				else
				{
					if (turn % 2 != 0)
					{
						pan[co.y][co.x] = 1;
					}
					else
					{
						pan[co.y][co.x] = 2;
					}
					gotoxy(5, 21);
					cout << "                                   ";
					break;
				}
			}
		}
	}
}

int check_right(int ck)								// 가로
{
	int check_1num = 0;
	for (int a = 0; a < 19; a++)
	{
		for (int b = 0; b < 19; b++)
		{
			if (pan[a][b] != 0)
			{
				if (b == 0 && pan[a][b + 5] != ck)
				{
					if (pan[a][b] == ck && pan[a][b + 1] == ck && pan[a][b + 2] == ck && pan[a][b + 3] == ck && pan[a][b + 4] == ck)
						check_1num++;
				}
				else if (b + 5 > 19)
				{
					check_1num = 0;
				}
				else if (pan[a][b - 1] != ck && pan[a][b + 5] != ck)
				{
					if (pan[a][b] == ck && pan[a][b + 1] == ck && pan[a][b + 2] == ck && pan[a][b + 3] == ck && pan[a][b + 4] == ck)
						check_1num++;
				}
				if (check_1num == 1)
					return ck;
			}
		}
	}
	return 0;
}
int check_rightdown(int ck)								// 오른쪽 아래
{
	int check_1num = 0;
	for (int a = 0; a < 19; a++)
	{
		for (int b = 0; b < 19; b++)
		{
			if (pan[a][b] != 0)
			{
				if (a == 0 && b == 0 && pan[a + 5][b + 5] != ck)
				{
					if (pan[a][b] == ck && pan[a + 1][b + 1] == ck && pan[a + 2][b + 2] == ck && pan[a + 3][b + 3] == ck && pan[a + 4][b + 4] == ck)
						check_1num++;
				}
				else if (b + 5 > 19 || a + 5 > 19)
				{
					check_1num = 0;
				}
				else if (pan[a - 1][b - 1] != ck && pan[a + 5][b + 5] != ck)
				{
					if (pan[a][b] == ck && pan[a + 1][b + 1] == ck && pan[a + 2][b + 2] == ck && pan[a + 3][b + 3] == ck && pan[a + 4][b + 4] == ck)
						check_1num++;
				}
				if (check_1num == 1)
					return ck;
			}
		}
	}
	return 0;
}
int check_rightup(int ck)								// 왼쪽 아래
{
	int check_1num = 0;
	for (int a = 0; a < 19; a++)
	{
		for (int b = 0; b < 19; b++)
		{
			if (pan[a][b] != 0)
			{
				if (a - 4 < 0 || b + 4 > 18)
				{
					check_1num = 0;
				}
				else if (pan[a + 1][b - 1] != ck && pan[a - 5][b + 5] != ck)
				{
					if (pan[a][b] == ck && pan[a - 1][b + 1] == ck && pan[a - 2][b + 2] == ck && pan[a - 3][b + 3] == ck && pan[a - 4][b + 4] == ck)
						check_1num++;
				}
				if (check_1num == 1)
					return ck;
			}
		}
	}
	return 0;
}
int check_down(int ck)
{
	int check_1num = 0;
	for (int a = 0; a < 19; a++)
	{
		for (int b = 0; b < 19; b++)
		{
			if (pan[a][b] != 0)
			{
				if (a == 0 && pan[a + 5][b] != ck)
				{
					if (pan[a][b] == ck && pan[a + 1][b] == ck && pan[a + 2][b] == ck && pan[a + 3][b] == ck && pan[a + 4][b] == ck)
						check_1num++;
				}
				else if (a + 5 > 19)
				{
					check_1num = 0;
				}
				else if (pan[a - 1][b] != ck && pan[a + 5][b] != ck)
				{
					if (pan[a][b] == ck && pan[a + 1][b] == ck && pan[a + 2][b] == ck && pan[a + 3][b] == ck && pan[a + 4][b] == ck)
						check_1num++;
				}
				if (check_1num == 1)
					return ck;
			}
		}
	}
	return 0;
}
int check_pan()
{
	int check = 0;
	for (int a = 0; a < 19; a++)
	{
		for (int b = 0; b < 19; b++)
		{
			if (pan[a][b] == 0)
				check++;
		}
	}
	if (check == 0)
		return 1;
	else
		return 0;
}

void main()
{
	system("mode con cols=50 lines=33");// 콘솔 창 크기
	system("title 오목게임");			// 이름
	xy coor;							// 좌표 구조체
	int turn_check = 1;
	int checkck = 0;

	while (1)
	{
		if (check_pan() == 1)			// 무승부, 더이상 돌을 놓을 수 없을 떄
		{
			gotoxy(5, 24);
			cout << " 공간이 없습니다. <무승부> 리셋합니다" << endl;
			pan[18][18] = { 0, };
			turn_check = 1;
		}
		draw();						// 바둑판 그리기
		doll();						// 돌 놓기
		// 승리조건, 리턴값이 1이면 흑돌 승
		if (check_rightup(checkck) == 1 || check_right(checkck) == 1 || check_rightdown(checkck) == 1 || check_down(checkck) == 1)
		{
			gotoxy(5, 23);
			cout << " 게임 승리!! <흑돌 승>" << endl;
			system("pause");
			break;
		}
		// 승리조건, 리턴값이 2이면 백돌 승
		else if (check_rightup(checkck) == 2 || check_right(checkck) == 2 || check_rightdown(checkck) == 2 || check_down(checkck) == 2)
		{
			gotoxy(5, 23);
			cout << " 게임 승리!! <백돌 승>" << endl;
			system("pause");
			break;
		}
		if (turn_check % 2 != 0)		// turn_check이 홀수면 흑돌차례
		{
			gotoxy(5, 23);
			cout << " 흑돌차례" << endl;
			checkck = 1;
		}
		else							// turn_check이 짝수면 백돌차례
		{
			gotoxy(5, 23);
			cout << " 백돌차례" << endl;
			checkck = 2;
		}
		check_mouse(coor, turn_check);		// 마우스 클릭 
		turn_check++;
		system("cls");
	}
}
