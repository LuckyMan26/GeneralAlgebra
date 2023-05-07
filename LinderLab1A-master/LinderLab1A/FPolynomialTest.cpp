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

		fpol1 = FPolynomial("x^10-5x^5+1", PositiveNumber("5"));
		fpol2 = FPolynomial("x^5-4x^4-9x^3+2x^2-x-1", PositiveNumber("5"));

		sub = fpol1 - fpol2;
		CHECK(sub.toString() == "x^10+4x^5+4x^4+4x^3+3x^2+x+3");
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

	TEST_CASE("Normalization")
	{
			FPolynomial fpol("5x^2+6x+2", PositiveNumber("7"));
		CHECK(fpol.Normalized().toString() == "x^2+4x+6");

		fpol = FPolynomial("x^5+4x^4+9x^3+2x^2+x+1", PositiveNumber("11"));
		CHECK(fpol.Normalized().toString() == "x^5+4x^4+9x^3+2x^2+x+1");

		fpol = FPolynomial("2x^5+4x^4+8x^3+2x^2+6x", PositiveNumber("11"));
		CHECK(fpol.Normalized().toString() == "x^5+2x^4+4x^3+x^2+3x");

		fpol = FPolynomial("5x^5+4x^4+8x^3+2x^2+6x+1", PositiveNumber("11"));
		CHECK(fpol.Normalized().toString() == "x^5+3x^4+6x^3+7x^2+10x+9");
	}


	TEST_CASE("Fast Exponentiation")
	{
		FPolynomial fpol("6x+2", PositiveNumber("11"));

		CHECK(fpol.fastExponentiation(PositiveNumber("3")).toString() == "7x^3+7x^2+6x+8");
		CHECK(fpol.fastExponentiation(PositiveNumber("5")).toString() == "10x^5+2x^4+5x^3+9x^2+7x+10");

		FPolynomial fpol2("7x^3+6x+2", PositiveNumber("154"));
		CHECK(fpol2.fastExponentiation(PositiveNumber("5")).toString() == "21x^15+112x^13+140x^12+126x^11+84x^10+56x^9+42x^8+98x^7+28x^6+132x^5+122x^4+114x^3+108x^2+18x+32");		
		CHECK(fpol2.fastExponentiation(PositiveNumber("0")).toString() == "1");
	}
}