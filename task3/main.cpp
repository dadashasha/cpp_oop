#include "Character.h"
#include "Game.h"

int main(void) {
	Game game;
	char key;
	do {
		key = _getch();
		game.HandleInput(key);
		game.Draw();
		Sleep(100);
	} while (true);
	return 0;
}
