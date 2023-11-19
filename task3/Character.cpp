#include "Character.h"

bool Character::CanMove(int dx, int dy, const std::vector<std::vector<char>>& maze) const{
	int newX = (x + dx + maze[0].size()) % maze[0].size();
	int newY = y + dy;

	if (newX < 0 || newX >= maze[0].size() || newY < 0 || newY >= maze.size()) {
		return false;
	}

	return (maze[newY][newX] != '#' && maze[newY][newX] != '_');
}

void Character::Move(char key, const std::vector<std::vector<char>>& maze) {
	int dx = 0, dy = 0;

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

	if (CanMove(dx, dy, maze)) {
		x = (x + dx + maze[0].size()) % maze[0].size();
		y += dy;
	}
}
int Character::GetX() const{
	return x;
}
int Character::GetY() const {
	return y;
}
