
#include "doctest.h"

#include "RPolynomial.h"

#include <random>
#include <string>
#include <chrono>
#include <fstream>

//Test and implementation by M. Tyshchenko
//Using Gorner rule
TEST_CASE("Value at X") {
	std::ifstream f;
	f.open("../RPolynomial/Value at X.txt");
	std::string polinomial1Str, polinomial2Str, polinomial3Str;
	f >> polinomial1Str >> polinomial2Str >> polinomial3Str;
	RPolynomial polinomial = RPolynomial(polinomial1Str);
	RPolynomial polinomial2 = RPolynomial(polinomial2Str);
	RPolynomial polinomial3 = RPolynomial(polinomial3Str);
	CHECK(polinomial.valueAt(SignedNumber("6")).toString() == "7776");
	CHECK(polinomial2.valueAt(SignedNumber("3")).toString() == "57835");
	CHECK(polinomial3.valueAt(SignedNumber("10")).toString() == "6");
	f.close();
}

//Test and implementation by M. Tyshchenko
TEST_CASE("Derivative") {
	std::ifstream f;
	f.open("../RPolynomial/Derivative.txt");
	std::string polinomial1Str, polinomial2Str, polinomial3Str;
	f >> polinomial1Str >> polinomial2Str >> polinomial3Str;

	RPolynomial polinomial = RPolynomial(polinomial1Str);
	RPolynomial polinomial2 = RPolynomial(polinomial2Str);
	RPolynomial polinomial3 = RPolynomial(polinomial3Str);

	CHECK(polinomial.toString() == "x^5-4x^4-9x^3+2x^2-x-3");
	CHECK(polinomial2.toString() == "x^10-5x^5+1");
	CHECK(polinomial3.toString() == "6");
	CHECK(polinomial.derivative().toString() == "5x^4-16x^3-27x^2+4x-1");
	CHECK(polinomial2.derivative().toString() == "10x^9-25x^4");
	CHECK(polinomial3.derivative().toString() == "0");
	f.close();
}

// Implemented by Y. Kishchuk
TEST_CASE("Addition")
{
	std::ifstream f;
	f.open("../RPolynomial/Addition.txt");
	std::string polinomial1Str, polinomial2Str, polinomial3Str;
	f >> polinomial1Str >> polinomial2Str;
	RPolynomial polinomial = RPolynomial(polinomial1Str),
	polinomial2 = RPolynomial(polinomial2Str);

	auto sum = polinomial + polinomial2;
	CHECK(sum.toString() == "x^3+x^2+1");
	sum = polinomial2 + polinomial;
	CHECK(sum.toString() == "x^3+x^2+1");
	f >> polinomial1Str >> polinomial2Str;

	polinomial = RPolynomial(polinomial1Str);
	polinomial2 = RPolynomial(polinomial2Str);

	sum = polinomial + polinomial2;
	CHECK(sum.toString() == "x^10-4x^5-4x^4-9x^3+2x^2-x-2");
	sum = polinomial2 + polinomial;
	CHECK(sum.toString() == "x^10-4x^5-4x^4-9x^3+2x^2-x-2");
	f >> polinomial1Str >> polinomial2Str;
	polinomial = RPolynomial(polinomial1Str);
	polinomial2 = RPolynomial(polinomial2Str);

	sum = polinomial + polinomial2;
	CHECK(sum.toString() == "0");
	sum = polinomial2 + polinomial;
	CHECK(sum.toString() == "0");
	f >> polinomial1Str >> polinomial2Str;
	polinomial = RPolynomial(polinomial1Str);
	polinomial2 = RPolynomial(polinomial2Str);

	sum = polinomial + polinomial2;
	CHECK(sum.toString() == "x^10-4x^5-4x^4-9x^3+2x^2-x");
	sum = polinomial2 + polinomial;
	CHECK(sum.toString() == "x^10-4x^5-4x^4-9x^3+2x^2-x");
	f.close();
}


