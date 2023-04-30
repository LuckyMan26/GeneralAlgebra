
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
	RPolynomial polinomial = RPolynomial("-2x^4+x^2+1"),
		polinomial2 = RPolynomial("2x^4+x^3");

	auto sum = polinomial + polinomial2;
	CHECK(sum.toString() == "x^3+x^2+1");
	sum = polinomial2 + polinomial;
	CHECK(sum.toString() == "x^3+x^2+1");

	polinomial = RPolynomial("-2-x-4x^4-9x^3+x^5+2x^2-1");
	polinomial2 = RPolynomial("x^10-5x^5+1");

	sum = polinomial + polinomial2;
	CHECK(sum.toString() == "x^10-4x^5-4x^4-9x^3+2x^2-x-2");
	sum = polinomial2 + polinomial;
	CHECK(sum.toString() == "x^10-4x^5-4x^4-9x^3+2x^2-x-2");
	
	polinomial = RPolynomial("-2-x-4x^4-7326738238625862586038757037503857353350098852685286358237253276358238625856382x^3+x^5+2x^2-1");
	polinomial2 = RPolynomial("2+x+4x^4+7326738238625862586038757037503857353350098852685286358237253276358238625856382x^3-x^5-2x^2+1");

	sum = polinomial + polinomial2;
	CHECK(sum.toString() == "0");
	sum = polinomial2 + polinomial;
	CHECK(sum.toString() == "0");

	polinomial = RPolynomial("x^5-4x^4-9x^3+2x^2-x-1");
	polinomial2 = RPolynomial("x^10-5x^5+1");

	sum = polinomial + polinomial2;
	CHECK(sum.toString() == "x^10-4x^5-4x^4-9x^3+2x^2-x");
	sum = polinomial2 + polinomial;
	CHECK(sum.toString() == "x^10-4x^5-4x^4-9x^3+2x^2-x");
}


TEST_CASE("Substraction")
{
	RPolynomial polinomial = RPolynomial("-2-x-4x^4-9x^3+x^5+2x^2-1"),
		polinomial2 = RPolynomial("x^10-5x^5+1");

	auto sub = polinomial - polinomial2;
	CHECK(sub.toString() == "-x^10+6x^5-4x^4-9x^3+2x^2-x-4");

	polinomial = RPolynomial("-2-x-4x^4-7326738238625862586038757037503857353350098852685286358237253276358238625856382x^3+x^5+2x^2-1");
	polinomial2 = RPolynomial("-2-x-4x^4-7326738238625862586038757037503857353350098852685286358237253276358238625856382x^3+x^5+2x^2-1");

	sub = polinomial - polinomial2;
	CHECK(sub.toString() == "0");

	polinomial = RPolynomial("x^5-4x^4-9x^3+2x^2-x-1");
	polinomial2 = RPolynomial("x^10-5x^5+1");

	sub = polinomial - polinomial2;
	CHECK(sub.toString() == "-x^10+6x^5-4x^4-9x^3+2x^2-x-2");

	polinomial = RPolynomial("x^3+x^2");
	polinomial2 = RPolynomial("x^3+x");

	sub = polinomial - polinomial2;
	CHECK(sub.toString() == "x^2-x");

	polinomial = RPolynomial("x^3+5x^2");
	polinomial2 = RPolynomial("x^3+4x^2");

	sub = polinomial - polinomial2;
	CHECK(sub.toString() == "x^2");
}

TEST_CASE("Multiplication")
{
	RPolynomial polinomial = RPolynomial("-x^2+4"),
		polinomial2 = RPolynomial("6x^8+x");

	auto mult = polinomial * polinomial2;
	CHECK(mult.toString() == "-6x^10+24x^8-x^3+4x");
	mult = polinomial2 * polinomial;
	CHECK(mult.toString() == "-6x^10+24x^8-x^3+4x");

	polinomial = RPolynomial("-2-x-4x^4-9x^3+x^5+2x^2-1");
	polinomial2 = RPolynomial("x^10-5x^5+1");

	mult = polinomial * polinomial2;
	CHECK(mult.toString() == "x^15-4x^14-9x^13+2x^12-x^11-8x^10+20x^9+45x^8-10x^7+5x^6+16x^5-4x^4-9x^3+2x^2-x-3");
	mult = polinomial2 * polinomial;
	CHECK(mult.toString() == "x^15-4x^14-9x^13+2x^12-x^11-8x^10+20x^9+45x^8-10x^7+5x^6+16x^5-4x^4-9x^3+2x^2-x-3");

	polinomial = RPolynomial("x^5-4x^4-9x^3+2x^2-x-1");
	polinomial2 = RPolynomial("x^10-5x^5+1");

	mult = polinomial * polinomial2;
	CHECK(mult.toString() == "x^15-4x^14-9x^13+2x^12-x^11-6x^10+20x^9+45x^8-10x^7+5x^6+6x^5-4x^4-9x^3+2x^2-x-1");
	mult = polinomial2 * polinomial;
	CHECK(mult.toString() == "x^15-4x^14-9x^13+2x^12-x^11-6x^10+20x^9+45x^8-10x^7+5x^6+6x^5-4x^4-9x^3+2x^2-x-1");
}


