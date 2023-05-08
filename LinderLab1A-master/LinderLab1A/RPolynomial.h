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
	static RPolynomial cyclotomic(PositiveNumber degree) {
		assert(degree.toString() != "0");
		
		if (degree.toString() == "1") {
			RPolynomial res;
			res.emplaceDegree(SignedNumber("1"), PositiveNumber("1"));
			res.emplaceDegree(SignedNumber("-1"), PositiveNumber("0"));
			return res;
		}
		else if (degree.is_prime()) {
			RPolynomial res = RPolynomial();
			SignedNumber uno = SignedNumber("1");
			for (PositiveNumber i = degree - uno; i >= PositiveNumber("0"); i -= uno) {
				res.coefficients.push_back(PolynomialElement<SignedNumber>(uno, i));
				if (i.toString() == "0") {
					break;
				}
			}
			return res;
		}
		else {
			RPolynomial res;
			RPolynomial divider;
			divider.emplaceDegree(SignedNumber("1"), PositiveNumber("1"));
			divider.emplaceDegree(SignedNumber("-1"), PositiveNumber("0"));
			RPolynomial dividend;
			dividend.emplaceDegree(SignedNumber("1"), degree);
			dividend.emplaceDegree(SignedNumber("-1"), PositiveNumber("0"));
			PositiveNumber two("2");
			PositiveNumber zero("0");
			PositiveNumber uno("1");
			PositiveNumber half = degree / two;
			std::string D1 = divider.toString();
			std::string D2 = dividend.toString();
			for (PositiveNumber i = two; i <= half; i += uno) {
				if (degree % i == zero) {
					divider = divider * RPolynomial::cyclotomic(i);
				}
				D1 = divider.toString();
			}
			res = dividend / divider;
			return res;
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
		if (coefficients.empty())
			return zero;
		SignedNumber current = SignedNumber();
		auto prevElement = PolynomialElement<SignedNumber>(SignedNumber("0"), coefficients.front().getDegree() + PositiveNumber("1"));
		for (auto element : coefficients) {
			if (current != zero) {
				current = current * exp.fastExponentiation(x, prevElement.getDegree() - element.getDegree() - PositiveNumber("1"));
			}
			current = (x * current) + element.getCoefficient();
			prevElement = element;
		}
		PositiveNumber n = coefficients.back().getDegree();
		current = current * exp.fastExponentiation(x, n);
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

	RPolynomial operator/(const RPolynomial& divider) const {

		auto deg1 = PositiveNumber("0"), deg2 = deg1;
		auto nullNum = SignedNumber("0");
		if (divider.coefficients.empty() || divider.coefficients.front().getCoefficient() == nullNum) {
			throw std::invalid_argument("Division by zero");
		}

		auto quotient = RPolynomial();
		RPolynomial divident = *this;
		deg1 = divident.degree();
		deg2 = divider.degree();

		while (deg1 >= deg2 && !divident.coefficients.empty()) {
			
			auto num1 = divident.coefficients.front().getCoefficient().toUnsigned();
			auto num2 = divider.coefficients.front().getCoefficient().toUnsigned();
			if (!(num1 % num2 == SignedNumber())) {
				break;
			}
			
			auto leadingElement = divident.coefficients.front() / divider.coefficients.front();
			auto leadingPolynomial = RPolynomial(); leadingPolynomial.emplaceDegree(leadingElement.getCoefficient(), leadingElement.getDegree());
			quotient.emplaceDegree(leadingElement.getCoefficient(), leadingElement.getDegree());

			leadingPolynomial = leadingPolynomial * divider;
		
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

		while (deg1 >= deg2 && !divident.coefficients.empty()) {
			
			

			auto num1 = divident.coefficients.front().getCoefficient().toUnsigned();
			auto num2 = divider.coefficients.front().getCoefficient().toUnsigned();
			if (!(num1 % num2 == nullNum)) {
				return divident;
			}
			
			auto deb1 = divident.coefficients.front();
			auto deb2 = divider.coefficients.front();

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
