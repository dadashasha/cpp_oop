#include "Game.h"

void Game::HandleInput() {
	Update_Super();
	Update_Enemy();
	while (_kbhit()) {
		char key = _getch();
		if (key == 'x') {
			std::cout << "End of game!" << std::endl;
			exit(0);
		}
		else if (key == 'w' || key == 's' || key == 'a' || key == 'd') {
			Update_Character();
			player.Move(maze, key);
			maze[player.GetY()][player.GetX()] = 'C';
		}
	}
}

void Game::Update_Super() {
	super.Move(maze);
}

void Game::Update_Enemy() {
	for (Enemy& enemy : enemies) {
		maze[enemy.GetY()][enemy.GetX()] = '.';
		enemy.Move(maze);
		maze[enemy.GetY()][enemy.GetX()] = 'g';
	}
}

void Game::Update_Character() {
		maze[player.GetY()][player.GetX()] = ' ';
		++score;
		if (maze[player.GetY() - 1][player.GetX()] == 'O' ||
			maze[player.GetY() + 1][player.GetX()] == 'O' ||
			maze[player.GetY()][player.GetX() - 1] == 'O' ||
			maze[player.GetY()][player.GetX() + 1] == 'O' ||
			maze[player.GetY() - 1][player.GetX() - 1] == 'O' ||
			maze[player.GetY() + 1][player.GetX() + 1] == 'O' ||
			maze[player.GetY() - 1][player.GetX() + 1] == 'O' ||
			maze[player.GetY() + 1][player.GetX() - 1] == 'O') {
			score += 100;
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
			else if (cell == 'O') {
				std::cout << "O" << " ";
			}
			else {
				std::cout << cell << " ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << "Scoring: " << score << std::endl;
	std::cout << "To end the game press \"x\". " << std::endl;

}
