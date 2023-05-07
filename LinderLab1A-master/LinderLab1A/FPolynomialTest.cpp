#include "doctest.h"

#include "FPolynomial.h"
#include "PositiveNumber.h"

#include <string>
#include <fstream>
// Implemented by Y. Kishchuk
TEST_SUITE("FPolynomial")
{
	TEST_CASE("Addition")
	{
		std::ifstream f;
		f.open("../FPolynomial/Addition.txt");
		std::string polinomial1Str, polinomial2Str;
		std::string mod;
		f >> mod;
	
		f >> polinomial1Str >> polinomial2Str;
		FPolynomial fpol1(polinomial1Str, PositiveNumber(mod)), fpol2(polinomial2Str, PositiveNumber(mod));
		auto sum = fpol1 + fpol2;
		CHECK(sum.toString() == "x^10+2x^5+4x^4+3");
		sum = fpol2 + fpol1;
		CHECK(sum.toString() == "x^10+2x^5+4x^4+3");
		f >> polinomial1Str >> polinomial2Str;
		fpol1 = FPolynomial(polinomial1Str, PositiveNumber(mod));
		fpol2 = FPolynomial(polinomial2Str, PositiveNumber(mod));

		sum = fpol1 + fpol2;
		CHECK(sum.toString() == "x^10+x^5+4x^4+4x^3+2x^2+x+2");
		sum = fpol2 + fpol1;
		CHECK(sum.toString() == "x^10+x^5+4x^4+4x^3+2x^2+x+2");
		f >> polinomial1Str >> polinomial2Str;
		fpol1 = FPolynomial(polinomial1Str, PositiveNumber(mod));
		fpol2 = FPolynomial(polinomial2Str, PositiveNumber(mod));
		
		sum = fpol1 + fpol2;
		CHECK(sum.toString() == "x^10+x^5+x^4+x^3+2x^2+4x");
		sum = fpol2 + fpol1;
		CHECK(sum.toString() == "x^10+x^5+x^4+x^3+2x^2+4x");
		f.close();
	}

	TEST_CASE("Substraction")
	{
		std::ifstream f;
		f.open("../FPolynomial/Substraction.txt");
		std::string polinomial1Str, polinomial2Str;
		std::string mod;
		f >> mod;

		f >> polinomial1Str >> polinomial2Str;
		FPolynomial fpol1(polinomial1Str, PositiveNumber(mod)), fpol2(polinomial2Str, PositiveNumber(mod));

		auto sub = fpol1 - fpol2;
		CHECK(sub.toString() == "4x^10+x^5+4x^4+4x^3+2x^2+x");
		f >> polinomial1Str >> polinomial2Str;

		fpol1 = FPolynomial(polinomial1Str, PositiveNumber(mod));
		fpol2 = FPolynomial(polinomial2Str, PositiveNumber(mod));

		sub = fpol1 - fpol2;
		CHECK(sub.toString() == "x^10+4x^5+4x^4+4x^3+3x^2+x+3");
		f.close();
	}

	TEST_CASE("Multiplication")
	{
		std::ifstream f;
		f.open("../FPolynomial/Multiplication.txt");
		std::string polinomial1Str, polinomial2Str;
		std::string mod;
		f >> mod;

		f >> polinomial1Str >> polinomial2Str;
		FPolynomial fpol1(polinomial1Str, PositiveNumber(mod)), fpol2(polinomial2Str, PositiveNumber(mod));

		auto mult = fpol1 * fpol2;
		CHECK(mult.toString() == "x^15+4x^14+4x^13+2x^12+x^11+x^10+x^5+4x^4+4x^3+2x^2+x+1");
		mult = fpol2 * fpol1;
		CHECK(mult.toString() == "x^15+4x^14+4x^13+2x^12+x^11+x^10+x^5+4x^4+4x^3+2x^2+x+1");
		f >> polinomial1Str >> polinomial2Str;

		fpol1 = FPolynomial(polinomial1Str, PositiveNumber(mod));
		fpol2 = FPolynomial(polinomial2Str, PositiveNumber(mod));

		mult = fpol1 * fpol2;
		CHECK(mult.toString() == "x^15+x^14+x^13+2x^12+4x^11+4x^10+x^5+x^4+x^3+2x^2+4x+4");
		mult = fpol2 * fpol1;
		CHECK(mult.toString() == "x^15+x^14+x^13+2x^12+4x^11+4x^10+x^5+x^4+x^3+2x^2+4x+4");
		f.close();
	}

	TEST_CASE("Normalization")
	{
		std::ifstream f;
		f.open("../FPolynomial/Normalization.txt");
		std::string polinomial1Str;


		f >> polinomial1Str;
			FPolynomial fpol(polinomial1Str, PositiveNumber("7"));
		CHECK(fpol.Normalized().toString() == "x^2+4x+6");
		f >> polinomial1Str;

		fpol = FPolynomial(polinomial1Str, PositiveNumber("11"));
		CHECK(fpol.Normalized().toString() == "x^5+4x^4+9x^3+2x^2+x+1");
		f >> polinomial1Str;

		fpol = FPolynomial(polinomial1Str, PositiveNumber("11"));
		CHECK(fpol.Normalized().toString() == "x^5+2x^4+4x^3+x^2+3x");
		f >> polinomial1Str;

		fpol = FPolynomial(polinomial1Str, PositiveNumber("11"));
		CHECK(fpol.Normalized().toString() == "x^5+3x^4+6x^3+7x^2+10x+9");
		f.close();
	}


	TEST_CASE("Fast Exponentiation")
	{
		std::ifstream f;
		f.open("../FPolynomial/Fast Exponentiation.txt");
		std::string polinomial1Str;
		f >> polinomial1Str;
		FPolynomial fpol(polinomial1Str, PositiveNumber("11"));

		CHECK(fpol.fastExponentiation(PositiveNumber("3")).toString() == "7x^3+7x^2+6x+8");
		CHECK(fpol.fastExponentiation(PositiveNumber("5")).toString() == "10x^5+2x^4+5x^3+9x^2+7x+10");
		f >> polinomial1Str;

		FPolynomial fpol2(polinomial1Str, PositiveNumber("154"));
		CHECK(fpol2.fastExponentiation(PositiveNumber("5")).toString() == "21x^15+112x^13+140x^12+126x^11+84x^10+56x^9+42x^8+98x^7+28x^6+132x^5+122x^4+114x^3+108x^2+18x+32");		
		CHECK(fpol2.fastExponentiation(PositiveNumber("0")).toString() == "1");
	}
}