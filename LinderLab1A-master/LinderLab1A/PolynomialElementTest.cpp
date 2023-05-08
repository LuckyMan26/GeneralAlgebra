#include "doctest.h"


#include "PolynomialElement.h"
#include "SignedNumber.h"
#include "FiniteNumber.h"
#include <fstream>

TEST_SUITE("PolynomialElement")
{
	TEST_CASE("Addition")
	{
		SUBCASE("SignedNumber")
		{
			std::ifstream f;
			f.open("../PolynomialElement/AdditionSignedNumber.txt");
			std::string elem1StrS;
			std::string elem1StrP;
			std::string elem2StrS;
			std::string elem2StrP;
			f >> elem1StrS >> elem1StrP >> elem2StrS >> elem2StrP;
			PositiveNumber deg1 = PositiveNumber(elem1StrP);
			PositiveNumber deg2 = PositiveNumber(elem2StrP);
			PolynomialElement<SignedNumber> elem1(SignedNumber(elem1StrS), deg1);
			PolynomialElement<SignedNumber>	elem2(SignedNumber(elem2StrS), deg2);


			PolynomialElement<SignedNumber> res = elem1 + elem2;
			auto coef = res.getCoefficient();
			CHECK(SignedNumber("7326738238625862586038756104830033490763840200000000000000000000000000000000000") == coef);
			auto deg = res.getDegree();
			CHECK(PositiveNumber("8545475848486794864479494204829847289469726479267526546254625462424242") == deg);
		}
		SUBCASE("FiniteNumber")
		{
			std::ifstream f;
			f.open("../PolynomialElement/AdditionFiniteNumber.txt");
			std::string elem1StrS;
			std::string elem1StrP;
			std::string elem2StrS;
			std::string elem2StrP;
			getline(f, elem1StrS);
			getline(f, elem1StrP);
			getline(f, elem2StrS);
			getline(f, elem2StrP);
			PositiveNumber deg1 = PositiveNumber(elem1StrP);
			PositiveNumber deg2 = PositiveNumber(elem2StrP);
		
			PolynomialElement<FiniteNumber> elem1(FiniteNumber(elem1StrS), deg1),
				elem2(FiniteNumber(elem2StrS), deg2);

			PolynomialElement<FiniteNumber> res = elem1 + elem2;
			auto coef = res.getCoefficient();
			CHECK("15115042928469151401199775346988024428292" == coef.toString());
			auto deg = res.getDegree();
			CHECK("8545475848486794864479494204829847289469726479267526546254625462424242" == deg.toString());
			f.close();
		}
	}

	TEST_CASE("Substraction")
	{
		SUBCASE("SignedNumber")
		{
			std::ifstream f;
			f.open("../PolynomialElement/SubstractionSignedNumber.txt");
			std::string elem1StrS;
			std::string elem1StrP;
			std::string elem2StrS;
			std::string elem2StrP;
			f >> elem1StrS >> elem1StrP >> elem2StrS >> elem2StrP;
			PositiveNumber deg1 = PositiveNumber(elem1StrP);
			PositiveNumber deg2 = PositiveNumber(elem2StrP);

			PolynomialElement<SignedNumber> elem1(SignedNumber(elem1StrS), deg1),
				elem2(SignedNumber(elem2StrS), deg2);

			PolynomialElement<SignedNumber> res = elem1 - elem2;
			auto coef = res.getCoefficient();
			CHECK(SignedNumber("-7326738238625862586038757970177681215936357505370572716474506552716477251712764") == coef);
			auto deg = res.getDegree();
			CHECK(PositiveNumber("8545475848486794864479494204829847289469726479267526546254625462424242") == deg);
			f.close();
		}
		SUBCASE("FiniteNumber")
		{
			std::ifstream f;
			f.open("../PolynomialElement/SubstractionFiniteNumber.txt");
			std::string elem1StrS;
			std::string elem1StrP;
			std::string elem2StrS;
			std::string elem2StrP;
			getline(f, elem1StrS);
			getline(f, elem1StrP);
			getline(f, elem2StrS);
			getline(f, elem2StrP);
			PositiveNumber deg1 = PositiveNumber(elem1StrP);
			PositiveNumber deg2 = PositiveNumber(elem2StrP);
			PolynomialElement<FiniteNumber> elem1(FiniteNumber(elem1StrS), deg1),
				elem2(FiniteNumber(elem2StrS), deg2);

			PolynomialElement<FiniteNumber> res = elem1 - elem2;
			auto coef = res.getCoefficient();
			CHECK("28062420516180245075013349993121225682064" == coef.toString());
			auto deg = res.getDegree();
			CHECK(PositiveNumber("8545475848486794864479494204829847289469726479267526546254625462424242") == deg);
		}
	}

	TEST_CASE("Product")
	{
		SUBCASE("SignedNumber")
		{
			std::ifstream f;
			f.open("../PolynomialElement/ProductSignedNumber.txt");
			std::string elem1StrS;
			std::string elem1StrP;
			std::string elem2StrS;
			std::string elem2StrP;
			f >> elem1StrS >> elem1StrP >> elem2StrS >> elem2StrP;
			PositiveNumber deg1 = PositiveNumber(elem1StrP);
			PositiveNumber deg2 = PositiveNumber(elem2StrP);
			PolynomialElement<SignedNumber> elem1(SignedNumber(elem1StrS), deg1),
				elem2(SignedNumber(elem2StrS), deg2);

			PolynomialElement<SignedNumber> res = elem1 * elem2;
			auto coef = res.getCoefficient();
			CHECK("-6833456969459413250177282067799619441992914255539016523674322432973837599202619331930221900531549336054950176783070332846042890129924" == coef.toString());
			auto deg = res.getDegree();
			CHECK(PositiveNumber("8545475848486794864479494204829847289469727116926892482851021160063811") == deg);
		}
		SUBCASE("FiniteNumber")
		{
			std::ifstream f;
			f.open("../PolynomialElement/ProductFiniteNumber.txt");
			std::string elem1StrS;
			std::string elem1StrP;
			std::string elem2StrS;
			std::string elem2StrP;
			getline(f, elem1StrS);
			getline(f, elem1StrP);
			getline(f, elem2StrS);
			getline(f, elem2StrP);
			PositiveNumber deg1 = PositiveNumber(elem1StrP);
			PositiveNumber deg2 = PositiveNumber(elem2StrP);
			PolynomialElement<FiniteNumber> elem1(FiniteNumber(elem1StrS), deg1),
				elem2(FiniteNumber(elem2StrS), deg2);

			PolynomialElement<FiniteNumber> res = elem1 * elem2;
			auto coef = res.getCoefficient();
			CHECK("13324760039211868344887847235231864308540" == coef.toString());
			auto deg = res.getDegree();
			CHECK(PositiveNumber("8545475848486794864479494204829847289469727116926892482851021160063811") == deg);
		}
	}
}