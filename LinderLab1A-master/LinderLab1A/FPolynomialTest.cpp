#include "doctest.h"

#include "FPolynomial.h"
#include "PositiveNumber.h"

#include <string>

// Implemented by Y. Kishchuk
TEST_SUITE("FPolynomial")
{
	TEST_CASE("Addition")
	{
		FPolynomial fpol1("x^5+4x^4+9x^3+2x^2+x+1", PositiveNumber("5")), fpol2("x^10+5x^5+1", PositiveNumber("5"));

		std::cout << fpol1.toString() << "   " << fpol2.toString() << "\n";

		auto sum = fpol1 + fpol2;
		CHECK(sum.toString() == "x^10+x^5+4x^4+4x^3+2x^2+x+2");

		fpol1 = FPolynomial("x^5-4x^4-9x^3+2x^2-x-1", PositiveNumber(5));
		fpol2 = FPolynomial("x^10-5x^5+1", PositiveNumber(5));
		
		sum = fpol1 + fpol2;
		CHECK(sum.toString() == "x^10+x^5+x^4+x^3+2x^2+4");
	}
}

