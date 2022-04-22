#if !defined(MINESWEEPWER_h)
#define MINESWEEPWER_h

#include <iostream>
#include <chrono>
#include <array>
#include <time.h>
#include <random>

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
    OPEN,
    AUTOS,
};

using namespace std;
class minesweeper
{
private:
    array<array<bool, MAXCOL>, MAXLN> mineBoard{false};
    array<array<int, 2>, 8> sides{{{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}}};
    void generate();
    bool checkThisMine(int col, int ln);
    int checkRoundMine(int col, int ln);
    void showBoard();
    void openSides(int col, int ln);
    void lose();
    void win();

public:
    int boardCol, boardLn, mine, flags;
    array<array<char, MAXCOL>, MAXLN> coverBoard{};
    array<array<bool, MAXCOL>, MAXLN> opened{false};

    void setBoard(int diffi);
    void setAttrib(int diffi);
    void init();

    void operate(int col, int ln, int mov);
};

#endif // MINESWEEPWER_h
