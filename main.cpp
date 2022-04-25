#include "libs\libs.h"
using namespace std;

minesweeper myGame;

int main(int argc, char const *argv[])
{
	while (true)
	{
		system("cls");
		cout << "0 - EASY (board: 8*8, mines: 10)\n"
			 << "1 - MEDIUM (board: 16*16, mines: 40)\n"
			 << "2 - HARD (board: 16*30, mines: 99)\n"
			 << "3 - CUSTOM\n"
			 << "Select game mode: ";
		int gMode;
		cin >> gMode;
		myGame.setAttrib(gMode);
		myGame.init();
	}

	return 0;
}
