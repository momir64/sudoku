#include <cstdlib> 
#include "CppUnitTest.h"
#include "..\SudokuSolver.h"
#include "..\SudokuFileIO.h"
#include "..\SudokuChecker.h"
#include "..\SudokuSolver.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestSudoku {
	TEST_CLASS(TestSudokuSolver) {
public:
	TEST_METHOD(TestImpossible) {
		Sudoku9 puzzle = SudokuFileIO::load("..\\..\\TestSudoku\\impossible.txt");
		SudokuSolver solver = SudokuSolver(puzzle);
		Assert::IsFalse(solver.isSolved());
	}

	TEST_METHOD(TestInvalid) {
		Sudoku9 puzzle = SudokuFileIO::load("..\\..\\TestSudoku\\invalid4.txt");
		SudokuSolver solver = SudokuSolver(puzzle);
		Assert::IsFalse(solver.isSolved());
	}

	TEST_METHOD(TestValid) {
		Sudoku9 puzzle = SudokuFileIO::load("..\\..\\TestSudoku\\puzzle1.txt");
		Sudoku9 solution = SudokuFileIO::load("..\\..\\TestSudoku\\solution1.txt");
		SudokuSolver solver = SudokuSolver(puzzle);

		Sudoku9 test = solver.getSolution();
		Assert::IsTrue(solver.isSolved());

		for (int row = 0; row < 9; row++)
			for (int col = 0; col < 9; col++)
				Assert::AreEqual(solution.getValue(row, col), test.getValue(row, col));
	}

	TEST_METHOD(TestEmpty) {
		Sudoku9 puzzle = Sudoku9();
		SudokuSolver solver = SudokuSolver(puzzle);
		Assert::IsTrue(solver.isSolved());
		Assert::AreEqual(81, SudokuChecker(puzzle, solver.getSolution()).getCorrect());
	}

	};
}
