#include "Board.h"
#include <random>
#include <iostream>

Board::Board()
{
}


Board& Board::getInstance()
{
    static Board board;
    return board;
}

void Board::setup()
{
    cells.resize(boardWidth * boardHeight);
    setCells();
}

void Board::setCells()
{
    for (int i = 0; i < cells.size(); i++)
    {
        cells[i].setNumber(randomNumberGen(0,(boardHeight > boardWidth) ? boardHeight : boardWidth));
        cells[i].setSymbol(randomSymbolGen());

        if (cells[i].getNumber() == 0 && cells[i].getSymbol() == '/')
        {
            cells[i].setSymbol('*');
        }
    }

    cells[0].setNumber(0);
    cells[0].setSymbol(' ');
    cells[cells.size() - 1].setNumber(0);
    cells[cells.size() - 1].setSymbol(' ');
}


void Board::DrawBoard()
{
    int index = 0;

    for (int iY = 0; iY < boardHeight; ++iY)
    {
        for (int iX = 0; iX < boardWidth; ++iX)
        {
            DrawCell(iX, iY, index);
            index++;
        }
    }
}

void Board::setBoardHeight(int boardHeight)
{
    this->boardHeight = boardHeight;
    boardX = ((960 + (960 * 0.25)) - (boardWidth * 65 + 275)) / 2;
}

int Board::getBoardHeight()
{
    return this->boardHeight;
}

void Board::setBoardWidth(int boardWidth)
{
    this->boardWidth = boardWidth;
    boardY = ((540 + (540 * 0.25)) - (boardHeight * 65)) / 2;
}

int Board::getBoardWidth()
{
    return this->boardWidth;
}

// CELL FUNCTIONS //


uint64_t timeSinceEpochMicrosec()
{
    using namespace std::chrono;
    return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
}

int Board::randomNumberGen(int minRange, int maxRange)
{
    std::random_device rd;
    std::mt19937 rng(rd()); 

    std::uniform_int_distribution<int> dist(minRange, maxRange+2);

    int randomNumber = dist(rng);
    return randomNumber;
}

char Board::randomSymbolGen()
{
    std::random_device rd;
    std::mt19937 rng(rd());

    std::uniform_int_distribution<int> dist(1, 4);

    int randomNumber = dist(rng);

    switch (randomNumber)
    {
    case 1:
        return '*';
        break;
    case 2:
        return '+';
        break;
    case 3:
        return '-';
        break;
    case 4:
        return '/';
        break;
    }

}

Board::Cell::Cell()
{
}

void Board::DrawCell(int x, int y, int index)
{
    DrawRectangleLines(boardX + x * cellSize, boardY + y * cellSize, cellSize, cellSize, WHITE);
    DrawText(TextFormat("%c", cells[index].getSymbol()), boardX + x * cellSize + 20, boardY + y * cellSize + 25, 20, WHITE);
    DrawText(TextFormat("%i", cells[index].getNumber()), boardX + x * cellSize + 36, boardY + y * cellSize + 25, 20, WHITE);
}

void Board::Cell::setNumber(int number)
{
    this->number = number;
}

int Board::Cell::getNumber()
{
    return this->number;
}

void Board::Cell::setSymbol(char symbol)
{
    this->symbol = symbol;
}

char Board::Cell::getSymbol()
{
    return this->symbol;
}

void Board::Cell::setOwner(int owner)
{
    this->owner = owner;
}

int Board::Cell::getOwner()
{
    return this->owner;
}
