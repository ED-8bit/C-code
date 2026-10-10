#include <iostream>
using namespace std;

class three_d
{
	int x, y, z;
public:
	three_d() { x = y = z = 0; }
	three_d(int i, int j, int k){
		x = i; y = j; z = k;
	}
	three_d operator+(three_d op2);
	three_d operator++();
	three_d operator++(int notused);
	three_d operator=(three_d op2);
	bool operator==(three_d op2);
	void show();
};
void three_d::show() {
	if (x)
		cout << x << ", ";
	else
		cout << "0, ";
	if (y)
		cout << y << ", ";
	else
		cout << "0, ";
	if (z)
		cout << z;
	cout << '\n';
}
three_d three_d::operator+(three_d op2) {
	three_d temp;
	temp.x = x + op2.x;
	temp.y = y + op2.y;
	temp.z = z + op2.z;
	return temp;
}
three_d three_d::operator++() {
	x++; y++; z++;
	return *this;
}
three_d three_d::operator++(int notused) {
	three_d temp = *this;
	x++; y++; z++;
	return temp;
}
three_d three_d::operator=(three_d op2) {
	x = op2.x;
	y = op2.y;
	z = op2.z;
	return *this;
}
bool three_d::operator==(three_d op2) {
	if ((x == op2.x) &&
		(y == op2.y) &&
		(z = op2.z))
		return true;
	else
		return false;
}

class CL
{
public:
	int count;
	CL operator=(CL obj);
	friend CL operator+(CL ob, int i);
	friend CL operator+(int i, CL ob);
};
CL CL::operator=(CL obj) {
	count = obj.count;
	return *this;
}
CL operator+(CL ob, int i) {
	CL temp;
	temp.count = ob.count + i;
	return temp;
}
CL operator+(int i, CL ob) {
	CL temp;
	temp.count = ob.count + i;
	return temp;
}

class my_vector
{
	int n;
	double* v;
public:
	my_vector(int c = 2);
	my_vector(const my_vector& copy);
	~my_vector();
	my_vector operator=(const my_vector other);
	my_vector operator+(const my_vector& other) const;
	my_vector operator+=(my_vector& other);
	my_vector operator*(double m);
	friend my_vector operator*(double m, my_vector& v);
	double operator^(my_vector& other);
	double& operator[](int i);

	void Enter(double d, int i) {
		if (i < n && i >= 0)
			v[i] = d;
		else
			cout << "Неправильный индекс";
	}
	void Print() {
		cout << '(';
		for (int i = 0; i < n; i++)
		{
			if (i + 1 != n)
				cout << v[i] << ", ";
			else
				cout << v[i] << ' ';
		}
		cout << ')';
		cout << '\n';
	}
};
my_vector::my_vector(int c): n(c){
	v = new double[n];
	for (int i = 0; i < n; i++) v[i] = 0.0;
}
my_vector::my_vector(const my_vector& copy) {
	n = copy.n;
	v = new double[n];
	for (int i = 0; i < n; i++)
	{
		v[i] = copy.v[i];
	}
}
my_vector::~my_vector(){ 
	delete[] v; 
}

my_vector my_vector::operator=(const my_vector other) {
	if (this == &other) return *this;

	if (n != other.n)
	{
		delete[] v;
		n = other.n;
		v = new double[n];
	}
	for (int i = 0; i < n; i++)
	{
		v[i] = other.v[i];
	}
	return *this;
}
my_vector my_vector::operator+(const my_vector& other) const {

	int maxLen, minLen;

	auto my_sum = [&maxLen, &minLen](const double a[], const double b[]) {
		my_vector temp(maxLen);
		for (int i = 0; i < maxLen; i++) {
			if (i < minLen)
			{
				temp.v[i] = a[i] + b[i];
			}
			else
				temp.v[i] = a[i];
		}
		return temp;
		};

	if (n > other.n)
	{
		maxLen = n; minLen = other.n;
		return my_sum(this->v, other.v);
	}
	else
	{
		maxLen = other.n; minLen = n;
		return my_sum(other.v, this->v);
	}

}
my_vector my_vector::operator+=(my_vector& other) {
	my_vector temp = *this + other;
	return temp;
}
my_vector my_vector::operator*(double m) {
	my_vector temp(n);
	for (int i = 0; i < n; i++)
	{
		temp.v[i] = v[i] * m;
	}
	return temp;
}
my_vector operator*(double m, my_vector& v) {
	my_vector temp(v.n);
	for (int i = 0; i < temp.n; i++)
	{
		temp.v[i] = v.v[i] * m;
	}
	return temp;
}
double my_vector::operator^(my_vector& other) {
	int maxLen, minLen;

	auto my_scal = [&maxLen, &minLen](const double a[], const double b[]) {
		double scal = 0;
		for (int i = 0; i < maxLen; i++) {
			if (i < minLen)
			{
				scal += a[i] * b[i];
			}
		}
		return scal;
		};

	if (n > other.n)
	{
		maxLen = n; minLen = other.n;
		return my_scal(this->v, other.v);
	}
	else
	{
		maxLen = other.n; minLen = n;
		return my_scal(other.v, this->v);
	}
}
double& my_vector::operator[](int i) {
	if (i < n && i >= 0)
		return v[i];
}

