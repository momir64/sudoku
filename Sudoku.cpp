#include <iostream>
#include "SudokuFileIO.h"
#include "SudokuConsole.h"

int main(int argc, char** argv) {
	SudokuConsole::Menu menu;
	menu.print();
	menu.printSeparator();
	menu.printStats(1, 2, 3);
	menu.printSeparator();
	menu.print();
	menu.print(SudokuFileIO::load("TestSudoku\\solved.txt"));
	menu.print();
	menu.getOption();
}
