/// Description: SudokuGenerator, class for generating the sudoku puzzles
/// Author: Momir Stanišić
/// Last modified: 4.1.2024.

#pragma once
#include "SudokuSolver.h"
#include "Sudoku9.h"
#include <algorithm>
#include <numeric>
#include <random>
#include <array>

class SudokuGenerator {
private:
	Sudoku9 table;     // sudoku table
	std::mt19937 rng;  // random generator engine

	// Creates and returns shuffled array of consecutive numbers starting from 'start'.
	template <unsigned int N> std::array<int, N> getRandomArray(int start = 0);

	// Fills the specified subgrid (box) with unique random numbers from 1 to 9.
	void fillBox(int box);

public:
	// Initializes random generator engine.
	SudokuGenerator();

	// Creates and returns new puzzle with specified number of 'emptyCells'.
	// Generated puzzle has the specified 'puzzleNo'.
	Sudoku9 generate(int puzzleNo = 0, int emptyCells = 42);
};

