#pragma once
#ifndef WartosciStale
#define WartosciStale

#include <Windows.h>

const int maxHeight = 31;
const int maxWidth = 28;
const int G_X = 13;
const int G_Y = 12;

const char WITHOUT_COLISION_TILES[3] = {' ', 'o','\xfa'};

const char CONSTOL_CHARS[4] = { 'w','a','s','d' };
const char PACMAN_RUCHY[4] = { 'v','>','^','<' };
const char DUSZEK_IKONA = { 'G' };

const char MARTWY_DUSZEK = { 'W' };

const int WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const int RED = FOREGROUND_RED | FOREGROUND_INTENSITY;
const int BLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const int DARK_BLUE = FOREGROUND_BLUE;
const int CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const int MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const int YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int BLACK = 0;

const int SUPER_MAX = 500;
const int ONE_UP_MAX = 13;
const int PELLET_MAX = 8;
const int PACMAN_MAX = 8;
const int GHOST_MAX = 10;
const int RUN_MAX = 16;
const int DEAD_MAX = 3;
const int MODE_MAX = 1000;

const int BLINKY = 0;
const int PINKY = 1;
const int INKY = 2;
const int CLYDE = 3;

#endif;