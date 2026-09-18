#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

class timer
{
private:
	int seconds;
public:
	timer(const char* t) { seconds = atoi(t); }
	timer(int t) { seconds = t; }
	timer(int min, int sec) { seconds = min * 60 + sec; }
	~timer(){}
	
	void run();
};
void timer::run() {
	clock_t t1 = clock();
	while ((clock() - t1) / CLOCKS_PER_SEC < seconds)
	{}
	cout << "\a";
}

class MyClass
{
private:
	int *val;
public:
	MyClass(int i) { val = new int; *val = i; cout << "Создание\n"; }
	~MyClass() { cout << "Разрушение\n"; delete val; }

	int getVal() { return *val; }

	void display(MyClass(&ob)) {
		cout << ob.getVal() << '\n';
	}
};

class Money
{
private:
	int rubles = 0;
	int kopecks = 0;
public:
	Money(){}
	Money(int totalKopecks) {
			rubles = totalKopecks / 100;
			kopecks = totalKopecks % 100;	
	}
	Money(int rub, int kop) {
		int total = rub * 100 + kop;
		rubles = total / 100;
		kopecks = total % 100;
		
	}
	Money(string amount) {
		int len = size(amount);
		int dot_pos = amount.find('.');
		if (dot_pos != string::npos)
		{
			rubles = stoi(amount.substr(0, dot_pos));
			kopecks = stoi(amount.substr(dot_pos + 1));
		}
	}
	~Money(){}

	int getRUB() { return rubles; }
	int getCOP() { return kopecks; }

	void print() {
		cout << rubles << " руб. " << kopecks << " коп.\n";
	}

};

class Marker {
	int id;
public:
	Marker(int i) : id(i) { cout << "Создание " << id << "\n"; }
	Marker(const Marker& m) : id(m.id) { cout << "Копия" << id << "\n"; }
	~Marker() {
		cout << "Удаление " <<	id << "\n"; }
	};

Marker make(int i) {
	Marker temp(i); return temp;
}
void use(Marker m) {
	cout << "Внутри use()\n";
}

class Matrix
{
private:
	int rows;
	int cols;
	double** data;

	void init() {
		data = new double* [rows];
		for (int i = 0; i < rows; i++)
		{
			data[i] = new double[cols];
		}
	}
	bool outBorder(int x, int y) {
		return (x >= rows && y >= cols);
	}
public:
	Matrix(int r, int c) : rows(r), cols(c) {
		init();
		for (int x = 0; x < rows; x++)
			for (int y = 0; y < cols; y++)
				data[x][y] = 0.0;
		cout << "Матрица " << rows << "x" << cols << " создана\n";
	}
	Matrix(const Matrix& copy) {
		rows = copy.rows;
		cols = copy.cols;
		init();
		for (int x = 0; x < rows; x++)
		{
			for (int y = 0; y < cols; y++)
				data[x][y] = copy.data[x][y];
		}

	}
	~Matrix(){
		for (int i = 0; i < rows; i++)
		{
			delete[] data[i];
		}
		delete[] data;
		cout << "Матрица удалена\n";
	}

	void Set(int x, int y, double val) {
		if (!outBorder(x, y))
			data[x][y] = val;
	}
	double Get(int x, int y) {
		if (!outBorder(x, y))
			return data[x][y];
	}

	void print() {
		for (int x = 0; x < rows; x++)
		{
			cout << "[";
			for (int y = 0; y < cols; y++)
			{
				if (y != cols - 1)
				{
					cout << data[x][y] << ',';
				}
				else
					cout << data[x][y];
			}
			
			cout << "]\n";
		}
		

	}
};
void printElement(Matrix m, int x, int y)
{
	cout << "Элемент: ("<< x << ", " << y << ") -> " << m.Get(x, y) << '\n';
}

class Polynomial
{
private:
	int degree;
	double* coeffs;

	bool outOfRange(int i) {
		return i >= degree;
	}
public:
	Polynomial(int deg): degree(deg){
		coeffs = new double[degree + 1];
		for (int i = 0; i < degree; i++)
			coeffs[i] = 0.0;
	}
	Polynomial(const Polynomial &copy): degree(copy.degree) {
		coeffs = new double[degree + 1];
		for (int i = 0; i < degree; i++)
			coeffs[i] = copy.coeffs[i];
	}
	~Polynomial() { delete[] coeffs; }

	void SetCoeff(int power, double value) {
		if (!outOfRange(power))
		coeffs[power] = value;
	}
	double GetCoeff(int power) {
		if (!outOfRange(power))
		return coeffs[power];
	}
	void print() {

	}
};

int main()
{
	system("chcp 1251");

	//Money T;
	//Money V(450);
	//Money S(125, 45);
	//Money A("245.32");
	//T.print();
	//V.print();
	//S.print();
	//A.print();
	//cout << "\n\n";

	/*
	Вывод:  "Создание 1\n" Вызовы: Конструктором a
			"Создание 2\n"         Конструктором b
			"Копия 1\n"            Конструктором копии из make 
			"Внутри use()\n"       Функцией use
			"Удаление 1"           Деструктором копии из make
			"Копия1"               Конструктором копии с = a
			"Удаление 1"		   Деструктором а
			"Удаление 2"           Деструктором b
			"Удаление 1"           Деструктором c
	*/
	//Marker a(1);
	//Marker b = make(2);
	//use(a);
	//Marker c = a;

	//cout << "\n\n";

	Matrix m(3, 2);
	m.Set(0, 0, 1.5);
	m.Set(0, 1, 2.0);
	m.Set(2, 0, 3.5);
	m.print();
	printElement(m, 0, 1);

	




	return 0;
}