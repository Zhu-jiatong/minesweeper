#include "minesweeper.h"

void minesweeper::operate(int col, int ln, int mov)
{
    system("cls");
    if (isValid(col, ln))
    {
        switch (mov)
        {
        case OPEN:
            if (coverBoard.at(ln).at(col) == '.')
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
                else
                {
                    lose();
                }
            }
            break;

        case FLAG:
            if (coverBoard.at(ln).at(col) == '.')
            {
                coverBoard.at(ln).at(col) = '#';
                ++flags;
            }
            else if (coverBoard.at(ln).at(col) == '#')
            {
                coverBoard.at(ln).at(col) = '.';
                --flags;
            }

            break;

        case EXIT:
            exit(0);
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
    for (auto &&calc : sides)
    {
        int checkLn = ln + calc.at(0), checkCol = col + calc.at(1);
        if (isValid(checkCol, checkLn) && mineBoard.at(checkLn).at(checkCol))
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
    cout << "You WIN :)\nStats: Wrong moves: " << loseCount << '\n';
    system("pause");
}

void minesweeper::lose()
{
    ++loseCount;
    cout << "You LOSE (" << loseCount << ") :(\n";
    system("pause");
}

void minesweeper::showBoard()
{
    system("cls");
    cout << "    ";
    for (int x = 0; x < coverBoard.at(0).size(); ++x)
    {
        cout << x << (x < 10 ? "   " : "  ");
    }
    cout << "\n    ";
    for (int x = 1; x < coverBoard.at(0).size(); ++x)
    {
        cout << "----";
    }
    cout << "--";

    for (int y = 0; y < coverBoard.size(); ++y)
    {
        cout << (!y ? "" : "|") << '\n'
             << (y < 10 ? " " : "") << y << "| ";
        for (int x = 0; x < coverBoard.at(y).size(); ++x)
        {
            cout << coverBoard.at(y).at(x) << ((x == coverBoard.at(y).size() - 1) ? " " : "   ");
        }
        cout << "|\n";

        if (y != coverBoard.size() - 1)
        {
            cout << "  |";
            for (int x = 0; x < coverBoard.at(y).size(); ++x)
            {
                cout << ((x == coverBoard.at(y).size() - 1) ? "   " : "    ");
            }
        }
    }

    cout << "mov: 0 - EXIT\n"
         << "     1 - FLAG (" << flags << "/" << mine << ")\n"
         << "     2 - OPEN (" << opened << "/" << boardCol * boardLn - mine << ")\n"
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

    case CUSTOM:
    custConfig:
        system("cls");
        cout << "Cols: ", cin >> boardCol;
        cout << "Lns:", cin >> boardLn;
        cout << "Mines (Max: boardLn * boardCol - 1): ", cin >> mine;
        if (mine >= boardLn * boardCol)
        {
            cout << "Too many mines (" << mine << "/" << boardLn * boardCol - 1;
            system("pause");
            goto custConfig;
        }

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
            coverBoard.at(y).push_back('.');
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
    ++opened;
    coverBoard.at(ln).at(col) = (!countRoundMine(col, ln) && coverBoard.at(ln).at(col) == '.') ? (' ') : ('0' + countRoundMine(col, ln));
    if (!countRoundMine(col, ln))
    {
        coverBoard.at(ln).at(col) = ' ';
        if (isValid(col - 1, ln + 1) && coverBoard.at(ln + 1).at(col - 1) == '.')
            openSides(col - 1, ln + 1);
        if (isValid(col - 1, ln) && coverBoard.at(ln).at(col - 1) == '.')
            openSides(col - 1, ln);
        if (isValid(col - 1, ln - 1) && coverBoard.at(ln - 1).at(col - 1) == '.')
            openSides(col - 1, ln - 1);

        if (isValid(col, ln - 1) && coverBoard.at(ln - 1).at(col) == '.')
            openSides(col, ln - 1);
        if (isValid(col, ln + 1) && coverBoard.at(ln + 1).at(col) == '.')
            openSides(col, ln + 1);

        if (isValid(col + 1, ln + 1) && coverBoard.at(ln + 1).at(col + 1) == '.')
            openSides(col + 1, ln + 1);
        if (isValid(col + 1, ln) && coverBoard.at(ln).at(col + 1) == '.')
            openSides(col + 1, ln);
        if (isValid(col + 1, ln - 1) && coverBoard.at(ln - 1).at(col + 1) == '.')
            openSides(col + 1, ln - 1);
    }
    else
    {
        coverBoard.at(ln).at(col) = (!countRoundMine(col, ln) && coverBoard.at(ln).at(col) == '.') ? (' ') : ('0' + countRoundMine(col, ln));
    }
}

void minesweeper::open(int col, int ln)
{
    if (!countRoundMine(col, ln))
    {
        openSides(col, ln);
    }
    else
    {
        coverBoard.at(ln).at(col) = (!countRoundMine(col, ln)) ? (' ') : ('0' + countRoundMine(col, ln));
        ++opened;
    }
}