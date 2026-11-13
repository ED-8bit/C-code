#include <iostream>
#include <vector>
using namespace std;

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
//
//template<class Type1, class Type2>
//class MyClass
//{
//	Type1 i;
//	Type2 j;
//public:
//	MyClass(Type1 a, Type2 b) { i = a, j = b; }
//	~MyClass(){}
//
//	void show() { cout << i << ' ' << j << '\n'; }
//};
//
//template<class AType, int size>
//class arr 
//{
//private:
//	AType a[size];
//public:
//	arr() { for (int i = 0; i < size; i++) { a[i] = 0; } }
//	AType &operator[](int i);
//};
//
//template<class AType, int size>
//AType &arr<AType, size>::operator[](int i) 
//{
//	if (i < 0 || i >= size)
//	{
//		cout << "Значение индекса " << i << " за пределами границ массива.\n";
//		exit(1);
//	}
//	return a[i];
//}

template<class T>
class Set
{
	vector<T> data;
public:
	Set(){}
	~Set(){}
	size_t size() { return data.size(); }
	void Add(T elem) {
		if (!In(elem))
		data.push_back(elem);
	}
	bool Del(T elem) {
		for (int i = 0; i < *this->size(); i++)
		{
			if (data[i] == elem)
			{
				data.erase(data.begin() + i);
				return true;
			}
		}
		return false;
	}
	bool In(T elem) {
		for (int i = 0; i < *this->size(); i++)
		{
			if (data[i] == elem)
			{
				return true;
			}
		}
		return false;
	}
	T getElem(size_t i) 
	{ 
		if (i >= 0 && i < *this->size())
			return data[i];
		else
			exit(1);
	}

	Set operator*(Set other) {

		Set* bigger, smaller;
		if (*this->size() >= other.size()) { bigger = this; smaller = &other; }
		else { bigger = &other; smaller = this; }

		Set result;
		int i;
		for (i = 0; i < smaller->size(); i++)
		{
			if (*smaller.In(bigger->getElem(i)))
				result.Add(bigger->getElem(i));
		}
		for (i; bigger->size(); i++)
		{
			result.Add(bigger->getElem(i));
		}

		return result;
	}
	Set operator+(Set other) {
		Set* bigger, smaller;
		if (*this->size() >= other.size()) { bigger = this; smaller = &other; }
		else { bigger = &other; smaller = this; }

		Set result;
		int i;
		for (i = 0; i < smaller->size(); i++)
		{
			if (*smaller.In(bigger->getElem(i)))
				result.Add(bigger->getElem(i));
		}
		for (i; bigger->size(); i++)
		{
			result.Add(bigger->getElem(i));
		}

		return result;
	}
};






int main()
{
	system("chcp 1251");
	int arr1[3] = { 64, 54, 100 };
	double arr2[3] = { 5.3, 2.5, 4.9 };
	long int arr3[3] = { 14135, 2456, 34535 };
	const char* arr4[3] = { "cout << ","Hello ", "World" };
	char arr5[3] = { 'b', 'a', 'c' };
	bool arr7[3] = { true, false, true };
	string arr8[3] = { "баребук", "купец", "чернобыль" };

	int number = 1;
	while (number > 0 && number <= 6)
	{
		system("cls");
		cout << "Выберите номер задания: ";
		cin >> number;
		cout << "\n";
		switch (number)
		{
		case 1:
		{
			
			break;
		}
		case 2:
		{
			
			break;
		}
		case 3:
		{
			
			break;
		}
		case 4:
		{
			
			break;
		}
		case 5:
		{
			
			break;
		}
		case 0:
			return 0;
		}
		cout << "\n";
		system("pause");
	}
}
