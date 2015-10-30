#pragma once
#include "Tetris_Class.cpp" // Подключение заг.файла класса 


int main() //Начало программы Тетрис
{	
	setlocale(0, "");   // Руссификация для windods( что бы буквы по русски отоброжались)
	system("color 1A"); // Устанавливаем зеленый цвет вывода.
	Tetris tetris;      // Обьект класса Tetris обьявление
	tetris.gameTitle(); // Вызов метода класса Tetris для показа титров начальных
	tetris.gameMenu();  // Вызов метода для меню
}
