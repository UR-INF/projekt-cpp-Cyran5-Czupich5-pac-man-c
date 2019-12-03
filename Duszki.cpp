#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <clocale>
#include <cstdlib>

#include "WartosciStale.h"

#include "Game.h"
#include "Duszki.h"
#include "UstalanieAtrybut.h"

using namespace std;

Duszki::Duszki(Game* const g)
	: game(g) {}

void Duszki::Move(int playerY, int playerX) {
	if (wait) {
		--wait;
	}
	else {
		switch (mode) {
		case 'w':
			Hide();
			if (y == G_Y + 2) {
				++y;
			}
			else {
				--y;
			}
			Show();
			wait = GHOST_MAX;
			break;
		case 'e':
			Hide();
			wait = GHOST_MAX;
			if (y > G_Y + 1) {
				--y;
			}
			else if (x < G_X) {
				++x;
			}
			else if (x > G_X) {
				--x;
			}
			else if (y != G_Y - 1) {
				--y;
				SetPosCursor(G_Y, G_X + 1);
				cout << game->GetLevel(G_Y, G_X + 1);
			}
			else {
				modeOld = mode;
				if (color == BLUE) {
					mode = 'r';
				}
				else {
					mode = 'c';
				}
				dirOld = 'w';
				wait = 0;
			}
			Show();
			break;
		case 'n':
			if (y != G_Y + 1) {
				dir = 's';
				ChangeCoords();
				SetPosCursor(G_Y, G_X + 1);
				cout << game->GetLevel(G_Y, G_X + 1);
				wait = DEAD_MAX;
			}
			else {
				color = colorInit;
				mode = 'e';
				wait = GHOST_MAX;
				icon = DUSZEK_IKONA;
			}
			break;
		case 's':
			GetOpposite();
			if (modeOld == 'e') {
				modeOld = mode;
			}
			if (mode != modeOld) {
				dir = dirOpp;
				ChangeCoords();
				modeOld = mode;
			}
			else {
				RandomDirection();
			}
			dirOld = dir;
			wait = GHOST_MAX;
			break;
		case 'c':
			GetOpposite();
			if (modeOld == 'e') {
				modeOld = mode;
			}
			if (mode != modeOld) {
				dir = dirOpp;
				ChangeCoords();
				modeOld = mode;
			}
			else {
				bool down = y < playerY;
				bool up = y > playerY;
				bool right = x < playerX;
				bool left = x > playerX;
				bool favorableDirs[4] = { up, left, down, right };
				TargetObject(favorableDirs);
			}
			dirOld = dir;
			wait = GHOST_MAX;
			break;
		case 'r':
			GetOpposite();
			if (modeOld == 'e') {
				modeOld = mode;
			}
			if (mode != modeOld) {
				dir = dirOpp;
				ChangeCoords();
				modeOld = mode;
			}
			else {
				bool down = !(y < playerY);
				bool up = !(y > playerY);
				bool right = !(x < playerX);
				bool left = !(x > playerX);
				bool favorableDirs[4] = { up, left, down, right };
				TargetObject(favorableDirs);
			}
			dirOld = dir;
			wait = RUN_MAX;
			break;
		case 'd':
			GetOpposite();
			if (y != G_Y - 1 || x != G_X) {
				bool down = y < G_Y - 1;
				bool up = y > G_Y - 1;
				bool right = x < G_X;
				bool left = x > G_X;
				bool favorableDirs[4] = { up, left, down, right };
				TargetObject(favorableDirs);
			}
			else {
				mode = 'n';
			}
			dirOld = dir;
			wait = DEAD_MAX;
		}
	}
}

void Duszki::TargetObject(bool favorableDirs[4]) {
	int good = 0;
	char goodDirs[4] = { ' ',' ',' ',' ' };
	for (int i = 0; i < 4; ++i) {
		dir = CONSTOL_CHARS[i];
		if (favorableDirs[i] && TestForCollision() == false && dir != dirOpp) {
			goodDirs[good] = dir;
			++good;
		}
	}
	if (good == 0) {
		RandomDirection();
	}
	else {
		dir = goodDirs[rand() % good];
		ChangeCoords();
	}
}

void Duszki::RandomDirection() {
	GetOpposite();
	
	do {
		
		do {

			dir = CONSTOL_CHARS[rand() % 4];
		} while (dir == dirOpp);
	} while (TestForCollision() == true);
	ChangeCoords();
}

bool Duszki::TestForCollision() {
	
	switch (dir) {
	case 'a':
		
		if (x == 0 || strchr(WITHOUT_COLISION_TILES, game->GetLevel(y, x - 1))) {
			return false;
		}
		break;
	case 'd':
		
		if (x == maxWidth - 1 || strchr(WITHOUT_COLISION_TILES, game->GetLevel(y, x + 1))) {
			return false;
		}
		break;
	case 'w':
		if (strchr(WITHOUT_COLISION_TILES, game->GetLevel(y - 1, x))) {
			return false;
		}
		break;
	case 's':
		if (strchr(WITHOUT_COLISION_TILES, game->GetLevel(y + 1, x))) {
			return false;
		}
		break;
	}
	return true;
}

void Duszki::ChangeCoords() {
	Hide();
	if (dir == 'a') {
		if (x == 0) {
			x = maxWidth - 1;
		}
		else {
			--x;
		}
	}
	if (dir == 'd') {
		if (x == maxWidth - 1) {
			x = 0;
		}
		else {
			++x;
		}
	}
	if (dir == 'w') {
		--y;
	}
	if (dir == 's') {
		++y;
	}
	Show();
}

void Duszki::GetOpposite() {
	if (dirOld == 'a') {
		dirOpp = 'd';
	}
	if (dirOld == 'd') {
		dirOpp = 'a';
	}
	if (dirOld == 'w') {
		dirOpp = 's';
	}
	if (dirOld == 's') {
		dirOpp = 'w';
	}
}

void Duszki::Dead() {
	color = WHITE;
	modeOld = mode;
	mode = 'd';
	icon = MARTWY_DUSZEK;
}

void Duszki::Show() {
	SetTextColor(color);
	SetPosCursor(y, x);
	cout << icon;
}

void Duszki::Hide() {
	SetTextColor(WHITE);
	if (game->GetLevel(y, x) == 'o') {
		SetTextColor(game->GetPelletColor());
	}
	SetPosCursor(y, x);
	cout << game->GetLevel(y, x);
}