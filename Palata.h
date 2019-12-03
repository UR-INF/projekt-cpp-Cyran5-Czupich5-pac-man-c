#pragma once

#ifndef  PALATA_H

#define PALATA_H

class Game;

class Palata {
private:
	int x, y;

	Game* game;

public:
	Palata(Game* const g);
	void Print();
	void SetX(int x)
	{
		this->x = x;
	}
	void SetY(int y)
	{
		this->y = y;
	}

};

#endif