#include <iostream>
#include <ctime>
#include <cstdlib>

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

int main()
{
	system("chcp 1251");
	MyClass a(10);
	a.display(a);
	return 0;
}