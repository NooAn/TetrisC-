#pragma once
#include "header.h"
#include "System_Class.cpp"
#include "define.h"
class Screen : System {
public:
	void clear(int screen[SIZEX][SIZEY]) //очистка экрана
	{
		int i, j;
		for (i = 0; i < SIZEY; i++)
		for (j = 0; j < SIZEX; j++)
			screen[j][i] = 0;
	}
	void createRandom(int screen[SIZEX][SIZEY]) //создать случайный экран
	{
		int i, j, rn;
		clear(screen);

		rn = random(10);
		for (i = SIZEY - 1; i >= (SIZEY - 1) - rn; i--)
		for (j = 0; j < SIZEX; j++)
		{
			screen[j][i] = random(1);
		}
	}
};