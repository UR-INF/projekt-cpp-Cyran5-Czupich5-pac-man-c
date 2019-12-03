#include <iostream>

#include "Game.h"
#include "Palata.h"
#include "UstalanieAtrybut.h"

using namespace std;

Palata::Palata(Game* const g)
	: game(g) {}

void Palata::Print() {
	SetCursorPosition(x, y);
	cout << game->GetLeveL(x, y);
}