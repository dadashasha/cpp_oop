#pragma once
#include "Entity.h"
#include <ctime>

class Super : public Entity {
public:
	Super(int startX, int startY) : Entity(startX, startY) {}

	void Move(std::vector<std::vector<char>>& maze);
};

