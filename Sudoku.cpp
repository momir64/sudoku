#include <iostream>
#include "SudokuFileIO.h"
#include "SudokuConsole.h"
#include "SudokuGenerator.h"

void benchmark();

int main(int argc, char** argv) {
	benchmark();
	//SudokuConsole::Menu menu; //(SudokuConsole::Magenta, SudokuConsole::Black, SudokuConsole::Purple, 150, 50);
	//SudokuGenerator gen;

	//menu.printBanner();
	//menu.printSeparator();
	//menu.printStats(1);
	//menu.printSeparator(0, 1);
	//menu.print(gen.generate()); //SudokuFileIO::load("TestSudoku\\puzzle.txt"));
	//menu.printSeparator(1, 2);

	//std::vector<std::string> options = { "Load the new puzzle from file",
	//									 "Load the solution from file",
	//									 "Save the puzzle to file",
	//									 "Generate new puzzle",
	//									 "Solve the puzzle", };
	//int option = menu.selectOption(options);

	//return option;
}

void benchmark() {
	SudokuConsole::Menu menu(70, 44); //(SudokuConsole::Magenta, SudokuConsole::Black, SudokuConsole::Purple, 150, 50);
	SudokuGenerator gen;
	bool slow = true;
	menu.printBanner();
	menu.printSeparator();

	int i = 0;
	double genSum = 0, slvSum = 0;
	while (true) {
		menu.goTo(11);
		menu.printStats(i + 1);
		menu.printSeparator(0, 2);

		std::clock_t start = std::clock();
		Sudoku9 puzzle = gen.generate();
		genSum += (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000);
		menu.print(Sudoku9(), puzzle);
		menu.goTo(15);

		if (slow) Sleep(1000);
		if (_kbhit()) {
			int _ = _getch();
			slow = !slow;
		}

		start = std::clock();
		Sudoku9 solution = SudokuSolver(puzzle).getSolution();
		slvSum += (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000);
		menu.print(solution, puzzle);

		i++;
		menu.goTo(37);
		menu.print("Generate: " + std::to_string(genSum / i) + " ms ");
		menu.print(" Solving: " + std::to_string(slvSum / i) + " ms ");

		if (slow) Sleep(1000);
		if (_kbhit()) {
			int _ = _getch();
			slow = !slow;
		}
	}
}
