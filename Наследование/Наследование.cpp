#include <iostream>
#include <string>

using namespace std;

class Date {
	int day, month, year;

	bool isHighYear(int y) const {
		return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
	}
	int daysInMonth(int m, int y) const {
		if (m == 2) return isHighYear(y) ? 29 : 28;
		if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
		return 31;
	}

public:
	Date(int d = 1, int m = 1, int y = 2000) : day(d), month(m), year(y) {}

	void Print() {
		cout << day << "." << month << '.' << year;
	}

	Date& operator++() {
		day++;
		if (day > daysInMonth(month, year)) {
			day = 1;
			month++;
			if (month > 12) {
				month = 1;
				year++;
			}
		}
		return *this;
	}
	Date operator++(int) {
		Date temp = *this;
		++(*this);
		return temp;
	}
	Date& operator--() {
		day--;
		if (day < 1) {
			month--;
			if (month < 1) {
				month = 12;
				year--;
			}
			day = daysInMonth(month, year);
		}
		return *this;
	}
	Date operator--(int) {
		Date temp = *this;
		--(*this);
		return temp;
	}
	bool operator==(const Date& o) const {
		return year == o.year && month == o.month && day == o.day;
	}
	bool operator!=(const Date& o) const { return !(*this == o); }
	bool operator<(const Date& o) const {
		if (year != o.year) return year < o.year;
		if (month != o.month) return month < o.month;
		return day < o.day;
	}
	bool operator>(const Date& o) const { return o < *this; }
	bool operator<=(const Date& o) const { return !(o < *this); }
	bool operator>=(const Date& o) const { return !(*this < o); }
};
class Person
{
protected:
	string name;
	Date birthday;
	int passport;
public:
	Person(string n, Date b, int p): name(n), birthday(b), passport(p){}
	void showPerson() {
		if (name != "")
			cout << name << " | ";
		if (birthday != Date{ 1, 1, 2000 })
		{
			birthday.Print();
			cout << " | ";
		}
		if (passport)
			cout << passport;
		cout << '\n';
	}
};
class Employee : public Person
{
protected:
	string place;
	int salary;
	int experience;
public:
	Employee(string n, Date b, int p, string pl, int s, int exp): Person(n, b, p), place(pl), salary(s), experience(exp){}

	void Print() {
		cout << "Employee: \n";
		showPerson();
		if (place != "")
			cout << place << " | ";
		if (salary)
			cout << salary << " | ";
		if (experience)
			cout << experience;
		cout << '\n';
	}
};
class Student : public Person
{
protected:
	string course;
	int group;
	string prof;
public:
	Student(string n, Date b, int p, string pl, int s, string exp) : Person(n, b, p), course(pl), group(s), prof(exp) {}

	void Print() {
		cout << "Student: \n";
		showPerson();
		if (course != "")
			cout << course << " | ";
		if (group)
			cout << group << " | ";
		if (prof != "")
			cout << prof;
		cout << '\n';
	}
};
class Aspirant : public Person
{
protected:
	string boss;
	string theme;
	int year;
public:
	Aspirant(string n, Date b, int p, string pl, string s, int exp) : Person(n, b, p), boss(pl), theme(s), year(exp) {}

	void Print() {
		cout << "Aspirant: \n";
		showPerson();
		if (boss != "")
			cout << boss << " | ";
		if (theme != "")
			cout << theme << " | ";
		if (year)
			cout << year;
		cout << '\n';
	}
};

enum gender
{
	noGender,
	Male, 
	Female
};
void printGender(gender gen) {
	if (gen != noGender)
	{
		cout << "Пол: ";
		switch (gen)
		{
		case(Male):
			cout << "Мужской";
			break;
		case (Female):
			cout << "Женский";
			break;
		}
	}
}
enum coloration
{
	noColor, White, Black, Gray, Brown, Orange, Green, Red, Blue, Pink
};
void printColor(coloration color) {
	if (color != noColor)
	{
		cout << "Окрас: ";
		switch (color)
		{
		case(Black):
			cout << "Черный";
			break;
		case (White):
			cout << "Белый";
			break;
		case Gray:
			cout << "Серый";
			break;
		case Brown:
			cout << "Коричневый";
			break;
		case Green:
			cout << "Зеленый";
			break;
		case Orange:
			cout << "Оранжевый";
			break;
		case Red:
			cout << "Красный";
			break;
		case Pink:
			cout << "Розовый";
			break;
		case Blue:
			cout << "Синий";
			break;
		default:
			cout << "Неизвестный";
			break;
		}
	}
}
class Animal
{
private:
	string name;
	double weight;
	gender gen;
public:
	Animal(string n = "", double w = 0.0, gender g = noGender) : name(n), weight(w), gen(g) {}

	void setName(string NewName) {name = NewName;}
	void setWeight(double NewWeight) { weight = NewWeight; }
	void setGender(gender NewGender) { gen = NewGender; }
	string getName() { return name; }
	double getWeight() { return weight; }
	gender getGender() { return gen; }

