#include "SignedNumber.h"
#include "FiniteNumber.h"


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

	SignedNumber signedN = SignedNumber("200");
	SignedNumber signedM = SignedNumber("-300");
	signedN.addTo(signedM);
	std::cout << signedN.toString() << std::endl;
	signedN.substract(signedM);
	std::cout << signedN.toString() << std::endl;
	signedN.multiplyBy(signedM);
	std::cout << signedN.toString() << std::endl;
	
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
	PositiveNumber b = PositiveNumber("0");
	PositiveNumber c = a * b;
	PositiveNumber d = b * a;
	std::cout << c.toString() << std::endl;
	std::cout << d.toString() << std::endl;
}



int main() {
	testDifferentSize();
	testPositiveNumbers();
	testSignedNumbers();
	testFiniteNumbers();
}