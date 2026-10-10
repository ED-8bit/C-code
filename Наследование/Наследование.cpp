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



int main() {
	system("chcp 1251");
	system("cls");

	int number;
	cout << "Введите номер задания: ";
	cin >> number;
	system("cls");
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


		break;
	}

	default:
		return 0;
	}
	return 0;
}