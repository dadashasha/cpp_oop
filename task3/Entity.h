#pragma once
#include <vector>

class Entity {
protected:
    int x;
    int y;
public:
    bool death;
    Entity(int startX, int startY) : x(startX), y(startY), death(false) {}

    int SetDeath(bool value);
    int GetX() const;
    int GetY() const;
    bool CanMove(int dx, int dy, const std::vector<std::vector<char>>& maze) const;
};
