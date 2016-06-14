#include"HGame.h"

int HGame::Init()
{
	int i, j;
	cur_x = 4;
	cur_y = -2;
	for (i = 0; i < 3; i++)
	{
		cur_block[i] = 0;
		next_block[i] = 0;
	}
	
	Set_StageData(GetLevel());

	for (i = 0; i < 21; i++)
		for (j = 0; j < 10; j++)
			InitTotalBlock(i, j);

	for (i = 0; i<21; i++)
	{
		SetTotalBlock(i, 0, 9);
		SetTotalBlock(i, 9, 9);
	}
	for (i = 0; i<10; i++)
	{
		SetTotalBlock(20, i, 9);
	}
	//랜덤 seed값 넣기
	srand((unsigned)time(NULL));

	make_new_block(cur_block);
	make_new_block(next_block);
	show_total_block();
	show_next_block(next_block);
	show_gamestat();

	return 0;
}

void HGame::UpdateRender()
{
	int i;
	char keytemp;
	int is_gameover;
	int shape_tmp;
	int blank_block[3] = { 0,0,0 };
	int return_tmp;
	show_logo();
	while (1)
	{
		gotoxy(77, 23);		//화면 잔상을 없애기 위함
		cout << "  \b\b";
		input_data();
		Init();
		for (i = 1; 1; i++)
		{
			gotoxy(77, 23);		//화면 잔상을 없애기 위함
			cout << "  \b";

			if (kbhit())
			{
				keytemp = getche();
				if (keytemp == EXT_KEY)
				{
					keytemp = getche();
					show_cur_block(blank_block, cur_x, cur_y);	//이동하기전 위치의 블럭 모양을지운다
					switch (keytemp)
					{
					case KEY_UP:		//회전하기
						shape_tmp = cur_block[2];
						cur_block[2] = cur_block[1];
						cur_block[1] = cur_block[0];
						cur_block[0] = shape_tmp;

						break;
					case KEY_LEFT:		//왼쪽으로 이동
						if (cur_x>1)
						{
							if (GetTotalBlock(cur_y + 2,cur_x - 1) == 0)
								cur_x--;
						}
						break;
					case KEY_RIGHT:		//오른쪽으로 이동
						if (cur_x<8)
						{
							if (GetTotalBlock(cur_y + 2,cur_x + 1) == 0)
								cur_x++;
						}
						break;
					case KEY_DOWN:		//아래로 이동
						return_tmp = move_down(&cur_x, &cur_y);
						if (return_tmp == 1)		//블럭이 바닥에 닿았을때
						{
							if ((cur_y<0) && (GetTotalBlock(cur_y + 3, cur_x) != 0))
							{
								is_gameover = 1;
							}
							else {

								find_fair(0);
								show_total_block();
								show_gamestat();
							}
						}
						break;
					}
				}
				if (keytemp == KEY_SPACE)	//스페이스바를 눌렀을때
				{
					return_tmp = 0;
					while (return_tmp == 0)
						return_tmp = move_down(&cur_x, &cur_y);

					if ((cur_y<0) && (GetTotalBlock(cur_y + 3,cur_x) != 0))
					{
						is_gameover = 1;
					}
					else {

						find_fair(0);
						show_total_block();
						show_gamestat();
					}

				}

				show_cur_block(cur_block, cur_x, cur_y);
			}

			if (i%GetSpeed() == 0)
			{
				if (GetBlocks()>=GetClear_block())
					if (GetLevel() < 7)
					{
						Set_Level(GetLevel() + 1);
						Set_StageData(GetLevel());
					}
				show_cur_block(blank_block, cur_x, cur_y);	//이동하기전 위치의 블럭 모양을지운다
				return_tmp = move_down(&cur_x, &cur_y);		//블럭을 이동한다.

				if (return_tmp == 1)		//블럭이 바닥에 닿았을때	
				{
					if ((cur_y<0) && (GetTotalBlock(cur_y + 3, cur_x) != 0))
					{
						is_gameover = 1;
					}
					else {

						find_fair(0);
						show_total_block();
						show_gamestat();
					}
				}
				show_cur_block(cur_block, cur_x, cur_y);
			}
			if (is_gameover == 1)
			{
				show_gameover();
				SetColor(GRAY);
				break;
			}
			Sleep(13);
		}
	}
}

