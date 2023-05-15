﻿#pragma once

#include <cassert>

#include "FPolynomial.h"
#include "FiniteField.h"

// Really true Polynomial in Finite Field. Trust me, bro 😎
class TrueFPolynomial : protected FPolynomial
{
private:
	FPolynomial irreducible;

	TrueFPolynomial(const FPolynomial& fpol, const FPolynomial& irreducible) : FPolynomial(fpol), irreducible(irreducible) {
		this->toFieldSize();
	}

	void toFieldSize() {
		this->remainder(irreducible);
	}

public:
	explicit TrueFPolynomial(const std::string& str, const FPolynomial& irreducible)
		: irreducible(irreducible), FPolynomial(str, irreducible.getP()) {
		this->toFieldSize();
	}

	TrueFPolynomial operator+(const TrueFPolynomial& right) const {
		//assert(this->irreducible == right.irreducible);
		return TrueFPolynomial(FPolynomial::operator+(right), this->irreducible);
	}

	TrueFPolynomial operator-(const TrueFPolynomial& right) const {
		//assert(this->irreducible == right.irreducible);
		return TrueFPolynomial(FPolynomial::operator-(right), this->irreducible);
	}

	TrueFPolynomial operator*(const TrueFPolynomial& right) const {
		//assert(this->irreducible == right.irreducible);
		return TrueFPolynomial(FPolynomial::operator*(right), this->irreducible);
	}

	TrueFPolynomial Normalized() const {
		TrueFPolynomial fpol = *this;
		assert(fpol.coefficients.size() > 0);
		auto leading = fpol.coefficients.front().getCoefficient();
		for (auto& coef : fpol.coefficients)
			coef.setCoefficient(coef.getCoefficient() / leading);
		return fpol;
	}


	TrueFPolynomial fastExponentiation(PositiveNumber degree)
	{
		std::string binDegree = degree.bitsReverse();
		TrueFPolynomial answer("1", this->irreducible);
		TrueFPolynomial temp(*this);

		const int countOfIterations = binDegree.size() - 1;

		for (int i = countOfIterations; i > 0; i--)
		{
			if (binDegree[i] == '1')
			{
				answer = answer * temp;
			}

			answer = answer * answer;
		}

		if (binDegree[0] == '1')
			answer = answer * temp;

		return answer;
	}
};
