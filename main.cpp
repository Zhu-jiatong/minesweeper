#include "libs\libs.h"

using namespace std;

minesweeper myGame;

int main(int argc, char const *argv[])
{
	while (true)
	{
		cout << "0 - EASY\n"
			 << "1 - MEDIUM\n"
			 << "2 - HARD\n"
			 << "GAME_MODE: ";
		int gMode;
		cin >> gMode;
		myGame.setAttrib(gMode);
		myGame.init();
	}

	return 0;
}
