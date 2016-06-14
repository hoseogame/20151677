#pragma once

using namespace std;

class TCStage{
private:
	int speed;
	int stick_rate;	
	int clear_line;
	int total_block[21][14];
	int level;
	int lines;
	int score;
public:
	void Set_StageData(int n);
	void Set_Level(int n);
	void Set_Line(int n);
	void Set_Score(int n);
	int GetRate();
	int GetSpeed();
	int GetClear_line();
	int GetLevel();
	int GetLine();
	int GetScore();
	
};