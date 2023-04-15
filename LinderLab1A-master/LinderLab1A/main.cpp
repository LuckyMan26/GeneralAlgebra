#include "SignedNumber.h"
#include "FiniteNumber.h"
#include "Exponent.h"

void testPositiveNumbers() {
	PositiveNumber a = PositiveNumber("1234");
	PositiveNumber b = PositiveNumber("99");
	PositiveNumber c = a + b;
	PositiveNumber d = b - a;
	PositiveNumber e = b * a;
	std::cout << c.toString() << std::endl;
	std::cout << d.toString() << std::endl;
	std::cout << e.toString() << std::endl;
}

void testSignedNumbers() {
	FiniteNumber finite = FiniteNumber("x10 1344");
	std::cout << "Testing signed numbers" << std::endl;
	SignedNumber signedN = SignedNumber("1555");
	SignedNumber signedM = SignedNumber("-300");
	SignedNumber res = signedN;
	res -= signedM;
	std::cout << res.toString() << std::endl;
	
}
//Testing FiniteNumbers by Vlad Avramenko
void testFiniteNumbers() {
	std::cout << "\nTESTING FINITE NUMBERS\n";
	FiniteNumber fin1 = FiniteNumber("x10 6");
	FiniteNumber fin2 = FiniteNumber("x10 6");
	std::cout << "fin1 = " << fin1.toString() << " fin2 = " << fin2.toString() << std::endl;
	FiniteNumber fin3 = fin1 + fin2;
	std::cout << "fin1 + fin2 = " << fin3.toString() << std::endl;
	fin1 += fin2;
	std::cout << "fin1 += fin2 => " << fin1.toString() << std::endl;
	fin3 = fin1 - fin2;
	std::cout << "fin1 - fin2 = " << fin3.toString() << std::endl;
	fin1 -= fin2;
	std::cout << "fin1 -= fin2 => " << fin1.toString() << std::endl;
	fin3 = fin1 * fin2;
	std::cout << "fin1 * fin2 = " << fin3.toString() << std::endl;
	FiniteNumber orig = FiniteNumber("x10 1");
	std::cout << " inverse to " << orig.toString() << " is " << orig.inverse().toString() << std::endl;
	fin1 = FiniteNumber("x10 4");
	fin2 = FiniteNumber("x10 3");
	std::cout << " fin1 / fin2 = " << (fin1 / fin2).toString() << "\t fin2 / fin1 " << (fin2 / fin1).toString() << std::endl;
	fin1.divideBy(fin2);
	std::cout << "fin1 /= fin2 => " << fin1.toString() << std::endl;
}

void testDifferentSize() {
	PositiveNumber a = PositiveNumber("10000");
	PositiveNumber b = PositiveNumber("0000");
	PositiveNumber c = a * b;
	PositiveNumber d = b * a;
	std::cout << c.toString() << std::endl;
	std::cout << d.toString() << std::endl;
}

void testFunction(std::string expected, std::string actual) {
	if (expected == actual) {
		std::cout << "\033[35;32mSUCCESS\033[35;0m";
		std::cout << ": " << expected << " == " << actual << std::endl;
	}
	else {
		std::cout << "\033[35;31mERROR\033[35;0m";
		std::cout << ": " << expected << " != " << actual << std::endl;
	}
}

void exponentTest() {
	FiniteNumber n = FiniteNumber(PositiveNumber("100"), PositiveNumber("17"));
	FiniteNumber m = FiniteNumber(PositiveNumber("431"), PositiveNumber("17"));
	std::cout << n.toString() << std::endl;
	testFunction(n.toString(), "15");
	testFunction((n * m).toString(), "5");
	testFunction((m * n).toString(), "5");
	testFunction((n.shift(2)).toString(), "1500");
	testFunction((m.shift(-2)).toString(), "0");
	std::cout << FiniteNumber("x257 10000").inverse().toString() << std::endl;
	FiniteNumber toMultiply = FiniteNumber("x257 128");
	FiniteNumber toMultiply2 = FiniteNumber("x257 80");
	Exponentiation exp = Exponentiation();
	FiniteNumber result = exp.montgomeryMultiplication(toMultiply, toMultiply2);
	std::cout << result.toString() << std::endl;
}


int main2() {
	testDifferentSize();
	testPositiveNumbers();
	testSignedNumbers();
	testFiniteNumbers();
	exponentTest();
	return 0;
}