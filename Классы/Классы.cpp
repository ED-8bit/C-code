#include <iostream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

enum inum_type
{
	s, t
};
class inum
{
private:
	double real;
	double im;
	double r;
	double phi;
public:
	inum(double a = 0, double b = 0) : real(a), im(b) 
	{
		r = sqrt(real * real + im * im);
		phi = atan(im / real);
		if (im / real > 0 && im < 0)
			phi += 3.14;
		if (im / real < 0 && im > 0)
			phi += 3.14;
	}

	double getRE() const { return real; }
	double getIM() const { return im; }
	void setRE(double NewREAL) { real = NewREAL; }
	void setIM(double NewIM) { im = NewIM; }

	void print_inum(inum_type a = s)
	{
		if (a == s)
		{
			cout << real;
			if (im > 0)
				cout << "+" << im << "i\n";
			else if (im < 0)
				cout << im << "i\n";
		}
		else if (a == t)
		{
			cout << r << "cos(" << phi << ")+i*sin(" << phi << ")\n";
		}
	}
	inum add(inum D)
	{
		return { real + D.real, im + D.im };
	}
	inum sub(inum D)
	{
		return { real - D.real, im - D.im };
	}
	inum mult(inum D)
	{
		return { real * D.real - im * D.im, real * D.im + D.real * im };
	}
	inum div(inum D)
	{
		return { (real * D.real + im * D.im) / (D.real * D.real + D.im * D.im),(im * D.real - real * D.im) / (D.real * D.real + D.im * D.im) };
	}
	


	~inum() {}
};

class Stack
{
private:
	int data[100] = {};
	int top = 0;
public:
	Stack() {}
	~Stack(){}

	bool isEmpty() {
		if (top == 0)
			return true;
		else
			return false;
	}
	bool isFull()
	{
		if (top == 100)
			return true;
		else
			return false;
	}
	void Push(int val)
	{
		if (!isFull())
		{
			data[top++] = val;
		}
		else
		{
			cout << "Стек уже заполнен\n";
		}
	}
	int Pop() 
	{
		if (!isEmpty())
		{
			return data[--top];
		}
		else
		{
			cout << "Стек уже пуст\n";
			return -1;
		}
	}
	
};

class Contact
{
private:
	string name;
	string surname;
	long long int phone;
	string address;

public:
	Contact(string n, string s, long long int p): name(n), surname(s), phone(p){}
	Contact() : name(""), surname(""), phone() {}
	~Contact(){}

	void setName(string NewName) { name = NewName; }
	void setFirstname(string NewName) { surname = NewName; }
	void setPhoneNumber(long long int NewPhone) { phone = NewPhone; }
	void setAddress(string NewAddress) { address = NewAddress; }
	
	string getName() const{ return name; }
	string getSurname() const{ return surname; }
	long long int getPhoneNumber() const{ return phone; }
	string getAddress() const{ return address; }

	void Print()
	{
		cout <<  name << " " << surname  << " | " << phone << " | " << address << "\n";
	}
};
class PhoneBook
{
private:
	Contact data[100];
	int count;
public:
	PhoneBook(): count(0) {}
	~PhoneBook(){}

	bool isEmpty() {
		if (count == 0)
			return true;
		else
			return false;
	}
	bool isFull()
	{
		if (count == 100)
			return true;
		else
			return false;
	}

	void AddContact(Contact c) 
	{
		if (!isFull())
		{
			data[count++] = c;
		}
		else
		{
			cout << "Книга переполнена\n";
		}
	}
	Contact& FindBySurname(string surname)
	{
		if (!isEmpty())
		{
			for (int i = 0; i < count; i++)
			{
				if (data[i].getSurname() == surname)
					return data[i];
			}
		}
		else
			cout << "Книга пуста\n";
	}
	void RemoveContact(string surname)
	{
		if (!isEmpty())
		{
			for (int i = 0; i < count; i++)
			{
				if (data[i].getSurname() == surname)
				{
					for (int j = i; j < 99; j++)
					{
						data[j] = data[j + 1];
					}
					count--;
					break;
				}
			}
		}
		else
			cout << "Книга пуста\n";
	}
	void PrintAll()
	{
		if (!isEmpty())
		{
			for (int i = 0; i < count; i++)
			{
				data[i].Print();
			}
		}
	}
};

class Date
{
private:
	int day;
	int month;
	int year;
public:
	Date(int d, int m, int y): day(d), month(m), year(y) {}
	Date() : day(1), month(1), year(2000) {}
	~Date(){}

