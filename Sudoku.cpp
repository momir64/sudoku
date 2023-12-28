#include <iostream>
#include "SudokuFileIO.h"
#include "SudokuConsole.h"

int main(int argc, char** argv) {
	SudokuConsole::Menu menu;
	menu.printBanner();
	menu.printSeparator();
	menu.printStats(1);
	menu.printSeparator();
	menu.print("\n");
	menu.print(SudokuFileIO::load("TestSudoku\\puzzle.txt"));
	menu.print("\n");
	menu.printSeparator();
	menu.print("\n\n");

	std::vector<std::string> options = { "Load the new puzzle from file",
										 "Load the solution from file",
										 "Save the puzzle to file",
										 "Generate new puzzle",
										 "Solve the puzzle", };
	int option = menu.selectOption(options);

	return option;
}