#pragma once
#include <vector>
#include <raylib.h>
#include <time.h>
#include <chrono>

class Board
{
private:
	class Cell {
	public:
		Cell();

		void setNumber(int number);
		int getNumber();

		void setSymbol(char symbol);
		char getSymbol();

		void setOwner(int owner);
		int getOwner();
	private:
		int number = 0;
		char symbol = ' ';
		int owner = 0;
	};
public:
	Board();

	static Board& getInstance();

	void setup();
	void setCells();
	void DrawBoard();

	void setBoardHeight(int boardHeight);
	int getBoardHeight();

	void setBoardWidth(int boardWidth);
	int getBoardWidth();
private:
	std::vector<Cell> cells;

	int boardHeight = 0;
	int boardWidth = 0;
	int boardX = 0;
	int boardY = 0;
	int cellSize = 65;

	int randomNumberGen(int minRange, int maxRange);
	char randomSymbolGen();

	void DrawCell(int x, int y, int index);

};
