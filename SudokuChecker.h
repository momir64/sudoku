/// Description: SudokuChecker, checks the number of correct and incorrect inputs
/// Author: Momir Stanišić
/// Last modified: 4.1.2024.

#pragma once
#include <unordered_set>
#include "Sudoku9.h"

class SudokuChecker {
private:
	int correct;      // Number of correct inputs, equals to -1 if puzzle is invalid.
	int incorrect;	  // Number of incorrect inputs, equals to -1 if puzzle is invalid.

public:
	// Sets the number of correct and incorrect fileds to -1.
	SudokuChecker();

	// Calls the checker for specified puzzle and solution.
	SudokuChecker(const Sudoku9& puzzle, const Sudoku9& solution);

	// Returns true if solution is valid or false if it's not.
	// Updates the number of correct and incorrect input fields.
	bool check(const Sudoku9& puzzle, const Sudoku9& solution);

	// Returns number of correctly inputted numbers for the last checked puzzle.
	// Returns -1 if puzzle is invalid.
	int getCorrect() const;

	// Returns number of incorrectly inputted numbers for the last checked puzzle.
	// Returns -1 if puzzle is invalid.
	int getIncorrect() const;
};

