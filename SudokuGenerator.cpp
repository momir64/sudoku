#include "SudokuGenerator.h"

template<unsigned int N> std::array<int, N> SudokuGenerator::getRandomArray(int start) {
	static std::random_device rd = std::random_device{};
	static std::mt19937 rng = std::default_random_engine{ rd() };
	std::array<int, N> values;
	std::iota(values.begin(), values.end(), start);
	std::shuffle(values.begin(), values.end(), rng);
	return values;
}

void SudokuGenerator::fillBox(int box) {
	std::array<int, 9> values = getRandomArray<9>(1);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			table.setValue(box * 3 + i, box * 3 + j, values[(size_t)i * 3 + j]);
}

Sudoku9 SudokuGenerator::generate(int puzzleNo, int emptyCells) {
	table = Sudoku9(puzzleNo);

	for (int i = 0; i < 3; i++)
		fillBox(i);

	SudokuSolver solver(table);
	table = solver.getSolution();

	std::array<int, 81> pos = getRandomArray<81>();
	for (int i = 0; i < emptyCells; i++)
		table.setValue(pos[i] / 9, pos[i] % 9, 0);

	return table;
}
