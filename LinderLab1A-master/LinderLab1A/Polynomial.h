#pragma once
#include "FiniteNumber.h"
class Polynomial {
private:
	std::vector<FiniteNumber> coefficients;
	PositiveNumber p;
public:
	/**
	* s - is sequence of polynomial coefficients in incresing order (starting from x0) separated with spaces
	* 4 0 0 1 = { 4 + x^3 }
	* p - is field's modulus
	*/
	Polynomial(std::string s, PositiveNumber p) {
		std::string delimiter = " ";
		size_t pos = 0;
		this->p = p;
		std::string token;
		while ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);
			s.erase(0, pos + delimiter.length());
			this->coefficients.push_back(FiniteNumber(token, p));
		}
	}
	/**
	* Returns string of coefficients, separated with spaces
	* { 4 + x^3 } = 4 0 0 1
	*/
	std::string toString() {
		std::string result = "";
		for (FiniteNumber n : coefficients) {
			result += n.toString();
			result += ' ';
		}
		return result.substr(0, result.size() - 1);
	}
};