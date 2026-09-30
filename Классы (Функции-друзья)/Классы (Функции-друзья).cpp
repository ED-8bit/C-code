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

class Student
{
	string name;
	int grades[3];
public:
	Student(string n, int a, int b, int c): name(n){
	
	}
	~Student(){}
};




int main() {
	system("chcp 1251");
	cout << "\n";

	//Order a("лемминги", 200);
	//Warehouse A("лемминги", 300);
	//ShipOrder(a, A);





}