int HGame::make_new_block(int* shape)
{
	int i;
	int rtn_tmp;
	rtn_tmp = rand() % 100;
	if (GetRate() > rtn_tmp)	//트리플 확률로 트리플이 나올때
	{
		rtn_tmp = rand() % 5 + 1;
		shape[0] = rtn_tmp;
		shape[1] = rtn_tmp;
		shape[2] = rtn_tmp;
		return 0;
	}
	for (i = 0; i<3; i++)
	{
		shape[i] = rand() % 5 + 1;
	}
	return 0;
}

int HGame::show_total_block()
{
	int i, j;
	for (i = 0; i<21; i++)
	{
		for (j = 0; j<10; j++)
		{
			gotoxy(j * 2 + ABS_X, i + ABS_Y);
			switch (GetTotalBlock(i,j))
			{
			case 0:
				SetColor(GRAY | GRAY * 16);
				cout << "  ";
				break;
			case 1:
				SetColor(BLUE | DARK_GRAY * 16);
				cout << "●";
				break;
			case 2:
				SetColor(SKY_BLUE | DARK_GRAY * 16);
				cout << "◆";
				break;
			case 3:
				SetColor(BLACK | DARK_GRAY * 16);
				cout << "■";
				break;
			case 4:
				SetColor(GREEN | DARK_GRAY * 16);
				cout << "♥";
				break;
			case 5:
				SetColor(RED | DARK_GRAY * 16);
				cout << "★";
				break;
			case 9:
				SetColor(((GetLevel() % 6) + 1) * 16);
				cout << "  ";
				break;
			}
		}
	}

	return 0;
}

void HGame::SetColor(int color)
{
	static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_output_handle, color);

}

int HGame::show_next_block(int* shape)
{
	int i, j;
	//SetColor(((level+1)%6+1)|GRAY*16);
	for (i = 2; i<7; i++)
	{
		gotoxy(28, i);
		for (j = 0; j<5; j++)
		{
			if (i == 2 || i == 6 || j == 0 || j == 4)
			{
				SetColor(((GetLevel() + 1) % 6 + 1));
				cout << "■";
			}
			else {
				SetColor(GRAY * 16);
				cout << "  ";
			}

		}
	}
	show_cur_block(shape, 13, 1);
	return 0;
}

int HGame::show_gamestat()
{
	
	static int printed_text = 0;
	SetColor(GRAY);
	if (printed_text == 0)
	{
		gotoxy(29, 7);
		cout << "STAGE";

		gotoxy(29, 9);
		cout << "SCORE";

		gotoxy(29, 12);
		cout << "BLOCKS";

		gotoxy(29, 15);
		cout << "MAX COMBO";

	}
	gotoxy(35, 7);
	cout << "          " << GetLevel() + 1;
	gotoxy(29, 10);
	cout << "          " << (int)GetScore();
	gotoxy(29, 13);
	cout << "          " << GetClear_block() - GetBlocks();
	gotoxy(29, 16);
	cout << "          " << GetCombo();
	return 0;
}

int HGame::gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.Y = y;
	pos.X = x;
	SetConsoleCursorPosition(hConsole, pos);
	return 0;
}

int HGame::input_data()
{
	int i = 0;
	SetColor(GRAY);
	gotoxy(10, 7);
	cout << "┏━━━━<GAME KEY>━━━━━┓";
	Sleep(10);
	gotoxy(10, 8);
	cout << "┃ UP   : Rotate Block        ┃";
	Sleep(10);
	gotoxy(10, 9);
	cout << "┃ DOWN : Move One-Step Down  ┃";
	Sleep(10);
	gotoxy(10, 10);
	cout << "┃ SPACE: Move Bottom Down    ┃";
	Sleep(10);
	gotoxy(10, 11);
	cout << "┃ LEFT : Move Left           ┃";
	Sleep(10);
	gotoxy(10, 12);
	cout << "┃ RIGHT: Move Right          ┃";
	Sleep(10);
	gotoxy(10, 13);
	cout << "┗━━━━━━━━━━━━━━┛";


	while (i<1 || i>8)
	{
		gotoxy(10, 3);
		cout << "Select Start level[1-8]:       \b\b\b\b\b\b\b";
		cin >> i;
	}


	Set_Level(i - 1);
	system("cls");
	return 0;
}

