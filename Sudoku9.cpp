#include "Sudoku9.h"

Sudoku9::Sudoku9(int puzzleNo) {
	std::fill_n(&table[0][0], sizeof(table) / sizeof(**table), 0);
	this->puzzleNo = std::max(0, puzzleNo);
}

void Sudoku9::setValue(int row, int col, int value) {
	if (row < 0 || row > 8) throw std::invalid_argument("Row must be less or equal to 8!");
	if (col < 0 || col > 8) throw std::invalid_argument("Col must be less or equal to 8!");
	if (value < 0 || value > 9) throw std::invalid_argument("Value must be less or equal to 9!");

	table[row][col] = value;
}

int Sudoku9::getValue(int row, int col) const {
	if (row < 0 || row > 8) throw std::invalid_argument("Row must be less or equal to 8!");
	if (col < 0 || col > 8) throw std::invalid_argument("Col must be less or equal to 8!");

	return table[row][col];
}

int Sudoku9::getPuzzleNo() const {
	return puzzleNo;
}