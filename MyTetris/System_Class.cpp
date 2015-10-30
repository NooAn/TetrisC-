#pragma once //см google))
#include "header.h"
#include "define.h" // подключения заголовочных файлов библиотек и определений  
/*
Класс System. 
Реализует методы рандома, задержки, и паузы.
*/
class System {
public:

	int random(int max) //рандомизация
	{
		return (int)(rand() * (max+1) / RAND_MAX);
	}

	void sleep(int milsec) //задержка
	{
		clock_t t = clock();
		while (clock() - t < milsec);
	}

	int getkey(void)//-пауза во время игры
	{
		int c;
		if (_kbhit()) //если нажата клавиша
		{
			if ((c = _getch()) == 224)
				c = _getch();
			//если нажата клавиша p (пауза), то нажать любую клавишу для продолжения игры
			return c;
		}
		return 0;
	}
};