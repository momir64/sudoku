#include <cstdlib> 
#include "CppUnitTest.h"
#include "..\SudokuFileIO.h"
#include "..\SudokuFileIO.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestSudoku {
	TEST_CLASS(TestSudokuFileIO) {
public:
	TEST_METHOD(TestLoad) {
		Sudoku9 sudoku = SudokuFileIO::load("..\\..\\TestSudoku\\empty.txt");

		for (int row = 0; row < 9; row++) {
			for (int col = 0; col < 9; col++) {
				Assert::AreEqual(sudoku.getValue(row, col), 0);
			}
		}

		Assert::ExpectException<std::invalid_argument>([]() {
			SudokuFileIO::load("..\\..\\TestSudoku\\invalid1.txt");
			});

		Assert::ExpectException<std::invalid_argument>([]() {
			SudokuFileIO::load("..\\..\\TestSudoku\\invalid2.txt");
			});

		Assert::ExpectException<std::invalid_argument>([]() {
			SudokuFileIO::load("..\\..\\TestSudoku\\invalid3.txt");
			});
	}

	TEST_METHOD(TestSave) {
		Sudoku9 sudokuOut;
		srand((unsigned int) time(0));

		for (int row = 0; row < 9; row++) {
			for (int col = 0; col < 9; col++) {
				sudokuOut.setValue(row, col, rand() % 10);
			}
		}

		SudokuFileIO::save("test.txt", sudokuOut);
		Sudoku9 sudokuIn = SudokuFileIO::load("test.txt");

		for (int row = 0; row < 9; row++) {
			for (int col = 0; col < 9; col++) {
				Assert::AreEqual(sudokuOut.getValue(row, col), sudokuIn.getValue(row, col));
			}
		}
	}

	};
}
