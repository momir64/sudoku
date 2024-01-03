#include <cstdlib> 
#include "CppUnitTest.h"
#include "..\SudokuFileIO.h"
#include "..\SudokuChecker.h"
#include "..\SudokuChecker.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestSudoku {
	TEST_CLASS(TestSudokuChecker) {
public:
	TEST_METHOD(TestChecker) {
		bool solved;
		SudokuChecker checker;
		Sudoku9 puzzle1 = SudokuFileIO::load("..\\..\\TestSudoku\\puzzle1.txt");
		Sudoku9 puzzle2 = SudokuFileIO::load("..\\..\\TestSudoku\\puzzle2.txt");
		Sudoku9 puzzle3 = SudokuFileIO::load("..\\..\\TestSudoku\\puzzle3.txt");
		Sudoku9 solution1 = SudokuFileIO::load("..\\..\\TestSudoku\\solution1.txt");
		Sudoku9 solution2 = SudokuFileIO::load("..\\..\\TestSudoku\\solution2.txt");
		Sudoku9 solution3 = SudokuFileIO::load("..\\..\\TestSudoku\\solution3.txt");

		solved = checker.check(puzzle1, solution1);
		Assert::AreEqual(49, checker.getCorrect());
		Assert::AreEqual(0, checker.getIncorrect());
		Assert::IsTrue(solved);

		solved = checker.check(puzzle2, solution2);
		Assert::AreEqual(38, checker.getCorrect());
		Assert::AreEqual(1, checker.getIncorrect());
		Assert::IsFalse(solved);

		solved = checker.check(puzzle3, solution3);
		Assert::AreEqual(-1, checker.getCorrect());
		Assert::AreEqual(-1, checker.getIncorrect());
		Assert::IsFalse(solved);
	}
	};
}
