#include "CppUnitTest.h"
#include "..\Sudoku9.h"
#include "..\Sudoku9.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestSudoku {
	TEST_CLASS(TestSudoku9) {
public:
	TEST_METHOD(TestSetValue) {
		Assert::ExpectException<std::invalid_argument>([]() {
			Sudoku9 sudoku;
			sudoku.setValue(9, 0, 0);
			});
		Assert::ExpectException<std::invalid_argument>([]() {
			Sudoku9 sudoku;
			sudoku.setValue(0, 9, 0);
			});
		Assert::ExpectException<std::invalid_argument>([]() {
			Sudoku9 sudoku;
			sudoku.setValue(0, 0, 10);
			});
	}

	TEST_METHOD(TestGetValue) {
		Assert::ExpectException<std::invalid_argument>([]() {
			Sudoku9 sudoku;
			sudoku.getValue(9, 0);
			});
		Assert::ExpectException<std::invalid_argument>([]() {
			Sudoku9 sudoku;
			sudoku.getValue(0, 9);
			});
	}

	};
}
