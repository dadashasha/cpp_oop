#include "Character.h"

void Character::Move(int dx, int dy) {
	x += dx;
	y += dy;
}
int Character::GetX() const{
	return x;
}
int Character::GetY() const {
	return y;
}