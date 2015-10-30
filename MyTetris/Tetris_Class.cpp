#pragma once
#include "header.h"
#include "Screen_Class.cpp"
#include "Print_Class.cpp"
#include "define.h"
using namespace std;
class Tetris {
private:
	// поля класса закрытые для других классов
	int screen[SIZEX][SIZEY];    //размер экрана
	int map[SIZE_MAP][SIZE_MAP]; //фигура
	int px, py; //Координаты экрана.
	int score, nextmap; //Количесство очков и следующая фигура
	const char* GAME_TITLE =
		"###########  #########  ###########  ######## ####    ####  #########  \n"
		"##   ##  ##  ##         ##   ##  ##  ##    ##  ##    ####   ##     ##  \n"
		"##   ##  ##  ##         ##   ##  ##  ##    ##  ##   ## ##   ##         \n"
		"     ##      #########       ##      ########  ##  ##  ##   ##         \n"
		"     ##      ##              ##      ##        ## ##   ##   ##         \n"
		"     ##      ##              ##      ##        ####    ##   ##     ##  \n"
		"   ######    #########     ######   ####      ####    ####  #########  \n\n";


private:
	int valnewpos(int x, int y) //необходимость движения фигуры вниз. Если вернула TRUE то двигаемся вниз.Иначе нет.
	{
		int i, j;
		if (x < 0) return FALSE; // Двигаться не куда.
		for (i = 0; i < 4; i++)// Перебираем варианты
		{
			for (j = 0; j < 4; j++)
			{
				if (map[j][i])
				{
					if ((j + x >= SIZEX) || (i + y >= SIZEY)) return FALSE;//-проверка не зашла ли фигура за границы нашего экрана.
					if (screen[j + x][i + y])
					{
						return FALSE;//-если да то вернем "фолс"
					}
				}
			}
		}
		return TRUE;//-если нет возвращаем "тру" - фигура движется вниз.
	}

	void moveDownStep(int px, int py){// двигаемся вниз на один шаг.( координату)
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				if (map[j][i]) screen[px + j][py + i] = 1;
			}
		}
	}
	void moveDownFast(int screen[SIZEX][SIZEY]){// Двигаемся быстро до самого конца. Пока разрешает valnewpos()
		for (; valnewpos(px, py + 1); py++);
		moveDownStep(px, py);
		
	}
	void rotatemap(void) //поворот фигуры
	{
		int _map[4][4]; // буферный( дополнительный) массив для рабботы с map  
		int i, j, sx = 4, sy = 4;

		for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			_map[j][i] = map[j][i];//-создание копию фигуры,для того что бы вернуть первоначальный вид.
			if (map[j][i])//с услувием ЕСЛИ - фигура равна нулю ,то 
			{
				if (i < sx) sx = i;//проходим по фигурке запоминаем новую координату х
				if (inv(j) < sy) sy = inv(j);//новую координату у
			}
			map[j][i] = 0;//-обнуляем матрицу с фигурой
		}
		// вообщем здесь мы переворачиваем фигуру
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
				if (_map[inv(i)][j]) map[j - sx][i - sy] = 1;//рисуем перевертыш
				
		if (!valnewpos(px, py))
			for (i = 0; i < 4; i++) // Если двигаться уже нельзя
				for (j = 0; j < 4; j++)
					map[j][i] = _map[j][i];//возвращаем обратно на изначальную фигурку
	}
	void deleteline(int screen[SIZEX][SIZEY]) //убить собранную линию
	{
		int i, j, k, flag;
		System s; // создаем обьекта класса System
		Print print;// Создаем обьект класса Print для печати на экран (который мы написали ранее)
		for (i = SIZEY - 1; i >= 0; i--)
		{
			flag = 1;
			for (j = 0, flag = 1; j < SIZEX; j++)
			{
				if (!screen[j][i]) flag = 0; //пробегаемся по всем строчкам и проверяем ее на заполненость.
			}
			if (flag) // Если она так и осталась равная 1 то перерисовываем нашу игру, убираем линию. И добавляем очки
			{
				print.gotoxy(0, i);
				for (k = 0; k < SIZEX; k++) putchar('_'), s.sleep(20);
				/* --------- */

				score += (((i * (-1)) + SIZEY) * 10);// добавляем очки

				for (k = i; k > 0; k--)
				{
					for (j = 0; j < SIZEX; j++)
					{
						screen[j][k] = screen[j][k - 1];
					}
				}
				i++;
				print.print(screen, map, px, py, score);
			}
		}
	}
	void createmap(void) //создание фигуры
	{
		
		System s; // Обьекта класса System
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				map[j][i] = fmap[nextmap][j][i]; 
		py = 0;
		px = SIZEX / 2;

		Print print;// печать следующего
		nextmap = s.random(FMAP_COUNTS - 1);
		print.nextmap(fmap, nextmap);
	}
	void startGame(void){
		int i, j, c;
		time_t tm;

		system("cls"); // функция для очистки 
		System s;
		Print print;
		px = SIZEX / 2;//значение для падения фигуры по х,выход из центра
		py = 0;
		score = 0;//Очки в начале игры

		tm = clock();// получаем время. Нужно для падание фигуры

		nextmap = s.random(FMAP_COUNTS - 1);//следующая фигура выбирается из 6 
		createmap();//создание фигурки
		
		while (TRUE)
		{
			System s;
			c = s.getkey(); // вызывается метод класса System getKey()

			switch (c)
			{
			case KEY_UP:
				rotatemap();//поворот
				break;
			case KEY_SPACE:
				rotatemap();//поворот
				break;
			case KEY_DOWN://движение вниз
				moveDownFast(screen); //двиаемся вниз, при нажатии клавиши вниз
				print.print(screen, map, px, py, score);
				deleteline(screen);//проход по функции проверки заполнилась ли линия и её удаление
				createmap();//новая фигура
				break;
			case KEY_LEFT:
				if (valnewpos(px - 1, py)) px--;//движение влево ,уменьшаем значение пера по х
				break;
			case KEY_RIGHT:
				if (valnewpos(px + 1, py)) px++;//движение вправо ,увеличиваем значение пера по х
				break;
			case 'p'://пауза
				_getch();
				break;
			case KEY_ESC://выход
				return;
			}


			if ((clock() - tm) > 720)//-время падения фигуры 
			{
				tm = clock();

				if (!(valnewpos(px, py + 1)))
				{
					moveDownStep(px, py); // Если есть куда падать, то двигается вниз. 
					createmap();
					deleteline(screen);//  И делается проверка на заполненость строчки.
				}
				else py++;//падение вниз
			}

			print.print(screen, map, px, py, score); //печать экрана

			for (i = 0; i < SIZEX; i++)
			{
				if (screen[i][0])//если экраный у и у фигуры совпали и равны 0,то конец игры ,поле заполнилось до верха
				{
					system("cls");
					print.gotoxy(2, 8);
					printf("КОНЕЦ ИГРЫ! :(");
					return;
				}
			}
		}
	}