	void print()
	{
		if (day > 9) cout << day;
		else cout << '0' << day;
		cout << '.';
		if (month > 9) cout << month;
		else cout << '0' << month;
		cout << '.';
		cout << year;
	}
};
class Person
{
private:
	string name;
	string surname;
	Date birthday;
	int passport;

public:
	Person(string n, string sn, Date b, int pass) : name(n), surname(sn), birthday(b), passport(pass) {}
	Person() : name(""), surname(""), birthday(Date()), passport(0) {}
	~Person(){}



};
enum Oper_type
{
	Withdraw,
	Deposit
};
class Operation
{
private:
	Date time;
	Oper_type operation;
	double sum;

public:
	Operation(Date d, Oper_type op, double s) : time(d), operation(op), sum(s) {}
	Operation() : time(Date()), operation(Deposit), sum(0) {}
	~Operation(){}

	void print_info()
	{
		time.print();
		cout << '|';
		switch (operation)
		{
		case Withdraw:
			cout << " Withdraw ";
			break;
		case Deposit:
			cout << " Deposit ";
			break;
		default:
			cout << " NONE ";
			break;
		}
		cout << '|';
		cout << ' ' << sum << '\n';

	}



};
class Account
{
private:
	Date created;
	double money;
	Person owner;
	Operation data[10];
	int ops = 0;

public:
	Account(Person p) : owner(p) { created = { 6,9,2026 }; money = 0; }
	~Account(){} 

	void Deposit(double amount)
	{
		money += amount;
		cout << "Пополнение на "<< amount <<'.' << " Баланс: " << money << '\n';
		if (ops > 9)
		{
			for (int i = 0; i < ops - 1; i++)
			{
				data[i] = data[i + 1];
			}
			data[ops - 1] = { {6,9,2026}, Oper_type::Deposit, amount };
		}
		else
		{
			data[ops] = { {6,9,2026}, Oper_type::Deposit, amount };
			ops++;
		}
	}
	void Withdraw(double amount)
	{
		if (amount <= money)
		{
			money -= amount;
			cout << "Снятие на " << amount << '.' << " Баланс: " << money << '\n';
			if (ops > 9)
			{
				for (int i = 0; i < ops - 1; i++)
				{
					data[i] = data[i + 1];
				}
				data[ops - 1] = { {6,9,2026}, Oper_type::Withdraw, amount };
			}
			else 
			{
				data[ops] = { {6,9,2026}, Oper_type::Withdraw, amount };
				ops++;
			}
			
		}
		else
		{
			cout << "Недостаточно средств для снятия. Баланс " << money << '\n';
		}
	}
	void PrintLastOperations()
	{
		cout << "Последние операции: \n";
		for (int i = 0; i < ops; i++)
		{
			data[i].print_info();
		}
		cout << '\n';
	}

};

class Time
{
private:
	int hour;
	int minute;
public:
	Time(int h = 0, int m = 0): hour(h), minute(m) {}
	~Time(){}

	void setHour(int h) { hour = h; }
	void setMinute(int m) { minute = m; }
	void setTime(int h, int m) { hour = h; minute = m; }

	int getHour() const { return hour; }
	int getMinute() const { return minute; }


	void print()
	{
		if (hour > 9) cout << hour;
		else cout << '0' << hour;
		cout << ':';
		if (minute > 9) cout << minute;
		else cout << '0' << minute;
	}
};
enum species
{
	lion,
	zebra,
	giraffe,
	hippo,
	penguin,
	lemur,
	gorrila,
	otter,
};
class Animal
{
private:
	species animal;
	string name;
	int cage;
	string fav_food;
	bool hunger;

public:
	Animal(species a, string n, int c = 0, string ff = "", bool h = true) : animal(a), name(n), cage(c), fav_food(ff), hunger(h) {}
	Animal() {}
	~Animal() {}

	void setSpecies(species s) { animal = s; }
	void setName(string n) { name = n; }
	void setCage(int c) { cage = c; }
	void setFavFood(string ff) { fav_food = ff; }
	void setHunger(bool t) { hunger = t; }

	species getSpecies() const { return animal; }
	string getName() const { return name; }
	int getCage() const { return cage; }
	string getFavFood() const{return fav_food;}
	bool getHunger() const { return hunger; }
	
};
class Zoo
{
private:
	int count = 0;
	Animal data[20];
	Time open;
	Time close;
	string warden_surname;
public:
	Zoo() : open({8, 30 }), close(21, 0) {}
	~Zoo() {}

	void setOpenTime(int h, int m) { open.setTime(h, m); }
	void setCloseTime(int h, int m) { close.setTime(h, m); }

	
	string getWarden() const { return warden_surname; }
	int getCount() const { return count; }
	Time getOpenTime() const { return open; }
	Time getCloseTime() const { return close; }

