/// Description: SudokuFileIO, module for loading and saving sudoku boards to and from files.
/// Author: Momir Stanišić
/// Last modified: 4.1.2024.

#pragma once
#include "Sudoku9.h"
#include <iostream>
#include <fstream>
#include <string>

namespace SudokuFileIO {
	// Loads and returns the puzzle or solution from the file with 'fileName'.
	Sudoku9 load(std::string fileName);

	// Saves the given puzzle or solution to the file with 'fileName'.
	void save(std::string fileName, Sudoku9 sudoku);
};

