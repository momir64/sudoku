#pragma once
#include "SudokuSolver.h"
#include "Sudoku9.h"
#include <algorithm>
#include <numeric>
#include <random>
#include <array>

class SudokuGenerator {
private:
	Sudoku9 table;
	std::mt19937 rng;

	template <unsigned int N> std::array<int, N> getRandomArray(int start = 0);
	void fillBox(int box);

public:
	SudokuGenerator();
	Sudoku9 generate(int puzzleNo = 0, int emptyCells = 42);
};

