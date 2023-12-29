#include <iostream>
#include "SudokuFileIO.h"
#include "SudokuConsole.h"

int main(int argc, char** argv) {
	SudokuConsole::Menu menu; //(SudokuConsole::Magenta, SudokuConsole::Black, SudokuConsole::Purple, 150, 50);
	menu.printBanner();
	menu.printSeparator();
	menu.printStats(1);
	menu.printSeparator(0, 1);
	menu.print(SudokuFileIO::load("TestSudoku\\puzzle.txt"));
	menu.printSeparator(1, 2);

	std::vector<std::string> options = { "Load the new puzzle from file",
										 "Load the solution from file",
										 "Save the puzzle to file",
										 "Generate new puzzle",
										 "Solve the puzzle", };
	int option = menu.selectOption(options);

	return option;
}