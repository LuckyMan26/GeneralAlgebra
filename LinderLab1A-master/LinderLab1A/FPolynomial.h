#pragma once

#include "string"

#include "Polynomial.h"
#include "PositiveNumber.h"
#include "FiniteNumber.h"
#include "FiniteField.h"
#include "Exponent.h"

class FPolynomial : public Polynomial<FiniteNumber>
{
private:
	FiniteField f;
	FPolynomial() {}
	FPolynomial(const std::string& str) : Polynomial(str) {};
	FPolynomial(const Polynomial& pol, const FiniteField& f) : Polynomial(pol), f(f) {}

	virtual FiniteNumber genZeroCoefficient() const override {
		return FiniteNumber("", f.getP());
	}

	virtual FiniteNumber genCoefficient(const std::string& str) const override {
		return FiniteNumber(str, f.getP());
	}

public:
	FPolynomial(const std::string& str, const PositiveNumber& p) {
		f.setP(p);

		auto s = str;

		s = replaceAll(s, " ", ""); //no spaces
		s = replaceAll(s, "-", "+-"); //for split

		if (s[0] != '+')
			s = "+" + s;
		s = s + '+';

		auto coefficients = parseTerms(s);
		for (auto& term : coefficients) {
			emplaceDegree(term.getCoefficient(), term.getDegree());
		}

		trim();

	}

	void setP(const PositiveNumber& p) {
		f.setP(p);
	}

	PositiveNumber getP() const {
		return f.getP();
	}

	FPolynomial Normalise() {
		// TODO:
		return *this;
	}

	FPolynomial operator+(const FPolynomial& right) const {
		assert(f == const_cast<FiniteField&>(right.f));
		const Polynomial& pol = *this;
		auto res = FPolynomial(pol + right, f);
		res.trim();
		return res;
	}

	FPolynomial operator-(const FPolynomial& right) const {
		assert(f == const_cast<FiniteField&>(right.f));
		const Polynomial& pol = *this;
		auto res = FPolynomial(pol - right, f);
		res.trim();
		return res;
	}

	FPolynomial operator*(const FPolynomial& right) const {
		assert(f == const_cast<FiniteField&>(right.f));
		const Polynomial& pol = *this;
		auto res = FPolynomial(pol * right, f);
		res.trim();
		return res;
	}

	FiniteNumber valueAt(FiniteNumber x) {
		if (x.getP() != this->f.getP()) {
			return FiniteNumber("0"); //illegal arguments
		}
		Exponentiation exp;
		FiniteNumber zero = FiniteNumber("0");
		FiniteNumber current = FiniteNumber();
		PositiveNumber one = PositiveNumber("1");
		auto prevElement = PolynomialElement<FiniteNumber>(FiniteNumber("0"), coefficients.front().getDegree() + PositiveNumber("1"));
		for (auto element : coefficients) {
			if (current != zero) {
				PositiveNumber degree = prevElement.getDegree() - element.getDegree() - one;
				current = current * exp.montgomeryExponentiation(x, degree);
			}
			current = (x * current) + element.getCoefficient();
			prevElement = element;
		}
		return current;
	}

	FPolynomial derivative() {
		FPolynomial deriv = FPolynomial("0");
		FiniteNumber zero = FiniteNumber("0");
		for (auto element : coefficients) {
			FiniteNumber coefficient = FiniteNumber(element.getCoefficient() * element.getDegree(), f.getP());
			if (coefficient != zero)
				deriv.coefficients.push_back(PolynomialElement<FiniteNumber>(coefficient, element.getDegree() - PositiveNumber("1")));
		}
		deriv.trim();
		return deriv;
	}

	//FPolynomial operator/(const FPolynomial& divider) const {

	//	auto deg1 = PositiveNumber("0"), deg2 = deg1;
	//	auto nullNum = FiniteNumber("0", f.getP());
	//	if (divider.coefficients.empty() || divider.coefficients.front().getCoefficient() == nullNum) {
	//		throw std::invalid_argument("Division by zero");
	//	}

	//	auto quotient = FPolynomial();
	//	FPolynomial divident = *this;
	//	deg1 = divident.degree();
	//	deg2 = divider.degree();

	//	while (deg1 >= deg2 && !divident.coefficients.empty()) {

	//		FiniteNumber num1 = divident.coefficients.front().getCoefficient();
	//		FiniteNumber num2 = divider.coefficients.front().getCoefficient();
	//		if (!((num1 % num2).toString() == "0")) {
	//			break;
	//		}

	//		auto leadingElement = divident.coefficients.front() / divider.coefficients.front();
	//		auto leadingPolynomial = FPolynomial(); leadingPolynomial.emplaceDegree(leadingElement.getCoefficient(), leadingElement.getDegree());
	//		quotient.emplaceDegree(leadingElement.getCoefficient(), leadingElement.getDegree());

	//		leadingPolynomial = leadingPolynomial * divider;

	//		divident = divident - leadingPolynomial;

	//		deg1 = divident.degree();
	//		deg2 = divider.degree();
	//	}

	//	return quotient;
	//}

	//FPolynomial operator %(const FPolynomial& divider) const {

	//	auto deg1 = PositiveNumber("0"), deg2 = deg1;
	//	auto nullNum = FiniteNumber("0", f.getP());

	//	if (/*divider.degree() <= deg1*/divider.coefficients.empty() || divider.coefficients.front().getCoefficient() == nullNum) {
	//		throw std::invalid_argument("Division by zero");
	//	}
	//	auto quotient = FPolynomial();
	//	FPolynomial divident = *this;
	//	deg1 = divident.degree();
	//	deg2 = divider.degree();

	//	while (deg1 >= deg2 && !divident.coefficients.empty()) {



	//		auto num1 = divident.coefficients.front().getCoefficient();
	//		auto num2 = divider.coefficients.front().getCoefficient();
	//		if (!((num1 % num2).toString() == "0")) {
	//			return divident;
	//		}

	//		auto deb1 = divident.coefficients.front();
	//		auto deb2 = divider.coefficients.front();

	//		auto leadingElement = divident.coefficients.front() / divider.coefficients.front();
	//		auto leadingPolynomial = FPolynomial(); leadingPolynomial.emplaceDegree(leadingElement.getCoefficient(), leadingElement.getDegree());


	//		quotient.emplaceDegree(leadingElement.getCoefficient(), leadingElement.getDegree());

	//		leadingPolynomial = leadingPolynomial * divider;
	//		divident = divident - leadingPolynomial;

	//		deg1 = divident.degree();
	//		deg2 = divider.degree();


	//	}

	//	return divident;
	//}

	//friend FPolynomial divideByNum(FPolynomial R, FiniteNumber Num) {
	//	FPolynomial res;
	//	FiniteNumber zorro("0", R.f.getP());
	//	for (auto item : R.coefficients) {
	//		if (item.getCoefficient() % Num == zorro) {
	//			res.emplaceDegree(item.getCoefficient() / Num, item.getDegree());
	//		}
	//		else {
	//			return R;
	//		}
	//	}
	//	return res;
	//}

	//static FPolynomial GCD(const FPolynomial& a, const FPolynomial& b) {

	//	FPolynomial A = a;
	//	FPolynomial B = b;
	//	if (B.toString() == "0") {
	//		return A;
	//	}

	//	FPolynomial R = A % B;
	//	auto DEBUGA = A.toString();
	//	auto DEBUGB = B.toString();
	//	auto DEBUGR = R.toString();
	//	if (R.toString() != "0") {
	//		R = FPolynomial(R, R.coefficients.front().getCoefficient());
	//	}
	//	return GCD(B, R);
	//}


};