int HGame::show_cur_block(int* shape, int x, int y)
{
	int i;
	for (i = 0; i<3; i++)
	{
		if (y + i <0)		//화면 위쪽의 블럭은 보여주지 않음
			continue;

		gotoxy((x * 2) + ABS_X, y + i + ABS_Y);
		cout << "  \b\b";
		switch (shape[i])
		{
		case 0:
			SetColor(GRAY * 16);
			cout <<"  ";
			break;
		case 1:
			SetColor(BLUE | WHITE * 16);
			cout << "●";
			break;
		case 2:
			SetColor(SKY_BLUE | WHITE * 16);
			cout << "◆";
			break;
		case 3:
			SetColor(BLACK | WHITE * 16);
			cout << "■";
			break;
		case 4:
			SetColor(GREEN | WHITE * 16);
			cout << "♥";
			break;
		case 5:
			SetColor(RED | WHITE * 16);
			cout << "★";
			break;
		}
	}
	return 0;
}

int HGame::move_down(int* x, int* y)
{
	int j;
	if (GetTotalBlock(*y + 3, *x))		//블럭이 바닥에 닿았을때
	{
		for (j = 0; j < 3; j++)
			SetTotalBlock(*y + j, *x, cur_block[j]);
		cur_block[0] = next_block[0];
		cur_block[1] = next_block[1];
		cur_block[2] = next_block[2];
		make_new_block(next_block);
		show_total_block();
		show_next_block(next_block);
		*x = 4;
		*y = -2;
		return 1;
	}
	else {
		(*y)++;
		return 0;
	}

}

int HGame::find_fair(int combo)
{
	int fair_num = 0;
	int i = 0, j = 1, k = 0, l = 1;
	int tmp_shape;
	int tmp_x, tmp_y;
	int fair_arr[21][10];
	int is_del_block = 0;

	for (i = 0; i<21; i++)		//fair_arr 초기화
		for (j = 0; j<10; j++)
			fair_arr[i][j] = 0;

	for (i = 0; i<20; i++)			//세로
	{
		for (j = 1; j<9; j++)		//가로
		{
			tmp_shape = GetTotalBlock(i,j);

			if (tmp_shape == 0)	//빈칸일경우 기준점을 다음칸으로 옮김
				continue;

			for (k = 0; k<4; k++)	//방향
			{
				tmp_y = i;
				tmp_x = j;
				fair_num = 0;
				for (l = 1; l<5; l++)	//깊이
				{
					switch (k)
					{
					case 0:		//기준점에서 왼쪽 아래 대각선 방향을
						tmp_y++;
						tmp_x--;
						break;
					case 1:		//기준점에서 아래 방향
						tmp_y++;
						break;
					case 2:		//기준점에서 오른쪽 아래 대각선 방향
						tmp_y++;
						tmp_x++;
						break;
					case 3:		//기준점에서 오른쪽 방향
						tmp_x++;
						break;
					}
					if (tmp_x <1 || tmp_x >12 || tmp_y > 20)
						break;
					if (GetTotalBlock(tmp_y,tmp_x) == tmp_shape)
						fair_num++;
					else
						break;
				}
				if (fair_num >= 2)
				{
					is_del_block = 1;
					tmp_y = i;
					tmp_x = j;
					for (l = 0; l <= fair_num; l++)
					{
						fair_arr[tmp_y][tmp_x] = 1;
						switch (k)
						{
						case 0:		//기준점에서 왼쪽 아래 대각선 방향을
							tmp_y++;
							tmp_x--;
							break;
						case 1:		//기준점에서 아래 방향
							tmp_y++;
							break;
						case 2:		//기준점에서 오른쪽 아래 대각선 방향
							tmp_y++;
							tmp_x++;
							break;
						case 3:		//기준점에서 오른쪽 방향
							tmp_x++;
							break;
						}
					}
				}

			}
		}
	}
	if (is_del_block == 1)	//3개이상이 연달아 있을때
	{
		combo++;
		ani_del_block(fair_arr);
		del_block(fair_arr, combo);
		show_total_block();

		if (combo > GetCombo())
			Set_Combo(combo);

		find_fair(combo);
		return 1;
	}
	return 0;
}

