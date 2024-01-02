#include <iostream>
#include "SudokuGame.h"

int main(int argc, char** argv) {
	if (argc > 1) {
		if (argv[1] == std::string("--load")) {
			if (argc == 3)
				SudokuGame::load(SudokuConsole::Menu(), 1, argv[2]);

		} else if (argv[1] == std::string("--generate")) {
			if (argc == 2)
				SudokuGame::generate(SudokuConsole::Menu(), 1);
			else if (argc == 3)
				SudokuGame::generate(SudokuConsole::Menu(), 1, argv[2]);

		} else if (argv[1] == std::string("--solve")) {
			if (argc == 3)
				SudokuGame::solve(SudokuConsole::Menu(), 1, argv[2]);
			else if (argc == 4)
				SudokuGame::solve(SudokuConsole::Menu(), 1, argv[2], argv[3]);

		} else if (argv[1] == std::string("--check")) {
			if (argc == 4)
				SudokuGame::check(SudokuConsole::Menu(), 1, argv[2], argv[3]);

		} else if (argv[1] == std::string("--benchmark"))
			SudokuGame::benchmark();

		else
			SudokuGame::help();

	} else
		SudokuGame::help();
}