//Test implementation by V.Horbanov
TEST_CASE("Division")
{
	RPolynomial pol1 = RPolynomial("x^3+5x^2-2x-6"), 
				pol2 = RPolynomial("x+1");

	auto res = pol1 / pol2;
	CHECK(res.toString() == "x^2+4x-6");


	pol1 = RPolynomial("x^3-4x^2+5");
	pol2 = RPolynomial("9x^3+x+1");
	res = pol1 / pol2;
	CHECK(res.toString() == "0");

	pol1 = RPolynomial("x^15-4x^14-9x^13+2x^12-x^11-6x^10+20x^9+45x^8-10x^7+5x^6+6x^5-4x^4-9x^3+2x^2-x-1");
	pol2 = RPolynomial("-4x^14-9x^13+2x^12-x^11-6x^10+20x^9+45x^8-10x^7+5x^6+6x^5-4x^4-9x^3+2x^2-x-1");
	res = pol1 / pol2;
	CHECK(res.toString() == "0");

	pol1 = RPolynomial("x^3+x^2");
	pol2 = RPolynomial("x^2+1");
	res = pol1 / pol2;
	CHECK(res.toString() == "x+1");

	pol1 = RPolynomial("x^3+5x^2-2x-6");
	pol2 = RPolynomial("x+4");
	res = pol1 / pol2;
	CHECK(res.toString() == "x^2+x-6");
}

TEST_CASE("Remainder")
{
	RPolynomial pol1 = RPolynomial("3x^3+2x^2-3x-5"),
				pol2 = RPolynomial("x+4");

	auto res = pol1 % pol2;
	CHECK(res.toString() == "-153");

	pol1 = RPolynomial("x^3-4x^2+5");
	pol2 = RPolynomial("9x^3+x+1");
	res = pol1 % pol2;
	CHECK(res.toString() == "x^3-4x^2+5");

	pol1 = RPolynomial("x^15-4x^14-9x^13+2x^12-x^11-6x^10+20x^9+45x^8-10x^7+5x^6+6x^5-4x^4-9x^3+2x^2-x-1");
	pol2 = RPolynomial("-4x^14-9x^13+2x^12-x^11-6x^10+20x^9+45x^8-10x^7+5x^6+6x^5-4x^4-9x^3+2x^2-x-1");
	res = pol1 % pol2;
	CHECK(res.toString() == "x^15-4x^14-9x^13+2x^12-x^11-6x^10+20x^9+45x^8-10x^7+5x^6+6x^5-4x^4-9x^3+2x^2-x-1");

	pol1 = RPolynomial("x^3+x^2");
	pol2 = RPolynomial("x^2+1");
	res = pol1 % pol2;
	CHECK(res.toString() == "-x-1");

	pol1 = RPolynomial("x^3+5x^2-2x-6");
	pol2 = RPolynomial("x+4");
	res = pol1 % pol2;
	CHECK(res.toString() == "18");
}


TEST_CASE("GCD") 
{
	//RPolynomial pol1 = RPolynomial("x^2+11x+28"),
	//			pol2 = RPolynomial("x^2+8x+7");

	//RPolynomial res = RPolynomial::GCD(pol1, pol2);
	//CHECK(res.toString() == "x+7");
	///*auto res = RPolynomial::GCD(pol1, pol2);
	//CHECK(res.toString() == "x^2+4x-6");
	//*/
	//
	//pol1 = RPolynomial("x^3+5x^2-2x-6"),
	//pol2 = RPolynomial("x+4");
	//res = RPolynomial::GCD(pol1, pol2);
	//CHECK(res.toString() == "1");
	RPolynomial pol1 = RPolynomial("x^3+5x^2-2x-6"),
		pol2 = RPolynomial("x^2+4x-6");

	auto res = RPolynomial::GCD(pol1, pol2);
	CHECK(res.toString() == "x^2+4x-6");


	pol1 = RPolynomial("x^3+5x^2-2x-6"),
	pol2 = RPolynomial("x+4");
	res = RPolynomial::GCD(pol1, pol2);
	CHECK(res.toString() == "1");

	pol1 = RPolynomial("x^3+20x^2+127x+252"),
	pol2 = RPolynomial("x^3+17x^2+79x+63");
	res = RPolynomial::GCD(pol1, pol2);
	CHECK(res.toString() == "x^2+16x+63");

	pol1 = RPolynomial("x^2-2x+1"),
	pol2 = RPolynomial("x-1");
	res = RPolynomial::GCD(pol1, pol2);
	CHECK(res.toString() == "x-1");

	pol1 = RPolynomial("x^2+11x+28"),
	pol2 = RPolynomial("x^2+8x+7");
	res = RPolynomial::GCD(pol1, pol2);
	CHECK(res.toString() == "x+7");

}
