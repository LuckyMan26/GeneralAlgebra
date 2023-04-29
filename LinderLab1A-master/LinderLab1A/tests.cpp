#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "SignedNumber.h"
#include "FiniteNumber.h"
#include "Exponent.h"
#include "Polynomial.h"
#include "CalculationOfSquareRoot.h"
#include "MillerRabin.h"
#include "Pollard.h"

#include <random>
#include <string>
#include <chrono>

//Test by M. Tyshchenko
TEST_CASE("Positive numbers") {
	PositiveNumber a = PositiveNumber("1234");
	PositiveNumber b = PositiveNumber("99");
	CHECK((a * b).toString() == "122166");
	CHECK((b * a).toString() == "122166");
	CHECK((a - b).toString() == "1135");
	CHECK((b - a).toString() == "1135");
	CHECK((b + a).toString() == "1333");
	CHECK((a + b).toString() == "1333");
	
}

//Test by V.Avramenko
TEST_CASE("Division Test for PositiveNumber") {
	PositiveNumber p1("12");
	PositiveNumber p2("3");
	PositiveNumber p3 = p1 / p2;
	CHECK(p3.toString() == "4");
	p3 = p2 / p1;
	CHECK(p3.toString() == "0");
	p1 = PositiveNumber("1008");
	p2 = PositiveNumber("23");
	p3 = p1 / p2;
	CHECK(p3.toString() == "43");
	p1 = PositiveNumber("669999");
	p2 = PositiveNumber("257");
	p3 = p1 / p2;
	CHECK(p3.toString() == "2607");
}

//Test by V.Avramenko
TEST_CASE("Division Test for SignedNumber") {
	SignedNumber p1("-12");
	SignedNumber p2("3");
	SignedNumber p3 = p1 / p2;
	CHECK(p3.toString() == "-4");
	p3 = p2 / p1;
	CHECK(p3.toString() == "0");
	p1 = SignedNumber("-16");
	p2 = SignedNumber("3");
	p3 = p1 / p2;
	CHECK(p3.toString() == "-5");
	p1 = SignedNumber("-11");
	p2 = SignedNumber("-3");
	p3 = p1 / p2;
	CHECK(p3.toString() == "3");
	p1 = SignedNumber("2");
	p2 = SignedNumber("-3");
	p3 = p1 / p2;
	CHECK(p3.toString() == "0");
}

//Test by V.Avramenko
TEST_CASE("Remainder Test for Positive Numbers") {
	PositiveNumber p1("10");
	PositiveNumber p2("8");
	PositiveNumber p3 = p1 % p2;
	CHECK(p3.toString() == "2");
	p1 = PositiveNumber("102");
	p3 = p1 % p2;
	CHECK(p3.toString() == "6");
	p2 = PositiveNumber("2");
	p3 = p1 % p2;
	CHECK(p3.toString() == "0");
	p1 = PositiveNumber("7");
	p2 = PositiveNumber("8");
	p3 = p1 % p2;
	CHECK(p3.toString() == "7");
}

//Test by V.Avramenko
TEST_CASE("Remainder Test for Signed Numbers") {
	SignedNumber p1("-10");
	SignedNumber p2("8");
	SignedNumber p3 = p1 % p2;
	CHECK(p3.toString() == "-2");
	p1 = SignedNumber("-102");
	p3 = p1 % p2;
	CHECK(p3.toString() == "-6");
	p2 = SignedNumber("-2");
	p3 = p1 % p2;
	CHECK(p3.toString() == "0");
	p1 = SignedNumber("7");
	p2 = SignedNumber("-8");
	p3 = p1 % p2;
	CHECK(p3.toString() == "7");
	p1 = SignedNumber("-9");
	p2 = SignedNumber("-8");
	p3 = p1 % p2;
	CHECK(p3.toString() == "-1");
}