	void Print() {
		if (name != "")
			cout << "Кличка: " << name << " | ";
		if (weight != 0.0)
			cout << "Вес: " << weight << " кг | ";
		printGender(gen);
		cout << '\n';
	}
};
class Dog: public Animal
{
private:
	string breed;
	coloration color;
	double height;
public:
	Dog(string n = "", double w = 0.0, gender g = noGender, string b = "", coloration c = noColor, double h = 0.0): Animal(n, w, g), breed(b), color(c), height(h){}

	void Print()
	{
		Animal::Print();
		if (breed != "")
			cout << "Порода: " << breed << " | ";
		printColor(color);
		cout << " | ";
		if (height != 0.0)
			cout << "Рост в холке: " << height << " см";
		cout << '\n';
	}
};
class Cat: public Animal
{
private:
	string breed;
	coloration color;
	coloration eyes_color;
public:
	Cat(string n = "", double w = 0.0, gender g = noGender, string b = "", coloration c = noColor, coloration ec = noColor): Animal(n, w, g), breed(b), color(c), eyes_color(ec){}
	void Print()
	{
		Animal::Print();
		if (breed != "")
			cout << "Порода: " << breed << " | ";
		printColor(color);
		cout << " | ";
		printColor(eyes_color);
		cout << '\n';
	}
};

class Schedule {
public:
	int day; 
	double start_time; 
	double end_time;

	Schedule(int d = 1, double s = 0.0, double e = 0.0) : day(d), start_time(s), end_time(e) {}
};
class Student3 {
protected:
	Schedule study_schedule[7];
	int study_count;
public:
	Student3() { study_count = 0; }

	void addStudy(int d, double s, double e) {
		if (study_count < 7) {
			study_schedule[study_count] = Schedule(d, s, e);
			study_count++;
		}
	}
};
class Rabota {
protected:
	Schedule work_schedule[7];
	int work_count;
public:
	Rabota() { work_count = 0; }

	void addWork(int d, double s, double e) {
		if (work_count < 7) {
			work_schedule[work_count] = Schedule(d, s, e);
			work_count++;
		}
	}
};
class WorkingStudent : public Student3, public Rabota {
public:
	WorkingStudent() {}

	double getOverlap() {
		double total_overlap = 0.0;

		// Сравниваем каждый день учебы с каждым днем работы
		for (int i = 0; i < study_count; i++) {
			for (int j = 0; j < work_count; j++) {
				// Если дни недели совпадают
				if (study_schedule[i].day == work_schedule[j].day) {

					double max_start = (study_schedule[i].start_time > work_schedule[j].start_time) ?
						study_schedule[i].start_time : work_schedule[j].start_time;

					double min_end = (study_schedule[i].end_time < work_schedule[j].end_time) ?
						study_schedule[i].end_time : work_schedule[j].end_time;

					double overlap = min_end - max_start;

					if (overlap > 0) {
						total_overlap += overlap;
					}
				}
			}
		}
		return total_overlap;
	}
};

class Shape {
protected:
	double x;
	double y;
	coloration color;

public:
	Shape(double x = 0.0, double y = 0.0, coloration c = White)
		: x(x), y(y), color(c) {
	}
};
class Circle : public Shape {
private:
	double radius;

public:
	Circle(double x, double y, coloration c, double r)
		: Shape(x, y, c), radius(r) {
	}

	void Area() {
		double area = 3.14159 * radius * radius;
		cout << "Круг | Цвет: "; printColor(color); cout << " | Координаты центра: (" << x << ", " << y << ")\n";
		cout << "Площадь круга: " << area << "\n";
	}
};
class Rectangle : public Shape {
private:
	double width;
	double height;

public:
	Rectangle(double x, double y, coloration c, double w, double h)
		: Shape(x, y, c), width(w), height(h) {
	}

	void Area() {
		double area = width * height;
		cout << "Прямоугольник | Цвет: "; printColor(color); cout << " | Координаты: (" << x << ", " << y << ")\n";
		cout << "Площадь прямоугольника: " << area << "\n";
	}
};

class List {
protected:
	int data[100];
	int count;
public:
	List() { count = 0; for (int i = 0; i < 100; i++) data[i] = 0; }

	void Add(int value) {
		if (count < 100) {
			data[count] = value;
			count++;
		}
	}
	void RemoveLast() {
		if (count > 0) {
			count--;
		}
	}
	int Get(int index) {
		if (index >= 0 && index < count) {
			return data[index];
		}
		return -1;
	}
	int Size() {
		return count;
	}
};
class Stack : private List {
public:
	//методы List не видны.
	void Push(int value) {
		List::Add(value);
	}
	int Pop() {
		if (IsEmpty()) return -1;
		int val = List::Get(List::Size() - 1);
		List::RemoveLast();
		return val;
	}
	bool IsEmpty() {
		return List::Size() == 0;
	}
	int GetStackSize() {
		return List::Size();
	}
};
class BoundedStack : public Stack {
private:
	int max_limit;
public:
	BoundedStack(int limit) : max_limit(limit) {}

