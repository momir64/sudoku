/// Description: SudokuSolver, class for solving the sudoku puzzles
/// Author: Momir Stanišić
/// Last modified: 4.1.2024.

#pragma once
#include "Sudoku9.h"
#include <bitset>
#include <array>

class SudokuSolver {
private:
	Sudoku9 table;  // solution table
	bool solved;    // is puzzle solved

	// Returns index of subgrid (box) that contains field with specified 'row' and 'col'.
	int getBox(int row, int col);

	// Recursive method for solving sudoku, returns true if solved and false otherwise.
	// Assumes that all fields before 'rowStart' and 'colStart' are filled.
	// 'rows', 'cols' and 'boxes' contain the used numbers for the respective groups.
	bool solve(int rowStart, int colStart, std::bitset<9> rows[], std::bitset<9> cols[], std::bitset<9> boxes[]);

	// Updates 'row' and 'col' to the next empty field.
	// Returns true if such a field is found and false otherwise.
	bool nextEmpty(int& row, int& col);

public:
	// Solves the given 'puzzle'.
	SudokuSolver(const Sudoku9& puzzle);

	// Returns the solution if possible.
	// Returns unchanged puzzle if puzzle is invalid.
	Sudoku9 getSolution() const;

	// Returns true if solved, false otherwise.
	bool isSolved() const;
};

