#include "HStage.h"

//HCStage::HCStage()
//{
//}
//
//HCStage::~HCStage()
//{
//}

void HCStage::Set_StageData(int n)
{
	speed = 40 - (3 * n);
	clear_block = 60 + (10 * n);
	triple_rate = 8 - n;
	blocks = 0;
	max_combo = 0;
}

void HCStage::Set_Level(int n)
{
	level = n;
}

void HCStage::Set_Combo(int n)
{
	max_combo = n;
}

void HCStage::Set_Blocks(int n)
{
	blocks = n;
}

void HCStage::Set_Score(double n)
{
	score = n;
}

int HCStage::GetRate()
{
	return triple_rate;
}

int HCStage::GetSpeed()
{
	return speed;
}

int HCStage::GetClear_block()
{
	return clear_block;
}

int HCStage::GetLevel()
{
	return level;
}

int HCStage::GetBlocks()
{
	return blocks;
}

int HCStage::GetCombo()
{
	return max_combo;
}

double HCStage::GetScore()
{
	return score;
}

int HCStage::GetTotalBlock(int i, int j)
{
	return total_block[i][j];
}

void HCStage::InitTotalBlock(int i, int j)
{
	total_block[i][j] = 0;
}

void HCStage::SetTotalBlock(int i, int j, int n)
{
	total_block[i][j] = n;
}
