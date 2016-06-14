#pragma once
#include<time.h>
#include<math.h>
#include<conio.h.>
#include<string.h>
#include"TStage.h"
#include"stdafx.h"
#include"Define.h"

using namespace std;



class TGame : public TCStage{
private:
	int block_shape;
	int next_block_shape;
	int block_angle;
	int block_x;
	int block_y;
	int ab_x;
	int ab_y;
	int total_block[21][14];

	char block[7][4][4][4] = {
		//막대모양
		1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,

		//네모모양
		1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,

		//'ㅓ' 모양
		0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,

		//'ㄱ'모양
		1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,	0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,

		//'ㄴ' 모양
		1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,	1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,	1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,

		//'Z' 모양
		1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,

		//'S' 모양
		0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0

	};

public:
	int Init();
	void UpdateRender();
	int gotoxy(int x, int y);	//커서옮기기
	void SetColor(int color);	//색표
	int show_cur_block(int shape, int angle, int x, int y);	//진행중인 블럭을 화면에 표시한다
	int erase_cur_block(int shape, int angle, int x, int y);	//블럭 진행의 잔상을 지우기 위한 함수
	int show_total_block();	//쌓여져있는 블럭을 화면에 표시한다.
	int show_next_block(int shape);
	int make_new_block();	//return값으로 block의 모양번호를 알려줌
	int strike_check(int shape, int angle, int x, int y);	//블럭이 화면 맨 아래에 부닥쳤는지 검사 부닥치면 1을리턴 아니면 0리턴
	int merge_block(int shape, int angle, int x, int y);	//블럭이 바닥에 닿았을때 진행중인 블럭과 쌓아진 블럭을 합침
	int block_start(int shape, int* angle, int* x, int* y);	//블럭이 처음 나올때 위치와 모양을 알려줌
	int move_block(int* shape, int* angle, int* x, int* y, int* next_shape);	//게임오버는 1을리턴 바닥에 블럭이 닿으면 2를 리턴
	int show_gameover();
	int show_gamestat();
	int show_logo();
	int input_data();
	int check_full_line();
};
