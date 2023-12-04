#include "Character.h"

void Character::Move(std::vector<std::vector<char>>& maze, char key) {
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

	int newX = GetX() + dx;
	int newY = GetY() + dy;

	if (CanMove(newX, newY, maze)) {
		x = newX;
		y = newY;
	}
}
