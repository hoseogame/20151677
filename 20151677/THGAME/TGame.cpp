#include"TGame.h"

int TGame::Init()
{
	int i, j;
	ab_x = 5;
	ab_y = 1;

	//랜덤 seed값 넣기
	srand((unsigned)time(NULL));
	Set_StageData(GetLevel());

	//화면 배열 초기화
	for (i = 0; i<20; i++)
	{
		for (j = 0; j<14; j++)
		{
			if ((j == 0) || (j == 13))
			{
				total_block[i][j] = 1;
			}
			else {
				total_block[i][j] = 0;
			}
		}
	}

	for (j = 0; j<14; j++)			//화면의 제일 밑의 줄은 1로 채운다.
		total_block[20][j] = 1;

	return 0;
}

void TGame::UpdateRender()
{
	int i;
	int is_gameover = 0;
	char keytemp;

	show_logo();
	Init();
	while (1)
	{
		input_data();
		
		show_total_block();
		block_shape = make_new_block();
		next_block_shape = make_new_block();
		show_next_block(next_block_shape);
		block_start(block_shape, &block_angle, &block_x, &block_y);
		show_gamestat();
		for (i = 1; 1; i++)
		{
			if (kbhit())
			{
				keytemp = getche();
				if (keytemp == EXT_KEY)
				{
					keytemp = getche();
					switch (keytemp)
					{
					case KEY_UP:		//회전하기

						if (strike_check(block_shape, (block_angle + 1) % 4, block_x, block_y) == 0)
						{
							erase_cur_block(block_shape, block_angle, block_x, block_y);
							block_angle = (block_angle + 1) % 4;
							show_cur_block(block_shape, block_angle, block_x, block_y);
						}
						break;
					case KEY_LEFT:		//왼쪽으로 이동
						if (block_x > 1)
						{
							erase_cur_block(block_shape, block_angle, block_x, block_y);
							block_x--;
							if (strike_check(block_shape, block_angle, block_x, block_y) == 1)
								block_x++;

							show_cur_block(block_shape, block_angle, block_x, block_y);
						}
						break;
					case KEY_RIGHT:		//오른쪽으로 이동

						if (block_x < 14)
						{
							erase_cur_block(block_shape, block_angle, block_x, block_y);
							block_x++;
							if (strike_check(block_shape, block_angle, block_x, block_y) == 1)
								block_x--;
							show_cur_block(block_shape, block_angle, block_x, block_y);
						}
						break;
					case KEY_DOWN:		//아래로 이동
						is_gameover = move_block(&block_shape, &block_angle, &block_x, &block_y, &next_block_shape);
						show_cur_block(block_shape, block_angle, block_x, block_y);
						break;
					}
				}
				if (keytemp == 32)	//스페이스바를 눌렀을때
				{
					while (is_gameover == 0)
					{
						is_gameover = move_block(&block_shape, &block_angle, &block_x, &block_y, &next_block_shape);
					}
					show_cur_block(block_shape, block_angle, block_x, block_y);
				}
			}
			if (i%GetSpeed() == 0)
			{
				is_gameover = move_block(&block_shape, &block_angle, &block_x, &block_y, &next_block_shape);

				show_cur_block(block_shape, block_angle, block_x, block_y);
			}

			if (GetClear_line() <= GetLine())	//클리어 스테이지
			{
				Set_Level(GetLevel() + 1);
				Set_StageData(GetLevel());
			}
			if (is_gameover == 1)
			{
				show_gameover();
				SetColor(GRAY);
				is_gameover = 0;
				break;
			}

			gotoxy(77, 23);
			Sleep(15);
			gotoxy(77, 23);
		}
		Init();
	}
}

int TGame::make_new_block()
{
	int shape;
	int i;
	i = rand() % 100;
	if (i <= GetRate())		//막대기 나올확률 계산
		return 0;							//막대기 모양으로 리턴

	shape = (rand() % 6) + 1;		//shape에는 1~6의 값이 들어감
	show_next_block(shape);
	return shape;
}