TEST_CASE("Substraction")
{
	std::ifstream f;
	f.open("../RPolynomial/Substraction.txt");
	std::string polinomial1Str, polinomial2Str;
	f >> polinomial1Str >> polinomial2Str;
	RPolynomial polinomial = RPolynomial(polinomial1Str),
		polinomial2 = RPolynomial(polinomial2Str);

	auto sub = polinomial - polinomial2;
	CHECK(sub.toString() == "-x^10+6x^5-4x^4-9x^3+2x^2-x-4");
	f >> polinomial1Str >> polinomial2Str;
	polinomial = RPolynomial(polinomial1Str);
	polinomial2 = RPolynomial(polinomial2Str);

	sub = polinomial - polinomial2;
	CHECK(sub.toString() == "0");
	f >> polinomial1Str >> polinomial2Str;

	polinomial = RPolynomial(polinomial1Str);
	polinomial2 = RPolynomial(polinomial2Str);

	sub = polinomial - polinomial2;
	CHECK(sub.toString() == "-x^10+6x^5-4x^4-9x^3+2x^2-x-2");

	f >> polinomial1Str >> polinomial2Str;
	polinomial = RPolynomial(polinomial1Str);
	polinomial2 = RPolynomial(polinomial2Str);

	sub = polinomial - polinomial2;
	CHECK(sub.toString() == "x^2-x");
	f >> polinomial1Str >> polinomial2Str;
	polinomial = RPolynomial(polinomial1Str);
	polinomial2 = RPolynomial(polinomial2Str);

	sub = polinomial - polinomial2;
	CHECK(sub.toString() == "x^2");
	f.close();

}

TEST_CASE("Multiplication")
{
	std::ifstream f;
	f.open("../RPolynomial/Multiplication.txt");
	std::string polinomial1Str, polinomial2Str;
	f >> polinomial1Str >> polinomial2Str;
	RPolynomial polinomial = RPolynomial(polinomial1Str),
		polinomial2 = RPolynomial(polinomial2Str);

	auto mult = polinomial * polinomial2;
	CHECK(mult.toString() == "-6x^10+24x^8-x^3+4x");
	mult = polinomial2 * polinomial;
	CHECK(mult.toString() == "-6x^10+24x^8-x^3+4x");
	f >> polinomial1Str >> polinomial2Str;
	polinomial = RPolynomial(polinomial1Str);
	polinomial2 = RPolynomial(polinomial2Str);

	mult = polinomial * polinomial2;
	CHECK(mult.toString() == "x^15-4x^14-9x^13+2x^12-x^11-8x^10+20x^9+45x^8-10x^7+5x^6+16x^5-4x^4-9x^3+2x^2-x-3");
	mult = polinomial2 * polinomial;
	CHECK(mult.toString() == "x^15-4x^14-9x^13+2x^12-x^11-8x^10+20x^9+45x^8-10x^7+5x^6+16x^5-4x^4-9x^3+2x^2-x-3");
	f >> polinomial1Str >> polinomial2Str;
	polinomial = RPolynomial(polinomial1Str);
	polinomial2 = RPolynomial(polinomial2Str);

	mult = polinomial * polinomial2;
	CHECK(mult.toString() == "x^15-4x^14-9x^13+2x^12-x^11-6x^10+20x^9+45x^8-10x^7+5x^6+6x^5-4x^4-9x^3+2x^2-x-1");
	mult = polinomial2 * polinomial;
	CHECK(mult.toString() == "x^15-4x^14-9x^13+2x^12-x^11-6x^10+20x^9+45x^8-10x^7+5x^6+6x^5-4x^4-9x^3+2x^2-x-1");

	f.close();

}


//Test implementation by V.Horbanov
TEST_CASE("Division")
{


	std::ifstream f;
	f.open("../RPolynomial/Division.txt");
	std::string polinomial1Str, polinomial2Str;
	f >> polinomial1Str >> polinomial2Str;
	RPolynomial pol1 = RPolynomial(polinomial1Str),
				pol2 = RPolynomial(polinomial2Str);


	auto res = pol1 / pol2;
	CHECK(res.toString() == "x^2+4x-6");

	f >> polinomial1Str >> polinomial2Str;
	pol1 = RPolynomial(polinomial1Str);
	pol2 = RPolynomial(polinomial2Str);
	res = pol1 / pol2;
	CHECK(res.toString() == "0");
	f >> polinomial1Str >> polinomial2Str;

	pol1 = RPolynomial(polinomial1Str);
	pol2 = RPolynomial(polinomial2Str);
	res = pol1 / pol2;
	CHECK(res.toString() == "0");
	f >> polinomial1Str >> polinomial2Str;
	pol1 = RPolynomial(polinomial1Str);
	pol2 = RPolynomial(polinomial2Str);
	res = pol1 / pol2;
	CHECK(res.toString() == "x+1");
	f >> polinomial1Str >> polinomial2Str;
	pol1 = RPolynomial(polinomial1Str);
	pol2 = RPolynomial(polinomial2Str);
	res = pol1 / pol2;
	CHECK(res.toString() == "x^2+x-6");
	f.close();

}

