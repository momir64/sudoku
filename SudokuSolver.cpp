/// Description: SudokuSolver, class for solving the sudoku puzzles
/// Author: Momir Stanišić
/// Last modified: 4.1.2024.

#include "SudokuSolver.h"

SudokuSolver::SudokuSolver(const Sudoku9& puzzle) {
	std::bitset<9> rows[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	std::bitset<9> cols[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	std::bitset<9> boxes[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	table = puzzle;

	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			int value = table.getValue(row, col);
			if (value) {
				int box = getBox(row, col);

				std::bitset<9> contains = rows[row] | cols[col] | boxes[box];
				if (contains[--value]) {
					solved = false;
					return;
				}

				rows[row].set(value);
				cols[col].set(value);
				boxes[box].set(value);
			}
		}
	}

	solved = solve(0, 0, rows, cols, boxes);
}

int SudokuSolver::getBox(int row, int col) {
	return (row / 3) * 3 + col / 3;
}

bool SudokuSolver::nextEmpty(int& row, int& col) {
	for (; row < 9; row++) {
		for (; col < 9; col++)
			if (!table.getValue(row, col))
				return true;
		col = 0;
	}
	return false;
}

bool SudokuSolver::solve(int row, int col, std::bitset<9> rows[], std::bitset<9> cols[], std::bitset<9> boxes[]) {
	if (!nextEmpty(row, col))
		return true;

	int box = getBox(row, col);
	std::bitset<9> contains = rows[row] | cols[col] | boxes[box];

	if (contains.all())
		return false;

	for (int value = 0; value < 9; value++) {
		if (!contains[value]) {
			table.setValue(row, col, value + 1);

			rows[row].set(value);
			cols[col].set(value);
			boxes[box].set(value);

			if (solve(row, col, rows, cols, boxes))
				return true;

			rows[row].reset(value);
			cols[col].reset(value);
			boxes[box].reset(value);
		}
	}

	table.setValue(row, col, 0);
	return false;
}

Sudoku9 SudokuSolver::getSolution() const {
	return table;
}

bool SudokuSolver::isSolved() const {
	return solved;
}
