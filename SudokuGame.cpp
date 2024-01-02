#include "SudokuGame.h"


void SudokuGame::help() {
	std::cout << "Usage:" << std::endl
		<< "\t--load <puzzle-file-name>" << std::endl
		<< "\t--generate [<puzzle-file-name>]" << std::endl
		<< "\t--solve <puzzle-file-name> [<solution-file-name>]" << std::endl
		<< "\t--check <puzzle-file-name> <solution-file-name>" << std::endl
		<< "\t--benchmark" << std::endl
		<< "\t--help" << std::endl;
}


void SudokuGame::load(SudokuConsole::Menu menu, int puzzleNo, Sudoku9 puzzle) {
	menu.goTo(11);
	menu.printStats(puzzleNo);
	menu.printSeparator(0, 2);
	menu.print(Sudoku9(), puzzle);
	menu.printSeparator(1, 2);

	std::vector<std::string> options = { "Load the new puzzle from file",
										 "Load the solution from file",
										 "Save the puzzle to file",
										 "Generate new puzzle",
										 "Solve the puzzle" };

	int option = menu.selectOption(options);

	try {
		if (option == -1) return;
		else if (option == 0) {
			std::string pzlFileName = menu.getString("Puzzle file name: ");
			Sudoku9 puzzle = SudokuFileIO::load(pzlFileName);
			load(menu, ++puzzleNo, puzzle);
		} else if (option == 1) {
			std::string slnFileName = menu.getString("Solution file name: ");
			Sudoku9 solution = SudokuFileIO::load(slnFileName);
			check(menu, puzzleNo, puzzle, solution);
		} else if (option == 2) {
			std::string pzlFileName = menu.getString("Puzzle file name: ");
			SudokuFileIO::save(pzlFileName, puzzle);
			load(menu, puzzleNo, puzzle);
		} else if (option == 3)
			generate(menu, ++puzzleNo);
		else if (option == 4)
			solve(menu, puzzleNo, puzzle);
	} catch (std::invalid_argument e) {
		menu.print(e.what());
		int _ = _getch();
		load(menu, puzzleNo, puzzle);
	}
}


void SudokuGame::solve(SudokuConsole::Menu menu, int puzzleNo, Sudoku9 puzzle, std::string slnFileName) {
	Sudoku9 solution = SudokuSolver(puzzle).getSolution();
	SudokuChecker checker(puzzle, solution);

	menu.goTo(11);
	menu.printStats(puzzleNo, checker.getCorrect(), checker.getIncorrect());
	menu.printSeparator(0, 2);
	menu.print(solution, puzzle);
	menu.printSeparator(1, 2);

	if (!slnFileName.empty())
		SudokuFileIO::save(slnFileName, solution);

	std::vector<std::string> options = { "Load the new puzzle from file",
										 "Save the solution to file",
										 "Generate new puzzle" };

	int option = menu.selectOption(options);

	try {
		if (option == -1) return;
		else if (option == 0) {
			std::string pzlFileName = menu.getString("Puzzle file name: ");
			Sudoku9 puzzle = SudokuFileIO::load(pzlFileName);
			load(menu, ++puzzleNo, puzzle);
		} else if (option == 1) {
			std::string slnFileName = menu.getString("Solution file name: ");
			SudokuFileIO::save(slnFileName, solution);
			check(menu, puzzleNo, puzzle, solution);
		} else if (option == 2)
			generate(menu, ++puzzleNo);
	} catch (std::invalid_argument e) {
		menu.print(e.what());
		int _ = _getch();
		solve(menu, puzzleNo, puzzle, slnFileName);
	}
}


void SudokuGame::check(SudokuConsole::Menu menu, int puzzleNo, Sudoku9 puzzle, Sudoku9 solution) {
	SudokuChecker checker(puzzle, solution);

	menu.goTo(11);
	menu.printStats(puzzleNo, checker.getCorrect(), checker.getIncorrect());
	menu.printSeparator(0, 2);
	menu.print(solution, puzzle);
	menu.printSeparator(1, 2);

	std::vector<std::string> options = { "Load the new puzzle from file",
										 "Generate new puzzle" };

	int option = menu.selectOption(options);

	try {
		if (option == -1) return;
		else if (option == 0) {
			std::string pzlFileName = menu.getString("Puzzle file name: ");
			Sudoku9 puzzle = SudokuFileIO::load(pzlFileName);
			load(menu, ++puzzleNo, puzzle);
		} else if (option == 1)
			generate(menu, ++puzzleNo);
	} catch (std::invalid_argument e) {
		menu.print(e.what());
		int _ = _getch();
		check(menu, puzzleNo, puzzle, solution);
	}
}


void SudokuGame::load(SudokuConsole::Menu menu, int puzzleNo, std::string puzFileName) {
	try {
		Sudoku9 puzzle = SudokuFileIO::load(puzFileName);
		load(menu, puzzleNo, puzzle);
	} catch (std::invalid_argument e) {
		menu.print(e.what());
		int _ = _getch();
		return;
	}
}

void SudokuGame::generate(SudokuConsole::Menu menu, int puzzleNo, std::string puzFileName) {
	try {
		Sudoku9 puzzle = SudokuGenerator().generate();
		if (!puzFileName.empty())
			SudokuFileIO::save(puzFileName, puzzle);
		load(menu, puzzleNo, puzzle);
	} catch (std::invalid_argument e) {
		menu.print(e.what());
		int _ = _getch();
		return;
	}
}

void SudokuGame::solve(SudokuConsole::Menu menu, int puzzleNo, std::string puzFileName, std::string slnFileName) {
	try {
		Sudoku9 puzzle = SudokuFileIO::load(puzFileName);
		solve(menu, puzzleNo, puzzle, slnFileName);
	} catch (std::invalid_argument e) {
		menu.print(e.what());
		int _ = _getch();
		return;
	}
}

void SudokuGame::check(SudokuConsole::Menu menu, int puzzleNo, std::string puzFileName, std::string slnFileName) {
	try {
		Sudoku9 puzzle = SudokuFileIO::load(puzFileName);
		Sudoku9 solution = SudokuFileIO::load(slnFileName);
		check(menu, puzzleNo, puzzle, solution);
	} catch (std::invalid_argument e) {
		menu.print(e.what());
		int _ = _getch();
		return;
	}
}


bool slowing(bool& slow) {
	if (slow) Sleep(1000);
	if (_kbhit()) {
		slow = !slow;
		return _getch() == 27;
	}
	return false;
}

void SudokuGame::benchmark() {
	SudokuConsole::Menu menu(70, 44);
	bool slow = false, end = false;
	double genSum = 0, slvSum = 0;
	SudokuGenerator gen;
	int i = 0;

	while (true) {
		menu.printStats(++i);
		menu.printSeparator(0, 2);

		clock_t start = clock();
		Sudoku9 puzzle = gen.generate();
		genSum += (float)(clock() - start) / (float)(CLOCKS_PER_SEC / 1000);
		menu.print(Sudoku9(), puzzle);
		menu.goTo(15);

		if (slowing(slow))
			return;

		start = clock();
		Sudoku9 solution = SudokuSolver(puzzle).getSolution();
		slvSum += (float)(clock() - start) / (float)(CLOCKS_PER_SEC / 1000);
		menu.print(solution, puzzle);

		menu.goTo(37);
		menu.print("Creating: " + std::to_string(genSum / i) + " ms ");
		menu.print(" Solving: " + std::to_string(slvSum / i) + " ms ");

		menu.goTo(11);
		if (slowing(slow))
			return;
	}
}