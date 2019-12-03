#include <iostream>
#include <Windows.h>
#include <WinDef.h>

#include "WartosciStale.h"

#include "Game.h"
#include "PacMan.h"
#include "Duszki.h"
#include "Palata.h"
#include "UstalanieAtrybut.h"

using namespace std;

Game::Game() {
	SetTitleGame("TRUST ME, I'M PAC MAN");
	SetSizeGame(maxHeight + 5, maxWidth);
	SetVisibleCursor(false);
	gracz = new PacMan(this);
	for (int i = 0; i < 4; ++i) {
		duszki[i] = new Duszki(this);
		palata[i] = new Palata(this);
	}
}

Game::~Game() {
	delete gracz;
	for (int i = 0; i < 4; ++i) {
		delete duszki[i];
		delete palata[i];
	}
}

void Game::Go() {
	while (true) {
		MainLoop();
	}
}

void Game::MainLoop() {
	gracz->SetScore(0);
	gracz->SetLives(3);
	bool gameOver = false;
	for (int levelNum = 1; levelNum <= 255; ++levelNum) {
		LoadLevel();
		while (gracz->GetLeft() != 0) {
			gracz->Move();
			CheckForDeath();
			if (!gracz->GetLives()) {
				gameOver = true;
				break;
			}
			MoveGhosts();
			CheckForDeath();
			if (!gracz->GetLives()) {
				gameOver = true;
				break;
			}
			UpdateTimers();
		}
		if (gameOver) {
			break;
		}
		NextLevel();
	}
}

void Game::LoadLevel() {
	char levelMap[maxHeight][maxWidth + 1] = {
		"1555555555555555555555555552",
		"6............^^............6",
		"6.!%%@.!%%%@.^^.!%%%@.!%%@.6",
		"67^  ^.^   ^.^^.^   ^.^  ^86",
		"6.#%%$.#%%%$.#$.#%%%$.#%%$.6",
		"6..........................6",
		"6.!%%@.!@.!%%%%%%@.!@.!%%@.6",
		"6.#%%$.^^.#%%@!%%$.^^.#%%$.6",
		"6......^^....^^....^^......6",
		"355552.^#%%@ ^^ !%%$^.155554",
		"     6.^!%%$ #$ #%%@^.6     ",
		"     6.^^    B     ^^.6     ",
		"     6.^^ 155&&552 ^^.6     ",
		"555554.#$ 6      6 #$.355555",
		"      .   6I   C 6   .      ",
		"555552.!@ 6  P   6 !@.155555",
		"     6.^^ 35555554 ^^.6     ",
		"     6.^^          ^^.6     ",
		"     6.^^ !%%%%%%@ ^^.6     ",
		"155554.#$ #%%@!%%$ #$.355552",
		"6............^^............6",
		"6.!%%@.!%%%@.^^.!%%%@.!%%@.6",
		"6.#%@^.#%%%$.#$.#%%%$.^!%$.6",
		"69..^^.......X .......^^..06",
		"6%@.^^.!@.!%%%%%%@.!@.^^.!%6",
		"6%$.#$.^^.#%%@!%%$.^^.#$.#%6",
		"6......^^....^^....^^......6",
		"6.!%%%%$#%%@.^^.!%%$#%%%%@.6",
		"6.#%%%%%%%%$.#$.#%%%%%%%%$.6",
		"6..........................6",
		"3555555555555555555555555554" };
	char curChar;
	SetTextColor(WHITE);
	SetPosCursor(-3, 3);
	cout << "1UP";
	SetPosCursor(-3, 9);
	cout << "HIGH SCORE";
	gracz->PrintScore(0);
	SetPosCursor(0, 0);
	gracz->SetLeft(0);
	for (int y = 0; y < maxHeight; ++y) {
		for (int x = 0; x < maxWidth; ++x) {
			curChar = levelMap[y][x];
			SetTextColor(DARK_BLUE);
			switch (curChar) {
			case 'X':
				gracz->SetYInit(y);
				gracz->SetXInit(x);
				lvl[y][x] = ' ';
				break;
			case 'B':
				duszki[BLINKY]->SetYInit(y);
				duszki[BLINKY]->SetXInit(x);
				duszki[BLINKY]->SetColorInit(RED);
				duszki[BLINKY]->SetDirOpp('s');
				lvl[y][x] = ' ';
				break;
			case 'P':
				duszki[PINKY]->SetYInit(y);
				duszki[PINKY]->SetXInit(x);
				duszki[PINKY]->SetColorInit(MAGENTA);
				lvl[y][x] = ' ';
				break;
			case 'I':
				duszki[INKY]->SetYInit(y);
				duszki[INKY]->SetXInit(x);
				duszki[INKY]->SetColorInit(CYAN);
				lvl[y][x] = ' ';
				break;
			case 'C':
				duszki[CLYDE]->SetYInit(y);
				duszki[CLYDE]->SetXInit(x);
				duszki[CLYDE]->SetColorInit(YELLOW);
				lvl[y][x] = ' ';
				break;
			case '7':
				palata[0]->SetY(y);
				palata[0]->SetX(x);
				SetTextColor(WHITE);
				lvl[y][x] = 'o';
				gracz->SetLeft(gracz->GetLeft() + 1);
				break;
			case '8':
				palata[1]->SetY(y);
				palata[1]->SetX(x);
				SetTextColor(WHITE);
				lvl[y][x] = 'o';
				gracz->SetLeft(gracz->GetLeft() + 1);
				break;
			case '9':
				palata[2]->SetY(y);
				palata[2]->SetX(x);
				SetTextColor(WHITE);
				lvl[y][x] = 'o';
				gracz->SetLeft(gracz->GetLeft() + 1);
				break;
			case '0':
				palata[3]->SetY(y);
				palata[3]->SetX(x);
				SetTextColor(WHITE);
				lvl[y][x] = 'o';
				gracz->SetLeft(gracz->GetLeft() + 1);
				break;
			case '.':
				SetTextColor(WHITE);
				lvl[y][x] = char(250);
				gracz->SetLeft(gracz->GetLeft() + 1);
				break;
			case ' ':
				lvl[y][x] = curChar;
				break;
			case '&':
				SetTextColor(WHITE);
				curChar = '%';
			}
			if (curChar == '1') {
				lvl[y][x] = char(201);
			}
			else if (curChar == '2') {
				lvl[y][x] = char(187);
			}
			else if (curChar == '3') {
				lvl[y][x] = char(200);
			}
			else if (curChar == '4') {
				lvl[y][x] = char(188);
			}
			else if (curChar == '5') {
				lvl[y][x] = char(205);
			}
			else if (curChar == '6') {
				lvl[y][x] = char(186);
			}
			else if (curChar == '!') {
				lvl[y][x] = char(218);
			}
			else if (curChar == '@') {
				lvl[y][x] = char(191);
			}
			else if (curChar == '#') {
				lvl[y][x] = char(192);
			}
			else if (curChar == '$') {
				lvl[y][x] = char(217);
			}
			else if (curChar == '%') {
				lvl[y][x] = char(196);
			}
			else if (curChar == '^') {
				lvl[y][x] = char(179);
			}
			cout << lvl[y][x];
		}
		SetPosCursor(y + 1, 0);
	}
	InitAll();
	ShowAll();
	gracz->PrintLives();
	PrintReady();
}

