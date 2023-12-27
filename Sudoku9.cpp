#include "Sudoku9.h"

Sudoku9::Sudoku9(unsigned int puzzleNo) {
	std::fill_n(&table[0][0], sizeof(table) / sizeof(**table), 0);
	this->puzzleNo = puzzleNo;
}

Sudoku9::Sudoku9() : Sudoku9::Sudoku9(0) {}

void Sudoku9::setValue(unsigned int row, unsigned int col, unsigned int value) {
	if (row > 8) throw std::invalid_argument("Row must be less or equal to 8!");
	if (col > 8) throw std::invalid_argument("Col must be less or equal to 8!");
	if (value > 9) throw std::invalid_argument("Value must be less or equal to 9!");

	table[row][col] = value;
}

int Sudoku9::getValue(unsigned int row, unsigned int col) {
	if (row > 8) throw std::invalid_argument("Row must be less or equal to 8!");
	if (col > 8) throw std::invalid_argument("Col must be less or equal to 8!");

	return table[row][col];
}

int Sudoku9::getPuzzleNo() {
	return puzzleNo;
}


