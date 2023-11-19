#include "Character.h"
#include "Game.h"

int main(void) {
	Game game;
	char key = '\0';
	while (true) {
		game.Draw();
		game.HandleInput(key);
		Sleep(100);
	}
	return 0;
}
