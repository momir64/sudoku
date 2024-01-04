/// Description: SudokuConsole, module for custom I/O terminal
/// Author: Momir Stanišić
/// Last modified: 4.1.2024.

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
			EscKey = 27,
			SpaceKey = 32,
			UpArrow = 72,
			LeftArrow = 75,
			RightArrow = 77,
			DownArrow = 80
		};

		short margin;  // Text margin
		short height;  // Terminal height
		short width;   // Terminal width
		Color fColor;  // Text color
		Color bColor;  // Background color
		Color sColor;  // Special text color

		// Hides the cursors.
		void hideCursor();

		// Shows the cursors.
		void showCursor();

		// Sets window size to given 'width' and 'height'.
		void setWindowSize(short width = 0, short height = 0);

		// Prints given text but uses provided length instead of number of bytes of given text.
		// Used for centering the strings containing the UTF8 characters.
		void printEncoded(std::string text, int printedLength = 0, bool center = true);

		// Colors and returns the given text with "Special text color".
		std::string color(std::string text);

		// Underlines and returns the given text.
		std::string underline(std::string text);

		// Returns the padding of given length.
		std::string pad(int padding);

	public:
		// Sets up the terminal dimensions and colors, prints the header.
		Menu(unsigned short width = 70,
			unsigned short height = 50,
			unsigned short margin = 3,
			Color frontColor = DarkBlack,
			Color backColor = White,
			Color specialColor = Gray);

		// Constructor with different order of arguments for easier usage of default arguments.
		Menu(Color frontColor,
			Color backColor = White,
			Color specialColor = Gray,
			unsigned short width = 70,
			unsigned short height = 50,
			unsigned short margin = 3);

		// Returns the terminal to default settings
		~Menu();

		// Clears text from terminal and sets cursor postion to (0, 0)
		void clear() const;

		// Moves the cursor to specified 'row' and 'col'
		void goTo(unsigned int row = 0, unsigned int col = 0);

		// Prints the given sudoku board
		// 'solution' is printed normally, while the non empty puzzle fields (if puzzle is provided) are faded.
		void print(Sudoku9 solution, Sudoku9 puzzle = Sudoku9());

		// Prints given text (centered if 'center' is true).
		void print(std::string text = "", bool center = true);

		// Prints "SUDOKU" banner
		void printBanner();

		// Prints the separator that fills the terminal width,
		// with specifed 'emptyBefore' new lines and 'emptyAfter' new lines.
		void printSeparator(unsigned int emptyBefore = 0, unsigned int emptyAfter = 0);

		// Prints the line with puzzle number, and number of correct and incorrect inputs.
		void printStats(int puzzleNo, int correct = -1, int incorrect = -1);

		// Prints provided 'options' and returns the order number (from 0) of option selected by the user.
		int selectOption(std::vector<std::string> options);

		// Prints given text, and returns text inputed by the user.
		std::string getString(std::string text = "");
	};
}