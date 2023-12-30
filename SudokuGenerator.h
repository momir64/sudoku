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

	template <unsigned int N> std::array<int, N> getRandomArray(int start = 0);
	void fillBox(int box);

public:
	Sudoku9 generate(int emptyCells = 33, int puzzleNo = 0);
};

