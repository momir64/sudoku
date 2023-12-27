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
		Color bColor;
		Color fColor;

		void hideCursor();
		void showCursor();
		void setWindowsSize();
		void printEncoded(std::string text, int printedLength = 0, bool center = true);
		std::string color(std::string text, Color frontColor = Color::Gray);
		std::string underline(std::string text);
		std::string pad(int padding);

	public:
		Menu(unsigned short width = 70, unsigned short height = 46, Color frontColor = Color::DarkBlack, Color backColor = Color::White, unsigned short margin = 3);
		~Menu();

		void clear();
		void print(Sudoku9 sudoku, Sudoku9 original = Sudoku9());
		void print(std::string text = "", bool center = true);
		void printBanner();
		void printSeparator();
		void printStats(int puzzleNo, int correct, int incorrect);
		int selectOption(std::vector<std::string> options);
		std::string getString();
	};
}