#include <iostream>

#include "Game.h"
#include "Palata.h"
#include "UstalanieAtrybut.h"

using namespace std;

Palata::Palata(Game* const g)
	: game(g) {}

void Palata::Print() {
	SetPosCursor(x, y);
	cout << game->GetLevel(x, y);
}