#pragma once
#include "Polynomial.h"
#include "PositiveNumber.h"
#include "FiniteNumber.h"
#include "FiniteField.h"


class FPolynomial : public Polynomial<FiniteNumber>
{
private:
	FiniteField f;

public:
	FPolynomial(const PositiveNumber& p) {
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
};