TEST_CASE("Remainder")
{

	std::ifstream f;
	f.open("../RPolynomial/Remainder.txt");
	std::string polinomial1Str, polinomial2Str;
	f >> polinomial1Str >> polinomial2Str;
	RPolynomial pol1 = RPolynomial(polinomial1Str),
				pol2 = RPolynomial(polinomial2Str);

	auto res = pol1 % pol2;
	CHECK(res.toString() == "-153");
	f >> polinomial1Str >> polinomial2Str;
	pol1 = RPolynomial(polinomial1Str);
	pol2 = RPolynomial(polinomial2Str);
	res = pol1 % pol2;
	CHECK(res.toString() == "x^3-4x^2+5");
	f >> polinomial1Str >> polinomial2Str;
	pol1 = RPolynomial(polinomial1Str);
	pol2 = RPolynomial(polinomial2Str);
	res = pol1 % pol2;
	CHECK(res.toString() == "x^15-4x^14-9x^13+2x^12-x^11-6x^10+20x^9+45x^8-10x^7+5x^6+6x^5-4x^4-9x^3+2x^2-x-1");
	f >> polinomial1Str >> polinomial2Str;
	pol1 = RPolynomial(polinomial1Str);
	pol2 = RPolynomial(polinomial2Str);
	res = pol1 % pol2;
	CHECK(res.toString() == "-x-1");
	f >> polinomial1Str >> polinomial2Str;

	pol1 = RPolynomial(polinomial1Str);
	pol2 = RPolynomial(polinomial2Str);
	res = pol1 % pol2;
	CHECK(res.toString() == "18");
	f.close();

}


TEST_CASE("GCD") 
{

	std::ifstream f;
	f.open("../RPolynomial/GCD.txt");
	std::string polinomial1Str, polinomial2Str;
	f >> polinomial1Str >> polinomial2Str;
	RPolynomial pol1 = RPolynomial(polinomial1Str),
		pol2 = RPolynomial(polinomial2Str);

	auto res = RPolynomial::GCD(pol1, pol2);
	CHECK(res.toString() == "x^2+4x-6");

	f >> polinomial1Str >> polinomial2Str;

	pol1 = RPolynomial(polinomial1Str),
	pol2 = RPolynomial(polinomial2Str);
	res = RPolynomial::GCD(pol1, pol2);
	CHECK(res.toString() == "1");
	f >> polinomial1Str >> polinomial2Str;
	pol1 = RPolynomial(polinomial1Str),
	pol2 = RPolynomial(polinomial2Str);
	res = RPolynomial::GCD(pol1, pol2);
	CHECK(res.toString() == "x^2+16x+63");
	f >> polinomial1Str >> polinomial2Str;
	pol1 = RPolynomial(polinomial1Str),
	pol2 = RPolynomial(polinomial2Str);
	res = RPolynomial::GCD(pol1, pol2);
	CHECK(res.toString() == "x-1");
	f >> polinomial1Str >> polinomial2Str;
	pol1 = RPolynomial(polinomial1Str),
	pol2 = RPolynomial(polinomial2Str);
	res = RPolynomial::GCD(pol1, pol2);
	CHECK(res.toString() == "x+7");
	f.close();


}

TEST_CASE("Cyclotomic") {
	RPolynomial test = RPolynomial::cyclotomic(PositiveNumber("25"));
	std::string DEBUG = test.toString();
	CHECK(test.toString() == "x^20+x^15+x^10+x^5+1");
	test = RPolynomial::cyclotomic(PositiveNumber("2"));
	DEBUG = test.toString();
	CHECK(test.toString() == "x+1");
	test = RPolynomial::cyclotomic(PositiveNumber("3"));
	DEBUG = test.toString();
	CHECK(test.toString() == "x^2+x+1");
	test = RPolynomial::cyclotomic(PositiveNumber("6"));
	DEBUG = test.toString();
	CHECK(test.toString() == "x^2-x+1");
	test = RPolynomial::cyclotomic(PositiveNumber("7"));
	DEBUG = test.toString();
	CHECK(test.toString() == "x^6+x^5+x^4+x^3+x^2+x+1");
	test = RPolynomial::cyclotomic(PositiveNumber("12"));
	DEBUG = test.toString();
	CHECK(test.toString() == "x^4-x^2+1");
	test = RPolynomial::cyclotomic(PositiveNumber("16"));
	DEBUG = test.toString();
	CHECK(test.toString() == "x^8+1");
	test = RPolynomial::cyclotomic(PositiveNumber("30"));
	DEBUG = test.toString();
	CHECK(test.toString() == "x^8+x^7-x^5-x^4-x^3+x+1");
	test = RPolynomial::cyclotomic(PositiveNumber("105"));
	DEBUG = test.toString();
	CHECK(test.toString() == "x^48+x^47+x^46-x^43-x^42-2x^41-x^40-x^39+x^36+x^35+x^34+x^33+x^32+x^31-x^28-x^26-x^24-x^22-x^20+x^17+x^16+x^15+x^14+x^13+x^12-x^9-x^8-2x^7-x^6-x^5+x^2+x+1");


}