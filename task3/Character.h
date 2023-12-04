#pragma once
#include "Entity.h"

class Character : public Entity {
public:
	Character(int startX, int startY) : Entity(startX, startY) {}

	void Move(std::vector<std::vector<char>>& maze, char key);
};
