#include <iostream>

using namespace std;

class Printer
{
	
public:
	string ID;
	Printer(string i): ID(i){}
	~Printer(){}

	void Print(string document) {
		cout << "Печать " << document << "\n";
	}
};

class Scanner
{
	
public:
	int dpi;
	Scanner(int d): dpi(d){}
	~Scanner(){}
	void Scan() {
		cout << "Сканирование с разрешением " << dpi << '\n';
	}
};

class MFP: public Printer, public Scanner
{

public:
	MFP(string i, int d): Printer(i), Scanner(d){}
	~MFP(){}
	void Copy() {
		cout << "Копирование " << ID;
		Scan();
		Print();
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
			MFP d("doc", 1080);
			d.Copy();
			break;
		}
		case 2:
		{
			
			break;
		}
		case 3:
		{
			
			break;
		}
		case 4:
		{
			
			break;
		}
		case 5:
		{
			
			break;
		}
		case 6:
		{
			
			break;
		}
		case 0:
			return 0;
		}
		cout << "\n";
		system("pause");
	}
}
