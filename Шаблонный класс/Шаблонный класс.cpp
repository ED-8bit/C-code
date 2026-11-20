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

class InvalidIndex : public exception {
public:
	const char* what() const noexcept override {
		return "Индекс выходит за пределы объекта\n";
	}
};

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
		if (i >= 0 && i < size())
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
	T& operator[](size_t id) {
		try {
			if (id >= 0 && id < size())
				return data[id];
			else
				throw id;
		}
		catch (size_t i) {
			cout << "Индекс " << int(i) << " выходит за пределы множества. Возврат последнего элемента.\n";
			return data[size() - 1];
		}
		
	}
};


template<class T1>
class List
{
	struct Node {
		T1 elem;
		Node* next;
		Node(T1 e, Node* n = nullptr) : elem(e), next(n) {}
	};

	Node* root;
	Node** last;
public:
	List(): root(nullptr), last(&root) {}
	~List() 
	{
		if (!IsEmpty())
		{
			Node* CurNode = root;
			Node* NextNode;
			while (CurNode != nullptr)
			{
				NextNode = CurNode->next;
				delete CurNode;
				CurNode = NextNode;
			};
		}
	}
	bool IsEmpty() {
		return root == nullptr;
	}
	void AddFront(T1 value)
	{
		Node* NewRoot = new Node(value, root);
		root = NewRoot;
		if (last == &root)
			last = &NewRoot->next;
	}
	void AddBack(T1 value)
	{
		Node* NewLast = new Node(value);
		*last = NewLast;
		last = &NewLast->next;
	}
	void Remove(T1 value)
	{
		Node* back = nullptr, *cur = root, *forward = nullptr;
		while (cur != nullptr)
		{
			forward = cur->next;
			if (cur->elem == value)
			{
				if (back != nullptr && forward != nullptr)
					back->next = forward;
				else if (back == nullptr && forward != nullptr)
					root = forward;
				else if (back != nullptr && forward == nullptr)
					back->next = nullptr;
				delete cur;
				break;
			}

			back = cur;
			cur = forward;
			
		}
	}
	void Print()
	{
		if (!IsEmpty())
		{
			Node* CurNode = root;
			Node* NextNode;
			while (CurNode != nullptr)
			{
				NextNode = CurNode->next;
				cout << CurNode->elem << ' ';
				CurNode = NextNode;
			};
			cout << '\n';
		}
	}
};

template<class T>
class Result
{
	T Value{};
	bool Success;
	string Error;

	Result(): Success(false) {}
public: 
	Result(T val): Value(val), Success(true), Error("") {}
	Result(string err) : Success(false), Error(err) {}
	~Result(){}
	bool IsOk() const
	{
		return Success;
	}
	const T* GetValue() const
	{
		if(IsOk())
			return &Value;
		return nullptr;
	}
	const string* GetError() const
	{
		return &Error;
	}

	friend ostream& operator<<(ostream& os, const Result<T>& p) {
		if (p.IsOk())
		{
			os << *p.GetValue() << '\n';
		}
		else
			os << *p.GetError() << '\n';
		return os;
	}
};

template<class T>
Result<T> SafeDivide(T a, T b)
{
	if (b == 0)
		return Result<T>("Деление на ноль");
	return Result<T>(a / b);
}


class Product
{
	string name;
	double price;
	int count;
public:
	Product(): name("product"), price(0.0), count(0) {}
	Product(string n, double p, int c = 0): name(n), price(p), count(c){}
	~Product(){}

	friend ostream& operator<<(ostream& os, const Product& p) {
		os << p.name << " - " << p.price << " руб. (На складе: "
			<< p.count << " шт.)";
		return os;
	}

};

template<class T, int capacity>
class Inventory
{
	string name;
	T items[capacity];
	size_t count;
public:
	Inventory(string n): name(n), count(0){}
	~Inventory(){}

	bool AddItem(T item)
	{
		if (count < capacity)
		{
			items[count++] = item;
			return true;
		}
		else 
			return false;
	}
	bool RemoveItem(size_t id)
	{
		if (id <= count - 1)
		{
			for (size_t i = id; i < capacity - 1; i++)
			{
				items[i] = items[i + 1];
			}
			count--;
			return true;
		}
		else
			return false;
	}
	bool IsFull()
	{
		return count == capacity - 1;
	}
	size_t TotalCount()
	{
		return count;
	}
	void PrintAll()
	{
		cout << "Склад: "<< name << '\n';
		for (size_t i = 0; i < count; i++)
		{
			cout <<"[ " << items[i] << " ]\n";
		}
	}
};


template<class T>
class Statistics
{
	T min;
	T max;
	T sum;
	int count;
public:
	Statistics():min(0), max(0), sum(0), count(0){}
	~Statistics(){}
	void AddValue(T value)
	{
		if (value > max || count == 0)
		{
			max = value;
		}
		if (value < min || count == 0)
		{
			min = value;
		}
		count++;
		sum += value;
	}
	T GetMin() {
		return min;
	}
	T GetMax() {
		return max;
	}
	double GetAverage()
	{
		return sum / double(count);
	}
	void PrintStats()
	{
		cout << "Статистика \n";
		cout << "Минимум: " << min << '\n';
		cout << "Максимум: " << max << '\n';
		cout << "Сумма: " << sum << '\n';
		cout << "Количество: " << count << '\n';
		
	}
};




int main()
{
	system("chcp 1251");
	int arr1[6] = { 64, 54, 100, 54, 44, 98 };
	int arr2[6] = { 135, 2456, 335, 2456, 54, 46 };
	string arr3[6] = { "баребук", "World", "чернобыль", "чернобыль", "london", "Hello"};
	string arr4[6] = { "cow","Hello", "World", "qwerty123", "orel1234", "wasd"};
	Product GPUs[6] = { {"RTX 5060", 40000.0, 1000}, {"RTX 5060 TI", 60000.0, 420}, {"RTX 5070", 110000.0, 100},
		{"RTX 5070 TI", 140000.0, 23}, {"RTX 5080", 300000.0, 10}, {"RTX 5090", 879000.99, 5} };
	
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
			List<int> l1;
			List<string> l2;
			for (int i : arr1)
			{
				l1.AddFront(i);
			}
			l1.Print();
			break;
		}
		case 3:
		{
			Result<int> r1 = SafeDivide(18, 6);
			Result<double> r2 = SafeDivide(14.3, 0.0);
			cout << r1;
			cout << r2;
			break;
		}
		case 4:
		{
			Inventory<Product, 6> DNS("DNS");
			for (Product videocard : GPUs)
			{
				DNS.AddItem(videocard);
			}
			DNS.PrintAll();
			cout << '\n';
			Inventory<string, 6> strokes("Строки");
			for (string stroke : arr3)
			{
				strokes.AddItem(stroke);
			}
			strokes.PrintAll();
			break;
		}
		case 5:
		{
			Statistics<double> temp;
			temp.AddValue(17.5);
			temp.AddValue(17.4);
			temp.AddValue(16.2);
			temp.AddValue(14.9);
			temp.AddValue(12.8);
			temp.AddValue(15.11);
			temp.AddValue(12.4);
			temp.PrintStats();
			cout << "Среднее: " << temp.GetAverage() << '\n';
			cout << '\n';
			Statistics<int> res;
			res.AddValue(4);
			res.AddValue(1);
			res.AddValue(6);
			res.AddValue(2);
			res.AddValue(7);
			res.PrintStats();
			cout << "Среднее: " << res.GetAverage() << '\n';
			break;
		}
		case 0:
			return 0;
		}
		cout << "\n";
		system("pause");
	}
}
