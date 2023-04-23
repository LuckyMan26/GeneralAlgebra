#pragma once

#include "SignedNumber.h"

class PolynomialElement {
private:
	PositiveNumber degree;
	SignedNumber coefficient;
public:
	PolynomialElement(SignedNumber coefficient, PositiveNumber degree) {
		this->degree = degree;
		this->coefficient = coefficient;
	}
	void setDegree(PositiveNumber degree) {
		this->degree = degree;
	}
	PositiveNumber getDegree() {
		return this->degree;
	}
	void setCoefficient(SignedNumber coefficient) {
		this->coefficient = coefficient;
	}
	SignedNumber getCoefficient() {
		return this->coefficient;
	}

	std::string toString() {
		PositiveNumber zero = PositiveNumber("0");
		if (this->degree == zero) {
			return coefficient.toString();
		}
		PositiveNumber one = PositiveNumber("1");
		if (this->degree == one) {
			std::string coef = coefficient.toString();
			if (coef == "1")
				coef = "";
			return coef + "x";
		}
		std::string coef = coefficient.toString();
		if (coef == "1")
			coef = "";
		return coef + "x^" + degree.toString();
	}
};