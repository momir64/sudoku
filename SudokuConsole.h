#pragma once
#define WIN32_LEAN_AND_MEAN
#include <algorithm>
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include "Sudoku9.h"

namespace SudokuConsole {
	enum Color {
		Black,
		Red,
		Green,
		Yellow,
		Blue,
		Purple,
		BrightBlue,
		White,
		Gray,
		BrightRed,
		BrightGreen,
		BrightYellow,
		RoyalBlue,
		Magenta,
		Cyan,
		BrightWhite,
		DarkBlack
	};

	class Menu {
	private:
		short margin;
		short height;
		short width;
		Color bColor;
		Color fColor;

		void setWindowsSize();
		void printUTF8(std::string text, int printedLength = 0, bool center = true);
		std::string color(std::string text, Color frontColor = Color::Gray);
		std::string pad(int padding);

	public:
		Menu(unsigned short width = 70, unsigned short height = 50, Color frontColor = Color::DarkBlack, Color backColor = Color::White, unsigned short margin = 3);
		~Menu();

		void clear();
		void print(Sudoku9 sudoku);
		void print(std::string text = "", bool center = false);
		void printSeparator();
		void printStats(int puzzleNo, int correct, int incorrect);
		int getOption(int minValue = 0, int maxValue = 9);
		std::string getString();
	};
}