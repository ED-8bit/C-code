#include <iostream>
#include <cstring>
using namespace std;

class B_class
{
	char author[80];
public:
	B_class(){}
	~B_class(){}
	void put_author(char* s) { strcpy_s(author, s); }
	void show_author() { cout << author << '\n'; }
};
class D_class: public B_class
{
	char title[80];
public:
	void put_title(char* num) { strcpy_s(title, num); }
	void show_title() { cout << "Название: " << title << "\n"; }
};

class base {
public:
	virtual void who() {
		cout << "Это базовый класс \n";
	}
};
class first_d : public base
{
public:
	void who() {
		cout << "Это первый класс \n";
	}
};
class second_d : public base
{
public:
	void who() {
		cout << "Это второй класс \n";
	}
};

class figure
{
protected:
	double x, y;
public:
	void set_dim(double i, double j = 0)
	{
		x = i; y = j;
	}
	virtual void show_area() = 0;
};

class triangle : public figure {
public:
	void show_area() {
		cout << "Треугольник с высотой ";
		cout << x << " и основанием " << y;
		cout << " имеет площадь: ";
		cout << x * 0.5 * y << "\n";
	}
};

class rectangle :public figure {
public:
	void show_area() {
		cout << "Прямоугольник с размерами ";
		cout << x << " x " << y;
		cout << " имеет площадь: ";
		cout << x * y << "\n";
	}
};

class circle : public figure {
public:
	void show_area() {
		cout << "Круг с радиусом ";
		cout << x;
		cout << " имеет площадь ";
		cout << 3.14 * x * x;
	}
};

int main()
{
	system("chcp 1251");

	//B_class* p;
	//B_class B_ob;
	//D_class* dp;
	//D_class D_ob;

	//char b[80] = "Эмиль Золя";
	//p = &B_ob;
	//p->put_author(b);

	//char d[80] = "Уильям Шекспир";
	//p = &D_ob;
	//p->put_author(d);

	//char c[80] = "Буря";
	//dp = &D_ob;
	//dp->put_title(c);
	//p->show_author();
	//dp->show_title();

	//base base_obj;
	//base* p;
	//first_d fobj;
	//second_d sobj;

	//p = &base_obj;
	//p->who();

	//p = &fobj;
	//p->who();

	//p = &sobj;
	//p->who();

	figure* p;
	triangle a;
	rectangle b;
	circle c;

	p = &a;
	p->set_dim(4, 5);
	p->show_area();

	p = &b;
	p->set_dim(10, 6);
	p->show_area();

	p = &c;
	p->set_dim(4);
	p->show_area();


	cout << "\n";
	return 0;
}
