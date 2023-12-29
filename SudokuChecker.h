#pragma once
#include <unordered_set>
#include "Sudoku9.h"

class SudokuChecker {
private:
	int correct;
	int incorrect;

public:
	SudokuChecker(const Sudoku9& puzzle, const Sudoku9& solution);
	bool check(const Sudoku9& puzzle, const Sudoku9& solution);

	int getCorrect();
	int getIncorrect();
};