public:	 // Открытые методы класса, для ва
	void gameMenu(void) //игровое меню
	{
		Print print;
		Screen scr;
		int p = 1, c = 0;
		const char* GAME_MENU =
			"                     +===============================+\n"
			"                     |  1. СТАРТ                     |\n"
			"                     +===============================+\n"
			"                     |  2. СТАРТ(ПОВЫШ.УРОВЕНЬ)      |\n"
			"                     +===============================+\n"
			"                     |  3. УПРАВЛЕНИЕ                |\n"
			"                     +===============================+\n"
			"                     |  4. ВЫХОД                     |\n "
			"                    +===============================+";
		system("cls");
		printf("%s%s", GAME_TITLE, GAME_MENU);
		while (TRUE) { //Навигация по меню
			c = _getch();
			printf("\a");
			switch (c){
			case '1':
			case '2':
			case '3':
			case '4':
				p = c - '0'; //Реализация меню. ВЫбор зависит от нажатой клавиши. Смотрим какуюклавишу мы нажали
			case KEY_ENTER:
				switch (p)
				{
				case 1: // клавишу = 1
					scr.clear(screen);  
					startGame();
					print.gotoxy(0, SIZEY); 
					printf("Нажми ESC для выхода в главное меню...\n \a");  while (_getch() != KEY_ESC);
					break;
				case 2:
					scr.clear(screen); // Очистка экрана
					scr.createRandom(screen); // Создание рандомного заполнения экрана
					startGame(); // Начало игры
					print.gotoxy(0, SIZEY);
					printf("Нажми ESC для выхода в главное меню...\n \a");  while (_getch() != KEY_ESC);
					break;
				case 3:
					system("cls");
					printf("%s%s", GAME_TITLE,
						"+=======+=======+\n"
						"|\x1B      |Влево  |\n"
						"|\x1A      |Вправо |\n"
						"|\x19      |Вниз   |\n"
						"|\x18/Space|Поворот|\n"
						"|P      |Пауза  |\n"
						"|ESC    |Выход  |\n"
						"+=======+=======+\n\n"
						"Нажми клавишу...\n");
					_getch();
					printf("\a");
					if (_kbhit())
						_getch();
					break;

				case 4: return;
				}

				system("cls");
				printf("%s%s", GAME_TITLE, GAME_MENU);
				p = 1;
				break;
			case KEY_UP: // При нажатии вверх
				if (p > 1) p--; // уменьшаем значение
				break;
			case KEY_DOWN: // При нажатие вниз
				if (p < 4) p++;
				break;
			case KEY_ESC:
				return;
			}

		}
	}
	void gameTitle() { // Рисуем Титры Заголовка при запуске игры. Вызывается один раз из главной функции main()
		printf("%s", GAME_TITLE);
		printf("              Нажмите любую клавишу для продолжение");
		_getch();
		printf("\a");
		if (_kbhit()) _getch(); // Ждет нажатие клавиши
	}
};