int TGame::show_total_block()
{
	int i, j;
	SetColor(DARK_GRAY);
	for (i = 0; i<21; i++)
	{
		for (j = 0; j<14; j++)
		{
			if (j == 0 || j == 13 || i == 20)		//레벨에 따라 외벽 색이 변함
			{
				SetColor((GetLevel() % 6) + 1);

			}
			else {
				SetColor(DARK_GRAY);
			}
			gotoxy((j * 2) + ab_x, i + ab_y);
			if (total_block[i][j] == 1)
			{
				cout << "■";
			}
			else {
				cout << "  ";
			}
		}
	}

	SetColor(BLACK);
	gotoxy(77, 23);
	return 0;

	return 0;
}

void TGame::SetColor(int color)
{
	static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_output_handle, color);

}

int TGame::show_next_block(int shape)
{
	int i, j;
	SetColor((GetLevel() + 1) % 6 + 1);
	for (i = 1; i<7; i++)
	{
		gotoxy(33, i);
		for (j = 0; j<6; j++)
		{
			if (i == 1 || i == 6 || j == 0 || j == 5)
			{
				cout <<"■";
			}
			else {
				cout <<"  ";
			}

		}
	}
	show_cur_block(shape, 0, 15, 1);
	return 0;
}

int TGame::show_gamestat()
{

	static int printed_text = 0;
	SetColor(GRAY);
	if (printed_text == 0)
	{
		gotoxy(35, 7);
		cout <<"STAGE";

		gotoxy(35, 9);
		cout <<"SCORE";

		gotoxy(35, 12);
		cout <<"LINES";

	}
	gotoxy(41, 7);
	cout << "    " << GetLevel() + 1 << " ";
	gotoxy(35, 10);
	cout << "          " << GetScore() << " ";
	gotoxy(35, 13);
	cout << "          " << GetClear_line() - GetLine() << " ";
	return 0;
}

int TGame::gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.Y = y;
	pos.X = x;
	SetConsoleCursorPosition(hConsole, pos);
	return 0;
}

int TGame::input_data()
{
	int i = 0;
	SetColor(GRAY);
	gotoxy(10, 7);
	cout <<"┏━━━━<GAME KEY>━━━━━┓";
	Sleep(10);
	gotoxy(10, 8);
	cout <<"┃ UP   : Rotate Block        ┃";
	Sleep(10);
	gotoxy(10, 9);
	cout <<"┃ DOWN : Move One-Step Down  ┃";
	Sleep(10);
	gotoxy(10, 10);
	cout <<"┃ SPACE: Move Bottom Down    ┃";
	Sleep(10);
	gotoxy(10, 11);
	cout <<"┃ LEFT : Move Left           ┃";
	Sleep(10);
	gotoxy(10, 12);
	cout <<"┃ RIGHT: Move Right          ┃";
	Sleep(10);
	gotoxy(10, 13);
	cout <<"┗━━━━━━━━━━━━━━┛";


	while (i<1 || i>8)
	{
		gotoxy(10, 3);
		cout <<"Select Start level[1-8]:       \b\b\b\b\b\b\b";
		scanf("%d", &i);
	}


	Set_Level(i - 1);
	system("cls");
	return 0;
}

int TGame::check_full_line()
{
	int i, j, k;
	for (i = 0; i<20; i++)
	{
		for (j = 1; j<13; j++)
		{
			if (total_block[i][j] == 0)
				break;
		}
		if (j == 13)	//한줄이 다 채워졌음
		{
			Set_Line(GetLine() + 1);
			show_total_block();
			SetColor(BLUE);
			gotoxy(1 * 2 + ab_x, i + ab_y);
			for (j = 1; j<13; j++)
			{
				cout <<"□";
				Sleep(10);
			}
			gotoxy(1 * 2 + ab_x, i + ab_y);
			for (j = 1; j<13; j++)
			{
				cout <<"  ";
				Sleep(10);
			}

			for (k = i; k>0; k--)
			{
				for (j = 1; j < 13; j++)
					total_block[k][j] = total_block[k - 1][j];
			}
			for (j = 1; j < 13; j++)
				total_block[0][j] = 0;

			Set_Score(GetScore() + 100 + (GetLevel() * 10) + (rand() % 10));
			show_gamestat();
		}
	}
	return 0;
}

