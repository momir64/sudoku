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

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int value = solution.getValue(i, j);
			if (!value) {
				solved = false;
				continue;
			}

			int box = (i / 3) * 3 + j / 3;
			if (!puzzle.getValue(i, j)) {
				if (rows[i].count(value) || cols[j].count(value) || boxes[box].count(value)) {
					solved = false;
					incorrect++;
				} else
					correct++;
			} else if (puzzle.getValue(i, j) != value) {
				incorrect = -1;
				correct = -1;
				return false;
			}

			rows[i].insert(value);
			cols[j].insert(value);
			boxes[box].insert(value);
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
