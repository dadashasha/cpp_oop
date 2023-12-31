#pragma once
#include "Entity.h"
#include "Character.h"
#include "Enemy.h"
#include "Super.h"
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include <thread>
#include <chrono>

class Game {
private:
    std::vector<std::vector<char>> maze;
    Character player;
    std::vector<Enemy> enemies;
    Super super;
    int score;
    bool Death;
public:
    Game() : player(2, 1), enemies({ Enemy(1, 1), Enemy(26, 1)}), super(1, 2), score(0), Death(false) {
        maze = {
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
            {'#', '.', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '.', '#'},
            {'#', '.', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '.', '#'},
            {'#', '.', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '.', '#'},
            {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
            {'#', '.', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '.', '#'},
            {'#', '.', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '.', '#'},
            {'#', '.', '.', '.', '.', '.', '.', '#', '#', '.', '.', '.', '.', '#', '#', '.', '.', '.', '.', '#', '#', '.', '.', '.', '.', '.', '.', '#'},
            {'#', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '#'},
            {' ', ' ', ' ', ' ', ' ', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', '#', '.', '#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#', '.', '#', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', '#', '.', '#', '#', '.', '#', '#', '#', '.', '.', '#', '#', '#', '.', '#', '#', '.', '#', ' ', ' ', ' ', ' ', ' '},
            {'#', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '.', '.', '.', '.', '.', '.', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '#'},
            {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
            {'#', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '.', '.', '.', '.', '.', '.', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '#'},
            {' ', ' ', ' ', ' ', ' ', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', '#', '.', '#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#', '.', '#', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', ' ', ' ', ' ', ' ', ' '},
            {'#', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '#'},
            {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
            {'#', '.', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '.', '#'},
            {'#', '.', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '.', '#'},
            {'#', '.', '.', '.', '#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#', '.', '.', '.', '#'},
            {'#', '#', '#', '.', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '.', '#', '#', '#'},
            {'#', '#', '#', '.', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '.', '#', '#', '#'},
            {'#', '.', '.', '.', '.', '.', '.', '#', '#', '.', '.', '.', '.', '#', '#', '.', '.', '.', '.', '#', '#', '.', '.', '.', '.', '.', '.', '#'},
            {'#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#'},
            {'#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#'},
            {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
        };
        maze[player.GetY()][player.GetX()] = 'C';
        for (const auto& enemy : enemies) {
            maze[enemy.GetY()][enemy.GetX()] = 'g';
        }
        maze[super.GetY()][super.GetX()] = 'O';
    }

    void Update_Character();
    void Update_Enemy();
    void Update_Super();
    void Draw();
    void HandleInput();
};
