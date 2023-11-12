#pragma once
#include "Character.h"
#include <Windows.h>
#include <iostream>
#include <conio.h>

class Game {
private:
	static const int width = 20;
	static const int height = 10;

	Character player;
public:
	Game() : player(width / 2, height / 2) {
		int i = 0;
		while (i < width) {
			std::cout << "#";
			++i;
		}
		std::cout << std::endl;
		for (i = 1; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				if (j == 0 || j == (width - 1)) {
					std::cout << "#";
				}
				else if (i == player.GetY() && j == player.GetX()) {
					std::cout << "@";
				}
				else {
					std::cout << " ";
				}
			}
			std::cout << std::endl;
		}
		i = 0;
		while (i < width) {
			std::cout << "#";
			++i;
		}
	}

	void Draw();
	void HandleInput(char key);

	static const int GetWidth();
	static const int GetHeight();
};