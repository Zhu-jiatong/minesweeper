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
    generate();
    showBoard();
}

void minesweeper::operate(int col, int ln, int mov)
{
    system("cls");
    if (mine > flags)
    {
        switch (mov)
        {
        case OPEN:
            if (coverBoard[ln][col] != '#')
            {
                if (!checkThisMine(col, ln))
                {
                    if (checkRoundMine(col, ln) != 0)
                    {
                        coverBoard[ln][col] = '0' + checkRoundMine(col, ln);
                    }
                    else
                    {
                        coverBoard[ln][col] = ' ';
                        for (int i = 0; i < 8; ++i)
                        {
                            if (!mineBoard[ln + sides[i][0]][col + sides[i][1]] && coverBoard[ln + sides[i][0]][col + sides[i][1]] == '+')
                            {
                                operate(col + sides[i][1], ln + sides[i][0], OPEN);
                            }
                        }
                    }
                }
                else
                {
                    lose();
                }
            }
            break;

        case FLAG:
            if (coverBoard[ln][col] == '+')
            {
                coverBoard[ln][col] = '#';
            }
            else if (coverBoard[ln][col] == '#')
            {
                coverBoard[ln][col] = '+';
            }
            break;

        default:
            break;
        }
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
    for (int i = 0; i < 8; ++i)
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
    for (int placed = 0; placed < mine; ++placed)
    {
        random_device rdLn;
        mt19937 mtLn(rdLn());
        uniform_int_distribution<int> randLn(0, boardLn - 1);
        random_device rdCol;
        mt19937 mtCol(rdCol());
        uniform_int_distribution<int> randCol(0, boardCol - 1);
        int pLn = randLn(mtLn);
        int pCol = randCol(mtCol);
        if (mineBoard[pLn][pCol])
        {
            --placed;
            continue;
        }
        else
        {
            mineBoard[pLn][pCol] = true;
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
    for (int y = 0; y < boardLn; ++y)
    {
        if (firstLn)
        {
            for (int x = 0; x < boardCol; ++x)
            {
                cout << x << (x < 10 ? "  " : " ");
            }
            firstLn = false;
        }

        cout << '\n';
        for (int x = 0; x < boardCol; ++x)
        {
            cout << coverBoard[y][x] << "  ";
        }
        cout << "| " << y << '\n';
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

void minesweeper::openSides(int col, int ln)
{
    coverBoard[ln][col] = ' ';
}