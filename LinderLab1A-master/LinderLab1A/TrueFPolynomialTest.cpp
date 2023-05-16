#include "TrueFPolynomial.h"

#include "doctest.h"


TEST_SUITE("TrueFPolynomial")
{
	TEST_CASE("Multuplication")
	{
		FPolynomial irr("x^3+2x+1", 3);
		TrueFPolynomial p1("2x^2+1", irr);
		TrueFPolynomial p2("2x+2", irr);

		FPolynomial irr2("x^3+x+1", 2);
		TrueFPolynomial p12("x^2+1", irr2);
		TrueFPolynomial p22("x^2", irr2);
		CHECK((p12 * p22).toString() == "x");
	};

	TEST_CASE("Fast_Exp")
	{
		FPolynomial irr("x^3+x+1", 2);
		TrueFPolynomial p1("x+1", irr);
		TrueFPolynomial p2("x+1", irr);
		const int degree = 15;
		for (int i = 1; i < degree; i++)
		{
			p2 = p2 * p1;
		}

		CHECK(p1.fastExponentiation(degree).toString() == p2.toString());
	}
}