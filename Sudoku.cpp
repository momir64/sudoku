#include <iostream>
#include "SudokuFileIO.h"
#include "SudokuConsole.h"
#include "SudokuGenerator.h"

int main(int argc, char** argv) {
	SudokuConsole::Menu menu; //(SudokuConsole::Magenta, SudokuConsole::Black, SudokuConsole::Purple, 150, 50);
	SudokuGenerator gen;

	menu.printBanner();
	menu.printSeparator();
	menu.printStats(1);
	menu.printSeparator(0, 1);
	menu.print(gen.generate()); //SudokuFileIO::load("TestSudoku\\puzzle.txt"));
	menu.printSeparator(1, 2);

	std::vector<std::string> options = { "Load the new puzzle from file",
										 "Load the solution from file",
										 "Save the puzzle to file",
										 "Generate new puzzle",
										 "Solve the puzzle", };
	int option = menu.selectOption(options);

	return option;
}

//double sum = 0, i = 0;
//while (true) {
//	menu.printBanner();
//	menu.printSeparator();
//	menu.printStats(i + 1);
//	menu.printSeparator(0, 2);
//
//	std::clock_t start = std::clock();
//	menu.print(gen.generate()); //SudokuFileIO::load("TestSudoku\\puzzle.txt"));
//	sum += (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000);
//	i++;
//	menu.print();
//	menu.print("Time: " + std::to_string(sum / i) + " ms");
//	Sleep(1);
//
//	menu.clear();
//}