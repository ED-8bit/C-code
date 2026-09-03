#include <iostream>
#include <cmath>

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
				cout << "+" << im << "i";
			else if (im < 0)
				cout << im << "i";
		}
		else if (a == t)
		{
			cout << r << "cos(" << phi << ")+i*sin(" << phi << ")";
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

int main()
{
    cout << "Hello World!\n\n";


	inum a(5,5), b(3, 4), c(1, 1);

	c = a.div(b);
	c.print_inum(t);
	cout << "\n";


}

