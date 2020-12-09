#define _USE_MATH_DEFINES
#include <cmath>

double					// Исходные значения параметров X0, Y0, px, py
	X0=200,
	Y0=300,
	px=5,
	py=5;

double Parabola(double x)
{
	return x*x-2;
}

double Sinusoid(double x)
{
	return sin(x);
}
double test(double x)
{
	return 1 / (x*x);
}

double polarCos(double phi)
{
	return cos(phi);
}

double polarRose(double phi)
{
	return sin(phi);
}

double polarSpiral(double phi)
{
	return phi;
}
double polarR(double t)
{
	return t;
}
double polarPhi(double t)
{
	return t;
}