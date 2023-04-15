#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "SignedNumber.h"
#include "FiniteNumber.h"
#include "Exponent.h"

#include <random>
#include <string>


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
	p1 = PositiveNumber("1200000");
	p2 = PositiveNumber("10000");
	p3 = p1 / p2;
	CHECK(p3.toString() == "12");
}

//Test by M. Tyshchenko
TEST_CASE("Test on random numbers") {
	std::cout << "Testing on random values" << std::endl;
	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	std::uniform_int_distribution<int>  distr(0, 1000);
	for (int i = 0; i < 200; i++) {
		int a = distr(generator);
		int b = distr(generator);
		PositiveNumber aNum = PositiveNumber(std::to_string(a));
		PositiveNumber bNum = PositiveNumber(std::to_string(b));
		CHECK((aNum + bNum).toString() == std::to_string(a + b));
		CHECK((aNum - bNum).toString() == std::to_string(abs(a - b)));
		CHECK((aNum * bNum).toString() == std::to_string(a * b));
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

//Tests by M. Tyshchenko
TEST_CASE("Exponent") {
	FiniteNumber n = FiniteNumber(PositiveNumber("100"), PositiveNumber("17"));
	FiniteNumber m = FiniteNumber(PositiveNumber("431"), PositiveNumber("17"));
	std::cout << n.toString() << std::endl;
	CHECK(n.toString() == "15");
	CHECK((n * m).toString() == "5");
	CHECK((m * n).toString() == "5");
	CHECK((n.shift(2)).toString() == "1500");
	CHECK((m.shift(-2)).toString() == "0");
	CHECK(FiniteNumber("x257 10000").inverse().toString() == "67");
	/*
	FiniteNumber toMultiply = FiniteNumber("x257 128");
	FiniteNumber toMultiply2 = FiniteNumber("x257 80");
	Exponentiation exp = Exponentiation();
	FiniteNumber result = exp.montgomeryMultiplication(toMultiply, toMultiply2);
	std::cout << result.toString() << std::endl;*/
}