int HGame::show_gameover()
{
	SetColor(RED);
	gotoxy(15, 8);
	cout << "┏━━━━━━━━━━━━━┓";
	gotoxy(15, 9);
	cout << "┃**************************┃";
	gotoxy(15, 10);
	cout << "┃*        GAME OVER       *┃";
	gotoxy(15, 11);
	cout << "┃**************************┃";
	gotoxy(15, 12);
	cout << "┗━━━━━━━━━━━━━┛";
	fflush(stdin);
	Sleep(1000);

	getche();
	system("cls");

	return 0;
}

int HGame::ani_del_block(int block_arr[21][10])
{
	int i, j, k;

	for (k = 0; k<6; k++)
	{
		for (i = 0; i<21; i++)
		{
			for (j = 1; j<9; j++)
			{
				if (block_arr[i][j] == 0)
					continue;

				gotoxy(j * 2 + ABS_X, i + ABS_Y);
				switch (GetTotalBlock(i,j))
				{
				case 1:
					SetColor(BLUE | (DARK_GRAY + (k % 2)) * 16);
					cout << "●";
					break;
				case 2:
					SetColor(SKY_BLUE | (DARK_GRAY + (k % 2)) * 16);
					cout << "◆";
					break;
				case 3:
					SetColor(BLACK | (DARK_GRAY + (k % 2)) * 16);
					cout << "■";
					break;
				case 4:
					SetColor(GREEN | (DARK_GRAY + (k % 2)) * 16);
					cout << "♥";
					break;
				case 5:
					SetColor(RED | (DARK_GRAY + (k % 2)) * 16);
					cout << "★";
					break;
				}


				Sleep(24);
			}

		}

	}
	return 0;
}

int HGame::del_block(int block_arr[21][10], int combo)
{
	int i, j, k;
	int block_num = 0;		//없애는 블럭의 개수
	for (i = 19; i >= 0; i--)
	{
		for (j = 1; j<9; j++)
		{

			if (block_arr[i][j] == 1)
			{
				SetTotalBlock(i, j, 0);
				block_num++;
				Set_Blocks(GetBlocks() + 1);
			}

		}
	}
	for (i = 0; i<20; i++)
	{
		for (j = 1; j<9; j++)
		{
			if (GetTotalBlock(i,j) != 0)
				continue;

			for (k = i; k >= 0; k--)	//블럭을비운 빈공간을 위에 있는 블럭으로 채운다.
			{
				if (k == 0)
				{
					SetTotalBlock(k, j, 0);

				}
				else {
					SetTotalBlock(k, j, GetTotalBlock(k - 1, j));

				}
			}

		}
	}

	//점수 계산
	Set_Score(GetScore() + ( GetCombo() * 1.3 * (block_num * 12)));
	return 0;
}

int HGame::show_logo()
{
	int i, j;
	int cur_color = 0;
	gotoxy(13, 3);
	cout << "┏━━━━━━━━━━━━━━━━━━━━━━━┓";
	Sleep(100);
	gotoxy(13, 4);
	cout << "┃★      ★  ★★★★★  ★      ★     ★★   ┃";
	Sleep(100);
	gotoxy(13, 5);
	cout << "┃★      ★  ★            ★  ★     ★    ★ ┃";
	Sleep(100);
	gotoxy(13, 6);
	cout << "┃★★★★★  ★★★★★      ★      ★★★★★┃";
	Sleep(100);
	gotoxy(13, 7);
	cout << "┃★      ★  ★            ★  ★    ★      ★┃";
	Sleep(100);
	gotoxy(13, 8);
	cout << "┃★      ★  ★★★★★  ★      ★  ★      ★┃";
	Sleep(100);
	gotoxy(13, 9);
	cout << "┗━━━━━━━━━━━━━━━━━━━━━━━┛";
	gotoxy(13, 10);
	cout << " Ver 0.1                         Made By Jae-Dong  ";


	gotoxy(28, 20);
	cout << "Please Press Any Key~!";

	for (i = 0; i >= 0; i++)
	{
		if (i % 8 == 0)
		{
			gotoxy(20, 19);
			for (j = 0; j<37; j++)
			{
				SetColor((cur_color + j) % 16 * 16);
				cout << " ";
				//cur_color = (cur_color+j)%16;
			}
			if (cur_color >0)
				cur_color--;
			else
				cur_color = 15;
			//Sleep(100);
		}
		if (kbhit())
			break;
		Sleep(10);
	}

	getche();
	SetColor(GRAY);
	system("cls");

	return 0;
}