class Stack
{
	int* s;
	int top;
	int size;
public:
	Stack(int max = 10);
	Stack(const Stack& copy);
	~Stack();

	Stack& operator=(const Stack& other);
	// Stack operator!();
	friend Stack operator!(const Stack& st);

	void push(int n);
	int pop();
	void Print();
};

Stack::Stack(int max): size(max){
	top = -1; s = new int[size];
}
Stack::~Stack(){
	delete[] s;
}
//Stack Stack::operator!() {
//	Stack temp(size);
//	for (int i = 0; i <= top; i++)
//	{
//		temp.s[i] = -s[i];
//	}
//	return temp;
//}
Stack::Stack(const Stack& copy) {
	size = copy.size;
	top = copy.top;
	s = new int[size];
	for (int i = 0; i <= top; i++) {
		s[i] = copy.s[i];
	}
}
Stack& Stack::operator=(const Stack& other) {
	if (this == &other) return *this;

	if (size != other.size) {
		delete[] s;
		size = other.size;
		s = new int[size];
	}
	for (int i = 0; i <= other.top; i++) {
		s[i] = other.s[i];
	}
	top = other.top;
	return *this;
}
Stack operator!(const Stack& st) {
	Stack temp(st.size);
	for (int i = 0; i <= st.top; i++)
	{
		temp.s[i] = -st.s[i];
	}
	temp.top = st.top;
	return temp;
}
void Stack::push(int n) {
	if (top + 1 < size)
	{
		s[++top] = n;
	}
	else
		cout << "Стек заполнен\n";
}
int Stack::pop() {
	if (top >= 0) { 
		return s[top--]; 
	}
	else {
		cout << "Стек пуст\n";
		return 0; 
	}
}
void Stack::Print() {
	cout << '(';
	for (int i = 0; i <= top; i++)
	{
		if (i != top)
			cout << s[i] << ", ";
		else
			cout << s[i] << ' ';
	}
	cout << ')';
	cout << '\n';
}
// Стеку не нужны геттеры ир сеттеры по индексу, ведь структура работает по принципу LIFO. Достаточно иметь доступ для функции перегрузки операторов 

#include <cmath>
#include <stdexcept>

class Fraction {
	int num;
	int den;
	void Reduce() {

		int a = abs(num);
		int b = abs(den);
		while (b) {
			a %= b;
			swap(a, b);
		}
		int gcd = a;

		num /= gcd;
		den /= gcd;

		if (den < 0) {
			num = -num;
			den = -den;
		}
	}
public:
	Fraction(int n = 0, int d = 1) : num(n), den(d) {
		Reduce();
	}

	Fraction operator+(const Fraction& other) const {
		return Fraction(num * other.den + other.num * den, den * other.den);
	}
	Fraction operator-(const Fraction& other) const {
		return Fraction(num * other.den - other.num * den, den * other.den);
	}
	Fraction operator*(const Fraction& other) const {
		return Fraction(num * other.num, den * other.den);
	}
	Fraction operator/(const Fraction& other) const {
		if (other.num == 0)
			return;
		else
		return Fraction(num * other.den, den * other.num);
	}
	Fraction operator-() const {
		return Fraction(-num, den);
	}
	bool operator==(const Fraction& other) const {
		return num * other.den == other.num * den;
	}
	void Print() const {
		std::cout << num << "/" << den << "\n";
	}
};