	void AddAnimal(Animal a)
	{
		if (count < 20)
		{
			data[count] = a;
			count++;
			cout << "Животное добавлено: " << a.getName() << '\n';
		}
		else
			cout << "Зоопарк переполнен!\n";
	}
	void RemoveAnimal(int i)
	{
		if (i >= 0 && i < count)
		{
			cout << "Удалено животное: " << data[i].getName() << '\n';
			for (int j = i; j < count - 1; j++)
				data[j] = data[j + 1];
			count--;
		}
		else
			cout << "Неверный индекс!\n";
	}
	void FeedAnimal(int i)
	{
		if (data[i].getHunger())
		{
			data[i].setHunger(false);
			cout << data[i].getName() << " Покормлен \n";
		}
		else
			cout << data[i].getName() << " Уже сыт \n";
	}
	void MakeHungry(int i)
	{
		if (!data[i].getHunger())
		{
			data[i].setHunger(true);
			cout << data[i].getName() << " Проголодался \n";
		}
		else
			cout << data[i].getName() << " Уже голоден \n";
	}
	void ChangeKeeper(string surname) 
	{ 
		warden_surname = surname; 
		cout << "Новый сторож: " << getWarden() << '\n';
	}
	Animal& FindByName(string name) 
	{
		for (int i = 0; i < count; i++)
		{
			if (data[i].getName() == name)
			{
				return data[i];
				break;
			}
		}
	}
	void ShowAllAnimals() const
	{
		if (count == 0)
		{
			cout << "В зоопарке нет животных\n";
			return;
		}
		cout << "Список животных (" << count << " шт.):\n";
		for (int i = 0; i < count; i++)
		{
			cout << i + 1 << ". " << data[i].getName()
				<< " (" << data[i].getSpecies() << ")"
				<< ", клетка " << data[i].getCage()
				<< ", любимая еда: " << data[i].getFavFood()
				<< ", голоден: " << (data[i].getHunger() ? "да" : "нет") << '\n';
		}
	}
};

class Student
{
private:
	string name;
	string second_name;
	string surname;
	int pass;
	bool paid;
	string course_name;
public:
	Student() {}
	Student(string n, string sn = "", string s = "", int p = -1, bool pay = false, string course = "") : name(n), second_name(sn), surname(s), pass(p), paid(pay), course_name(course) {}
	~Student() {}

	string getName() const { return name; }
	string getSecondName() const { return second_name; }
	string getSurname() const { return surname; }
	int getPass() const { return pass; }
	bool getPaid() const { return paid; }
	string getCourseName() const { return course_name; }

	void setName(string n) { name = n; }
	void setSecondName(string sn) { second_name = sn; }
	void setSurname(string s) { surname = s; }
	void setPass(int p) { pass = p; }
	void setPaid(bool p) { paid = p; }
	void setCourseName(string n) { course_name = n; }

	void printFIO()
	{
		cout << second_name << ' ' << name << ' ' << surname << ' ';
	}
};
class Course
{
private:
	string name;
	double cost;
	int maxlist = 100;
	int curlist = 0;
	Student listeners[100];
public:
	Course() {}
	Course(string n, double c) : name(n), cost(c) {}
	~Course() {}

	string getName() const { return name; }
	double getCost() const { return cost; }
	int getCurList() const { return curlist; }
	int getMaxList() const { return maxlist; }

	void setCost(double c) { cost = c; }

	void AddStudent(Student& s)
	{
		if (curlist < maxlist)
		{
			s.setCourseName(name);
			listeners[curlist] = s;
			curlist++;
			cout << "Курс" << getName() << ": Добавлен студент "; s.printFIO(); cout << '\n';
		}
	}
	void RemoveStudent(string surname, string name, string second_name)  
	{
		for (int i = 0; i < curlist; i++)
		{
			if (listeners[i].getSurname() == surname &&
				listeners[i].getName() == name &&
				listeners[i].getSecondName() == second_name)
			{
				listeners[i].setCourseName("");
				cout << "Курс " << getName() << ": Исключен студент ";
				listeners[i].printFIO();
				cout << '\n';

				for (int j = i; j < curlist - 1; j++)
				{
					listeners[j] = listeners[j + 1];
				}
				curlist--;
				return;
			}
		}
		cout << "Студент " << surname << " " << name << " " << second_name << " не найден на курсе " << getName() << '\n';
	}
	void PrintUnpaidStudents()
	{
		bool found = false;
		cout << "Студенты, не оплатившие курс \"" << getName() << "\"\n";
		for (int i = 0; i < curlist; i++)
		{
			if (!listeners[i].getPaid())
			{
				cout << " - ";
				listeners[i].printFIO();
				cout << " (паспорт: " << listeners[i].getPass() << ")\n";
				found = true;
			}
		}
		if (!found)
			cout << "Все студенты оплатили курс\n";
	}
	void PrintAllStudents()  
	{
		if (curlist == 0)
		{
			cout << "На курсе \"" << getName() << "\" нет студентов\n";
			return;
		}
		cout << "Студенты курса \"" << getName() << "\"\n";
		for (int i = 0; i < curlist; i++)
		{
			cout << i + 1 << ". ";
			listeners[i].printFIO();
			cout << " (паспорт: " << listeners[i].getPass()
				<< ", оплачено: " << (listeners[i].getPaid() ? "да" : "нет") << ")\n";
		}
	}

};

