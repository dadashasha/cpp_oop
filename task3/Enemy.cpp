#include "Enemy.h"

void Enemy::Move(std::vector<std::vector<char>>& maze) {
    int dx = 0;
    int dy = 0;

    switch (direction) {
    case 0:  //Вверх
        dy = -1;
        break;
    case 1:  //Вправо
        dx = 1;
        break;
    case 2:  //Вниз
        dy = 1;
        break;
    case 3:  //Влево
        dx = -1;
        break;
    }

    int newX = GetX() + dx;
    int newY = GetY() + dy;

    if (CanMove(newX, newY, maze)) {
        x = newX;
        y = newY;

    }
    else {
        direction = std::rand() % 4;
    }
}
