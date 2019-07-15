#include "game/game.h"
#include "console/console.h"

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <set>
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

int main() {
	std::ifstream input("life.txt");
	std::vector<std::string> inputData;
	for (std::string line; input >> line;) {
		inputData.push_back(line);
	}
	std::vector<std::vector<bool>> map(inputData.size(), std::vector<bool>(inputData.front().size(), false));
	for (ui32 x = 0; x < inputData.size(); ++x) {
		auto& row = inputData[x];
		map[x].resize(row.size());
		std::transform(row.begin(), row.end(), map[x].begin(), [](char c) {return (c != '0'); });
	}

	NLifeGame::TGame<NLifeGame::TVectorState> game(map);

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