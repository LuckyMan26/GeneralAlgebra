
#include "doctest.h"

#include "RPolynomial.h"

#include <random>
#include <string>
#include <chrono>


//Test and implementation by M. Tyshchenko
//Using Gorner rule
TEST_CASE("Value at X") {
	RPolynomial polinomial = RPolynomial("x^5-4x^4-9x^3+2x^2-x-1");
	RPolynomial polinomial2 = RPolynomial("x^10-5x^5+1");
	RPolynomial polinomial3 = RPolynomial("6");
	CHECK(polinomial.valueAt(SignedNumber("2")).toString() == "-99");
	CHECK(polinomial2.valueAt(SignedNumber("3")).toString() == "57835");
	CHECK(polinomial3.valueAt(SignedNumber("10")).toString() == "6");
}

//Test and implementation by M. Tyshchenko
TEST_CASE("Derivative") {
	RPolynomial polinomial = RPolynomial("-2-x-4x^4-9x^3+x^5+2x^2-1");
	RPolynomial polinomial2 = RPolynomial("x^10-5x^5+1");
	RPolynomial polinomial3 = RPolynomial("6");

	CHECK(polinomial.toString() == "x^5-4x^4-9x^3+2x^2-x-3");
	CHECK(polinomial2.toString() == "x^10-5x^5+1");
	CHECK(polinomial3.toString() == "6");
	CHECK(polinomial.derivative().toString() == "5x^4-16x^3-27x^2+4x-1");
	CHECK(polinomial2.derivative().toString() == "10x^9-25x^4");
	CHECK(polinomial3.derivative().toString() == "0");
}