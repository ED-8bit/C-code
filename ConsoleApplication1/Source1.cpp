#include <iostream>
using namespace std;
int main()
{	double ml, km;
	system("chcp 1251");
	cout << "Введите количество километров";
	cin >> km;
	ml = km / 1.609;
	cout << "Миль:" << ml;
	return 0;
}