#pragma once
#include "Sudoku9.h"
#include <iostream>
#include <fstream>
#include <string>

namespace SudokuFileIO {
	Sudoku9 load(std::string fileName);
	void save(std::string fileName, Sudoku9 sudoku);
};