//Test by M. Tyshchenko
TEST_CASE("Test on random numbers") {
	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	std::uniform_int_distribution<int>  distr(0, 5000);
	for (int i = 0; i < 200; i++) {
		int a = distr(generator);
		int b = distr(generator);
		PositiveNumber aNum = PositiveNumber(std::to_string(a));
		PositiveNumber bNum = PositiveNumber(std::to_string(b));
		CHECK((aNum + bNum).toString() == std::to_string(a + b));
		CHECK((aNum - bNum).toString() == std::to_string(abs(a - b)));
		CHECK((aNum * bNum).toString() == std::to_string(a * b));
		if (b != 0) {
			CHECK((aNum / bNum).toString() == std::to_string(a / b));
			CHECK((aNum % bNum).toString() == std::to_string(a % b));
		}
	}
}

//Tests by M. Tyshchenko
TEST_CASE("Signed numbers") {
	FiniteNumber finite = FiniteNumber("x10 1344");
	CHECK(finite.toString() == "4");
	SignedNumber signedN = SignedNumber("1555");
	SignedNumber signedM = SignedNumber("-300");
	SignedNumber res = signedN;
	res -= signedM;
	CHECK(res.toString() == "1855");


	SignedNumber a = SignedNumber("-3");
	SignedNumber b = SignedNumber("0");
	SignedNumber c = a * b;
	CHECK(c.toString() == "0");

}
//Testing FiniteNumbers by Vlad Avramenko
TEST_CASE("Finite numbers") {
	FiniteNumber fin1 = FiniteNumber("x10 6");
	FiniteNumber fin2 = FiniteNumber("x10 6");
	CHECK(fin1.toString() == "6");
	CHECK(fin2.toString() == "6");
	FiniteNumber fin3 = fin1 + fin2;
	CHECK(fin3.toString() == "2");
	fin1 += fin2;
	CHECK(fin1.toString() == "2");
	fin3 = fin1 - fin2;
	CHECK(fin3.toString() == "4");
	fin1 -= fin2;
	CHECK(fin1.toString() == "4");
	fin3 = fin1 * fin2;
	CHECK(fin3.toString() == "4");
	FiniteNumber orig = FiniteNumber("x10 7");
	FiniteNumber inv = orig.inverse();
	CHECK(inv.toString() == "3");
	fin1 = FiniteNumber("x10 4");
	fin2 = FiniteNumber("x10 3");
	FiniteNumber fin4 = fin1 / fin2;
	FiniteNumber fin5 = fin2 / fin1;
	CHECK(fin4.toString() == "8");
	CHECK(fin5.toString() == "3");
	fin1.divideBy(fin2);
	CHECK(fin1.toString() == "8");
}

//Tests by M. Tyshchenko
TEST_CASE("Test zero") {
	PositiveNumber zero = PositiveNumber("0");
	PositiveNumber a = PositiveNumber("10000");
	PositiveNumber b = PositiveNumber("0000");
	CHECK(a * b == zero);
	CHECK(b * a == zero);
}

