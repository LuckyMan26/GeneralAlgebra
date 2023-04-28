#pragma once

#include "string"

#include "Polynomial.h"
#include "PositiveNumber.h"
#include "FiniteNumber.h"
#include "FiniteField.h"


class FPolynomial : public Polynomial<FiniteNumber>
{
private:
	FiniteField f;

	FPolynomial(const Polynomial& pol, const FiniteField& f) : Polynomial(pol), f(f) {}

public:
	FPolynomial(const std::string& s, const PositiveNumber& p) : Polynomial(s) {
		f.setP(p);
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
		return FPolynomial(pol + right, f);
	}

	FPolynomial operator-(const FPolynomial& right) const {
		assert(f == const_cast<FiniteField&>(right.f));
		const Polynomial& pol = *this;
		return FPolynomial(pol - right, f);
	}

	FPolynomial operator*(const FPolynomial& right) const {
		assert(f == const_cast<FiniteField&>(right.f));
		const Polynomial& pol = *this;
		return FPolynomial(pol * right, f);
	}
};