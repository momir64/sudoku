#include "SudokuConsole.h"

SudokuConsole::Menu::Menu(unsigned short width, unsigned short height, Color frontColor, Color backColor, unsigned short margin) {
	SetConsoleOutputCP(CP_UTF8);
	this->margin = min(margin, width / 4);
	this->height = height;
	this->width = width;
	fColor = frontColor;
	bColor = backColor;
	setWindowsSize();
}

SudokuConsole::Menu::~Menu() {
	COORD const size = { 150, 35 };
	CONSOLE_CURSOR_INFO info = { 100, TRUE };
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT const minimal_window = { 0, 0, 1, 1 };
	SMALL_RECT const window = { 0, 0, size.X - 1, size.Y - 1 };
	SetConsoleCursorInfo(handle, &info);
	SetConsoleWindowInfo(handle, TRUE, &minimal_window);
	SetConsoleScreenBufferSize(handle, size);
	SetConsoleWindowInfo(handle, TRUE, &window);
	fColor = White;
	bColor = Black;
	clear();
}

void SudokuConsole::Menu::setWindowsSize() {
	COORD const size = { width, height };
	CONSOLE_CURSOR_INFO info = { 100, FALSE };
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT const minimal_window = { 0, 0, 1, 1 };
	SMALL_RECT const window = { 0, 0, size.X - 1, size.Y - 1 };
	SetConsoleMode(handle, ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
	SetConsoleCursorInfo(handle, &info);
	SetConsoleWindowInfo(handle, TRUE, &minimal_window);
	SetConsoleScreenBufferSize(handle, size);
	SetConsoleWindowInfo(handle, TRUE, &window);
	clear();
}

void SudokuConsole::Menu::clear() {
	std::cout << "\x1B[38;5;" << fColor << "m";
	std::cout << "\x1B[48;5;" << bColor << "m";
	std::cout << "\x1B[H\x1B[2J\x1B[H";
}

std::string SudokuConsole::Menu::color(std::string text, Color frontColor) {
	return "\x1B[38;5;" + std::to_string(frontColor) + "m" + text + "\x1B[38;5;" + std::to_string(fColor) + "m";
}

void SudokuConsole::Menu::print(Sudoku9 sudoku) {
	static const int len = 37;
	static const std::string fatLine = color("┃");
	static const std::string slimLine = color("│");
	static const std::string borders[] = { color("┏━━━┯━━━┯━━━┳━━━┯━━━┯━━━┳━━━┯━━━┯━━━┓"),
										   color("┠───┼───┼───╂───┼───┼───╂───┼───┼───┨"),
										   color("┣━━━┿━━━┿━━━╋━━━┿━━━┿━━━╋━━━┿━━━┿━━━┫"),
										   color("┗━━━┷━━━┷━━━┻━━━┷━━━┷━━━┻━━━┷━━━┷━━━┛") };

	printUTF8(borders[0], len);
	for (int i = 0; i < 9; i++) {
		if (i && i % 3)
			printUTF8(borders[1], len);
		else if (i)
			printUTF8(borders[2], len);

		std::string line;
		for (int j = 0; j < 9; j++) {
			if (j % 3)
				line += slimLine;
			else
				line += fatLine;
			line += " " + std::to_string(sudoku.getValue(i, j)) + " ";
		}
		line += fatLine;

		printUTF8(line, len);
	}
	printUTF8(borders[3], len);

}

std::string SudokuConsole::Menu::pad(int padding) {
	return std::string(padding, ' ');
}

void SudokuConsole::Menu::printUTF8(std::string text, int printedLength, bool center) {
	if (center)
		std::cout << pad((width - printedLength) / 2);
	else
		std::cout << pad(margin);
	std::cout << text << std::endl;
}

void SudokuConsole::Menu::print(std::string text, bool center) {
	printUTF8(text, (int) text.length(), center);
}

void SudokuConsole::Menu::printSeparator() {
	print(std::string((size_t)width - (size_t)margin * 2, '-'));
}

void SudokuConsole::Menu::printStats(int puzzleNo, int correct, int incorrect) {
	std::string pzNo = "Puzzle No: " + std::to_string(puzzleNo);
	std::string cor = "   Correct: " + std::to_string(correct);
	std::string inc = "Incorrect: " + std::to_string(incorrect) + "   ";

	int s1 = (width - (int)pzNo.length()) / 2 - margin - (int)cor.length();
	int s2 = (width - (int)pzNo.length()) / 2 - margin - (int)inc.length();

	std::cout << pad(margin) << cor << pad(s1) << pzNo << pad(s2) << inc << std::endl;
}

int SudokuConsole::Menu::getOption(int minValue, int maxValue) {
	minValue = max(minValue, 0);
	maxValue = min(maxValue, 9);
	int option = -1;
	while (option < minValue || option > maxValue)
		option = _getch() - '0';
	return option;
}

std::string SudokuConsole::Menu::getString() {
	std::string text;
	std::cin >> text;
	return text;
}