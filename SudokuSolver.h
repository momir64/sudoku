#pragma once
#include "Sudoku9.h"
#include <bitset>
#include <array>

class SudokuSolver {
private:
	Sudoku9 table;
	bool solved;

	int getBox(int row, int col);
	bool solve(int rowStart, int colStart, std::bitset<9> rows[], std::bitset<9> cols[], std::bitset<9> boxes[]);
	bool nextEmpty(int& row, int& col);

public:
	SudokuSolver(const Sudoku9& table);
	Sudoku9 getSolution();
	bool isSolved();
};

