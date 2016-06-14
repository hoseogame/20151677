#include<iostream>
using namespace std;
#include"TGame.h"
#include"HGame.h"

int main()
{
	int n;

	cout << "테트리스와 헥사 게임중 하고 싶은 것을 고르세요." << endl;
	cout << "1 : 테트리스    2 : 헥사 " << endl;
	cout << "-1 : 종료" << endl;

	while (1)
	{
		cin >> n;

		if (n == 1)
		{
			TGame *tgame = new TGame();
			tgame->UpdateRender();
			free(tgame);
		}
		else if (n == 2)
		{
			HGame *hgame = new HGame();
			hgame->UpdateRender();
			free(hgame);
		}
		else if (n == -1)
			break;
		else
			cout << "둘 중 하나를 다시 고르세요." << endl;
	}



	return 0;
}