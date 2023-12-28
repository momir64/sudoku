#pragma once
#define WIN32_LEAN_AND_MEAN
#include <algorithm>
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
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
		enum KeyboardKey {
			EnterKey = 13,
			SpaceKey = 32,
			UpArrow = 72,
			LeftArrow = 75,
			RightArrow = 77,
			DownArrow = 80
		};

		short margin;
		short height;
		short width;
		Color fColor;
		Color bColor;
		Color sColor;

		void hideCursor();
		void showCursor();
		void setWindowSize();
		void printEncoded(std::string text, int printedLength = 0, bool center = true);
		std::string color(std::string text);
		std::string underline(std::string text);
		std::string pad(int padding);

	public:
		Menu(unsigned short width = 70,
			unsigned short height = 50,
			unsigned short margin = 3,
			Color frontColor = DarkBlack,
			Color backColor = White,
			Color specialColor = Gray);

		Menu(Color frontColor,
			Color backColor = White,
			Color specialColor = Gray,
			unsigned short width = 70,
			unsigned short height = 50,
			unsigned short margin = 3);

		~Menu();

		void clear();
		void print(Sudoku9 sudoku, Sudoku9 original = Sudoku9());
		void print(std::string text = "", bool center = true);
		void printBanner();
		void printSeparator(unsigned int emptyBefore = 0, unsigned int emptyAfter = 0);
		void printStats(int puzzleNo, int correct = -1, int incorrect = -1);
		int selectOption(std::vector<std::string> options);
		std::string getString();
	};
}