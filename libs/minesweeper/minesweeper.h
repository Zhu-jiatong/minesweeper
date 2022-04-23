#if !defined(MINESWEEPWER_h)
#define MINESWEEPWER_h

#include <iostream>
#include <chrono>
#include <array>
#include <time.h>
#include <random>
#include <vector>

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
    // array<array<bool, MAXCOL>, MAXLN> mineBoard{false};
    vector<vector<bool>> mineBoard;
    array<array<int, 2>, 8> sides{{{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}}};
    void generate(int num);
    int countRoundMine(int col, int ln);
    void showBoard();
    bool isValid(int col, int ln);
    void openSides(int col, int ln);
    void lose();
    void win();

public:
    int boardCol, boardLn, mine, flags, opened{};
    // array<array<char, MAXCOL>, MAXLN> coverBoard{};
    vector<vector<char>> coverBoard;
    // array<array<bool, MAXCOL>, MAXLN> opened{false};

    void setAttrib(int diffi);
    void init();

    void operate(int col, int ln, int mov);
};

#endif // MINESWEEPWER_h
