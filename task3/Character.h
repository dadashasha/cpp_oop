#pragma once

class Character {
private:
	int x;
	int y;
public:
	Character(int startX, int startY) : x(startX), y(startY) {}

	void Move(int dx, int dy);

	int GetX() const;
	int GetY() const;
};