class Matrix {
	int rows, cols;
	double** data;

	void init() {
		if (rows == 0 || cols == 0) {
			data = nullptr;
			return;
		}
		data = new double* [rows];
		for (int i = 0; i < rows; ++i) {
			data[i] = new double[cols] {0.0};
		}
	}

	void del() {
		if (data) {
			for (int i = 0; i < rows; ++i) delete[] data[i];
			delete[] data;
		}
	}

public:
	Matrix(int r = 0, int c = 0) : rows(r), cols(c) {
		init();
	}
	Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
		init();
		for (int i = 0; i < rows; ++i)
			for (int j = 0; j < cols; ++j)
				data[i][j] = other.data[i][j];
	}
	~Matrix() { del(); }

	Matrix& operator=(const Matrix& other) {
		if (this == &other) return *this;
		del();
		rows = other.rows;
		cols = other.cols;
		init();
		for (int i = 0; i < rows; ++i)
			for (int j = 0; j < cols; ++j)
				data[i][j] = other.data[i][j];
		return *this;
	}
	Matrix operator+(const Matrix& other) const {
		if (rows != other.rows || cols != other.cols) {
			cout << "Ошибка: размеры матриц не совпадают при сложении.\n";
			return Matrix(0, 0);
		}
		Matrix res(rows, cols);
		for (int i = 0; i < rows; ++i)
			for (int j = 0; j < cols; ++j)
				res.data[i][j] = data[i][j] + other.data[i][j];
		return res;
	}
	Matrix operator-(const Matrix& other) const {
		if (rows != other.rows || cols != other.cols) {
			cout << "Ошибка: размеры матриц не совпадают при вычитании.\n";
			return Matrix(0, 0);
		}
		Matrix res(rows, cols);
		for (int i = 0; i < rows; ++i)
			for (int j = 0; j < cols; ++j)
				res.data[i][j] = data[i][j] - other.data[i][j];
		return res;
	}
	Matrix operator*(const Matrix& other) const {
		if (cols != other.rows) {
			cout << "Ошибка: несовместимые размеры для умножения.\n";
			return Matrix(0, 0);
		}
		Matrix res(rows, other.cols);
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < other.cols; ++j) {
				for (int k = 0; k < cols; ++k) {
					res.data[i][j] += data[i][k] * other.data[k][j];
				}
			}
		}
		return res;
	}
	Matrix operator*(double scalar) const {
		Matrix res(rows, cols);
		for (int i = 0; i < rows; ++i)
			for (int j = 0; j < cols; ++j)
				res.data[i][j] = data[i][j] * scalar;
		return res;
	}
};

class Complex {
	double re;
	double im;

public:
	Complex(double r = 0.0, double i = 0.0) : re(r), im(i) {}

	Complex operator+(const Complex& other) const {
		return Complex(re + other.re, im + other.im);
	}
	Complex operator-(const Complex& other) const {
		return Complex(re - other.re, im - other.im);
	}
	Complex operator*(const Complex& other) const {
		return Complex(re * other.re - im * other.im,
			re * other.im + im * other.re);
	}
	Complex operator/(const Complex& other) const {
		double denominator = other.re * other.re + other.im * other.im;
		if (denominator == 0) throw std::invalid_argument("Деление на ноль.");
		return Complex((re * other.re + im * other.im) / denominator,
			(im * other.re - re * other.im) / denominator);
	}
	Complex operator-() const {
		return Complex(-re, -im);
	}
	bool operator==(const Complex& other) const {
		return (re == other.re) && (im == other.im);
	}

};

class Date {
	int day, month, year;

	bool isHighYear(int y) const {
		return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
	}
	int daysInMonth(int m, int y) const {
		if (m == 2) return isHighYear(y) ? 29 : 28;
		if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
		return 31;
	}

public:
	Date(int d = 1, int m = 1, int y = 2000) : day(d), month(m), year(y) {}

