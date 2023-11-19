#include "Enemy.h"

void Enemy::MoveRandom(std::vector<std::vector<char>>& maze) {
	int newX = x;
	int newY = y;

    switch (direction) {
    case 0:  //Вверх
        --newY;
        break;
    case 1:  //Вправо
        ++newX;
        break;
    case 2:  //Вниз
        ++newY;
        break;
    case 3:  //Влево
        --newX;
        break;
    }

    if (newX >= 0 && newX < maze[0].size() &&
        newY >= 0 && newY < maze.size() &&
        maze[newY][newX] != '#') {

        maze[y][x] = '.';
        x = newX;
        y = newY;
        maze[y][x] = 'g';

    }
    else {
        direction = std::rand() % 4;
    }
}

int Enemy::GetX() const{
	return x;
}

int Enemy::GetY() const {
	return y;
}
