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

	FPolynomial Normalized() const {
		FPolynomial fpol = *this;
		assert(fpol.coefficients.size() > 0);
		auto leading = fpol.coefficients.front().getCoefficient();
		for (auto& coef : fpol.coefficients)
			coef.setCoefficient(coef.getCoefficient() / leading);
		return fpol;
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

	FPolynomial operator/(const FPolynomial& divider) const {

		auto deg1 = PositiveNumber("0"), deg2 = deg1;
		auto nullNum = FiniteNumber("0", f.getP());
		if (divider.coefficients.empty() || divider.coefficients.front().getCoefficient() == nullNum) {
			throw std::invalid_argument("Division by zero");
		}

		auto quotient = FPolynomial();
		quotient.setP(divider.getP());
		FPolynomial divident = *this;
		deg1 = divident.degree();
		deg2 = divider.degree();
		

		while (deg1 >= deg2 && !divident.coefficients.empty()) {

			FiniteNumber num1 = divident.coefficients.front().getCoefficient();
			FiniteNumber num2 = divider.coefficients.front().getCoefficient();

			auto leadingElement = divident.coefficients.front() / divider.coefficients.front();
			auto leadingPolynomial = FPolynomial();
			leadingPolynomial.setP(divider.getP());
			leadingPolynomial.emplaceDegree(leadingElement.getCoefficient(), leadingElement.getDegree());
			quotient.emplaceDegree(leadingElement.getCoefficient(), leadingElement.getDegree());

			leadingPolynomial = leadingPolynomial * divider;

			divident = divident - leadingPolynomial;

			deg1 = divident.degree();
			deg2 = divider.degree();
		}

		return quotient;
	}

	FPolynomial operator %(const FPolynomial& divider) const {

		auto deg1 = PositiveNumber("0"), deg2 = deg1;
		auto nullNum = FiniteNumber("0", f.getP());

		if (/*divider.degree() <= deg1*/divider.coefficients.empty() || divider.coefficients.front().getCoefficient() == nullNum) {
			throw std::invalid_argument("Division by zero");
		}
		auto quotient = FPolynomial();
		quotient.setP(divider.getP());
		FPolynomial divident = *this;
		deg1 = divident.degree();
		deg2 = divider.degree();

		while (deg1 >= deg2 && !divident.coefficients.empty()) {

			auto num1 = divident.coefficients.front().getCoefficient();
			auto num2 = divider.coefficients.front().getCoefficient();

			auto deb1 = divident.coefficients.front();
			auto deb2 = divider.coefficients.front();

			auto leadingElement = divident.coefficients.front() / divider.coefficients.front();
			auto leadingPolynomial = FPolynomial();
			leadingPolynomial.setP(divider.getP());
			leadingPolynomial.emplaceDegree(leadingElement.getCoefficient(), leadingElement.getDegree());


			quotient.emplaceDegree(leadingElement.getCoefficient(), leadingElement.getDegree());

			leadingPolynomial = leadingPolynomial * divider;
			divident = divident - leadingPolynomial;

			deg1 = divident.degree();
			deg2 = divider.degree();


		}

		return divident;
	}

	friend FPolynomial divideByNum(FPolynomial R, FiniteNumber Num) {
		FPolynomial res;
		res.setP(R.getP());
		FiniteNumber zorro("0", R.f.getP());
		for (auto item : R.coefficients) {
			res.emplaceDegree(item.getCoefficient() / Num, item.getDegree());
		}
		return res;
	}

	static FPolynomial GCD(const FPolynomial& a, const FPolynomial& b) {

		FPolynomial A = a;
		FPolynomial B = b;
		if (B.toString() == "0") {
			return A;
		}

		FPolynomial R = A % B;
		/*auto DEBUGA = A.toString();
		auto DEBUGB = B.toString();
		auto DEBUGR = R.toString();*/
		if (R.toString() != "0") {
			R = divideByNum(R, R.coefficients.front().getCoefficient());
		}
		return GCD(B, R);
	}

	//Implemented by V.Avramenko

	/*
	Cyclotomic Polynomial
	*/
	static FPolynomial cyclotomic(PositiveNumber degree, FiniteField& field) {
		assert(degree.toString() != "0");

		if (degree.toString() == "1") {
			FPolynomial res;
			res.setP(field.getP());
			res.emplaceDegree(FiniteNumber("1", field.getP()), PositiveNumber("1"));
			res.emplaceDegree(FiniteNumber("-1", field.getP()), PositiveNumber("0"));
			return res;
		}
		else if (degree.is_prime()) {
			FPolynomial res = FPolynomial();
			res.setP(field.getP());
			FiniteNumber uno = FiniteNumber("1", field.getP());
			for (PositiveNumber i = degree - uno; i >= PositiveNumber("0"); i -= uno) {
				res.coefficients.push_back(PolynomialElement<FiniteNumber>(uno, i));
				if (i.toString() == "0") {
					break;
				}
			}
			return res;
		}
		else {
			FPolynomial res;
			FPolynomial divider;
			divider.setP(field.getP());
			res.setP(field.getP());
			divider.emplaceDegree(FiniteNumber("1", field.getP()), PositiveNumber("1"));
			divider.emplaceDegree(FiniteNumber("-1", field.getP()), PositiveNumber("0"));
			FPolynomial dividend;
			dividend.setP(field.getP());
			dividend.emplaceDegree(FiniteNumber("1", field.getP()), degree);
			dividend.emplaceDegree(FiniteNumber("-1", field.getP()), PositiveNumber("0"));
			PositiveNumber two("2");
			PositiveNumber zero("0");
			PositiveNumber uno("1");
			PositiveNumber half = degree / two;
			std::string D1 = divider.toString();
			std::string D2 = dividend.toString();
			for (PositiveNumber i = two; i <= half; i += uno) {
				if (degree % i == zero) {
					divider = divider * FPolynomial::cyclotomic(i, field);
				}
				D1 = divider.toString();
			}
			res = dividend / divider;
			return res;
		}
	}


	FPolynomial fastExponentiation(PositiveNumber degree)
	{
		std::string binDegree = degree.bitsReverse();
		FPolynomial answer("1",f.getP());
		FPolynomial temp(*this);

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