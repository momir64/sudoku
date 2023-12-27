#pragma once
#include <iostream>
#include <stdexcept>

class Sudoku9 {
private:
	unsigned int table[9][9];
	unsigned int puzzleNo;

public:
	Sudoku9(unsigned int puzzleNo);
	Sudoku9();

	void setValue(unsigned int row, unsigned int col, unsigned int value);
	int getValue(unsigned int row, unsigned int col);
	int getPuzzleNo();
};

