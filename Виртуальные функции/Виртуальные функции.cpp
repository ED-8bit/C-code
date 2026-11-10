#include <iostream>
#include <string>
#include <cmath>
using namespace std;
int PauseTime = 1000; // ms
const double PI = 3.14159265358979323846;

class TransportVehicle
{
protected:
	string model;          // модель
	double averageSpeed;   // средняя скорость, км/ч
	int passengers;        // количество пассажиров

public:
	TransportVehicle(const string& model, double averageSpeed, int passengers)
		: model(model), averageSpeed(averageSpeed), passengers(passengers) {
	}

	virtual ~TransportVehicle() {}

	virtual double FuelConsumption(double distance) = 0;
	double TravelTime(double distance)
	{
		return distance / averageSpeed;
	}
	virtual void Print()
	{
		cout << "Транспорт: " << model << " | Средняя скорость: " << averageSpeed << " | Количество пассажиров: " << passengers << '\n';
	}
};
class Bicycle : public TransportVehicle
{
public:
	Bicycle(const string& model, double averageSpeed, int passengers)
		: TransportVehicle(model, averageSpeed, passengers) {
	}
	double FuelConsumption(double distance) override
	{
		return 0.0;
	}
	void Print() override
	{
		cout << "Велосипед: " << model << " | Средняя скорость: " << averageSpeed << " км/ч | Количество пассажиров: " << passengers << '\n';
	}
};
class Car : public TransportVehicle
{
protected:
	double fuelPer100km;   
public:
	Car(const string& model, double averageSpeed, int passengers, double fuelPer100km)
		: TransportVehicle(model, averageSpeed, passengers), fuelPer100km(fuelPer100km) {
	}
	double FuelConsumption(double distance) override
	{
		return distance / 100 * fuelPer100km;
	}
	void Print() override
	{
		cout << "Автомобиль: " << model << " | Средняя скорость: " << averageSpeed << " км/ч | Количество пассажиров: " << passengers 
			<< " | Расход топлива: " << fuelPer100km << " л/100км \n";
	}
};
class Truck : public Car
{
protected:
	double loadCapacity;
public:
	Truck(const string& model, double averageSpeed, int passengers,
		double fuelPer100km, double loadCapacity)
		: Car(model, averageSpeed, passengers, fuelPer100km),
		loadCapacity(loadCapacity) {
	}
	double FuelConsumption(double distance) override
	{
		return distance / 100 * fuelPer100km;
	}
	void Print() override
	{
		cout << "Грузовик: " << model << " | Средняя скорость: " << averageSpeed << " км/ч | Количество пассажиров: " << passengers 
			<< " | Расход топлива: " << fuelPer100km << " л/100км | Объем груза: " << loadCapacity << " кг \n";
	}
};


class Solid
{
public:
	virtual ~Solid() {}

	virtual double Volume() = 0;
	virtual double SurfaceArea() = 0;
	virtual void Print()
	{
		cout << "Объем: " << Volume() << " | Площадь: " << SurfaceArea() << '\n';
	}
};
class Cube : public Solid
{
protected:
	double a;   

public:
	Cube(double a) : a(a) {}

	double Volume() override
	{
		return pow(a, 3);
	}
	double SurfaceArea() override
	{
		return 6*pow(a, 2);
	}
};
class Cylinder : public Solid
{
protected:
	double r;   
	double h;   

public:
	Cylinder(double r, double h) : r(r), h(h) {}

	double Volume() override
	{
		return PI*pow(r, 2)*h;
	}
	double SurfaceArea() override
	{
		return 2*(PI*pow(r, 2)+PI*r*h);
	}
};
class Tetrahedron : public Solid
{
protected:
	double a;   

public:
	Tetrahedron(double a) : a(a) {}

	double Volume() override
	{
		return pow(a, 3) / (6*sqrt(2.0));
	}
	double SurfaceArea() override
	{
		return sqrt(3.0)*pow(a,2);
	}
};

class Account
{
protected:
	string accountNumber;   
	double balance;         

public:
	Account(const string& accountNumber, double balance)
		: accountNumber(accountNumber), balance(balance) {
	}
	virtual ~Account() {}

	virtual bool Withdraw(double amount)
	{
		if (amount <= balance)
		{
			balance -= amount;
			return true;
		}
		return false;
	}
	virtual void Deposit(double amount)
	{
		balance += amount;
		cout << "Пополнение: " << amount << " руб. \n";
		cout << "Баланс: " << balance << '\n';
	}

