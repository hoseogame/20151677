#include<iostream>
using namespace std;
#include"TGame.h"
#include"HGame.h"

int main()
{
	int n;

	cout << "��Ʈ������ ��� ������ �ϰ� ���� ���� ������." << endl;
	cout << "1 : ��Ʈ����    2 : ��� " << endl;
	cout << "-1 : ����" << endl;

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
			cout << "�� �� �ϳ��� �ٽ� ������." << endl;
	}



	return 0;
}