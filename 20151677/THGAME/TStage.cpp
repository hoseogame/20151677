#include "TStage.h"

void TCStage::Set_StageData(int n)
{
	speed = 40 - (3 * n);
	clear_line = 10 + (2 * n);
	stick_rate = 20 - (1.5 * n);
	lines = 0;
}

void TCStage::Set_Level(int n)
{
	level = n;
}

void TCStage::Set_Line(int n)
{
	lines = n;
}

void TCStage::Set_Score(int n)
{
	score = n;
}

int TCStage::GetRate()
{
	return stick_rate;
}

int TCStage::GetSpeed()
{
	return speed;
}

int TCStage::GetClear_line()
{
	return clear_line;
}

int TCStage::GetLevel()
{
	return level;
}

int TCStage::GetLine()
{
	return lines;
}

int TCStage::GetScore()
{
	return score;
}