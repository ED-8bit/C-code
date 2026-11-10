#include <iostream>
using namespace std;

template <class X> X MaxInArray(X arr[], int size)
{
	X max = arr[0];
	for (int i = 0; i < size; i++) {
		if (max < arr[i])
			max = arr[i];
	}
	return max;
}
template<> const char* MaxInArray(const char* arr[], int size)
{
	int maxlenid = 0;
	for (int i = 0; i < size; i++) {
		if (strlen(arr[maxlenid]) < strlen(arr[i]))
			maxlenid = i;
	}
	return arr[maxlenid];
}

template <class item> void SortArray(item arr[], int size) {
	for (size_t i = 0; i < size - 1; ++i) {
		size_t min_index = i;

		for (size_t j = i + 1; j < size; ++j) {
			if (arr[j] < arr[min_index]) {
				min_index = j;
			}
		}

		if (min_index != i) {
			swap(arr[i], arr[min_index]);
		}
	}
	return;
}
class Animal
{
	string Name;
	double Weight;
public:
	Animal(string name, double weight): Name(name), Weight(weight){}
	~Animal(){}

	bool operator>(Animal other) {
		return this->Weight > other.Weight;
	}
	bool operator<(Animal other) {
		return this->Weight < other.Weight;
	}

	friend std::ostream& operator<<(std::ostream& out, const Animal& a) {
		out << a.Name;
		return out;
	}
};
template <class item> void ShowArray(item arr[], int size) {
	cout << "[ ";
	for (int i = 0; i < size; i++)
	{
		if (i < size - 1)
		{
			cout << arr[i] << ", ";
		}
		else
		{
			cout << arr[i];
		}
			
	}
	cout << " ]\n";
}

int main()
{
	system("chcp 1251");

	int arr1[3] = { 64, 54, 100 };
	double arr2[3] = { 5.3, 2.5, 4.9 };
	long int arr3[3] = { 14135, 2456, 34535 };
	const char* arr4[3] = { "cout << ","Hello ", "World" };
	char arr5[3] = { 'b', 'a', 'c' };
	Animal arr6[3] = { {"tigr", 250}, {"slon", 5000}, {"monkey", 15}};


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
			
			cout << MaxInArray(arr1, 3) << '\n';
			cout << MaxInArray(arr2, 3) << '\n';
			cout << MaxInArray(arr3, 3) << '\n';
			cout << MaxInArray(arr4, 3) << '\n';
			cout << MaxInArray(arr5, 3) << '\n';
			break;
		}
		case 2:
		{
			SortArray(arr1, 3);
			SortArray(arr2, 3);
			SortArray(arr3, 3);
			SortArray(arr5, 3);
			SortArray(arr6, 3);
			ShowArray(arr1, 3);
			ShowArray(arr2, 3);
			ShowArray(arr3, 3);
			ShowArray(arr5, 3);
			ShowArray(arr6, 3);
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
