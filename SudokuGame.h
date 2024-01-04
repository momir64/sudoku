/// Description: SudokuGame, helper module for basic program workflow
/// Author: Momir Stanišić
/// Last modified: 4.1.2024.

#pragma once
#include "SudokuFileIO.h"
#include "SudokuConsole.h"
#include "SudokuChecker.h"
#include "SudokuGenerator.h"

namespace SudokuGame {
	// load menu with the given 'puzzle'
	void load(SudokuConsole::Menu menu, int puzzleNo, Sudoku9 puzzle);

	// load menu with the puzzle from 'puzFileName' file
	void load(SudokuConsole::Menu menu, int puzzleNo, std::string puzFileName = "");

	// generate and load puzzle,
	// saves the puzzle to 'puzFileName' if provided
	void generate(SudokuConsole::Menu menu, int puzzleNo, std::string puzFileName = "");

	// solves and shows the solution for the given 'puzzle',
	// saves the solution to 'slnFileName' if provided
	void solve(SudokuConsole::Menu menu, int puzzleNo, Sudoku9 puzzle, std::string slnFileName = "");

	// solves and shows the solution for the puzzle from the 'puzFileName' file, 
	// saves the solution to 'slnFileName' if provided
	void solve(SudokuConsole::Menu menu, int puzzleNo, std::string puzFileName = "", std::string slnFileName = "");

	// checks and shows the given 'solution' for the given sudoku 'puzzle'
	void check(SudokuConsole::Menu menu, int puzzleNo, Sudoku9 puzzle, Sudoku9 solution);

	// checks and shows the 'solution' from the given 'slnFileName' file,
	// for the sudoku 'puzzle' from the given 'puzFileName' file
	void check(SudokuConsole::Menu menu, int puzzleNo, std::string puzFileName = "", std::string slnFileName = "");

	// starts the benchmark, ESC key stops the program, any other key slows down (speeds up) the benchmark 
	void benchmark();

	// prints the CLI help
	void help();
};

