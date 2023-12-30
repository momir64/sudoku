#include "SudokuConsole.h"

SudokuConsole::Menu::Menu(unsigned short width, unsigned short height, unsigned short margin, Color frontColor, Color backColor, Color specialColor) {
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
}

SudokuConsole::Menu::Menu(Color frontColor, Color backColor, Color specialColor, unsigned short width, unsigned short height, unsigned short margin) :
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
	std::cout << "\x1B[?25l";
}

void SudokuConsole::Menu::showCursor() {
	std::cout << "\x1B[?25h";
}

void SudokuConsole::Menu::clear() {
	std::cout << "\x1B[38;5;" << fColor << "m";
	std::cout << "\x1B[48;5;" << bColor << "m";
	std::cout << "\x1B[H\x1B[2J\x1B[H";
}

std::string SudokuConsole::Menu::color(std::string text) {
	return "\x1B[38;5;" + std::to_string(sColor) + "m" + text + "\x1B[38;5;" + std::to_string(fColor) + "m";
}

std::string SudokuConsole::Menu::underline(std::string text) {
	return "\x1B[4m" + text + "\x1B[24m";
}

void SudokuConsole::Menu::print(Sudoku9 table, Sudoku9 original) {
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

			int numValue = table.getValue(i, j);
			std::string txtValue = numValue ? std::to_string(numValue) : std::string(" ");
			txtValue = original.getValue(i, j) ? color(txtValue) : txtValue;
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
	print(std::string(width - margin * 2, '-'), false);
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
		std::cout << "\x1B[" << options.size() << "F";

		int input = _getch();
		if (input == UpArrow || input == LeftArrow)
			selected = max(selected - 1, 0);
		else if (input == DownArrow || input == RightArrow)
			selected = min(selected + 1, (int)options.size() - 1);
		else if (input == EnterKey || input == SpaceKey)
			return selected;
	}
}

std::string SudokuConsole::Menu::getString() {
	std::string text;
	showCursor();
	std::cin >> text;
	hideCursor();
	return text;
}