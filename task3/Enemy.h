#pragma once
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "Entity.h"

class Enemy : public Entity {
private:
	int direction;//направление движения врага

public:
	Enemy(int startX, int startY) : Entity(startX, startY) {
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		direction = std::rand() % 4;
	}

	void Move(std::vector<std::vector<char>>& maze);
};
