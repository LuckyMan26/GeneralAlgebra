#pragma once
#include "Polynomial.h"
#include "PolynomialElement.h"
#include <string>

#include "Exponent.h"

//Implemented by V.Avramenko and M.Tyshchenko
// Modified by Y. Kishchuk and V.Horbanov
/*
* Class for Polynomial in Polynomial Ring (signed coefficients)
*/
class RPolynomial : public Polynomial<SignedNumber>
{
private:
	
	RPolynomial(const Polynomial& pol) : Polynomial(pol) {}

	virtual SignedNumber genZeroCoefficient() const override {
		return SignedNumber();
	}

	virtual SignedNumber genCoefficient(const std::string& str) const override {
		return SignedNumber(str);
	}

public:

	RPolynomial() {	}

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

	PositiveNumber degree() const {
		if (coefficients.empty()) {
			return PositiveNumber("0");
		}
		return coefficients.front().getDegree();
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

	RPolynomial operator+(const RPolynomial& right) const {
		const Polynomial& pol = *this;
		return RPolynomial(pol + right);
	}

	RPolynomial operator-(const RPolynomial& right) const {
		const Polynomial& pol = *this;
		return RPolynomial(pol - right);
	}

	RPolynomial operator*(const RPolynomial& right) const {
		const Polynomial& pol = *this;
		return RPolynomial(pol * right);
	}

	RPolynomial operator/(/*const*/ RPolynomial& divider) const {

		auto deg1 = PositiveNumber("0"), deg2 = deg1;
		auto nullNum = SignedNumber("0");
		if (/*divider.degree() <= deg1*/ divider.coefficients.empty() || divider.coefficients.front().getCoefficient() == nullNum) {
			throw std::invalid_argument("Division by zero");
		}

		auto quotient = RPolynomial();
		RPolynomial divident = *this;
		deg1 = divident.degree();
		deg2 = divider.degree();

		while (deg1 >= deg2) {
			auto DEBUG1 = divident.toString(), DEBUG2 = divider.toString();
			auto num1 = divident.coefficients.front().getCoefficient().toUnsigned();
			auto num2 = divider.coefficients.front().getCoefficient().toUnsigned();
			if (!(num1 % num2 == SignedNumber())) {
				break;
			}
			
			auto leadingElement = divident.coefficients.front() / divider.coefficients.front();
			auto leadingPolynomial = RPolynomial(); leadingPolynomial.emplaceDegree(leadingElement.getCoefficient(), leadingElement.getDegree());
			quotient.emplaceDegree(leadingElement.getCoefficient(), leadingElement.getDegree());

			leadingPolynomial = leadingPolynomial * divider;
			auto DEBUG3 = leadingPolynomial.toString();
			divident = divident - leadingPolynomial;

			deg1 = divident.degree();
			deg2 = divider.degree();
		}

		return quotient;
	}

	RPolynomial operator %(const RPolynomial& divider) const {

		auto deg1 = PositiveNumber("0"), deg2 = deg1;
		auto nullNum = SignedNumber("0");

		if (/*divider.degree() <= deg1*/divider.coefficients.empty() || divider.coefficients.front().getCoefficient() == nullNum) {
			throw std::invalid_argument("Division by zero");
		}

		auto quotient = RPolynomial();
		RPolynomial divident = *this;
		deg1 = divident.degree();
		deg2 = divider.degree();

		while (deg1 >= deg2) {
			
			auto num1 = divident.coefficients.front().getCoefficient().toUnsigned();
			auto num2 = divider.coefficients.front().getCoefficient().toUnsigned();
			if (!(num1 % num2 == nullNum)) {
				return divident;
			}

			auto leadingElement = divident.coefficients.front() / divider.coefficients.front();
			auto leadingPolynomial = RPolynomial(); leadingPolynomial.emplaceDegree(leadingElement.getCoefficient(), leadingElement.getDegree());

			quotient.emplaceDegree(leadingElement.getCoefficient(), leadingElement.getDegree());

			leadingPolynomial = leadingPolynomial * divider;
			divident = divident - leadingPolynomial;

			deg1 = divident.degree();
			deg2 = divider.degree();
		}

		return divident;
	}

	friend RPolynomial divideByNum(RPolynomial R, SignedNumber Num) {
		RPolynomial res;
		SignedNumber zorro("0");
		for (auto item : R.coefficients) {
			if (item.getCoefficient() % Num == zorro) {
				res.emplaceDegree(item.getCoefficient() / Num, item.getDegree());
			}
			else {
				return R;
			}
		}
		return res;
	}

	static RPolynomial GCD(const RPolynomial& a, const RPolynomial& b) {

		RPolynomial A = a;
		RPolynomial B = b;
		if (B.toString() == "0") {
			return A;
		}
		/*
		auto degA = A.degree(),
			 degB = B.degree();

		if (B.degree() > A.degree())
			std::swap(A, B);

		while (B.degree() > 0) {

			auto num1 = A.coefficients.front().getCoefficient().toUnsigned();
			auto num2 = B.coefficients.front().getCoefficient().toUnsigned();
			auto DEBUG1 = A.toString(), DEBUG2 = B.toString();
			if (!(num1 % num2 == SignedNumber())) {
				break;
			}

			A = A % B;
			std::swap(A, B);
		}

		return A;*/
		RPolynomial R = A % B;
		auto DEBUGA = A.toString();
		auto DEBUGB = B.toString();
		auto DEBUGR = R.toString();
		if (R.toString() != "0") {
			R = divideByNum(R, R.coefficients.front().getCoefficient());
		}
		return GCD(B, R);
	}
};
