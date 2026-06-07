#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ofstream out;
	out.open("file.txt");
	out.close();
	return 0;
}
