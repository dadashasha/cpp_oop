#pragma once
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <vector>

class Enemy {
private:
	int x;
	int y;
	int direction;

public:
	Enemy(int startX, int startY) : x(startX), y(startY) {
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		direction = std::rand() % 4;
	}

	void MoveRandom(std::vector<std::vector<char>>& maze);
	int GetX() const;
	int GetY() const;
};
