#pragma once
#include<time.h>
#include<math.h>
#include<conio.h.>
#include<string.h>
#include"HStage.h"
#include"stdafx.h"
#include"Define.h"

using namespace std;

class HGame : public HCStage{
private:
	int cur_block[3];
	int next_block[3];
	int cur_x, cur_y;

public:
	int Init();
	void UpdateRender();
	int make_new_block(int* shape);
	int show_total_block();
	void SetColor(int color);
	int show_next_block(int * shape);
	int show_gamestat();
	int gotoxy(int x, int y);
	int input_data();
	int show_cur_block(int * shape, int x, int y);
	int move_down(int * x, int * y);
	int find_fair(int combo);
	int show_gameover();
	int ani_del_block(int block_arr[21][10]);
	int del_block(int block_arr[21][10], int combo);
	int show_logo();
};
