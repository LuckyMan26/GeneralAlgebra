#pragma once
#include "SignedNumber.h"

class RPolynomial
{
private:
	std::vector<SignedNumber> coefficients;

public:
	/**
	* s - is sequence of polynomial coefficients in incresing order (starting from x0) separated with spaces
	* 4 0 0 1 = { 4 + x^3 }
	* p - is field's modulus
	*/
	RPolynomial(std::string s) {
		std::string delimiter = " ";
		size_t pos = 0;
		std::string token;
		while ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);
			s.erase(0, pos + delimiter.length());
			this->coefficients.push_back(SignedNumber(token));
		}
		this->coefficients.push_back(SignedNumber(s));
	}
	/**
	* Returns string of coefficients, separated with spaces
	* { 4 + x^3 } = 4 0 0 1
	*/
	std::string toString() {
		std::string result = "";
		for (SignedNumber n : coefficients) {
			result += n.toString();
			result += ' ';
		}
		return result.substr(0, result.size() - 1);
	}

	RPolynomial derivative() {
		auto s = std::vector<SignedNumber>();
		if (coefficients.size() < 2) {
			s.push_back(SignedNumber("0"));
		}
		else {
			for (int i = 2; i < coefficients.size(); i++) {
				s.push_back(coefficients[i] * SignedNumber(std::to_string(i)));
			}
		}
		this->coefficients = s;
	}
	SignedNumber valueAt(SignedNumber x) {
		SignedNumber current = SignedNumber("1");
		for (int i = coefficients.size() - 1; i >= 0;i--) {
			current = x * current + coefficients[i];
		}
		return current;
	}
};

