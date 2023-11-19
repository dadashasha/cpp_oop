#include "Game.h"

void Game::Update() {
	{
		maze[player.GetY()][player.GetX()] = ' ';
		for (Enemy& enemy : enemies) {
			enemy.MoveRandom(maze);
		}
	}
}

void Game::Draw() {
	system("cls");

	for (const auto& row : maze) {
		for (const char& cell : row) {
			if (cell == 'C') {
				std::cout << "C" << " ";
			}
			else if (cell == 'g') {
				std::cout << "g" << " ";
			}
			else {
				std::cout << cell << " ";
			}
		}
		std::cout << std::endl;
	}
}
void Game::HandleInput(char key) {
	key = _getch();
	while (true) {
		std::lock_guard<std::mutex> lock(mazeMutex);
		if (key == 'x') {
			std::cout << "End of game!" << std::endl;
			exit(0);
		}
		else if (key == 'w' || key == 's' || key == 'a' || key == 'd') {
			Update();
			player.Move(key, maze);
			maze[player.GetY()][player.GetX()] = 'C';
			break;
		}
		else {
			key = _getch();
		}
	}
}

void Game::UpdateLuke() {
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(2));

		std::lock_guard<std::mutex> lock(mazeMutex);
		showLuke = !showLuke;
		if (showLuke) {
			maze[12][13] = '_';
			maze[12][14] = '_';
		}
		else {
			maze[12][13] = ' ';
			maze[12][14] = ' ';
		}
	}
}
