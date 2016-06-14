#pragma once

using namespace std;

class HCStage{
private:
	int speed;
	int triple_rate;
	int clear_block;
	int total_block[21][10];
	int level;
	int blocks;
	int max_combo;
	double score;

public:
	//CStage();
	//~CStage();
	void Set_StageData(int n);
	void Set_Level(int n);
	void Set_Combo(int n);
	void Set_Blocks(int n);
	void Set_Score(double n);
	int GetRate();
	int GetSpeed();
	int GetClear_block();
	int GetLevel();
	int GetBlocks();
	int GetCombo();
	double GetScore();
	int GetTotalBlock(int i, int j);
	void InitTotalBlock(int i, int j);
	void SetTotalBlock(int i, int j, int n);
};