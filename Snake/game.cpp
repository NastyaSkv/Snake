#include<iostream>
#include<conio.h>  //позволит взять функцию отслеживания
using namespace std;

bool gameOver;  //перем., начальное значение которой = false
const int width = 20; //ширина поля
const int height = 20; //высота поля
int x, y, fruitX, fruitY, score; //координаты змейки, фруктов, общий счет
int tailX[100], tailY[100]; //хранят элементы по X и Y
int nTail; //кол-во элементов в хвосте
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;  //

void Setup()   //ф-я, отв. за настройки параметров
{
	gameOver = false;  // false - т к изначально мы не проиграли
	dir = STOP;     //опишем начальное положение змейки. Она стоит
	x = width / 2 - 1;    //находится в середине экрана
	y = height / 2 - 1;
	fruitX = rand() % width;  //располагаем фрукты рандомно 
	fruitY = rand() % height;
	score = 0;   //начальный счет
}

void Draw()   //ф-я, которая будет рисовать
{
	system("cls"); //для очищения экрана
	for (int i = 0; i < width + 1; i++)  //верхняя границы
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++)  //боковая граница
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
				cout << "#";
			if (i == y && j == x)
				cout << "0";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;
						cout << "o";
					}
				}
				if (!print)cout << " ";
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width + 1; i++)  //нижняя граница
	{
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}

void Input()  //ф-я, которая будет отслеживать нажатия пользователя
{
	if (_kbhit())//ф-я возвр. истину, если пользователь нажал кнопку
	{
		switch (_getch()) //отслеж клавишу
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic()   //ф-я, где будет выполняться вся логика игры
{
	//Хвост
	int prevX = tailX[0]; //предыдущее значение
	int prevY = tailY[0];
	int prev2X, prev2Y;  //помещаем следующий элемент
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) //1 - т к нес 0-го элемента
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:  x--;
		break;
	case RIGHT: x++;
		break;
	case UP:    y--;
		break;
	case DOWN:  y++;
		break;
	}

	//if (x > width || x < 0 || y>height || y < 0)  //чтобы не выходил за границу
	//	gameOver = true;
	if (x >= width - 1)
		x = 0;
	else if (x < 0)
		x = width - 2;

	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;

	//съели ли мы хвост
	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

int main()
{
	Setup();   //эта ф-я запускается всего 1 раз
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
	}
	return 0;
}