	bool TryPush(int value) {
		if (GetStackSize() < max_limit) {
			Push(value);
			return true;
		}
		return false;
	}
};

class Vehicle {
protected:
	double maxSpeedKmh;
	string fuelType;
public:
	Vehicle(double speed = 0.0, string fuel = "") : maxSpeedKmh(speed), fuelType(fuel) {}

	void ShowSpecs() {
		cout << "Макс. скорость: " << maxSpeedKmh << " км/ч | Топливо: " << fuelType << '\n';
	}
};
class Car : public Vehicle {
protected:
	int numDoors;
public:
	Car(double speed = 0.0, string fuel = "", int doors = 4)
		: Vehicle(speed, fuel), numDoors(doors) {
	}

	double CalculateInsuranceRate() {
		return (maxSpeedKmh * 0.5) - (numDoors * 10) + 100;
	}
};
class SportsCar : public Car {
protected:
	double turboBoostKmh;
public:
	SportsCar(double speed = 0.0, string fuel = "", int doors = 2, double turbo = 0.0)
		: Car(speed, fuel, doors), turboBoostKmh(turbo) {
	}
	double EffectiveTopSpeed() {
		return maxSpeedKmh + turboBoostKmh;
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
			Employee a("Артур", { 20, 10, 2007 }, 1023203223, "Rainbow six siege operator", 1230000, 5);
			Student b("Арсен", { 25, 9, 2007 }, 1230325232, "IT TOP", 252, "programmer");
			Aspirant c("Давид", { 28, 10, 2005 }, 1023790322, "A. A. Tsybulnikov", "Tetris", 2026);

			a.Print();
			cout << '\n';
			b.Print();
			cout << '\n';
			c.Print();
			cout << '\n';
			break;
		}
		case 2:
		{
			Dog gaw("Benedict", 15.0, Male, "Мопс", Gray, 45.5);
			Cat myau("Magamed", 10.4, Male, "Британский Мышелов", Black, Green);

			gaw.Print();
			myau.Print();
			break;
		}
		case 3:
		{
			WorkingStudent ws;
			ws.addStudy(2, 8.3, 16.10);
			ws.addStudy(3, 8.3, 14.4);
			ws.addStudy(4, 8.3, 13.1);
			ws.addStudy(5, 8.3, 13.1);

			ws.addWork(1, 8.0, 20.0);
			ws.addWork(2, .0, 22.0);
			ws.addWork(3, 12.0, 22.0);

			// Учеба:              | Работа:
			// ПН ---------------- | ПН с 12:00 до 20:00
			// ВТ с 08:30 до 16:10 | ВТ с 08:00 до 22:00
			// СР с 08:30 до 14:40 | СР с 12:00 до 22:00
			// ЧТ c 08:30 до 13:10 | ЧТ ----------------
			// ПТ с 08:30 до 13:10 | ПТ ----------------
			cout << "Суммарное количество часов пересечения в неделю: " << ws.getOverlap() << " ч.\n";
			break;
		}
		case 4:
		{
			Circle c(5.0, -3.5, Black, 4.0);
			Rectangle r(10.0, 10.0, Red, 5.0, 8.0);

			c.Area();
			cout << '\n';
			r.Area();
			break;
		}
		case 5:
		{
			BoundedStack bs(3);
			cout << "10 " << (bs.TryPush(10) ? "Успешно" : "Лимит превышен") << '\n';
			cout << "20 " << (bs.TryPush(20) ? "Успешно" : "Лимит превышен") << '\n';
			cout << "30 " << (bs.TryPush(30) ? "Успешно" : "Лимит превышен") << '\n';
			cout << "40 " << (bs.TryPush(40) ? "Успешно" : "Лимит превышен") << '\n';
			cout << "\n\n";
			while (!bs.IsEmpty()) {
				cout << bs.Pop() << " ";
			}
			cout << '\n';

			// Нет доступа к методам листа
			// bs.Add(50);
			// bs.Get(0);
			break;
		}
		case 6:
		{
			Car standardCar(180.0, "Бензин", 4);
			SportsCar fastCar(280.0, "Бензин", 2, 50.0);

			cout << "Обычный автомобиль: \n";
			standardCar.ShowSpecs();
			cout << "Коэффициент риска: " << standardCar.CalculateInsuranceRate() << "\n\n";

			cout << "Спортивный автомобиль: \n";
			fastCar.ShowSpecs();
			cout << "Коэффициент риска: " << fastCar.CalculateInsuranceRate() << '\n';
			cout << "Макс. скорость с турбонаддувом: " << fastCar.EffectiveTopSpeed() << " км/ч\n";
			break;
		}
		case 0:
			return 0;
		}
		cout << "\n";
		system("pause");
	}
}