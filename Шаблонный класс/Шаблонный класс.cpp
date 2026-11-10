#include <iostream>
using namespace std;
const int SIZE = 100;

//template <class QType>
//class queue
//{
//private:
//	QType data[SIZE];
//	int sloc;
//	int rloc;
//public:
//	queque() { sloc = 0; rloc = 0; }
//	~queue(){}
//	QType qget();
//	void qput(QType put);
//};
//
//template<class QType>
//QType queue<QType>::qget()
//{
//	if (rloc == sloc)
//	{
//		cout << "Очередь пуста.\n";
//		return 0;
//	}
//	return data[rloc++];
//}
//template<class QType>
//void queue<QType>::qput(QType put)
//{
//	if (sloc == SIZE)
//	{
//		cout << "Очередь заполнена.\n";
//		return;
//	}
//	data[sloc] = put;
//	sloc++;
//}


template<class Type1, class Type2>
class MyClass
{
	Type1 i;
	Type2 j;
public:
	MyClass(Type1 a, Type2 b) { i = a, j = b; }
	~MyClass(){}

	void show() { cout << i << ' ' << j << '\n'; }
};

template<class AType, int size>
class arr 
{
private:
	AType a[size];
public:
	arr() { for (int i = 0; i < size; i++) { a[i] = 0; } }
	AType &operator[](int i);
};

template<class AType, int size>
AType &arr<AType, size>::operator[](int i) 
{
	if (i < 0 || i >= size)
	{
		cout << "Значение индекса " << i << " за пределами границ массива.\n";
		exit(1);
	}
	return a[i];
}


int main() {
	system("chcp 1251");
	//queue<int> d;
	//d.qput(55);
	//d.qput(23);
	//d.qput(89);
	//d.qput(1);
	//cout << d.qget() << '\n';
	//cout << d.qget() << '\n';
	//cout << d.qget() << '\n';
	//cout << d.qget() << '\n';

	//queue<double> a;
	//a.qput(3.7);
	//a.qput(7.98);
	//a.qput(89.23);
	//a.qput(3.14);
	//cout << a.qget() << '\n';
	//cout << a.qget() << '\n';
	//cout << a.qget() << '\n';
	//cout << a.qget() << '\n';

	MyClass<int, double> ob1(10, 0.23);
	MyClass<char, const char*> ob2('X', " Это тест.");
	ob1.show();
	ob2.show();

	arr<int, 10> a;
	for (int i = 0; i < 10; i++)
		a[i] = i;
	arr<double, 5> b;
	for (int i = 0; i < 5; i++)
		b[i] = i / 3.0;

	cout << "Массив int значений: ";
	for (int i = 0; i < 10; i++)
	{
		cout << a[i] << ' ';
	}
	cout << '\n';

	cout << "Массив double значений: ";
	for (int i = 0; i < 5; i++)
	{
		cout << b[i] << ' ';
	}
	cout << '\n';


	return 0;


}