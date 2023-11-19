#pragma once
#include "Character.h"
#include "Enemy.h"
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>

class Game {
private:
	std::vector<std::vector<char>> maze;
	Character player;
    std::vector<Enemy> enemies;
    bool showLuke;
    std::mutex mazeMutex;
public:
    Game() : player(13, 11), showLuke(false), enemies({ Enemy(1, 1), Enemy(26, 1) }) {
        maze = {
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
            {'#', '.', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '.', '#'},
            {'#', 'O', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', 'O', '#'},
            {'#', '.', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '.', '#'},
            {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
            {'#', '.', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '.', '#'},
            {'#', '.', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '.', '#'},
            {'#', '.', '.', '.', '.', '.', '.', '#', '#', '.', '.', '.', '.', '#', '#', '.', '.', '.', '.', '#', '#', '.', '.', '.', '.', '.', '.', '#'},
            {'#', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '#'},
            {' ', ' ', ' ', ' ', ' ', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', '#', '.', '#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#', '.', '#', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', '#', '.', '#', '#', '.', '#', '#', '#', '_', '_', '#', '#', '#', '.', '#', '#', '.', '#', ' ', ' ', ' ', ' ', ' '},
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
        std::thread lThread(&Game::UpdateLuke, this);
        lThread.detach();
    }

    void UpdateLuke();
    void Update();
	void Draw();
	void HandleInput(char key);
};
