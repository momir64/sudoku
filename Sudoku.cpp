#include <iostream>
#include "SudokuFileIO.h"
#include "SudokuConsole.h"

int main(int argc, char** argv) {
	SudokuConsole::Menu menu;
	menu.printBanner();
	menu.printSeparator();
	menu.printStats(1, 2, 3);
	menu.printSeparator();
	menu.print("\n");
	menu.print(SudokuFileIO::load("TestSudoku\\solved.txt"));
	menu.print("\n");
	menu.printSeparator();
	menu.print("\n\n");

	std::vector<std::string> options = { "Generate new puzzle",
										 "Solve the puzzle",
										 "Enter solution" };
	int option = menu.selectOption(options);
	
	return option;
}
