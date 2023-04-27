#pragma once
#include "Polynomial.h"
#include "PolynomialElement.h"
#include <string>

#include "Exponent.h"

//Implemented by V.Avramenko and M.Tyshchenko
// Modified by Y. Kishchuk
/*
* Class for Polynomial in Polynomial Ring (signed coefficients)
*/
class RPolynomial : public Polynomial<SignedNumber>
{
private:
	RPolynomial() {	}

public:
	RPolynomial(std::string s) : Polynomial(s) {}

	//Implemented by V.Avramenko

	/*
	Cyclotomic Polynomial
	*/
	friend RPolynomial cyclotomic(PositiveNumber degree) {
		if (degree.is_prime()) {
			RPolynomial res = RPolynomial();
			SignedNumber uno = SignedNumber("1");
			for (PositiveNumber i = PositiveNumber("0"); i < degree; i += uno) {
				res.coefficients.push_back(PolynomialElement<SignedNumber>(uno, i));
			}
			return res;
		}
		else if (degree.is_even()) {
			RPolynomial res = RPolynomial();
			SignedNumber uno = SignedNumber("1");
			bool switcher = false;
			for (PositiveNumber i = PositiveNumber("0"); i < degree; i += uno) {
				if (switcher) {
					uno.flipSign();
					res.coefficients.push_back(PolynomialElement<SignedNumber>(uno, i));
					uno.flipSign();
				}
				else {
					res.coefficients.push_back(PolynomialElement<SignedNumber>(uno, i));
				}
				switcher = !switcher;
			}
		}
		else {
			//TO BE CONTINUED
			//Waiting for var 13 implementation to continue my work
		}
	}


	//Returns derivative of the polynomial
	RPolynomial derivative() {
		RPolynomial deriv = RPolynomial();
		SignedNumber zero = SignedNumber("0");
		for (auto element : coefficients) {
			SignedNumber coefficient = element.getCoefficient() * element.getDegree();
			if (coefficient != zero)
				deriv.coefficients.push_back(PolynomialElement<SignedNumber>(coefficient, element.getDegree() - PositiveNumber("1")));
		}
		return deriv;
	}
	//Returns value of the polynomial at X
	SignedNumber valueAt(SignedNumber x) {
		Exponentiation exp;
		SignedNumber zero = SignedNumber("0");
		SignedNumber current = SignedNumber();
		auto prevElement = PolynomialElement<SignedNumber>(SignedNumber("0"), coefficients.front().getDegree() + PositiveNumber("1"));
		for (auto element : coefficients) {
			if (current != zero) {
				current = current * exp.fastExponention(x, prevElement.getDegree() - element.getDegree() - PositiveNumber("1"));
			}
			current = (x * current) + element.getCoefficient();
			prevElement = element;
		}
		return current;
	}
};

