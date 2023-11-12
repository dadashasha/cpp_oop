#include "Game.h"

void Game::Draw() {
	system("cls");

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
void Game::HandleInput(char key) {
	int dx = 0;
	int dy = 0;
	if (key == 'a') {
		dx = -1;
	}
	if (key == 'd') {
		dx = 1;
	}
	if (key == 'w') {
		dy = -1;
	}
	if (key == 's') {
		dy = 1;
	}
	if (key == 'x') {
		std::cout << "End of game!" << std::endl;
		exit(0);
	}
	/*
	switch (key) {
	case 'a':
		dx = -1;
	case 'd':
		dx = 1;
	case 'w':
		dy = -1;
	case 's':
		dy = 1;
	case 'x':
		exit(0);//выход из игры
	}
	*/
	player.Move(dx, dy);
}
const int Game::GetWidth() {
	return width;
}
const int Game::GetHeight() {
	return height;
}