void Game::NextLevel() {
	Sleep(1000);
	HideAll();
	SetPosCursor(12, 13);
	cout << "  ";
	for (int i = 0; i < 4; ++i) {
		SetScreenColor(WHITE);
		gracz->Show();
		Sleep(200);
		SetScreenColor(DARK_BLUE);
		gracz->Show();
		Sleep(200);
	}
	SetPosCursor(0, 0);
	InitAll();
}

void Game::PrintReady() {
	SetTextColor(YELLOW);
	SetPosCursor(17, 11);
	cout << "READY!";
	Sleep(2000);
	SetPosCursor(17, 11);
	cout << "      ";
}

void Game::PrintGameOver() {
	SetPosCursor(17, 9);
	SetTextColor(RED);
	cout << "GAME  OVER";
	Sleep(1000);
}

void Game::MoveGhosts() {
	if (gracz->GetSuper() == SUPER_MAX) {
		gracz->SetKillCount(0);
		for (int i = 0; i < 4; ++i) {
			if (duszki[i]->GetMode() != 'd') {
				duszki[i]->SetColor(BLUE);
			}
			if (duszki[i]->GetMode() == 's' || duszki[i]->GetMode() == 'c') {
				duszki[i]->SetMode('r');
			}
		}
		ShowAll();
	}
	if (gracz->GetLeft() == 235 && duszki[PINKY]->GetMode() == 'w') {
		duszki[PINKY]->SetMode('e');
	}
	if (gracz->GetLeft() == 200 && duszki[INKY]->GetMode() == 'w') {
		duszki[INKY]->SetMode('e');
	}
	if (gracz->GetLeft() == 165 && duszki[CLYDE]->GetMode() == 'w') {
		duszki[CLYDE]->SetMode('e');
	}
	for (int i = 0; i < 4; ++i) {
		duszki[i]->Move(gracz->GetY(), gracz->GetX());
	}
	ShowAll();
}