bool oneCourse(Student s1, Student s2)
{
	if (s1.getCourseName() == s2.getCourseName()) return true;
	else return false;
}

int main()
{
	system("chcp 1251");
    cout << "Hello World!\n\n";

	cout << "Комплексные числа: \n\n";
	inum a(5,5), b(3, 4), c(1, 1);

	c = a.div(b);
	c.print_inum(t);
	cout << "\n";


	cout << "Стек: \n\n";
	Stack st;

	st.Push(56);
	st.Push(49);
	cout << st.Pop()<<'\n';
	cout << st.Pop() << '\n';
	cout << st.Pop() << '\n' << '\n';

	cout << "Телефонная книга: \n\n";
	PhoneBook tel;

	tel.AddContact({ "Edgar","Tozlian", 89189210234 });
	tel.AddContact({ "Vladimir","Putin", 89899002007 });
	tel.AddContact({ "Donald","Trump", 1347946345 });
	tel.AddContact({ "Jeffry","Epstein", 132723555 });
	tel.AddContact({ "Artem","Keseyan", 147946345 });
	cout << "Ввод адреса: \n";
	tel.FindBySurname("Epstein").setAddress("Little SaintJames island");
	tel.FindBySurname("Epstein").Print();
	cout << "Список контактов: \n";
	tel.PrintAll();
	cout << '\n';

	cout << "Банковский счет: \n\n";
	Account SBER({ "Edgar","Tozlian",{14,4,2007},1234123 });

	SBER.Deposit(2500);
	SBER.Withdraw(3200);
	SBER.Deposit(1000);
	SBER.Withdraw(3200);
	SBER.PrintLastOperations();

	cout << "Зоопарк: \n\n";

	Zoo myZoo;

	myZoo.ChangeKeeper("Иванов");

	
	myZoo.setOpenTime(9, 0);
	myZoo.setCloseTime(20, 0);

	
	Animal a1(lion, "Алекс", 1, "мясо", true);
	Animal a2(zebra, "Марти", 2, "трава", false);
	Animal a3(giraffe, "Мелман", 3, "листья", true);
	Animal a4(penguin, "Шкиппер", 4, "рыба", false);
	Animal a5(lemur, "Джулиан", 5, "фрукты", true);

	myZoo.AddAnimal(a1);
	myZoo.AddAnimal(a2);
	myZoo.AddAnimal(a3);
	myZoo.AddAnimal(a4);
	myZoo.AddAnimal(a5);

	cout << "Все животные: \n";
	myZoo.ShowAllAnimals();
	cout << '\n';

	cout << "Курсы (Астрология, Таро, Нумерология): \n\n";

	Course astro("Астрология", 1000000);
	Course taro("Таро", 2500000);
	Course numero("Нумерология", 40000000);
	Student s1("Edgar", "Tozlian", "Davidovich", 12314124, true);
	Student s2("Петр", "Петрович", "Петров", 234567, false);
	Student s3("Мария", "Сергеевна", "Сидорова", 345678, false);
	Student s4("Анна", "Алексеевна", "Смирнова", 456789, true);
	taro.AddStudent(s1);
	taro.AddStudent(s2);
	astro.AddStudent(s3);
	numero.AddStudent(s4);

	taro.PrintAllStudents();

	cout << "Проверка одногруппников: \n";
	if (oneCourse(s1, s4))
	{
		cout << "Студенты: "; s1.printFIO(); cout << " и "; s4.printFIO(); cout << "на одном курсе ( " << s1.getCourseName() << " )\n";
	}
	else
	{
		cout << "Студенты: "; s1.printFIO(); cout << " и "; s4.printFIO(); cout << "на разных курсах ( " << s1.getCourseName() << " и " << s4.getCourseName() << " )\n";
	}
	if (oneCourse(s1, s2))
	{
		cout << "Студенты: "; s1.printFIO(); cout << " и "; s2.printFIO(); cout << "на одном курсе ( " << s1.getCourseName() << " )\n";
	}
	else
	{
		cout << "Студенты: "; s1.printFIO(); cout << " и "; s2.printFIO(); cout << "на разных курсах ( " << s1.getCourseName() << " и " << s2.getCourseName() << " )\n";
	}
	getchar();
	return 0;
}

