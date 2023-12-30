#include "SudokuSolver.h"

SudokuSolver::SudokuSolver(const Sudoku9& table) {
	std::bitset<9> rowContains[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	std::bitset<9> colContains[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	std::bitset<9> gridContains[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	this->table = table;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (table.getValue(i, j)) {
				rowContains[i].set(table.getValue(i, j));
				colContains[j].set(table.getValue(i, j));
				gridContains[getGrid(i, j)].set(table.getValue(i, j));
			}
		}
	}

	solved = solve(0, 0, rowContains, colContains, gridContains);
}

int SudokuSolver::getGrid(int row, int col) {
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

bool SudokuSolver::solve(int row, int col, std::bitset<9> rows[], std::bitset<9> cols[], std::bitset<9> grids[]) {
	if (!nextEmpty(row, col))
		return true;

	int grid = getGrid(row, col);
	std::bitset<9> contains = rows[row] | cols[col] | grids[grid];

	if (contains.all())
		return false;

	for (int value = 0; value < 9; value++) {
		if (!contains[value]) {
			table.setValue(row, col, value + 1);

			rows[row].set(value);
			cols[col].set(value);
			grids[grid].set(value);

			if (solve(row, col, rows, cols, grids))
				return true;

			rows[row].reset(value);
			cols[col].reset(value);
			grids[grid].reset(value);
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
