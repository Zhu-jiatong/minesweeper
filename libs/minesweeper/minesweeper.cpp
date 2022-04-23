#include "minesweeper.h"

void minesweeper::operate(int col, int ln, int mov)
{
    system("cls");
    if (isValid(col, ln))
    {
        switch (mov)
        {
        case OPEN:
            if (coverBoard.at(ln).at(col) == '+')
            {
                if (!mineBoard.at(ln).at(col))
                {
                    open(col, ln);
                }
                else if (!opened)
                {
                    mineBoard.at(ln).at(col) = false;
                    generate(1);
                    open(col, ln);
                }
            }
            break;

        case FLAG:
            if (coverBoard.at(ln).at(col) == '+')
            {
                coverBoard.at(ln).at(col) = '#';
                ++flags;
            }
            else if (coverBoard.at(ln).at(col) == '#')
            {
                coverBoard.at(ln).at(col) = '+';
                --flags;
            }

            break;

        default:
            break;
        }
    }
    else
    {
        cout << "invalid move\n";
        system("pause");
    }

    if (opened >= boardCol * boardLn - mine)
    {
        win();
    }

    showBoard();
}

int minesweeper::countRoundMine(int col, int ln)
{
    int mCount{};
    for (int i = 0; i < 8; ++i)
    {
        int checkLn = ln + sides[i][0], checkCol = col + sides[i][1];
        if (isValid(checkCol, checkLn) && mineBoard[checkLn][checkCol])
        {
            ++mCount;
        }
    }

    return mCount;
}

bool minesweeper::isValid(int col, int ln)
{
    return (col >= 0 && col < boardCol && ln >= 0 && ln < boardLn) ? true : false;
}

void minesweeper::generate(int num)
{
    for (int placed = 0; placed < num; ++placed)
    {
        random_device rdLn;
        mt19937 mtLn(rdLn());
        uniform_int_distribution<int> randLn(0, boardLn - 1);
        random_device rdCol;
        mt19937 mtCol(rdCol());
        uniform_int_distribution<int> randCol(0, boardCol - 1);
        int pLn = randLn(mtLn);
        int pCol = randCol(mtCol);

        if (mineBoard.at(pLn).at(pCol))
        {
            --placed;
            continue;
        }
        else
        {
            mineBoard.at(pLn).at(pCol) = true;
        }
    }
}

void minesweeper::win()
{
    cout << "You WIN :)\n";
    system("pause");
}

void minesweeper::lose()
{
    cout << "You LOSE :(\n";
    system("pause");
}

void minesweeper::showBoard()
{
    system("cls");

    bool firstLn(true);
    for (int x = 0; x < coverBoard.at(0).size(); ++x)
    {
        cout << x << (x < 10 ? "  " : " ");
    }

    for (int y = 0; y < coverBoard.size(); ++y)
    {
        if (firstLn)
        {
            firstLn = false;
        }

        cout << '\n';
        for (int x = 0; x < coverBoard.at(y).size(); ++x)
        {
            cout << mineBoard.at(y).at(x) << "  ";
        }
        cout << "| " << y << '\n';
    }

    cout << "0 - FLAG (" << flags << "/" << mine << ")\n"
         << "1 - OPEN (" << opened << "/" << boardCol * boardLn - mine << ")\n"
         << "YOUR_MOVE (x y mov): ";
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
    coverBoard.resize(boardLn); // initialise the cover layer board.
    for (int y = 0; y < boardLn; ++y)
    {
        for (int x = 0; x < boardCol; ++x)
        {
            coverBoard.at(y).push_back('+');
        }
    }

    mineBoard.resize(boardLn); // initialise the mine layer board
    for (auto &&mineBoardY : mineBoard)
    {
        mineBoardY.resize(boardCol);
    }

    generate(mine);
    showBoard();
}

void minesweeper::openSides(int col, int ln)
{
    if (isValid(col, ln) && coverBoard.at(ln).at(col) == '+')
    {
        coverBoard.at(ln).at(col) = (countRoundMine(col, ln) == 0) ? (' ') : ('0' + countRoundMine(col, ln));
        ++opened;
    }
}

void minesweeper::open(int col, int ln)
{
    coverBoard.at(ln).at(col) = (!countRoundMine(col, ln)) ? (' ') : ('0' + countRoundMine(col, ln));
    ++opened;
    if (!countRoundMine(col, ln))
    {
        for (auto &&calc : sides)
        {
            int calcLn = ln + calc[0], calcCol = col + calc[1];
            openSides(calcCol, calcLn);
        }
    }
}