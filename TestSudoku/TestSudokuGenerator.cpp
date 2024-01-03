#include <cstdlib> 
#include "CppUnitTest.h"
#include "..\SudokuGenerator.h"
#include "..\SudokuGenerator.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestSudoku {
	TEST_CLASS(TestSudokuGenerator) {
public:
	TEST_METHOD(TestDifferent) {
		SudokuGenerator gen = SudokuGenerator();

		Sudoku9 puzzle1 = gen.generate();
		Sudoku9 puzzle2 = gen.generate();
		bool different = false;

		for (int row = 0; row < 9; row++)
			for (int col = 0; col < 9; col++)
				if (puzzle1.getValue(row, col) != puzzle2.getValue(row, col))
					different = true;

		Assert::IsTrue(different);
	}

	TEST_METHOD(TestSolvable) {
		for (int i = 0; i < 100; i++) {
			Sudoku9 puzzle = SudokuGenerator().generate();
			Sudoku9 solution = SudokuSolver(puzzle).getSolution();

			bool puzzleHasZeros = false;
			bool solutionHasZeros = false;

			for (int row = 0; row < 9; row++) {
				for (int col = 0; col < 9; col++) {
					if (!puzzle.getValue(row, col))
						puzzleHasZeros = true;

					if (!solution.getValue(row, col))
						solutionHasZeros = true;
				}
			}

			Assert::IsTrue(puzzleHasZeros);
			Assert::IsFalse(solutionHasZeros);
		}
	}

	};
}