//Tests for exponentiation by M. Tyshchenko
TEST_CASE("Exponent") {
	FiniteNumber n = FiniteNumber(PositiveNumber("100"), PositiveNumber("17"));
	FiniteNumber m = FiniteNumber(PositiveNumber("431"), PositiveNumber("17"));
	CHECK(n.toString() == "15");
	CHECK((n * m).toString() == "5");
	CHECK((m * n).toString() == "5");

	PositiveNumber aN = PositiveNumber("15");
	CHECK((aN.shift(2)).toString() == "1500");
	CHECK((aN.shift(-2)).toString() == "0");
	CHECK(FiniteNumber("x257 10000").inverse().toString() == "67");

	FiniteNumber toMultiply = FiniteNumber("x257 128");
	FiniteNumber toMultiply2 = FiniteNumber("x257 80");
	Exponentiation exp = Exponentiation();
	FiniteNumber result = exp.montgomeryMultiplication(toMultiply, toMultiply2);
	CHECK(result.toString() == "217");

	toMultiply = FiniteNumber("x97 15");
	toMultiply2 = FiniteNumber("x97 75");
	CHECK(exp.montgomeryMultiplication(toMultiply, toMultiply2).toString() == "58");
	exp.montgomeryMultiplicationDeprecated(toMultiply, toMultiply2).toString();

	FiniteNumber base = FiniteNumber("x257 30");
	PositiveNumber power = PositiveNumber("5");
	result = exp.montgomeryExponention(base, power);
	CHECK(result.toString() == "136");

	base = FiniteNumber("x113 1222");
	power = PositiveNumber("4");
	result = exp.montgomeryExponention(base, power);
	CHECK(result.toString() == "8");


	base = FiniteNumber("x1015843 222222");
	power = PositiveNumber("600");
	std::string expected = "839534";
	//TIMING
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	CHECK(exp.montgomeryExponention(base, power).toString() == expected);
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	//std::cout << "Montgomery = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " ms" << std::endl;

	begin = std::chrono::steady_clock::now();
	CHECK(exp.fastExponention(base, power).toString() == expected);
	end = std::chrono::steady_clock::now();
	//std::cout << "Fast = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " ms" << std::endl;

	//begin = std::chrono::steady_clock::now();
	//CHECK(exp.slowExponention(base, power).toString() == expected);
	//end = std::chrono::steady_clock::now();
	//std::cout << "Slow = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " ms" << std::endl;
}

TEST_CASE("Exponentiation on random values") {
	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	std::uniform_int_distribution<int> baseDistr(0, 2000);
	std::uniform_int_distribution<int> powDistr(0, 20);
	Exponentiation exponent;
	for (int i = 0; i < 200; i++) {
		int a = baseDistr(generator);
		int b = powDistr(generator);
		FiniteNumber aNum = FiniteNumber(std::to_string(a), PositiveNumber("197"));
		PositiveNumber bNum = PositiveNumber(std::to_string(b));
		CHECK(exponent.montgomeryExponention(aNum, bNum).toString() == exponent.slowExponention(aNum, bNum).toString());
	}
}
//Tests for bits function
TEST_CASE("Test binary form") {
	CHECK(PositiveNumber("5").bits() == "101");
	CHECK(PositiveNumber("0").bits() == "0");
	CHECK(PositiveNumber("100").bits() == "1100100");
	CHECK(PositiveNumber("4").bits() == "100");
}


//Tests for polynomial constructor
TEST_CASE("Test zero") {
	Polynomial p = Polynomial("100 20 10", PositiveNumber("17"));
	CHECK(p.toString() == "15 3 10");
}

//Tests by P. Velychko #6
TEST_CASE("TestNonQuadraticPositive") {
	FiniteNumber a("2",11);
	FiniteNumber one("1", 11);
	FiniteNumber x(a.power_mod((11 - 1) / 2));
	if ( x != one) {
		cout << "a is not a quadratic residue mod p" << endl;
	
	}
	else {
		FiniteNumber root1 = a.tonelli_shanks();

		CHECK(root1.power_mod(2) == a);
	}
}

TEST_CASE("TestQuadraticResidue") {
	FiniteNumber a("3", 11);
	FiniteNumber b("5", 11);
	FiniteNumber one("1", 11);

	FiniteNumber x(a.power_mod((11 - 1) / 2));

	if (x != one) {
		cout << "a is not a quadratic residue mod p" << endl;

	}
	else {
		FiniteNumber root(a.tonelli_shanks());
		CHECK(root == b);
	}
}

TEST_CASE("TestQuadraticResidue") {
	FiniteNumber a("3", 19);
	
	FiniteNumber one("1", 19);

	FiniteNumber x(a.power_mod((19 - 1) / 2));

	if (x != one) {
		cout << "a is not a quadratic residue mod p" << endl;

	}
	else {
		FiniteNumber root(a.tonelli_shanks());
		CHECK(root.power_mod(2) == a);
	}
}

