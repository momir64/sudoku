/// Description: Sudoku9, class that contains the sudoku board.
/// Author: Momir Stanišić
/// Last modified: 4.1.2024.

#pragma once
#include <stdexcept>
#include <iostream>

class Sudoku9 {
private:
	int table[9][9];
	int puzzleNo;     // Puzzle No.

public:
	// Initializes empty board with the given ordinal number of the puzzle.
	Sudoku9(int puzzleNo = 0);

	// Checks and sets given 'value' on specified 'row' and 'col'.
	void setValue(int row, int col, int value);

	// Returns value on specified 'row' and 'col'.
	int getValue(int row, int col) const;

	// Returns the ordinal number of the puzzle.
	int getPuzzleNo() const;
};