	double GetBalance() const { return balance; }
	string GetNumber() const { return accountNumber; }
};
class DepositAccount : public Account
{
protected:
	double interestRate;   

public:
	DepositAccount(const string& accountNumber, double balance, double interestRate)
		: Account(accountNumber, balance), interestRate(interestRate) {
	}
	bool Withdraw(double amount) override
	{
		double penalty = (amount / 100) * 5;
		if (Account::Withdraw(penalty))
		{
			balance -= penalty;
			cout << "Снятие: " << amount << " руб. Получен штраф (5% от суммы снятия): " << penalty << '\n';
			cout << "Баланс: " << balance << '\n';
			return true;
		}
		return false;
	}
};
class CurrentAccount : public Account
{
protected:
	double commission;   

public:
	CurrentAccount(const string& accountNumber, double balance, double commission)
		: Account(accountNumber, balance), commission(commission) {
	}
	bool Withdraw(double amount) override
	{
		double amount_with_commission = (amount + commission);
		if (Account::Withdraw(amount_with_commission))
			return true;
		return false;
	}
	void Deposit(double amount) override
	{
		if (amount > 2 * commission)
			Account::Deposit(amount - commission);
		else
			cout << "Минимальная сумма пополнения: " << (1 + 2 * commission);
	}
};

class Employee
{
protected:
	string name; 
public:
	Employee(const string& name) : name(name) {}
	virtual ~Employee() {}
	virtual double CalculateSalary() = 0;
};
class Manager : public Employee
{
protected:
	double salary;   
	double bonus;   
public:
	Manager(const string& name, double salary, double bonus)
		: Employee(name), salary(salary), bonus(bonus) {
	}
	double CalculateSalary() override
	{
		return salary+bonus;
	}
};
class Worker : public Employee
{
protected:
	double hourlyRate;   
	double hours;        
public:
	Worker(const string& name, double hourlyRate, double hours)
		: Employee(name), hourlyRate(hourlyRate), hours(hours) {
	}
	double CalculateSalary() override
	{
		return hourlyRate*hours;
	}
};

class Media
{
protected:
	string title;       
	int durationSec;   
public:
	Media(const string& title, int durationSec)
		: title(title), durationSec(durationSec) {
	}
	virtual ~Media() {}
	virtual void Play() = 0;
	void PrintInfo()
	{
		cout << title << ", " << durationSec << " сек \n";
	}
};
class AudioTrack : public Media
{
protected:
	string artist;   

public:
	AudioTrack(const string& title, int durationSec, const string& artist)
		: Media(title, durationSec), artist(artist) {
	}
	void Play() override
	{
		cout << "Играет трек исполнителя " << artist << " | "; PrintInfo();
	}
};
class VideoClip : public Media
{
protected:
	string resolution;   
public:
	VideoClip(const string& title, int durationSec, const string& resolution)
		: Media(title, durationSec), resolution(resolution) {
	}
	void Play() override
	{
		cout << "Воспроизводится " << resolution << " видео "; PrintInfo();
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
			unique_ptr<TransportVehicle> vehicles[3] = 
			{	
				make_unique<Bicycle>("BMX", 12, 0), 
				make_unique<Car>("Li Xiang Li 9", 60, 5, 8), 
				make_unique<Truck>("Mercedes Actros", 85, 1, 30, 25000) 
			};
			for (int i = 0; i < 3; i++)
			{
				vehicles[i]->Print(); cout << '\n';
			}
			break;
		}
		case 2:
		{
			unique_ptr<Solid> figures[3] =
			{
				make_unique<Cube>(2.5),
				make_unique <Cylinder>(4, 10),
				make_unique<Tetrahedron>(4.0),
			};
			for (int i = 0; i < 3; i++)
			{
				cout << typeid(*figures[i]).name() << " "; figures[i]->Print(); cout << '\n';
			}
			break;
		}
		case 3:
		{
			unique_ptr<Account> accounts[3] = 
			{
				make_unique<Account>("Sber", 4860.50),
				make_unique<DepositAccount>("Yandex Bank", 15000.87, 25.5),
				make_unique<CurrentAccount>("Tbank", 5000.23, 49.99)
			};
			for (int i = 0; i < 3; i++) 
			{
				cout << typeid(*accounts[i]).name() << "\n"; accounts[i]->Withdraw(2500); accounts[i]->Deposit(5000); cout << '\n';
			}
			break;
		}
		case 4:
		{
			unique_ptr<Employee> Employers[2] =
			{
				make_unique<Manager>("ioi-43532", 200.01, 25000.5),
				make_unique<Worker>("ioi-23124", 195.00, 180)
			};
			for (int i = 0; i < 2; i++)
			{
				cout << typeid(*Employers[i]).name() << "\n"; cout << Employers[i]->CalculateSalary(); cout << '\n';
			}
			break;
		}
		case 5:
		{
			unique_ptr<Media> content[2] = 
			{
				make_unique<AudioTrack>("Going for Greatness", 189, "Future Royalty"),
				make_unique<VideoClip>("GANGNAM STYLE", 252, "1920x1080")
			};
			for (int i = 0; i < 2; i++)
			{
				content[i]->Play();
			}
			break;
		}
		case 0:
			return 0;
		}
		cout << "\n";
		system("pause");
	}
}