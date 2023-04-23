
#include "doctest.h"

#include "RPolynomial.h"

#include <random>
#include <string>
#include <chrono>


//Test and implementation by M. Tyshchenko
//Using Gorner rule
TEST_CASE("Value at X") {
	RPolynomial polinomial = RPolynomial("-1 -1 2 -9 4 1");
	RPolynomial polinomial2 = RPolynomial("1 0 0 0 0 -5 0 0 0 0 1");
	RPolynomial polinomial3 = RPolynomial("6");
	CHECK(polinomial.valueAt(SignedNumber("2")).toString() == "29");
	CHECK(polinomial2.valueAt(SignedNumber("3")).toString() == "57835");
	CHECK(polinomial3.valueAt(SignedNumber("10")).toString() == "6");
}

//Test and implementation by M. Tyshchenko
TEST_CASE("Derivative") {
	RPolynomial polinomial = RPolynomial("-1 -1 2 -9 4 1");
	RPolynomial polinomial2 = RPolynomial("1 0 0 0 0 -5 0 0 0 0 1");
	RPolynomial polinomial3 = RPolynomial("6");
	CHECK(polinomial.derivative().toString() == "-1 4 -27 16 5");
	CHECK(polinomial2.derivative().toString() == "0 0 0 0 -25 0 0 0 0 10");
	CHECK(polinomial3.derivative().toString() == "0");
}