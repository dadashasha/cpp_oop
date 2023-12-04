#include "Game.h"

int main(void) {
	Game game;
	while (true) {
		game.Draw();
		game.HandleInput();
		Sleep(400);
	}
	return 0;
}