void Game::UpdateTimers() {
	if (gracz->GetSuper()) {
		gracz->SetSuper(gracz->GetSuper() - 1);
		if (gracz->GetSuper() <= 112 && gracz->GetSuper() % 28 == 0) {
			for (int i = 0; i < 4; ++i)
				if (duszki[i]->GetColor() == BLUE) {
					duszki[i]->SetColor(WHITE);
				}
			ShowAll();
		}
		if (gracz->GetSuper() <= 98 && (gracz->GetSuper() + 14) % 28 == 0) {
			for (int i = 0; i < 4; ++i) {
				if (duszki[i]->GetColor() == WHITE && duszki[i]->GetMode() != 'd' && duszki[i]->GetMode() != 'n') {
					duszki[i]->SetColor(BLUE);
				}
			}
			ShowAll();
		}
		if (!gracz->GetSuper()) {
			for (int i = 0; i < 4; ++i) {
				if (duszki[i]->GetMode() != 'd' && duszki[i]->GetMode() != 'n') {
					duszki[i]->SetColor(duszki[i]->GetColorInit());
				}
				if (duszki[i]->GetMode() == 'r') {
					duszki[i]->SetModeOld(duszki[i]->GetMode());
					duszki[i]->SetMode('c');
				}
			}
			ShowAll();
		}
	}
	if (oneUpTimer) {
		--oneUpTimer;
	}
	else {
		if (oneUpColor == WHITE) {
			oneUpColor = BLACK;
		}
		else {
			oneUpColor = WHITE;
		}
		SetTextColor(oneUpColor);
		SetPosCursor(-3, 3);
		cout << "1UP";
		oneUpTimer = ONE_UP_MAX;
	}
	// handle flashing super pellets
	if (pelletTimer) {
		--pelletTimer;
	}
	else {
		if (pelletColor == WHITE) {
			pelletColor = BLACK;
		}
		else {
			pelletColor = WHITE;
		}
		SetTextColor(pelletColor);
		for (int i = 0; i < 4; ++i) {
			palata[i]->Print();
		}
		ShowAll();
		pelletTimer = PELLET_MAX;
	}
	if (ghostModeTimer) {
		--ghostModeTimer;
		if (ghostModeTimer == MODE_MAX / 4) {
			for (int i = 0; i < 4; ++i) {
				if (duszki[i]->GetMode() == 'c') {
					duszki[i]->SetMode('s');
				}
			}
		}
	}
	else {
		for (int i = 0; i < 4; ++i) {
			if (duszki[i]->GetMode() == 's') {
				duszki[i]->SetMode('c');
			}
		}
		ghostModeTimer = MODE_MAX;
	}
	Sleep(15);
}

void Game::CheckForDeath() {
	for (int i = 0; i < 4; ++i) {
		if (gracz->GetX() == duszki[i]->GetX() && gracz->GetY() == duszki[i]->GetY() &&
			duszki[i]->GetMode() != 'd' && duszki[i]->GetMode() != 'n') {
			if (duszki[i]->GetMode() != 'r') {
				gracz->Dead();
			}
			else {
				gracz->PrintKillScore();
				duszki[i]->Dead();
			}
		}
	}
}

void Game::ShowAll() {
	gracz->Show();
	for (int i = 0; i < 4; ++i) {
		duszki[i]->Show();
	}
}

void Game::HideAll() {
	gracz->Hide();
	for (int i = 0; i < 4; ++i) {
		duszki[i]->Hide();
	}
}

void Game::InitAll() {
	gracz->SetY(gracz->GetYInit());
	gracz->SetX(gracz->GetXInit());
	gracz->SetColor(YELLOW);
	gracz->SetIcon(PACMAN_RUCHY[1]);
	gracz->SetDirOld('a');
	gracz->SetWait(0);
	gracz->SetSuper(0);
	for (int i = 0; i < 4; ++i) {
		duszki[i]->SetY(duszki[i]->GetYInit());
		duszki[i]->SetX(duszki[i]->GetXInit());
		duszki[i]->SetColor(duszki[i]->GetColorInit());
		duszki[i]->SetMode('w');
		duszki[i]->SetWait(0);
		duszki[i]->SetIcon(DUSZEK_IKONA);
	}
	duszki[BLINKY]->SetMode('c');
	duszki[BLINKY]->SetModeOld('c');
	if (gracz->GetLeft() <= 235) {
		duszki[PINKY]->SetMode('e');
	}
	if (gracz->GetLeft() <= 200) {
		duszki[INKY]->SetMode('e');
	}
	if (gracz->GetLeft() <= 165) {
		duszki[CLYDE]->SetMode('e');
	}
}
