#pragma once
#include <vector>

class Character{
private:
	int x;
	int y;
public:
	Character(int startX, int startY) : x(startX), y(startY) {}


	bool CanMove(int dx, int dy, const std::vector<std::vector<char>>& maze) const;
	void Move(char key, const std::vector<std::vector<char>>& maze);

	int GetX() const;
	int GetY() const;
};
