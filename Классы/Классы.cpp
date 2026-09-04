#include <iostream>
#include <cmath>
#include <vector>

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
		return { real + D.im, im + D.im };
	}
	inum sub(inum D)
	{
		return { real - D.im, im - D.im };
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
	int data[100];
	int top;
public:
	Stack(): top(0){}
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
	int phone;
	string address;

public:
	Contact(){}
	~Contact(){}

	void setName(string NewName) { name = NewName; }
	void setFirstname(string NewName) { surname = NewName; }
	void setPhoneNumber(int NewPhone) { phone = NewPhone; }
	void setAddress(string NewAddress) { address = NewAddress; }
	
	string getName() { return name; }
	string getSurname() { return surname; }
	int getPhoneNumber() { return phone; }
	string getAddress() { return address; }

	void Print()
	{
		cout << surname << " " << name << " | " << phone << " | " << address << "\n";
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
	Contact FindBySurname(string surname)
	{
		if (!isEmpty())
		{
			for (int i = 0; i < 100; i++)
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
		if (!isEmpty)
		{
			for (int i = 0; i < 100; i++)
			{
				if (data[i].getSurname() == surname)
				{
					for (int j = i; j < 99; j++)
					{
						data[j] = data[j + 1];
					}
					count--;
				}
			}
		}
		else
			cout << "Книга пуста\n";
	}
	void PrintAll()
	{
		if (!isEmpty)
		{
			for (int i = 0; i <= count; i++)
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
	Date(int d = 1, int m = 1, int y = 2000): day(d), month(m), year(y) {}
	~Date(){}
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
	~Person(){}



};
enum Oper_type
{
	decrease,
	increase
};
class Operation
{
private:
	Date time;
	Oper_type operation;
	int sum;

public:
	Operation(Date d, Oper_type op, int s) : time(d), operation(op), sum(s) {}
	~Operation(){}



};
class Account
{
private:
	Date created;
	double money;
	Person owner;
	vector<Operation> data;
	int ops = 0;

public:
	Account(Date c, double m, Person p, vector<Operation> d) : created(c), money(m), owner(p), data(d) {}
	~Account(){} 

	void Deposit(double amount)
	{
		
	}



};

int main()
{
	system("chcp 1251");
    cout << "Hello World!\n\n";


	inum a(5,5), b(3, 4), c(1, 1);

	c = a.div(b);
	c.print_inum(t);
	cout << "\n";

	Stack st;

	st.Push(56);
	st.Push(49);
	cout << st.Pop()<<'\n';
	cout << st.Pop() << '\n';
	cout << st.Pop() << '\n';


}

