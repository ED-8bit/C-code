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
		for (size_t i = 0; i < size(); i++)
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
		for (size_t i = 0; i < size(); i++)
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
		if (i >= 0 && i < size_t(this->size()))
			return data[i];
		else
			exit(1);
	}
	void Print() 
	{
		cout << "[ ";
		for (size_t i = 0; i < size(); i++)
		{
			cout << getElem(i) << ' ';
		}
		cout << "]\n";
	}

	Set operator*(Set other) {

		Set* bigger, *smaller;
		if (this->size() >= other.size()) { bigger = this; smaller = &other; }
		else { bigger = &other; smaller = this; }

		Set result;
		for (size_t i = 0; i < smaller->size(); i++)
		{
			if (bigger->In(smaller->getElem(i)))
				result.Add(smaller->getElem(i));
		}
		return result;
	}
	Set operator+(Set other) {

		Set result;
		for (size_t i = 0; i < this->size(); i++)
		{
			result.Add(this->getElem(i));
		}
		for (size_t i = 0; i < other.size(); i++)
		{
			result.Add(other.getElem(i));
		}

		return result;
	}
	Set operator-(Set other)
	{
		Set result;
		for (size_t i = 0; i < size(); i++)
		{
			if (!other.In(getElem(i)))
				result.Add(getElem(i));
		}
		return result;
	}

};



int main()
{
	system("chcp 1251");
	int arr1[6] = { 64, 54, 100, 54, 44, 98 };
	int arr2[6] = { 135, 2456, 335, 2456, 54, 46 };
	string arr3[6] = { "баребук", "World", "чернобыль", "чернобыль", "london", "Hello"};
	string arr4[6] = { "cow","Hello", "World", "qwerty", "orel", "wasd"};
	
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
			{ // int
				Set<int> s1;
				Set<int> s2;
				for (int i : arr1) { s1.Add(i); }
				for (int i : arr2) { s2.Add(i); }
				s1.Print();
				s2.Print();
				cout << '\n';
				Set<int> s3;
				Set<int> s4;
				Set<int> s5;
				s3 = s1 * s2;
				s4 = s1 + s2;
				s5 = s1 - s2;
				s3.Print();
				s4.Print();
				s5.Print();
			}
			cout << '\n';
			{ // string
				Set<string> s1;
				Set<string> s2;
				for (string i : arr3) { s1.Add(i); }
				for (string i : arr4) { s2.Add(i); }
				s1.Print();
				s2.Print();
				cout << '\n';
				Set<string> s3;
				Set<string> s4;
				Set<string> s5;
				s3 = s1 * s2;
				s4 = s1 + s2;
				s5 = s1 - s2;
				s3.Print();
				s4.Print();
				s5.Print();
			}
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
