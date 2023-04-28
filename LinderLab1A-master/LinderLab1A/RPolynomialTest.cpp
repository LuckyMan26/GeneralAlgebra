
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

// Implemented by Y. Kishchuk
TEST_CASE("Addition")
{
	RPolynomial polinomial = RPolynomial("-2-x-4x^4-9x^3+x^5+2x^2-1"),
		polinomial2 = RPolynomial("x^10-5x^5+1");

	auto sum = polinomial + polinomial2;
	CHECK(sum.toString() == "x^10-4x^5-4x^4-9x^3+2x^2-x-2");
	
	polinomial = RPolynomial("-2-x-4x^4-7326738238625862586038757037503857353350098852685286358237253276358238625856382x^3+x^5+2x^2-1");
	polinomial2 = RPolynomial("2+x+4x^4+7326738238625862586038757037503857353350098852685286358237253276358238625856382x^3-x^5-2x^2+1");

	sum = polinomial + polinomial2;
	CHECK(sum.toString() == "0");

	polinomial = RPolynomial("x^5-4x^4-9x^3+2x^2-x-1");
	polinomial2 = RPolynomial("x^10-5x^5+1");

	sum = polinomial + polinomial2;
	CHECK(sum.toString() == "x^10-4x^5-4x^4-9x^3+2x^2-x");
}


TEST_CASE("Substraction")
{
	RPolynomial polinomial = RPolynomial("-2-x-4x^4-9x^3+x^5+2x^2-1"),
		polinomial2 = RPolynomial("x^10-5x^5+1");

	auto sum = polinomial - polinomial2;
	CHECK(sum.toString() == "-x^10+6x^5-4x^4-9x^3+2x^2-x-4");

	polinomial = RPolynomial("-2-x-4x^4-7326738238625862586038757037503857353350098852685286358237253276358238625856382x^3+x^5+2x^2-1");
	polinomial2 = RPolynomial("-2-x-4x^4-7326738238625862586038757037503857353350098852685286358237253276358238625856382x^3+x^5+2x^2-1");

	sum = polinomial - polinomial2;
	CHECK(sum.toString() == "0");

	polinomial = RPolynomial("x^5-4x^4-9x^3+2x^2-x-1");
	polinomial2 = RPolynomial("x^10-5x^5+1");

	sum = polinomial - polinomial2;
	CHECK(sum.toString() == "-x^10+6x^5-4x^4-9x^3+2x^2-x-2");
}

TEST_CASE("Product")
{
	RPolynomial polinomial = RPolynomial("-2-x-4x^4-9x^3+x^5+2x^2-1"),
		polinomial2 = RPolynomial("x^10-5x^5+1");

	auto sum = polinomial * polinomial2;
	CHECK(sum.toString() == "x^15-4x^14-9x^13+2x^12-x^11-8x^10+20x^9+45x^8-10x^7+5x^6+16x^5-4x^4-9x^3+2x^2-x-3");

	polinomial = RPolynomial("x^5-4x^4-9x^3+2x^2-x-1");
	polinomial2 = RPolynomial("x^10-5x^5+1");

	sum = polinomial * polinomial2;
	CHECK(sum.toString() == "x^15-4x^14-9x^13+2x^12-x^11-6x^10+20x^9+45x^8-10x^7+5x^6+6x^5-4x^4-9x^3+2x^2-x-1");
}