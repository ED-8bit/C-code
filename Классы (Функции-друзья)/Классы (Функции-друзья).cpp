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





class Truck
{
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
	Truck* p = arr[0];
	Truck* max = arr[0];
	for (int i = 0; i < size; i++)
	{
		if (max->km < p->km)
		{
			max = p;
		}
		p++;
	}
	return *max;
}

int main() {
	system("chcp 1251");
	cout << "\n";

	//Order a("лемминги", 200);
	//Order b("гномы", 13);
	//Warehouse A("лемминги", 300);
	//ShipOrder(b, A);
	//ShipOrder(a, A);

	Truck arr[5](
		{ "E147BH", "Mercedes Actros", 1200.0 },
		{ "A034KK", "Volvo E350", 75000.0 },
		{ "X059EP", "Mercedes Actros", 270000.0 },
		{ "O001OO", "Renault 'noname'", 810000.0 },
		{ "H537KM", "Volvo E450", 1000000.1 }
		);
	MaxKM(arr, 5).printInfo();
}