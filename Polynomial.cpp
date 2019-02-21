#include "pch.h"
#include "Polynomial.h"


Polynomial::Polynomial(std::deque<double> _coeffs) : coeffs{_coeffs} {

	this->degree = this->coeffs.size() - 1;
}


Polynomial::~Polynomial() {

	// release resources
	
}

/*Polynomial Polynomial::operator+(const Polynomial & other)
{
	std::deque<double> res(other.coeffs.size());

	this->applyLambda(this->coeffs, other.coeffs, res, std::plus<double(double)>());

	return res;
}

Polynomial & Polynomial::operator+=(const Polynomial & other)
{
	
	this->applyLambda(this->coeffs, other.coeffs, this->coeffs, std::plus<double(double)>());

	return *this;
}


Polynomial Polynomial::operator-(const Polynomial & other)
{

	std::deque<double> res(other.coeffs.size());

	this->applyLambda(this->coeffs, other.coeffs, res, std::minus<double(double)>());

	return res;
}

Polynomial & Polynomial::operator-=(const Polynomial & other)
{

	this->applyLambda(this->coeffs, other.coeffs, this->coeffs, std::minus<double(double)>());
}*/

int Polynomial::getDegree()
{
	return this->degree;
}

double Polynomial::getCoeffOfDegree(int deg)
{

	if (deg <= 0 || deg >= this->degree)
		throw std::invalid_argument("degree too big for the polynomial: " + deg);


	return this->coeffs[deg-1];
}

double Polynomial::compute(double xval)
{

	double res = 0.0;

	int i = 0;
	for (auto term : this->coeffs) {
		res += (term * pow(xval, this->degree-i));
		++i;
	}

	return res;
}

double Polynomial::findZero(double a, double b)
{
	// test poly value in mid of interval

	double sxVal = this->compute(a);
	double dxVal = this->compute(b);
	double midVal = this->compute((a + b) / 2);

	printf("f(%.3f) = %.3f, f(%.3f) = %.3f, f(%.3f) = %.3f\n", a, sxVal, (a + b) / 2, midVal, b, dxVal);

	// zero found
	if (abs(midVal) < EPSILON) {
		return (a+b)/2;
	}

	// check where to split
	if (sxVal * midVal < 0) {

		return findZero(a, (a + b) / 2);
	}
	else if (midVal * dxVal < 0) {

		return findZero((a + b) / 2, b);
	}
}

double Polynomial::integrate(double a, double b)
{

	return this->integrateByCavSimp(a, b);
}

double Polynomial::integrateByRectangles(double a, double b)
{
	double runnerH;	// y-value
	double dx = this->getIntervalAmplitude(a, b);
	double result = 0;
	int intervalCounter = 0;

	printf("INTEGRATION BACKEND: RECTANGLES\n");
	printf("a: %lf b: %lf dx: %lf\n", a, b, dx);

	for (double runnerX = a; intervalCounter < N_INTERVALS; runnerX += dx, intervalCounter++) {
		
		runnerH = this->compute(runnerX);
		result += runnerH;
	}

	result *= dx;

	return result;
}

double Polynomial::integrateByTrapezoidal(double a, double b)
{
	double runnerH;	// y-value
	double dx = this->getIntervalAmplitude(a, b);
	double result = 0;
	int intervalCounter = 0;

	printf("INTEGRATION BACKEND: TRAPEZOIDAL\n");
	printf("a: %lf b: %lf dx: %lf\n", a, b, dx);

	for (double runnerX = a; intervalCounter < N_INTERVALS; runnerX += dx, intervalCounter++) {
		
		runnerH = this->compute(runnerX) + this->compute(runnerX + dx);
		result += runnerH;
	}

	result *= (dx / 2);

	return result;
}

double Polynomial::integrateByCavSimp(double a, double b)
{
	double runnerH; // y-value
	// so that is possible to have the mean point of all the N intervals.
	double numIntervals = N_INTERVALS * 2;
	double dx = this->getIntervalAmplitude(a, b) / 2;
	double result = 0;
	double firstAndLast = this->compute(a) + this->compute(b);
	double even = 0.0, odd = 0.0; 

	printf("INTEGRATION BACKEND: CAVALIERI-SIMPSON\n");
	printf("a: %lf b: %lf dx: %lf\n", a, b, dx);

	int intervalCounter = 1;
	// odd-indexed
	for (double runnerX = a; intervalCounter < numIntervals; runnerX += dx, intervalCounter++) {

		if (intervalCounter % 2)
			odd += this->compute(runnerX);
		else
			even += this->compute(runnerX);
	}

	odd *= 4;
	even *= 2;
	result = firstAndLast + odd + even;

	result *= (0.33*dx);

	return result;
}

double Polynomial::getIntervalAmplitude(double a, double b)
{
	return std::fabs(a-b) / N_INTERVALS;
}

template <typename T, typename BinaryOperator>
void Polynomial::applyLambda(const std::deque<T>& first, const std::deque<T>& second, std::deque<T>& res, BinaryOperator func) {

	if (first.size() != second.size())
		throw new std::invalid_argument("polynomial degrees must be equal");

	std::transform(first.begin(), first.end(), second.begin(), res.begin(), func);
}

std::ostream& operator<<(std::ostream & out, const Polynomial & p)
{
	
	int i = 0;
	for (auto coeff : p.coeffs) {
		out << p.coeffs[i] << "x^" << p.degree - i << " ";
		i++;
	}
	
	return out;
}
