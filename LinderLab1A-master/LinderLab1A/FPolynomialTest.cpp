#include "doctest.h"

#include "FPolynomial.h"
#include "PositiveNumber.h"

#include <string>

// Implemented by Y. Kishchuk
TEST_SUITE("FPolynomial")
{
	TEST_CASE("Addition")
	{
		FPolynomial fpol1("x^5+4x^4-3", PositiveNumber("5")), fpol2("x^10+6x^5+1", PositiveNumber("5"));
		auto sum = fpol1 + fpol2;
		CHECK(sum.toString() == "x^10+2x^5+4x^4+3");
		sum = fpol2 + fpol1;
		CHECK(sum.toString() == "x^10+2x^5+4x^4+3");

		fpol1 = FPolynomial("x^5+4x^4+9x^3+2x^2+x+1", PositiveNumber("5"));
		fpol2 = FPolynomial("x^10+5x^5+1", PositiveNumber("5"));

		sum = fpol1 + fpol2;
		CHECK(sum.toString() == "x^10+x^5+4x^4+4x^3+2x^2+x+2");
		sum = fpol2 + fpol1;
		CHECK(sum.toString() == "x^10+x^5+4x^4+4x^3+2x^2+x+2");

		fpol1 = FPolynomial("x^5-4x^4-9x^3+2x^2-x-1", PositiveNumber("5"));
		fpol2 = FPolynomial("x^10-5x^5+1", PositiveNumber("5"));
		
		sum = fpol1 + fpol2;
		CHECK(sum.toString() == "x^10+x^5+x^4+x^3+2x^2+4x");
		sum = fpol2 + fpol1;
		CHECK(sum.toString() == "x^10+x^5+x^4+x^3+2x^2+4x");
	}

	TEST_CASE("Substraction")
	{
		FPolynomial fpol1("x^5+4x^4+9x^3+2x^2+x+1", PositiveNumber("5")), fpol2("x^10+5x^5+1", PositiveNumber("5"));

		auto sub = fpol1 - fpol2;
		CHECK(sub.toString() == "4x^10+x^5+4x^4+4x^3+2x^2+x");

		/*fpol1 = FPolynomial("x^10-5x^5+1", PositiveNumber("5"));
		fpol2 = FPolynomial("x^5-4x^4-9x^3+2x^2-x-1", PositiveNumber("5"));

		sub = fpol1 - fpol2;
		CHECK(sub.toString() == "x^10+4x^5+4x^4+4x^3+3x^2+x+3");*/
		fpol1 = FPolynomial("x^10-5x^5+1", PositiveNumber("5"));
		fpol2 = FPolynomial("x^5-4x^4-4x^3+2x^2-x-1", PositiveNumber("5"));
		auto D = fpol2.toString();

		sub = fpol1 - fpol2;
		D = sub.toString();
		CHECK(sub.toString() == "x^10+4x^5+4x^4+4x^3+3x^2+x+2");
	}

	TEST_CASE("Multiplication")
	{
		FPolynomial fpol1("x^5+4x^4+9x^3+2x^2+x+1", PositiveNumber("5")), fpol2("x^10+5x^5+1", PositiveNumber("5"));

		auto mult = fpol1 * fpol2;
		CHECK(mult.toString() == "x^15+4x^14+4x^13+2x^12+x^11+x^10+x^5+4x^4+4x^3+2x^2+x+1");
		mult = fpol2 * fpol1;
		CHECK(mult.toString() == "x^15+4x^14+4x^13+2x^12+x^11+x^10+x^5+4x^4+4x^3+2x^2+x+1");

		fpol1 = FPolynomial("x^10-5x^5+1", PositiveNumber("5"));
		fpol2 = FPolynomial("x^5-4x^4-9x^3+2x^2-x-1", PositiveNumber("5"));

		mult = fpol1 * fpol2;
		CHECK(mult.toString() == "x^15+x^14+x^13+2x^12+4x^11+4x^10+x^5+x^4+x^3+2x^2+4x+4");
		mult = fpol2 * fpol1;
		CHECK(mult.toString() == "x^15+x^14+x^13+2x^12+4x^11+4x^10+x^5+x^4+x^3+2x^2+4x+4");
	}

	TEST_CASE("Value at X")
	{
		FPolynomial fpol1("x^5+4x^4+9x^3+2x^2+x+1", PositiveNumber("5")), fpol2("x^10+5x^5+1", PositiveNumber("5"));
	
		CHECK(fpol1.valueAt(FiniteNumber("x5 4")).toString() == "1");
		CHECK(fpol1.valueAt(FiniteNumber("x5 1")).toString() == "3");
		CHECK(fpol1.valueAt(FiniteNumber("x5 2")).toString() == "4");

		CHECK(fpol2.valueAt(FiniteNumber("x5 1")).toString() == "2");
		CHECK(fpol2.valueAt(FiniteNumber("x5 2")).toString() == "0");
		CHECK(fpol2.valueAt(FiniteNumber("x5 0")).toString() == "1");
		CHECK(fpol2.valueAt(FiniteNumber("x5 3")).toString() == "0");

		CHECK(fpol1.derivative().toString() == "x^3+2x^2+4x+1");
		CHECK(fpol2.derivative().toString() == "0");
	}

	TEST_CASE("Division")
	{
		FPolynomial pol1 = FPolynomial("5x^2+4x+6", PositiveNumber("7")),
			pol2 = FPolynomial("2x+1", PositiveNumber("7"));

		auto res = pol1 / pol2;
		auto DEBUG = res.toString();
		CHECK(res.toString() == "6x+6");


		/*pol1 = FPolynomial("x^3-4x^2+5");
		pol2 = FPolynomial("9x^3+x+1");
		res = pol1 / pol2;
		CHECK(res.toString() == "0");

		pol1 = FPolynomial("x^15-4x^14-9x^13+2x^12-x^11-6x^10+20x^9+45x^8-10x^7+5x^6+6x^5-4x^4-9x^3+2x^2-x-1");
		pol2 = FPolynomial("-4x^14-9x^13+2x^12-x^11-6x^10+20x^9+45x^8-10x^7+5x^6+6x^5-4x^4-9x^3+2x^2-x-1");
		res = pol1 / pol2;
		CHECK(res.toString() == "0");

		pol1 = FPolynomial("x^3+x^2");
		pol2 = FPolynomial("x^2+1");
		res = pol1 / pol2;
		CHECK(res.toString() == "x+1");

		pol1 = FPolynomial("x^3+5x^2-2x-6");
		pol2 = FPolynomial("x+4");
		res = pol1 / pol2;
		CHECK(res.toString() == "x^2+x-6");*/
	}

	//TEST_CASE("Remainder")
	//{
	//	FPolynomial pol1 = FPolynomial("3x^3+2x^2-3x-5"),
	//		pol2 = FPolynomial("x+4");

	//	auto res = pol1 % pol2;
	//	CHECK(res.toString() == "-153");

	//	pol1 = FPolynomial("x^3-4x^2+5");
	//	pol2 = FPolynomial("9x^3+x+1");
	//	res = pol1 % pol2;
	//	CHECK(res.toString() == "x^3-4x^2+5");

	//	pol1 = FPolynomial("x^15-4x^14-9x^13+2x^12-x^11-6x^10+20x^9+45x^8-10x^7+5x^6+6x^5-4x^4-9x^3+2x^2-x-1");
	//	pol2 = FPolynomial("-4x^14-9x^13+2x^12-x^11-6x^10+20x^9+45x^8-10x^7+5x^6+6x^5-4x^4-9x^3+2x^2-x-1");
	//	res = pol1 % pol2;
	//	CHECK(res.toString() == "x^15-4x^14-9x^13+2x^12-x^11-6x^10+20x^9+45x^8-10x^7+5x^6+6x^5-4x^4-9x^3+2x^2-x-1");

	//	pol1 = FPolynomial("x^3+x^2");
	//	pol2 = FPolynomial("x^2+1");
	//	res = pol1 % pol2;
	//	CHECK(res.toString() == "-x-1");

	//	pol1 = FPolynomial("x^3+5x^2-2x-6");
	//	pol2 = FPolynomial("x+4");
	//	res = pol1 % pol2;
	//	CHECK(res.toString() == "18");
	//}


	//TEST_CASE("GCD")
	//{
	//	FPolynomial pol1 = FPolynomial("x^3+5x^2-2x-6"),
	//		pol2 = FPolynomial("x^2+4x-6");

	//	auto res = FPolynomial::GCD(pol1, pol2);
	//	CHECK(res.toString() == "x^2+4x-6");


	//	pol1 = FPolynomial("x^3+5x^2-2x-6"),
	//		pol2 = FPolynomial("x+4");
	//	res = FPolynomial::GCD(pol1, pol2);
	//	CHECK(res.toString() == "1");

	//	pol1 = FPolynomial("x^3+20x^2+127x+252"),
	//		pol2 = FPolynomial("x^3+17x^2+79x+63");
	//	res = FPolynomial::GCD(pol1, pol2);
	//	CHECK(res.toString() == "x^2+16x+63");

	//	pol1 = FPolynomial("x^2-2x+1"),
	//		pol2 = FPolynomial("x-1");
	//	res = FPolynomial::GCD(pol1, pol2);
	//	CHECK(res.toString() == "x-1");

	//	pol1 = FPolynomial("x^2+11x+28"),
	//		pol2 = FPolynomial("x^2+8x+7");
	//	res = FPolynomial::GCD(pol1, pol2);
	//	CHECK(res.toString() == "x+7");

	//}
}