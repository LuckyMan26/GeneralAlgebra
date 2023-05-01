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


};