TEST_CASE("Test Integer Constuctors") {
	int aInt = 20;
	int bInt = 44;
	PositiveNumber a = PositiveNumber(aInt);
	PositiveNumber b = PositiveNumber(bInt);
	CHECK("64" == (a + b).toString());
	
	FiniteNumber finite1 = FiniteNumber(18, 17);
	CHECK("1" == finite1.toString());
}

TEST_CASE("Additional operators test") {
	FiniteNumber a = FiniteNumber(20, 17);
	FiniteNumber b = FiniteNumber(3, 17);
	FiniteNumber c = FiniteNumber(3, 11);
	FiniteNumber d = FiniteNumber(4, 17);
	CHECK(a == b);
	CHECK(a != c);
	CHECK(a != d);
}

TEST_CASE("Additional operators") {
	FiniteNumber a = FiniteNumber(16, 17);
	FiniteNumber b = FiniteNumber(14, 17);
	CHECK(a > b);
	CHECK(b < a);
	CHECK(!(a < b));
	CHECK(!(b > a));
}

TEST_CASE("Modular Power") {
	PositiveNumber a = PositiveNumber(81);
	PositiveNumber b = PositiveNumber(6);
	PositiveNumber c = PositiveNumber(12);
	auto result = mod_power(a, b, c).toString();
	CHECK("9" == result);
}

TEST_CASE("Miller-Rabin") {
	CHECK(!MillerRabin::miller_rabin(PositiveNumber("783")));
	CHECK(!MillerRabin::miller_rabin(PositiveNumber("890")));
	CHECK(!MillerRabin::miller_rabin(PositiveNumber("320")));
	CHECK(!MillerRabin::miller_rabin(PositiveNumber("178")));

	CHECK(MillerRabin::miller_rabin(PositiveNumber("2")));
	CHECK(MillerRabin::miller_rabin(PositiveNumber("3")));
	CHECK(MillerRabin::miller_rabin(PositiveNumber("5")));
	CHECK(MillerRabin::miller_rabin(PositiveNumber("7")));
	CHECK(MillerRabin::miller_rabin(PositiveNumber("11")));
	CHECK(MillerRabin::miller_rabin(PositiveNumber("13")));
	CHECK(MillerRabin::miller_rabin(PositiveNumber("17")));
	CHECK(MillerRabin::miller_rabin(PositiveNumber("19")));
	CHECK(MillerRabin::miller_rabin(PositiveNumber("23")));
	CHECK(MillerRabin::miller_rabin(PositiveNumber("61")));
	CHECK(MillerRabin::miller_rabin(PositiveNumber("79")));
	CHECK(MillerRabin::miller_rabin(PositiveNumber("83")));
	CHECK(MillerRabin::miller_rabin(PositiveNumber("2147483647")));
}

TEST_CASE("Pollard") {
	PositiveNumber a1 = PositiveNumber("204562");
	std::map<PositiveNumber,int> result1 = PollardFactorization::factorizePoll(a1);
	std::map<PositiveNumber, int> toCheck1 = {std::pair<PositiveNumber,int>(PositiveNumber(2),1),
		std::pair<PositiveNumber,int>(PositiveNumber(23),1),
		std::pair<PositiveNumber,int>(PositiveNumber(4447),1) };
	
	CHECK(result1 == toCheck1);

	PositiveNumber a2 = PositiveNumber("168");
	std::map<PositiveNumber, int> result2 = PollardFactorization::factorizePoll(a2);
	std::map<PositiveNumber, int> toCheck2 = { std::pair<PositiveNumber,int>(PositiveNumber(2),3),
		std::pair<PositiveNumber,int>(PositiveNumber(3),1),
		std::pair<PositiveNumber,int>(PositiveNumber(7),1) };

	CHECK(result2 == toCheck2);

	PositiveNumber a3 = PositiveNumber("43");
	std::map<PositiveNumber, int> result3 = PollardFactorization::factorizePoll(a3);
	std::map<PositiveNumber, int> toCheck3 = { std::pair<PositiveNumber,int>(PositiveNumber(43),1) };

	CHECK(result3 == toCheck3);

}