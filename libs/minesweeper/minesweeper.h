#if !defined(MINESWEEPWER_h)
#define MINESWEEPWER_h

#include <iostream>
#include <chrono>
#include <array>
#include <time.h>

#define MAXLN 16
#define MAXCOL 30

enum mode
{
    EASY,
    MEDIUM,
    HARD
};

enum moves
{
    FLAG,
    OPEN
};

using namespace std;
class minesweeper
{
private:
    bool mineBoard[MAXCOL][MAXLN]{false};
    // int sides[8][2]{{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};
    array<array<int, 2>, 8> sides{{{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}}};
    void generate();
    bool checkThisMine(int col, int ln);
    int checkRoundMine(int col, int ln);
    void setAttrib(int diffi);
    void showBoard();
    void openSides(int col, int ln);
    void lose();
    void win();

public:
    int boardCol, boardLn, mine, flags;
    //char coverBoard[MAXCOL][MAXLN]{};
    array<array<char, MAXCOL>, MAXLN> coverBoard{};
    bool opened[MAXLN][MAXCOL]{false};

    void setBoard(int diffi);
    void operate(int col, int ln, int mov);
};

#endif // MINESWEEPWER_h
