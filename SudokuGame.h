#pragma once
#include "SudokuFileIO.h"
#include "SudokuConsole.h"
#include "SudokuChecker.h"
#include "SudokuGenerator.h"

namespace SudokuGame {
	void load(SudokuConsole::Menu menu, int puzzleNo, Sudoku9 puzzle);
	void load(SudokuConsole::Menu menu, int puzzleNo, std::string puzFileName = "");
	void generate(SudokuConsole::Menu menu, int puzzleNo, std::string puzFileName = "");
	void solve(SudokuConsole::Menu menu, int puzzleNo, Sudoku9 puzzle, std::string slnFileName = "");
	void solve(SudokuConsole::Menu menu, int puzzleNo, std::string puzFileName = "", std::string slnFileName = "");
	void check(SudokuConsole::Menu menu, int puzzleNo, Sudoku9 puzzle, Sudoku9 solution);
	void check(SudokuConsole::Menu menu, int puzzleNo, std::string puzFileName = "", std::string slnFileName = "");
	void benchmark();
	void help();
};

