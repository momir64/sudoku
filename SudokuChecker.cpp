/// Description: SudokuChecker, checks the number of correct and incorrect inputs
/// Author: Momir Stanišić
/// Last modified: 4.1.2024.

#include "SudokuChecker.h"

SudokuChecker::SudokuChecker() {
	incorrect = -1;
	correct = -1;
}

SudokuChecker::SudokuChecker(const Sudoku9& puzzle, const Sudoku9& solution) {
	check(puzzle, solution);
}

bool SudokuChecker::check(const Sudoku9& puzzle, const Sudoku9& solution) {
	std::unordered_set<int> rows[9], cols[9], boxes[9];
	correct = incorrect = 0;
	bool solved = true;

	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			int value = puzzle.getValue(row, col);
			int box = (row / 3) * 3 + col / 3;

			if (!value)
				continue;

			if (rows[row].count(value) || cols[col].count(value) || boxes[box].count(value) ||
				value != solution.getValue(row, col)) {
				incorrect = -1;
				correct = -1;
				return false;
			}

			rows[row].insert(value);
			cols[col].insert(value);
			boxes[box].insert(value);
		}
	}

	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			int value = solution.getValue(row, col);

			if (!value) {
				solved = false;
				continue;
			}

			int box = (row / 3) * 3 + col / 3;
			if (!puzzle.getValue(row, col)) {
				if (rows[row].count(value) || cols[col].count(value) || boxes[box].count(value)) {
					solved = false;
					incorrect++;
				} else {
					correct++;
					rows[row].insert(value);
					cols[col].insert(value);
					boxes[box].insert(value);
				}
			}
		}
	}

	return solved;
}

int SudokuChecker::getCorrect() const {
	return correct;
}

int SudokuChecker::getIncorrect() const {
	return incorrect;
}
