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

		auto D = fpol2.toString();

		sub = fpol1 - fpol2;
		D = sub.toString();
		CHECK(sub.toString() == "x^10+4x^5+4x^4+4x^3+3x^2+x+2");

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

	//TEST_CASE("Normalization")
	//{
	//	std::ifstream f;
	//	f.open("../FPolynomial/Normalization.txt");
	//	std::string polinomial1Str;


	//	f >> polinomial1Str;
	//		FPolynomial fpol(polinomial1Str, PositiveNumber("7"));
	//	CHECK(fpol.Normalized().toString() == "x^2+4x+6");
	//	f >> polinomial1Str;

	//	fpol = FPolynomial(polinomial1Str, PositiveNumber("11"));
	//	CHECK(fpol.Normalized().toString() == "x^5+4x^4+9x^3+2x^2+x+1");
	//	f >> polinomial1Str;

	//	fpol = FPolynomial(polinomial1Str, PositiveNumber("11"));
	//	CHECK(fpol.Normalized().toString() == "x^5+2x^4+4x^3+x^2+3x");
	//	f >> polinomial1Str;

	//	fpol = FPolynomial(polinomial1Str, PositiveNumber("11"));
	//	CHECK(fpol.Normalized().toString() == "x^5+3x^4+6x^3+7x^2+10x+9");
	//	f.close();
	//}


	//TEST_CASE("Fast Exponentiation")
	//{
	//	std::ifstream f;
	//	f.open("../FPolynomial/Fast Exponentiation.txt");
	//	std::string polinomial1Str;
	//	f >> polinomial1Str;
	//	FPolynomial fpol(polinomial1Str, PositiveNumber("11"));

	//	CHECK(fpol.fastExponentiation(PositiveNumber("3")).toString() == "7x^3+7x^2+6x+8");
	//	CHECK(fpol.fastExponentiation(PositiveNumber("5")).toString() == "10x^5+2x^4+5x^3+9x^2+7x+10");
	//	f >> polinomial1Str;

	//	FPolynomial fpol2(polinomial1Str, PositiveNumber("154"));
	//	CHECK(fpol2.fastExponentiation(PositiveNumber("5")).toString() == "21x^15+112x^13+140x^12+126x^11+84x^10+56x^9+42x^8+98x^7+28x^6+132x^5+122x^4+114x^3+108x^2+18x+32");		
	//	CHECK(fpol2.fastExponentiation(PositiveNumber("0")).toString() == "1");
	//}

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

	//Implemented by V.Avramenko

	//A custom testing format for division\remainder until someone can manually create test samples for normal tests
	TEST_CASE("Combined Division and Remainder Test") {
		FPolynomial f1 = FPolynomial("x^3+5x^2-2x-6", PositiveNumber("7"));
		FPolynomial f2 = FPolynomial("x^2+4x-6", PositiveNumber("7"));
		FPolynomial quotient = f1 / f2;
		FPolynomial actual_remainder = f1 - quotient * f2;
		FPolynomial tested_remainder = f1 % f2;
		CHECK(tested_remainder.toString() == actual_remainder.toString());
		f1 = FPolynomial("x^5+5x^2-2x-6", PositiveNumber("7"));
		f2 = FPolynomial("x^5+4x^2-6", PositiveNumber("7"));
		quotient = f1 / f2;
		actual_remainder = f1 - quotient * f2;
		tested_remainder = f1 % f2;
		CHECK(tested_remainder.toString() == actual_remainder.toString());
		f1 = FPolynomial("x^2+11x+28", PositiveNumber("29"));
		f2 = FPolynomial("x^2+8x+7", PositiveNumber("29"));
		quotient = f1 / f2;
		actual_remainder = f1 - quotient * f2;
		tested_remainder = f1 % f2;
		CHECK(tested_remainder.toString() == actual_remainder.toString());
		f1 = FPolynomial("x^6-1", PositiveNumber("5"));
		f2 = FPolynomial("x^3-1", PositiveNumber("5"));
		quotient = f1 / f2;
		actual_remainder = f1 - quotient * f2;
		tested_remainder = f1 % f2;
		CHECK(tested_remainder.toString() == actual_remainder.toString());
		//Tests by T.Pysarenkov for kind of greater degrees and some smaller ones
		f1 = FPolynomial("x^4 + x^3 + 2*x^2 + 1", PositiveNumber("5"));
		f2 = FPolynomial("3*x^2 + 5*x + 1", PositiveNumber("5"));
		CHECK((f1 / f2).toString() == "2x^2+2x");
		CHECK((f1 % f2).toString() == "3x+1");
		f2 = FPolynomial("0", PositiveNumber("5"));
		CHECK_THROWS_AS(f1 / f2, std::invalid_argument);
		f1 = FPolynomial("17*x^16 + 13*x^15 - 10*x^12 + 34*x^8 - x^2", PositiveNumber("11"));
		f2 = FPolynomial("10*x^14 + 9*x^11 - x^3 + 1", PositiveNumber("11"));
		CHECK((f1 / f2).toString() == "5x^2+9x");
		CHECK((f1 % f2).toString() == "10x^13+8x^12+x^8+5x^5+9x^4+5x^2+2x");
		f1 = FPolynomial("x^29 - 1*x^25 + 27*x^22 - 17*x^16 + 13*x^15 - 10*x^12 + 34*x^8 - x^2", PositiveNumber("17"));
		f2 = FPolynomial("3*x^19 - 10*x^14 + 9*x^11 - x^3 + 1", PositiveNumber("17"));
		CHECK((f1 / f2).toString() == "6x^10+11x^6+3x^5+9x^3+16x^2+14x+10");
		CHECK((f1 % f2).toString() == "8x^17+14x^16+2x^14+15x^13+12x^11+11x^10+11x^9+3x^8+15x^6+13x^5+14x^4+x^3+3x+7");
		f1 = FPolynomial("x^29 - 1*x^25 + 27*x^22 - 17*x^16 + 13*x^15 - 10*x^12 + 34*x^8 - x^2", PositiveNumber("7"));
		f2 = FPolynomial("3*x^19 - 10*x^14 + 9*x^11 - x^3 + 1", PositiveNumber("7"));
		CHECK((f1 / f2).toString() == "5x^10+2x^6+5x^5+2x^3+6x^2+2x+5");
		CHECK((f1 % f2).toString() == "2x^17+5x^16+5x^15+4x^14+4x^11+2x^10+2x^9+4x^8+x^5+2x^4+3x^3+5x+2");
	}
	//Works fine so far :)

	//Test for Cyclotomic function in FPolynomial
	TEST_CASE("Cyclotomic") {
		FiniteField field(PositiveNumber("7"));
		FPolynomial test = FPolynomial::cyclotomic(PositiveNumber("25"), field);
		std::string DEBUG = test.toString();
		CHECK(test.toString() == "x^20+x^15+x^10+x^5+1");
		test = FPolynomial::cyclotomic(PositiveNumber("2"), field);
		DEBUG = test.toString();
		CHECK(test.toString() == "x+1");
		test = FPolynomial::cyclotomic(PositiveNumber("3"), field);
		DEBUG = test.toString();
		CHECK(test.toString() == "x^2+x+1");
		test = FPolynomial::cyclotomic(PositiveNumber("6"), field);
		DEBUG = test.toString();
		CHECK(test.toString() == "x^2+6x+1");
		test = FPolynomial::cyclotomic(PositiveNumber("7"), field);
		DEBUG = test.toString();
		CHECK(test.toString() == "x^6+x^5+x^4+x^3+x^2+x+1");
		test = FPolynomial::cyclotomic(PositiveNumber("12"), field);
		DEBUG = test.toString();
		CHECK(test.toString() == "x^4+6x^2+1");
		test = FPolynomial::cyclotomic(PositiveNumber("16"), field);
		DEBUG = test.toString();
		CHECK(test.toString() == "x^8+1");
		test = FPolynomial::cyclotomic(PositiveNumber("30"), field);
		DEBUG = test.toString();
		CHECK(test.toString() == "x^8+x^7+6x^5+6x^4+6x^3+x+1");
		test = FPolynomial::cyclotomic(PositiveNumber("105"), field);
		DEBUG = test.toString();
		CHECK(test.toString() == "x^48+x^47+x^46+6x^43+6x^42+5x^41+6x^40+6x^39+x^36+x^35+x^34+x^33+x^32+x^31+6x^28+6x^26+6x^24+6x^22+6x^20+x^17+x^16+x^15+x^14+x^13+x^12+6x^9+6x^8+5x^7+6x^6+6x^5+x^2+x+1");
	}
}