	Date& operator++() {
		day++;
		if (day > daysInMonth(month, year)) {
			day = 1;
			month++;
			if (month > 12) {
				month = 1;
				year++;
			}
		}
		return *this;
	}
	Date operator++(int) {
		Date temp = *this;
		++(*this);
		return temp;
	}
	Date& operator--() {
		day--;
		if (day < 1) {
			month--;
			if (month < 1) {
				month = 12;
				year--;
			}
			day = daysInMonth(month, year);
		}
		return *this;
	}
	Date operator--(int) {
		Date temp = *this;
		--(*this);
		return temp;
	}

	bool operator==(const Date& o) const {
		return year == o.year && month == o.month && day == o.day;
	}
	bool operator!=(const Date& o) const { return !(*this == o); }
	bool operator<(const Date& o) const {
		if (year != o.year) return year < o.year;
		if (month != o.month) return month < o.month;
		return day < o.day;
	}
	bool operator>(const Date& o) const { return o < *this; }
	bool operator<=(const Date& o) const { return !(o < *this); }
	bool operator>=(const Date& o) const { return !(*this < o); }
};

int main()
{
	system("chcp 1251");
	cout << '\n';

	//three_d d1(3, 5, 1);
	//three_d d2(2, 0, 7);
	//d1.show();
	//d2.show();
	//three_d d3;
	//d3 = ++d2;
	//d3.show();
	//d3 = d3 + d1;
	//d3.show();

	//CL a;
	//a.count = 5;
	//CL b;
	//b.count = 3;
	//b + 2;
	//a = b;

	//cout << "\n\n";

	//my_vector a(2), b(3), c(3);
	//a.Enter(1.5, 0);
	//a.Enter(4.0, 1);
	//b.Enter(-2.0, 0);
	//b.Enter(3.0, 1);
	//b.Enter(2.4, 2);
	//c.Enter(8.0, 0);
	//c.Enter(1.3, 1);
	//c.Enter(5.4, 2);
	//a.Print();
	//b.Print();
	//c.Print();

	//my_vector d = a + b;
	//d.Print();

	//double res;
	//res = a ^ b;
	//cout << res << '\n';
	//c = c * res;
	//c.Print();

	//my_vector *arr[4];
	//arr[0] = &a;
	//arr[1] = &b;
	//arr[2] = &c;
	//arr[3] = &d;

	//arr[0]/*a*/ = &c;

	//arr[0]->Print();
	//d = *arr[0]/*c*/;
	//d.Print();

	//cout << "\n\n";

	//Stack st(5);

	//for (int i = 0; i < 5; i++) {
	//	int n = (i % 2 != 0) ? -1 : 1;
	//	st.push(i * n * 17);
	//}
	//st.Print();
	//st = !st;
	//st.Print();

	//cout << "\n\n";

	//Fraction f1(1, 6); 
	//Fraction f2(1, 3); 

	//f1.Print();
	//f2.Print();
	//Fraction f3 = f1 + f2;
	//f3.Print();

	//Fraction f4 = f1 * f2;
	//f4.Print();

	//if (Fraction(1, 2) == Fraction(2, 4)) {
	//	cout << "Дроби 1/2 и 2/4 равны!\n";
	//}

	//Matrix m1(2, 2);
	//Matrix m2(2, 2);
	//Matrix m3 = m1 + m2;
	//Matrix m4 = m1 * m2;
	//Matrix m5 = m1 * 2.5;

	//cout << "\n\n";

	//Complex c1(2.0, 3.0);
	//Complex c2(1.0, -1.0);
	//Complex c3 = c1 + c2;
	//Complex c4 = c1 * c2;
	//Complex c5 = c1 / c2;

	//if (c1 == Complex(2.0, 3.0)) {
	//	cout << "Оператор == для Complex работает\n";
	//}

	//cout << "\n\n";

	//Date d1(28, 2, 2024); // Високосный год
	//Date d2(1, 3, 2024);

	//if (d1 < d2) {
	//	cout << "d1 раньше чем d2\n";
	//}
	//else if (d1 > d2)
	//	cout << "d1 позже чем d2\n";
	//else
	//	cout << "d1 = d2\n";

	//++d1; // d1 должен стать 29.02.2024

	//d1++; // d1 должен стать 01.03.2024

	//if (d1 < d2) {
	//	cout << "d1 раньше чем d2\n";
	//}
	//else if (d1 > d2)
	//	cout << "d1 позже чем d2\n";
	//else
	//	cout << "d1 = d2\n";

	//cout << "\n\n";


	return 0;


}


