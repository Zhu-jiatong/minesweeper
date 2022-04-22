#include "minesweeper.h"

void minesweeper::setBoard(int diffi)
{
    system("cls");

    for (int y = 0; y <= boardLn; ++y)
    {
        for (int x = 0; x <= boardCol; ++x)
        {
            coverBoard[y][x] = '+';
        }
    }
    cout << "Initialising board\n";
    generate();
    showBoard();
}

void minesweeper::operate(int col, int ln, int mov)
{
    system("cls");
    if (mine > flags)
    {
        if (!checkThisMine(col, ln))
        {
            cout << mineBoard[ln][col];
            if (checkRoundMine(col, ln) != 0)
            {
                cout << "alert";
                coverBoard[ln][col] = '0' + checkRoundMine(col, ln);
            }
            else
            {
                coverBoard[ln][col] = ' ';
                // operate(col, ln, OPEN);
            }
        }
        else
        {
            lose();
        }
        cout << "hello";
        showBoard();
    }
    else
    {
        win();
    }
}

bool minesweeper::checkThisMine(int col, int ln)
{
    return mineBoard[ln][col] ? true : false;
}

int minesweeper::checkRoundMine(int col, int ln)
{
    int mCount{};
    /*     mCount += (boardCol > col) ? (mineBoard[ln][col + 1] ? 1 : 0) : 0;
        mCount += (boardCol > col && boardLn > ln) ? (mineBoard[ln + 1][col + 1] ? 1 : 0) : 0;
        mCount += (boardCol > col && boardLn < ln) ? (mineBoard[ln - 1][col + 1] ? 1 : 0) : 0;
        mCount += (boardLn > ln) ? (mineBoard[ln + 1][col] ? 1 : 0) : 0;
        mCount += (boardLn < ln) ? (mineBoard[ln - 1][col] ? 1 : 0) : 0;
        mCount += (boardCol < col) ? (mineBoard[ln][col - 1] ? 1 : 0) : 0;
        mCount += (boardCol < col && boardLn > ln) ? (mineBoard[ln + 1][col - 1] ? 1 : 0) : 0;
        mCount += (boardCol < col && boardLn < ln) ? (mineBoard[ln - 1][col - 1] ? 1 : 0) : 0;
     */
    for (int i = 0; i <= 8; ++i)
    {
        if (mineBoard[ln + sides[i][0]][col + sides[i][1]])
        {
            ++mCount;
        }
    }

    return mCount;
}

void minesweeper::generate()
{
    srand(time(NULL));
    for (int placed = 0; placed < mine; ++placed)
    {
        int random = rand() % (boardCol * boardLn);
        int pLn = random / (boardLn + 1);
        int pCol = random % (boardCol + 1);
        if (mineBoard[pLn][pCol])
        {
            --placed;
            cout << "Repeated mine" << placed << '\n';
            continue;
        }
        else
        {
            mineBoard[pLn][pCol] = true;
            cout << "Placed 1 mine\n";
        }
    }
}

void minesweeper::win()
{
    cout << "win";
}

void minesweeper::lose()
{
    cout << "lose";
}

void minesweeper::showBoard()
{
    system("cls");

    bool firstLn(true);
    /*     for (int y = 0; y <= boardLn; ++y)
        {
            for (int i = 0; i <= boardCol && firstLn; ++i)
            {
                cout << i << (i < 10 ? "  " : " ");
            }
            firstLn = false;

            cout << '\n';

            for (int x = 0; x <= boardCol; ++x)
            {
                cout << coverBoard[y][x] << "  ";
            }
            cout << "| " << y << '\n';
        }
     */
    int y(0);
    for (auto &&thisLn : coverBoard)
    {
        int x(0);
        for (auto &&thisCol : coverBoard[0])
        {
            cout << ++x << (x < 10 ? "  " : " ");
        }
        firstLn = false;
        x = 0;

        cout << '\n';
        for (auto &&thisCol : coverBoard[x])
        {
            cout << thisCol << "  ";
        }
        cout << "| " << ++y << '\n';
    }

    cout << "0 - FLAG\n"
         << "1 - OPEN\n"
         << "YOUR_MOVE (col ln mov): ";
    int c, l, m;
    cin >> c >> l >> m;
    operate(c, l, m);
}

void minesweeper::setAttrib(int dif)
{
    switch (dif)
    {
    case EASY:
        boardLn = 8;
        boardCol = 8;
        mine = 10;
        break;

    case MEDIUM:
        boardLn = 16;
        boardCol = 16;
        mine = 40;
        break;

    case HARD:
        boardLn = 16;
        boardCol = 30;
        mine = 99;
        break;

    default:
        break;
    }
}

void minesweeper::init()
{
    coverBoard[0].fill('+');
    coverBoard.fill(coverBoard[0]);
    generate();
    showBoard();
}