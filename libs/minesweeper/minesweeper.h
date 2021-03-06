#if !defined(MINESWEEPWER_h)
#define MINESWEEPWER_h

#include <iostream>
#include <chrono>
#include <array>
#include <random>
#include <vector>

#define MAXLN 16
#define MAXCOL 30

enum mode
{
    EASY,
    MEDIUM,
    HARD,
    CUSTOM,
};

enum moves
{
    EXIT,
    FLAG,
    OPEN,
    REFRESH,
};

using namespace std;
class minesweeper
{
private:
    vector<vector<bool>> mineBoard;
    array<array<int, 2>, 8> sides{{{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}}};
    void generate(int num);
    int countRoundMine(int col, int ln);
    void showBoard();
    bool isValid(int col, int ln);
    void openSides(int col, int ln);
    void lose();
    void win();
    void open(int col, int ln);

public:
    int boardCol, boardLn, mine, flags{}, opened{}, loseCount{};
    vector<vector<char>> coverBoard;

    void setAttrib(int diffi);
    void init();

    void operate(int col, int ln, int mov);
};

#endif // MINESWEEPWER_h
