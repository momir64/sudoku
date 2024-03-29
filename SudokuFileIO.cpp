﻿/// Description: SudokuFileIO, module for loading and saving sudoku boards to and from files.
/// Author: Momir Stanišić
/// Last modified: 4.1.2024.

#include "SudokuFileIO.h"

namespace SudokuFileIO {
	Sudoku9 load(std::string fileName) {
		Sudoku9 sudoku;
		std::ifstream fin;
		int value;

		fin.open(fileName);

		if (fin.fail())
			throw std::invalid_argument("File \"" + fileName + "\" failed to open!");

		for (int row = 0; row < 9; row++) {
			for (int col = 0; col < 9; col++) {
				if (fin.eof())
					throw std::invalid_argument("Premature end of file \"" + fileName + "\"!");

				fin >> value;
				sudoku.setValue(row, col, value);
			}
		}

		return sudoku;
	}

	void save(std::string fileName, Sudoku9 sudoku) {
		std::ofstream fout;

		fout.open(fileName);

		if (fout.fail())
			throw std::invalid_argument("File \"" + fileName + "\" failed to open!");

		for (int row = 0; row < 9; row++) {
			for (int col = 0; col < 9; col++)
				fout << sudoku.getValue(row, col) << " ";

			fout << std::endl;
		}
	}
};