int TGame::show_cur_block(int shape, int angle, int x, int y)
{
	int i, j;

	switch (shape)
	{
	case 0:
		SetColor(RED);
		break;
	case 1:
		SetColor(BLUE);
		break;
	case 2:
		SetColor(SKY_BLUE);
		break;
	case 3:
		SetColor(WHITE);
		break;
	case 4:
		SetColor(YELLOW);
		break;
	case 5:
		SetColor(VOILET);
		break;
	case 6:
		SetColor(GREEN);
		break;
	}

	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			if ((j + y) <0)
				continue;

			if (block[shape][angle][j][i] == 1)
			{
				gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
				cout <<"■";

			}
		}
	}
	SetColor(BLACK);
	gotoxy(77, 23);
	return 0;
}

int TGame::erase_cur_block(int shape, int angle, int x, int y)
{
	int i, j;
	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			if (block[shape][angle][j][i] == 1)
			{
				gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
				cout <<"  ";
				//break;
			}
		}
	}
	return 0;
}

int TGame::show_gameover()
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

int TGame::show_logo()
{
	int i, j;
	gotoxy(13, 3);
	cout <<"┏━━━━━━━━━━━━━━━━━━━━━━━┓";
	Sleep(100);
	gotoxy(13, 4);
	cout <<"┃◆◆◆  ◆◆◆  ◆◆◆   ◆◆     ◆   ◆  ◆ ┃";
	Sleep(100);
	gotoxy(13, 5);
	cout <<"┃  ◆    ◆        ◆     ◆ ◆    ◆    ◆◆  ┃";
	Sleep(100);
	gotoxy(13, 6);
	cout <<"┃  ◆    ◆◆◆    ◆     ◆◆     ◆     ◆   ┃";
	Sleep(100);
	gotoxy(13, 7);
	cout <<"┃  ◆    ◆        ◆     ◆ ◆    ◆    ◆◆  ┃";
	Sleep(100);
	gotoxy(13, 8);
	cout <<"┃  ◆    ◆◆◆    ◆     ◆  ◆   ◆   ◆  ◆ ┃";
	Sleep(100);
	gotoxy(13, 9);
	cout <<"┗━━━━━━━━━━━━━━━━━━━━━━━┛";
	gotoxy(13, 10);
	cout <<" Ver 0.1                         Made By Jae-Dong  ";


	gotoxy(28, 20);
	cout <<"Please Press Any Key~!";

	for (i = 0; i >= 0; i++)
	{
		if (i % 40 == 0)
		{


			for (j = 0; j<5; j++)
			{
				gotoxy(18, 14 + j);
				cout <<"                                                          ";


			}
			show_cur_block(rand() % 7, rand() % 4, 6, 14);
			show_cur_block(rand() % 7, rand() % 4, 12, 14);
			show_cur_block(rand() % 7, rand() % 4, 19, 14);
			show_cur_block(rand() % 7, rand() % 4, 24, 14);
		}
		if (kbhit())
			break;
		Sleep(30);
	}

	getche();
	system("cls");

	return 0;
}

int TGame::strike_check(int shape, int angle, int x, int y)
{
	int i, j;
	int block_dat;

	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			if (((x + j) == 0) || ((x + j) == 13))
				block_dat = 1;
			else
				block_dat = total_block[y + i][x + j];


			if ((block_dat == 1) && (block[shape][angle][i][j] == 1))																							//좌측벽의 좌표를 빼기위함
			{
				return 1;
			}
		}
	}
	return 0;
}

int TGame::merge_block(int shape, int angle, int x, int y)
{
	int i, j;
	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			total_block[y + i][x + j] |= block[shape][angle][i][j];
		}
	}
	check_full_line();
	show_total_block();

	return 0;
}

int TGame::block_start(int shape, int * angle, int * x, int * y)
{
	*x = 5;
	*y = -1;
	*angle = 0;
	return 0;
}

int TGame::move_block(int * shape, int * angle, int * x, int * y, int *next_shape)
{
	erase_cur_block(*shape, *angle, *x, *y);

	(*y)++;	//블럭을 한칸 아래로 내림
	if (strike_check(*shape, *angle, *x, *y) == 1)
	{
		if (*y <= 0)	//게임오버
		{
			return 1;
		}
		(*y)--;
		merge_block(*shape, *angle, *x, *y);
		*shape = *next_shape;
		*next_shape = make_new_block();

		block_start(*shape, angle, x, y);	//angle,x,y는 포인터임
		show_next_block(*next_shape);
		return 2;
	}
	return 0;
}



