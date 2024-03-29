/// Description: SudokuConsole, module for custom I/O terminal
/// Author: Momir Stanišić
/// Last modified: 4.1.2024.

#include "SudokuConsole.h"

SudokuConsole::Menu::Menu(unsigned short width, unsigned short height, unsigned short margin,
	Color frontColor, Color backColor, Color specialColor) {
	SetConsoleOutputCP(CP_UTF8);
	this->margin = min(margin, width / 4);
	this->height = height;
	this->width = width;
	sColor = specialColor;
	fColor = frontColor;
	bColor = backColor;
	setWindowSize(width, height);
	hideCursor();
	clear();
	printBanner();
	printSeparator();
}

SudokuConsole::Menu::Menu(Color frontColor, Color backColor, Color specialColor,
	unsigned short width, unsigned short height, unsigned short margin) :
	Menu::Menu(width, height, margin, frontColor, backColor, specialColor) {}

SudokuConsole::Menu::~Menu() {
	setWindowSize();
	fColor = White;
	bColor = Black;
	showCursor();
	clear();
}

void SudokuConsole::Menu::setWindowSize(short width, short height) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT const minimal_window = { 0, 0, 1, 1 };
	COORD size = { width ? width : 150, height ? height : 300 };
	SMALL_RECT const window = { 0, 0, size.X - 1,  height ? size.Y - 1 : 34 };
	SetConsoleMode(handle, ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
	SetConsoleWindowInfo(handle, TRUE, &minimal_window);
	SetConsoleScreenBufferSize(handle, size);
	SetConsoleWindowInfo(handle, TRUE, &window);
}

void SudokuConsole::Menu::hideCursor() {
	std::cout << "\x1B[?25l";  // hides cursor
}

void SudokuConsole::Menu::showCursor() {
	std::cout << "\x1B[?25h";  // shows cursor
}

void SudokuConsole::Menu::clear() const {
	std::cout << "\x1B[38;5;" << fColor << "m";  // sets the foreground color
	std::cout << "\x1B[48;5;" << bColor << "m";  // sets the background color
	std::cout << "\x1B[H\x1B[2J\x1B[H";          // clears the screen and sets the cursor position to (0, 0)
}

void SudokuConsole::Menu::goTo(unsigned int row, unsigned int col) {
	std::cout << "\x1B[" << row << ";" << col << "H";  // sets the cursor position to 'row' and 'col'
}

std::string SudokuConsole::Menu::color(std::string text) {
	// colors the given text with special color
	return "\x1B[38;5;" + std::to_string(sColor) + "m" + text + "\x1B[38;5;" + std::to_string(fColor) + "m";
}

std::string SudokuConsole::Menu::underline(std::string text) {
	return "\x1B[4m" + text + "\x1B[24m";  // underlines the given text
}

void SudokuConsole::Menu::print(Sudoku9 solution, Sudoku9 puzzle) {
	static const int length = 37;
	static const std::string fatLine = color("┃");
	static const std::string slimLine = color("│");
	static const std::string borders[] = { color("┏━━━┯━━━┯━━━┳━━━┯━━━┯━━━┳━━━┯━━━┯━━━┓"),
										   color("┠───┼───┼───╂───┼───┼───╂───┼───┼───┨"),
										   color("┣━━━┿━━━┿━━━╋━━━┿━━━┿━━━╋━━━┿━━━┿━━━┫"),
										   color("┗━━━┷━━━┷━━━┻━━━┷━━━┷━━━┻━━━┷━━━┷━━━┛") };

	printEncoded(borders[0], length);
	for (int i = 0; i < 9; i++) {
		if (i && i % 3)
			printEncoded(borders[1], length);
		else if (i)
			printEncoded(borders[2], length);

		std::string line;
		for (int j = 0; j < 9; j++) {
			if (j % 3)
				line += slimLine;
			else
				line += fatLine;

			int slnValue = solution.getValue(i, j), puzValue = puzzle.getValue(i, j);
			std::string txtValue = slnValue ? std::to_string(slnValue) : std::string(" ");
			txtValue = puzValue ? color(std::to_string(puzValue)) : txtValue;
			line += " " + txtValue + " ";
		}
		line += fatLine;

		printEncoded(line, length);
	}
	printEncoded(borders[3], length);

}

