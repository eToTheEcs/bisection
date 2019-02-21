#pragma once
#pragma once

#ifndef POLY_H
#define POLY_H

#include <deque>
#include <algorithm>
#include <functional>
#include <ostream>
#include <cmath>

class Polynomial
{
public:

	Polynomial(std::deque<double>);
	~Polynomial();

	/*Polynomial operator+(const Polynomial&);
	Polynomial& operator+=(const Polynomial&);
	
	Polynomial operator-(const Polynomial&);
	Polynomial& operator-=(const Polynomial&);*/

	int getDegree();

	double getCoeffOfDegree(int deg);

	friend std::ostream& operator<<(std::ostream& out, const Polynomial& p);

	/**
	* plugs-in xval in the polynomial, returns the result P(xval). 
	*/
	double compute(double xval);

	/**
	 * returns a zero of the polynomial, if present, in the given interval.
	 */
	double findZero(double a, double b);

	/**
	* computes the definite integral from a to b of the polynomial.
	*/
	double integrate(double a, double b);

private:

	const double EPSILON = 10E-5;

	static const int N_INTERVALS = 64;

	/**
	 * polynomial coefficients
	 */
	std::deque<double> coeffs;

	int degree;

	std::deque<double> roots;

	/**
		calls the passed function object (or lambda) on all the elements of the container.
	*/
	template<typename T, typename BinaryOperator>
	void applyLambda(const std::deque<T>& first, const std::deque<T>& second, std::deque<T>& res, BinaryOperator func);

	// === integration backends ===

	/**
	* approximates the integral with rectangles method.
	*/
	double integrateByRectangles(double a, double b);

	/**
	* approximates the integral with trapezoidal rule.
	*/
	double integrateByTrapezoidal(double a, double b);

	/**
	* approximates the integral with Cavalieri-Simpson rule.
	*/
	double integrateByCavSimp(double a, double b);

	/**
	* returns the amplitude of the integration interval according to the decided no. of intervals.
	*/
	double getIntervalAmplitude(double a, double b);
};

#endif