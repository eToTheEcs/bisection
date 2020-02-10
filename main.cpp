#include "pch.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>

#include "Polynomial.h"

using namespace std;

int main(int argc, char** argv) {

	/*if (argc < 2) {

		cerr << "USAGE: bisezione coeff1 [, coeff2...[, coeffn]]";
		return EXIT_FAILURE;
	}*/

	ifstream in("input.txt");

	int N, n;
	deque<double> coefficients;

	in >> N;

	for (int i = 0; i < N; ++i) {
		in >> n;
		coefficients.push_back(n);
	}
	
	Polynomial poly(coefficients);

	cout << poly << endl;

	//cout << "ZERO AT: " << poly.findZero(2.5, 4);

	cout << poly.integrate(0, 2);

	in.close();
    return EXIT_SUCCESS;
}
