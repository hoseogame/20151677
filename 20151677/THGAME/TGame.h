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
		//������
		1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,

		//�׸���
		1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,

		//'��' ���
		0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,

		//'��'���
		1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,	0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,

		//'��' ���
		1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,	1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,	1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,

		//'Z' ���
		1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,

		//'S' ���
		0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0

	};

public:
	int Init();
	void UpdateRender();
	int gotoxy(int x, int y);	//Ŀ���ű��
	void SetColor(int color);	//��ǥ
	int show_cur_block(int shape, int angle, int x, int y);	//�������� ���� ȭ�鿡 ǥ���Ѵ�
	int erase_cur_block(int shape, int angle, int x, int y);	//�� ������ �ܻ��� ����� ���� �Լ�
	int show_total_block();	//�׿����ִ� ���� ȭ�鿡 ǥ���Ѵ�.
	int show_next_block(int shape);
	int make_new_block();	//return������ block�� ����ȣ�� �˷���
	int strike_check(int shape, int angle, int x, int y);	//���� ȭ�� �� �Ʒ��� �δ��ƴ��� �˻� �δ�ġ�� 1������ �ƴϸ� 0����
	int merge_block(int shape, int angle, int x, int y);	//���� �ٴڿ� ������� �������� ���� �׾��� ���� ��ħ
	int block_start(int shape, int* angle, int* x, int* y);	//���� ó�� ���ö� ��ġ�� ����� �˷���
	int move_block(int* shape, int* angle, int* x, int* y, int* next_shape);	//���ӿ����� 1������ �ٴڿ� ���� ������ 2�� ����
	int show_gameover();
	int show_gamestat();
	int show_logo();
	int input_data();
	int check_full_line();
};
