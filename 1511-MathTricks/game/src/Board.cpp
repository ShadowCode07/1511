#include "Board.h"
#include <random>
#include <iostream>

Board::Board()
    :
    currentPlayer(0, BLACK, 0)
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
}


void Board::DrawBoard()
{
    int index = 0;


    for (int iY = 0; iY < boardHeight; ++iY)
    {
        for (int iX = 0; iX < boardWidth; ++iX)
        {
            cellPosition = {(float)iX, (float)iY };

            if (currentPlayer.currentPosition == index)
            {
                currentPlayer.drawPlayer(boardX + iX * cellSize, boardY + iY * cellSize, GOLD);
                cells[index].color = currentPlayer.color;
                cells[index].setOwner(currentPlayer.own);
                index++;
            }
            else
            {
                DrawCell(iX, iY, index);
                index++;
            }
        }
    }
}

void Board::HandleMovement()
{
    static Player player1(0, BLUE, 1);
    static Player player2(cells.size() - 1, RED, 2);
   
    DrawText("Player1: ", boardX + boardWidth * 65 + 50, boardY + 50, 30, WHITE);
    DrawText("Player2: ", boardX + boardWidth * 65 + 50, boardY + 100, 30, WHITE);
    DrawText(TextFormat("%f", player1.score), boardX + boardWidth * 65 + 200, boardY + 50,30, WHITE);
    DrawText(TextFormat("%f", player2.score), boardX + boardWidth * 65 + 200, boardY + 100,30, WHITE);

    if (turn == 1)
    {
        currentPlayer = player1;
    }
    else
    {
        currentPlayer = player2;
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mousePos = GetMousePosition();

        int targetCellIndex = static_cast<int>((mousePos.y - boardY) / cellSize) * boardWidth + static_cast<int>((mousePos.x - boardX) / cellSize);

        if (targetCellIndex >= 0 && targetCellIndex < cells.size())
        {
            int currentPlayerCellIndex = currentPlayer.currentPosition;

            if (IsNeighboringCell(currentPlayerCellIndex, targetCellIndex) && cells[targetCellIndex].getOwner() == 0)
            {
                currentPlayer.currentPosition = targetCellIndex;

                switch (cells[targetCellIndex].getSymbol())
                {
                case '*':
                    currentPlayer.score *= cells[targetCellIndex].getNumber();
                    break;
                case '+':
                    currentPlayer.score += cells[targetCellIndex].getNumber();
                    break;
                case '-':
                    currentPlayer.score -= cells[targetCellIndex].getNumber();
                    break;
                case '/':
                    currentPlayer.score /= cells[targetCellIndex].getNumber();
                    break;
                }

                if (turn == 1)
                {
                    turn = 2;
                    player1 = currentPlayer;
                }
                else
                {
                    turn = 1;
                    player2 = currentPlayer;
                }
            }
        }
    }

    WhoWins(currentPlayer, player1, player2);
}

bool Board::IsNeighboringCell(int currentCellIndex, int targetCellIndex)
{
    int currentRow = currentCellIndex / boardWidth;
    int currentCol = currentCellIndex % boardWidth;
    int targetRow = targetCellIndex / boardWidth;
    int targetCol = targetCellIndex % boardWidth;

    if ((std::abs(currentRow - targetRow) <= 1) && (std::abs(currentCol - targetCol) <= 1))
    {
        if (currentCellIndex != targetCellIndex)
        {
            return true;
        }
    }

    return false;
}

void Board::WhoWins(Player currentPlayer, Player player1, Player player2)
{
    int currentPlayerCellIndex = currentPlayer.currentPosition;

    for (int i = 0; i < cells.size(); i++)
    {
        if (i != currentPlayerCellIndex)
        {
            if (IsNeighboringCell(currentPlayerCellIndex, i))
            {
                if (cells[i].getOwner() != currentPlayer.own && cells[i].getOwner() != 0)
                {
                    if (currentPlayer.own == 1)
                    {
                        DrawText("Player2 WINS", 0,0, 100, GOLD);
                    }
                    else
                    {
                        DrawText("Player1 WINS",0,0, 100, GOLD);
                    }
                }
            }
        }
    }

    int ownedCells = 0;

    for (int i = 0; i < cells.size(); i++)
    {
        if (cells[i].getOwner() != 0)
        {
            ownedCells++;
        }
    }

    if (ownedCells == boardHeight * boardWidth)
    {
        if(player1.score > player2.score)
        { 
            DrawText("Player1 WINS", 0,0, 100, GOLD);
        }
        else
        {
            DrawText("Player2 WINS", 0,0, 100, GOLD);
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
    DrawRectangle(boardX + x * cellSize, boardY + y * cellSize, cellSize, cellSize, cells[index].color);
    DrawRectangleLines(boardX + x * cellSize, boardY + y * cellSize, cellSize, cellSize, WHITE);

    if (cells[index].getOwner() == 0)
    {
        DrawText(TextFormat("%c", cells[index].getSymbol()), boardX + x * cellSize + 20, boardY + y * cellSize + 25, 20, WHITE);
        DrawText(TextFormat("%i", cells[index].getNumber()), boardX + x * cellSize + 36, boardY + y * cellSize + 25, 20, WHITE);
    }

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
