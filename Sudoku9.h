#pragma once
#include <stdexcept>
#include <iostream>

class Sudoku9 {
private:
	int table[9][9];
	int puzzleNo;

public:
	Sudoku9(int puzzleNo = 0);

	void setValue(int row, int col, int value);
	int getValue(int row, int col) const;
	int getPuzzleNo() const;
};

