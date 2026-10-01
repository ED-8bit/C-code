#include <iostream>
#include <string>

using namespace std;
class Order;
class Warehouse
{
	string name;
	int count;
public:
	Warehouse(string n = "", int c = 0) : name(n), count(c) {}
	~Warehouse(){}
	friend bool CanFullFill(Order o, Warehouse w);
	friend void ShipOrder(Order o, Warehouse& w);
};
class Order
{
	string name;
	int count;
public:
	Order(string n = "", int c = 0) : name(n), count(c) {}
	~Order(){}
	friend bool CanFullFill(Order o, Warehouse w);
	friend void ShipOrder(Order o, Warehouse& w);
};
bool CanFullFill(Order o, Warehouse w) {
	if (o.name == w.name)
	{
		if (o.count <= w.count)
			return true;
		else
			return false;
	}
	else
		return false;
}
void ShipOrder(Order o, Warehouse& w) {
	if (CanFullFill(o, w))
	{
		w.count -= o.count;
		cout << "Выполнен заказ: " << o.name << " " << o.count << " шт.\n";
	}
	else
		cout << "Заказ не может быть выполнен\n";
		
}
class Classroom;
class Student
{
	string name;
	int grades[3];
public:
	Student(string n = "", int a = 0, int b = 0, int c = 0) : name(n) {
		grades[0] = a;
		grades[1] = b;
		grades[2] = c;
	}
	~Student(){}
	friend void AddStudent(Classroom& c, Student s);
	friend double AverageGrade(Classroom& c, int p);
	friend Student& BestStudent(Classroom& c);

	string getName() { return name; }
};
class Classroom
{
	Student data[10];
	int count = 0;
public:
	Classroom(){}
	Classroom(Student d[], int n) {
		for (int i = 0; i < n && i < 10; i++)
			data[count++] = d[i];
	}
	~Classroom(){}
	friend void AddStudent(Classroom& c, Student s);
	friend double AverageGrade(Classroom& c, int p);
	friend Student& BestStudent(Classroom& c);
		
};
void AddStudent(Classroom& c, Student s) {
	if (c.count < 10)
	{
		c.data[c.count++] = s;
		cout << "Добавлен студент " << s.name << "\n";
	}
	else
		cout << "Список переполнен\n";
}
double AverageGrade(Classroom& c, int p) {
	if (p >= 0 && p < 3 && c.count > 0)
	{
		double avg = 0;
		for (int i = 0; i < c.count; i++)
		{
			avg += c.data[i].grades[p];
		}
		return avg / c.count;
	}
	return 0.0;
	

}
Student& BestStudent(Classroom& c) {
	double maxAVG = 0;
	Student *best = &c.data[0];
	for (int j = 0; j < 3; j++)
		maxAVG += c.data[0].grades[j];
	maxAVG /= 3.0;

	for (int i = 0; i < c.count; i++)
	{
		double avg = 0;
		for (int j = 0; j < 3; j++)
		{
			avg += c.data[i].grades[j];
		}
		avg /= 3.0;
		if (avg > maxAVG)
		{
			maxAVG = avg;
			best = &c.data[i];
		}
	}
	return *best;
}

class Truck {
	string num;
	string model;
	double km;
public:
	Truck(string n = "", string m = "", double k = 0) : num(n), model(m), km(k) {}
	friend Truck& MaxKM(Truck* arr[], int size);

	void printInfo() {
		if (num != "")
			cout << num << " ";
		if (model != "")
			cout << model << " ";
		if (km)
			cout << km << " ";
		cout << '\n';
	}
};
Truck& MaxKM(Truck* arr[], int size) {
	Truck** p = arr;
	Truck* max = *p;
	for (int i = 0; i < size; i++, p++)
	{
		if (max->km < (*p)->km)
		{
			max = *p;
		}
	}
	return *max;
}

class Product
{
	string name;
	double price;
public:
	Product(string n, double p): name(n), price(p) {}
	~Product(){}

	void setName(string name) { name = name; }
};

int main() {
	system("chcp 1251");
	cout << "\n";

	//Order a("лемминги", 200);
	//Order b("гномы", 13);
	//Warehouse A("лемминги", 300);
	//ShipOrder(b, A);
	//ShipOrder(a, A);

	//Student init[] = {
	//	Student{"Аня",   3, 4, 5},
	//	Student{"Боря",  5, 5, 5},
	//	Student{"Трамп", 3, 5, 2}
	//};
	//Classroom A2(init, 3);
	//AddStudent(A2, Student{ "Вася", 5, 5, 4 });
	//cout << "Лучший Студент: " << BestStudent(A2).getName() << "\n";
	//cout << "Средний балл: " << AverageGrade(A2, 0) << "\n";

	//Truck arr[5](
	//	{ "E147BH", "Mercedes Actros", 1200.0 },
	//	{ "A034KK", "Volvo E350", 75000.0 },
	//	{ "X059EP", "Mercedes Actros", 270000.0 },
	//	{ "O001OO", "Renault 'noname'", 810000.0 },
	//	{ "H537KM", "Volvo E450", 100000.1 }
	//	);
	//Truck* ptrs[5] = { &arr[0], &arr[1], &arr[2], &arr[3], &arr[4] };
	//MaxKM(ptrs, 5).printInfo();



}