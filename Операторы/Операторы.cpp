#include <iostream>
using namespace std;

class three_d
{
	int x, y, z;
public:
	three_d() { x = y = z = 0; }
	three_d(int i, int j, int k){
		x = i; y = j; z = k;
	}
	three_d operator+(three_d op2);
	three_d operator++();
	three_d operator++(int notused);
	three_d operator=(three_d op2);
	bool operator==(three_d op2);
	void show();
};
void three_d::show() {
	if (x)
		cout << x << ", ";
	else
		cout << "0, ";
	if (y)
		cout << y << ", ";
	else
		cout << "0, ";
	if (z)
		cout << z;
	cout << '\n';
}
three_d three_d::operator+(three_d op2) {
	three_d temp;
	temp.x = x + op2.x;
	temp.y = y + op2.y;
	temp.z = z + op2.z;
	return temp;
}
three_d three_d::operator++() {
	x++; y++; z++;
	return *this;
}
three_d three_d::operator++(int notused) {
	three_d temp = *this;
	x++; y++; z++;
	return temp;
}
three_d three_d::operator=(three_d op2) {
	x = op2.x;
	y = op2.y;
	z = op2.z;
	return *this;
}
bool three_d::operator==(three_d op2) {
	if ((x == op2.x) &&
		(y == op2.y) &&
		(z = op2.z))
		return true;
	else
		return false;
}

class CL
{
public:
	int count;
	CL operator=(CL obj);
	friend CL operator+(CL ob, int i);
	friend CL operator+(int i, CL ob);
};
CL CL::operator=(CL obj) {
	count = obj.count;
	return *this;
}
CL operator+(CL ob, int i) {
	CL temp;
	temp.count = ob.count + i;
	return temp;
}
CL operator+(int i, CL ob) {
	CL temp;
	temp.count = ob.count + i;
	return temp;
}

class my_vector
{
	int n;
	double* v;
public:
	my_vector(int c = 2);
	my_vector(const my_vector& copy);
	~my_vector();
	my_vector operator=(my_vector other);
	my_vector operator+(const my_vector& other) const;
	my_vector operator+=(my_vector& other);
	my_vector operator*(double m);
	friend my_vector operator*(double m, my_vector& v);
	my_vector operator^(my_vector& other);
};
my_vector::my_vector(int c): n(c){
	v = new double[n];
	for (int i = 0; i < n; i++) v[i] = 0.0;
}
my_vector::my_vector(const my_vector& copy) {
	n = copy.n;
	v = new double[n];
	for (int i = 0; i < n; i++)
	{
		v[i] = copy.v[i];
	}
}
my_vector::~my_vector(){ 
	delete[] v; 
}

my_vector my_vector::operator=(my_vector other) {
	if (this == &other) return *this;
	my_vector temp(other.n);
	for (int i = 0; i < n; i++)
	{
		temp.v[i] = other.v[i];
	}
	return temp;
}
my_vector my_vector::operator+(const my_vector& other) const {

	int maxLen, minLen;

	auto my_sum = [&maxLen, &minLen](const double a[], const double b[]) {
		my_vector temp(maxLen);
		for (int i = 0; i < maxLen; i++) {
			if (i < minLen)
			{
				temp.v[i] = a[i] + b[i];
			}
			else
				temp.v[i] = a[i];
		}
		return temp;
		};

	if (n > other.n)
	{
		maxLen = n; minLen = other.n;
		return my_sum(this->v, other.v);
	}
	else
	{
		maxLen = other.n; minLen = n;
		return my_sum(other.v, this->v);
	}

}
// a = b -> a = b     a += b -> a = a+b
my_vector my_vector::operator+=(my_vector& other) {
	my_vector temp = *this + other;
	return temp;
}
my_vector my_vector::operator*(double m) {
	my_vector temp(n);
	for (int i = 0; i < n; i++)
	{
		v[i] *= m;
	}
	return temp;
}
my_vector operator*(double m, my_vector& v) {
	my_vector temp(v.n);
	for (int i = 0; i < temp.n; i++)
	{
		temp.v[i] *= m;
	}
	return temp;
}
my_vector my_vector::operator^(my_vector& other) {
}

int main() {
	my_vector a, b, c;
	a = b * 3.0;


	
	return 0;
}
















int main()
{
	system("chcp 1251");
	cout << '\n';

	//three_d d1(3, 5, 1);
	//three_d d2(2, 0, 7);
	//d1.show();
	//d2.show();
	//three_d d3;
	//d3 = ++d2;
	//d3.show();
	//d3 = d3 + d1;
	//d3.show();

	//CL a;
	//a.count = 5;
	//CL b;
	//b.count = 3;
	//b + 2;
	//a = b;




}