std::string SudokuConsole::Menu::pad(int padding) {
	return std::string(padding, ' ');
}

void SudokuConsole::Menu::printEncoded(std::string text, int printedLength, bool center) {
	if (printedLength && center)
		std::cout << pad((width - printedLength) / 2);
	else
		std::cout << pad(margin);
	std::cout << text << std::endl;
}

void SudokuConsole::Menu::print(std::string text, bool center) {
	printEncoded(text, (int)text.length(), center);
}

void SudokuConsole::Menu::printSeparator(unsigned int emptyBefore, unsigned int emptyAfter) {
	if (emptyBefore) print(std::string(emptyBefore - 1, '\n'), false);
	print(std::string((size_t)width - (size_t)margin * 2, '-'), false);
	if (emptyAfter) print(std::string(emptyAfter - 1, '\n'), false);
}

void SudokuConsole::Menu::printStats(int puzzleNo, int correct, int incorrect) {
	std::string pzNo = "Puzzle No: " + std::to_string(puzzleNo), cor, inc;
	if (correct == -1 || incorrect == -1)
		cor = inc = "";
	else {
		cor = "   Correct: " + std::to_string(correct);
		inc = "Incorrect: " + std::to_string(incorrect) + "   ";
	}

	int s1 = (width - (int)pzNo.length()) / 2 - margin - (int)cor.length();
	int s2 = (width - (int)pzNo.length()) / 2 - margin - (int)inc.length();

	std::cout << pad(margin) << cor << pad(s1) << pzNo << pad(s2) << inc << std::endl;
}

void SudokuConsole::Menu::printBanner() {
	print("\n");
	printEncoded(color("▄█████■ ██    ██ █████▄   ▄████▄  ██  ▐█▌ ██    ██ "), 52);
	printEncoded(color("██      ██    ██ ██  ▀██ ██▀  ▀██ ██ ▄██  ██    ██ "), 52);
	printEncoded(color("▀█████▄ ██    ██ ██   ██ ██    ██ █████   ██    ██ "), 52);
	printEncoded(color("     ██ ▐█▄  ▄█▌ ██  ▄██ ██▄  ▄██ ██ ▀██  ▐█▄  ▄█▌ "), 52);
	printEncoded(color("■█████▀  ▀████▀  █████▀   ▀████▀  ██  ▐█▌  ▀████▀  "), 52);
	print("\n");
}

int SudokuConsole::Menu::selectOption(std::vector<std::string> options) {
	int selected = 0;
	while (true) {
		for (int i = 0; i < options.size(); i++)
			printEncoded(i == selected ? underline(options[i]) : options[i], (int)options[i].length());
		std::cout << "\x1B[" << options.size() << "F";  // returns the cursor to the options beginning row

		int input = _getch();
		if (input == UpArrow || input == LeftArrow)
			selected = selected - 1 == -1 ? (int)options.size() - 1 : selected - 1;
		else if (input == DownArrow || input == RightArrow)
			selected = selected + 1 == (int)options.size() ? 0 : selected + 1;
		else if (input == EnterKey || input == SpaceKey) {
			std::cout << "\x1B[0J";  // clears the options menu
			return selected;
		} else if (input == EscKey) {
			return -1;
		}
	}
}

std::string SudokuConsole::Menu::getString(std::string text) {
	showCursor();
	std::cout << "\x1B[s" << pad(margin) << text;  // saves the current cursor position
	std::cin >> text;
	std::cout << "\x1B[u\x1B[0J";                  // returns to the saved cursor position
	hideCursor();
	return text;
}