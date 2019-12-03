#include <iostream>
#include <iomanip>
//#include <conio.h>
#include <Windows.h>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <clocale>
#include <cmath>
#include <random>

#include "WartosciStale.h"

#include "Game.h"
#include "Pacman.h"
#include "UstalanieAtrybut.h"

using namespace std;

PacMan::PacMan(Game* const g)
	: game(g) {
	hiScore = 0;
}

void PacMan::Move() {
	if (wait) {
		--wait;
	}
	else {
		GetDirection();
		if (TestForCollision() == false) {
			SetPosCursor(yOld, xOld);
			cout << game->GetLevel(yOld, xOld);
			if (game->GetLevel(y, x) != ' ') {
				int scoreInc;
				if (game->GetLevel(y, x) == 'o') {
					scoreInc = 50;
					super = SUPER_MAX;
				}
				else {
					scoreInc = 10;
				}
				PrintScore(scoreInc);
				game->SetLevel(y, x, ' ');
				--left;
			}
			Show();
			dirOld = dir;
			wait = PACMAN_MAX;
		}
	}
}

void PacMan::GetDirection() {
	dir = 'x';
	if (_kbhit()) {
		dir = std::ctype::tolower(_getch());
	}
	if (!strchr(CONSTOL_CHARS, dir)) {
		dir = dirOld;
	}
}

bool PacMan::TestForCollision() {
	xOld = x;
	yOld = y;

	switch (dir) {
	case 'a':
		
		if (x == 0) {
			x = maxWidth - 1;
			icon = PACMAN_RUCHY[1];
		}
		else if (strchr(WITHOUT_COLISION_TILES, game->GetLevel(y, x - 1))) {
			--x;
			icon = PACMAN_RUCHY[1];
		}
		break;
	case 'd':
		if (x == maxWidth - 1) {
			x = 0;
			icon = PACMAN_RUCHY[3];
		}
		else if (strchr(WITHOUT_COLISION_TILES, game->GetLevel(y, x + 1))) {
			++x;
			icon = PACMAN_RUCHY[3];
		}
		break;
	case 'w':
		if (strchr(WITHOUT_COLISION_TILES, game->GetLevel(y - 1, x))) {
			--y;
			icon = PACMAN_RUCHY[0];
		}
		break;
	case 's':
		if (strchr(WITHOUT_COLISION_TILES, game->GetLevel(y + 1, x))) {
			++y;
			icon = PACMAN_RUCHY[2];
		}
	}
	if (x == xOld && y == yOld) {
		return true;
	}
	return false;
}

void PacMan::PrintScore(int scoreInc) {
	if (score / 10000 < (score + scoreInc) / 10000) {
		++lives;
		PrintLives();
	}
	score += scoreInc;
	SetTextColor(WHITE);
	SetPosCursor(-2, 0);
	if (score == 0) {
		cout << setw(7) << "00";
	}
	else {
		cout << setw(7) << score;
	}
	if (score > hiScore) {
		hiScore = score;
		cout << setw(11) << hiScore;
	}
}

void PacMan::PrintLives() {
	SetTextColor(color);
	SetPosCursor(maxHeight, 2);
	for (int i = 1; i < lives; ++i) {
		cout << PACMAN_RUCHY[1] << " ";
	}
	cout << " ";
}

void PacMan::PrintKillScore() {
	++killCount;
	int scoreInc = 200 * (int)pow(2, killCount - 1);
	int length = (int)floor(log10(scoreInc)) + 1;
	int killX = x - 1;
	if (x == 0) {
		killX = x;
	}
	if (x > WITHOUT_COLISION_TILES - length) {
		killX = WITHOUT_COLISION_TILES - length;
	}
	SetTextColor(CYAN);
	SetPosCursor(y, killX);
	cout << scoreInc;
	PrintScore(scoreInc);
	Sleep(750);
	SetPosCursor(y, killX);
	for (int i = killX; i < killX + length; ++i) {
		SetTextColor(DARK_BLUE);
		if (game->GetLevel(y, i) == char(250)) {
			SetTextColor(WHITE);
		}
		if (game->GetLevel(y, i) == 'o') {
			SetTextColor(game->GetPelletColor());
		}
		cout << game->GetLevel(y, i);
	}
	Show();
}

void PacMan::Dead() {
	Sleep(1000);
	game->HideAll();
	for (int i = 0; i < 8; ++i) {
		icon = PACMAN_RUCHY[i % 4];
		Show();
		Sleep(100);
	}
	Hide();
	Sleep(500);
	--lives;
	if (lives != 0) {
		game->InitAll();
		game->ShowAll();
		PrintLives();
		game->PrintReady();
	}
	else {
		game->PrintGameOver();
	}
}

void PacMan::Show() {
	SetTextColor(color);
	SetPosCursor(y, x);
	cout << icon;
}

void PacMan::Hide() {
	SetPosCursor(y, x);
	cout << game->GetLevel(y, x);
}