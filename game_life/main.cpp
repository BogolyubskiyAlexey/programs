#include "game/game.h"
#include "console/console.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

template <class T>
void RedrawConsoleInterface(const NLifeGame::TGame<T>& game) {
	NConsoleUtil::ClearConsole();
	if (game.Finished()) {
		std::cout << "Game finished" << std::endl;
	} else {
		std::cout << "Press 'n' to make one step, 'r' - to come to a finish state." << std::endl;
	}
	std::cout << "Step #" << game.GetStepNumber() << std::endl;
	std::cout << game.GetState();
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "Program usage: game_life input_file" << std::endl;
		return 1;
	}
	const std::string filename = argv[1];
	std::ifstream input(filename);
	if (input.fail()) {
		std::cout << "Cannot read from file: " << filename << std::endl;
		return 1;
	}
	std::vector<std::vector<bool>> map;
	for (std::string line; input >> line;) {
		if (map.size() && line.size() != map.back().size()) {
			std::cout << "Incorrect input data: the rows must be the same size" << std::endl;
			return 1;
		}
		std::vector<bool> row(line.size());
		std::transform(line.begin(), line.end(), row.begin(), [](char c) {return (c != '0'); });
		map.push_back(row);
	}

	NLifeGame::TGame<> game(map);

	RedrawConsoleInterface(game);

	while (!game.Finished()) {
		char key = NConsoleUtil::GetPressedKey();
		if (key == 'n') {
			game.MakeStep();
		} else if (key == 'r') {
			game.Run();
		} else {
			std::cout << "Unsupported key pressed" << std::endl;
			continue;
		}
		RedrawConsoleInterface(game);
	}
}