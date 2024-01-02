#include "SudokuSolver.h"

SudokuSolver::SudokuSolver(const Sudoku9& table) {
	std::bitset<9> rowContains[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	std::bitset<9> colContains[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	std::bitset<9> boxContains[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	this->table = table;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (table.getValue(i, j)) {
				int value = table.getValue(i, j) - 1;
				rowContains[i].set(value);
				colContains[j].set(value);
				boxContains[getBox(i, j)].set(value);
			}
		}
	}

	solved = solve(0, 0, rowContains, colContains, boxContains);
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

Sudoku9 SudokuSolver::getSolution() {
	return table;
}

bool SudokuSolver::isSolved() {
	return solved;
}
