#pragma once
#include "define.h"
#include "header.h"

/* Класс Print реализуют методы для работы с печатью на экран.
	
*/
class Print { 
public :
	void print(int screen[SIZEX][SIZEY],int map[SIZE_MAP][SIZE_MAP], int px, int py, int score) //печать
	{
		int i, j;
		int buff[SIZEX][SIZEY];

		for (i = 0; i < SIZEY; i++) for (j = 0; j < SIZEX; j++) buff[j][i] = screen[j][i]; //вывод из буфера на экран
		for (i = 0; i < 4; i++) for (j = 0; j < 4; j++) if (map[j][i]) buff[j + px][i + py] = 1; //если часть фигуры, то в буфере обозначить 1

		gotoxy(0, 0); //перейти в точку с координатами 0, 0
		for (i = 0; i < SIZEY; i++)
		{
			for (j = 0; j < SIZEX; j++)
			{
				putchar(buff[j][i] == 0 ? SCR_SP : SCR_OB); //если элемент в буфере не часть фигуры, то закрасить полем
			}
			putchar('\n');
		}

		gotoxy(SIZEX + 1, 0); //уйти вбок
		printf("Колличество очков: %i", score); //вывести количество очков, набираемое в ходе игры
	}
	void gotoxy(int xpos, int ypos) //стандартная функция перехода курсором в точку с координатами xpos, ypos
	{
		COORD scrn;
		HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);//создание "ручки" для вывода на экран консоли текста и прочего 
		scrn.X = xpos; scrn.Y = ypos;//-присваем значения
		SetConsoleCursorPosition(hOuput, scrn);//-ставим курсор,на нужную позицию.
	}
	void nextmap(const int fmap[FMAP_COUNTS][4][4], int nextmap) //напечатать следующую идущую фигуру в поле cправа
	{
		int i, j;
		gotoxy(SIZEX + 1, 2); //перейти в точку с координатами SIZE+x,2
		printf("Следующая: ");

		for (i = 0; i < 4; i++) 
		{
			gotoxy(SIZEX + 2, i + 3);//перейти в точку с координатами SIZE+2,i+3
			for (j = 0; j < 4; j++)
			{
				putchar(fmap[nextmap][j][i] == 0 ? ' ' : SCR_OB); //если не часть фигуры, то закрасить пробелами, иначе закрасить фигурой
			}
		}
	}
};