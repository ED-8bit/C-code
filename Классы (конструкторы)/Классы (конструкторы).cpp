#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class TextFile {
private:
	fstream file;
	string filename;
public:
	TextFile(string name) : filename(name) 
	{
		file.open(filename, ios::in | ios::out | ios::app);

		if (!file.is_open())
		{
			cerr << "Не удалось открыть файл " << filename << '\n';
		}
		else
		{
			cout << "Файл " << filename << " создан\n";
		}
	}
	~TextFile() {
		if (file.is_open())
		{
			file.close();
			if (remove(filename.c_str()) == 0)
			{
				cout << "Файл " << filename << " удален\n";
			}
		}
	}

	void WriteLine(string text);
	void PrintContents();
};

void  TextFile::WriteLine(string text) {
	if (file.is_open())
	{
		file << text << '\n';
	}
	else
	{
		cerr << "Ошибка. Файл закрыт, запись невозможна\n";
	}
}
void TextFile::PrintContents()
{
	if (!file.is_open())
	{
		cerr << "Ошибка. Файл закрыт.\n";
		return;
	}
	file.clear();
	file.seekg(0, ios::beg);

	string line;
	cout << "Содержимое файла " << filename << '\n';

	while (getline(file, line))
	{
		cout << line << '\n';
	}
}

class myvector
{
private:
	int len;
	int* v;
public:
	myvector(int length){
			
	}
	~myvector(){}

};






int main() {
	system("chcp 1251");
	system("cls");
	TextFile myFile("test.txt");

	myFile.WriteLine("Привет, мир!");
	myFile.WriteLine("Это TextFile на C++.");
	myFile.PrintContents();

	return 0; 
}
