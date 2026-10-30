#include <iostream>
#include <Windows.h>
int timing = 1000;
using namespace std;

class Printer
{
protected:
	string ID;
public:
	
	Printer(string i): ID(i){}
	~Printer(){}

	void Print(string document) {
		cout << "Печать " << document << "\n";
	}
};
class Scanner
{
protected:
	int dpi;
public:
	Scanner(int d): dpi(d){}
	~Scanner(){}
	void Scan() {
		cout << "Сканирование с разрешением " << dpi << '\n';
	}
};
class MFP: public Printer, public Scanner
{
	string model;
public:
	MFP(string m, string i, int d): model(m), Printer(i), Scanner(d){}
	~MFP(){}
	void Copy() {
		cout << "Устройство " << model << '\n';
		cout << "Копирование " << ID << "...\n";
		Sleep(timing/3);
		Scan();
		Sleep(timing/2);
		Print(ID);
	}
};

class A {
public:
	A() { cout << "Создание A.\n"; }
	~A() { cout << "Разрушение A.\n"; }
};
class B {
public:
	B() { cout << "Создание B.\n"; }
	~B() { cout << "Разрушение B.\n"; }
};
class C : public A, public B {
public:
	C() { cout << "Создание C.\n"; }
	~C() { cout << "Разрушение C.\n"; }
};
class D : public C {
public:
	D() { cout << "Создание D.\n"; }
	~D() { cout << "Разрушение D.\n"; }
};

class Vehicle
{
	string num;
	double MaxSpeed;
public:
	Vehicle(string n, double MS): num(n), MaxSpeed(MS){}
    ~Vehicle(){}
	void ShowVehicleInfo() {
		cout << 
			"Регистрационный номер: " << num << '\n' <<
			"Максимальная скорость: " << MaxSpeed << '\n';
	}
};

class Car: virtual public Vehicle
{
	int WheelsCount;
public:
	Car(string n, double MS, int WC): Vehicle(n, MS), WheelsCount(WC){}
	~Car(){}
	int getWC() { return WheelsCount; }
};

class Boat : virtual public Vehicle
{
	double BodyLength;
public:
	Boat(string n, double MS, double BL) : Vehicle(n, MS), BodyLength(BL) {}
	~Boat() {}
	double getBL() { return BodyLength; }
};

class AmphibiousVehicle : public Car, public Boat
{

public:
	AmphibiousVehicle(string n, double MS, double BL, int WC): Vehicle(n, MS), Car(n, MS, WC), Boat(n, MS, BL){}
	~AmphibiousVehicle(){}

	void Describe() {
		ShowVehicleInfo();
		cout << "Длина корпуса: " << getBL() << '\n';
		cout << "Количество колес: " << getWC() << '\n';
	}
};


int main()
{
	system("chcp 1251");
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
			MFP d("Canon TS13503", "ref.docx", 1080);
			d.Copy();
			break;
		}
		case 2:
		{
			D obj;
			//Вызываются Конструкторы A->B->C->D, а затем Деструкторы D->C->B->A (D наследник C, который наследник в первую очередь A, во вторую B)
			break;
		}
		case 3:
		{
			MFP d("Canon TS13503", "ref.docx", 1080);
			d.Copy();
			break;
		}
		case 4:
		{
			AmphibiousVehicle t("123rus", 99.9, 12.4, 8);
			t.Describe();
			break;
		}
		case 0:
			return 0;
		}
		cout << "\n";
		system("pause");
	}
}
