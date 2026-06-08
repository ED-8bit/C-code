#include <iostream>
#include <fstream>
#include <filesystem>
using namespace std;

int main()
{
	int ch;
	system("chcp 1251");
	system("cls");
	cout << "Path: " << filesystem::current_path() << '\n';
	cout << "1. write\n";
	cout << "2. erase\n";
	cout << "choice: ";
	cin >> ch;
	ofstream fout;
	switch(ch)
	{
	case 1:
		fout.open("file.txt", ios::app);
		if (fout.is_open())
		{
			fout << "Hello world!" << '\n';
			fout.close();
			cout << "\nWrited" << '\n';
		}
		else
			cout << "\nError" << '\n';
		break;
	case 2:
		fout.open("file.txt");
		if (fout.is_open())
		{
			fout << " ";
		}
		break;
	}
	
	return 0;
}
