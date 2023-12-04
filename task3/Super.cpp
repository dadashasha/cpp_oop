#include "Super.h"

void Super::Move(std::vector<std::vector<char>>& maze) {
	int newX = std::rand() % maze[0].size();
	int newY = std::rand() % maze.size();
	if (maze[newY][newX] != ' ' && 
		maze[newY][newX] != 'g' && 
		maze[newY][newX] != 'C' &&
		maze[newY][newX] != '#' &&
		maze[newY][newX] != '_') {
		if (CanMove(newX, newY, maze)) {
			maze[y][x] = '.';
			x = newX;
			y = newY;
			maze[y][x] = 'O';
		}
	}
}
