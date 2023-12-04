#include "Entity.h"

int Entity::GetX() const {
    return x;
}

int Entity::GetY() const {
    return y;
}

int Entity::SetDeath(bool value) {
    death = value;
}

bool Entity::CanMove(int newX, int newY, const std::vector<std::vector<char>>& maze) const {
    return (newX < maze[0].size() && 
        newY < maze.size() && 
        maze[newY][newX] != '#' &&
        maze[newY][newX] != '_');
}
