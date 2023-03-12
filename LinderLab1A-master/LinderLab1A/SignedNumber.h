#pragma once
#include "PositiveNumber.h"

enum Sign {PLUS, MINUS};

class SignedNumber : public PositiveNumber {
private:
	Sign sign = PLUS;
public:
	void addTo(SignedNumber other) {
		if (this->sign == other.sign) {
			PositiveNumber::addTo(other);
		}
		else {
			PositiveNumber::substract(other);
			this->sign = (*this > other) ? this->sign : other.sign;
		}

	}
	void substractFrom(SignedNumber other) {
		if (this->sign == other.sign) {
			PositiveNumber::substract(other);
			if (*this < other) {
				flipSign();
			}
		}
		else {
			PositiveNumber::addTo(other);
		}
	}
	SignedNumber(std::string str) {
		if (str[0] == '-') {
			str = str.substr(1);
			this->sign = MINUS;
		}
		this->digits = parseDigits(str);
	}
	std::string toString() {
		std::string s = sign == PLUS ? "" : "-";
		s += PositiveNumber::toString();
		return s;
	}
	void flipSign() {
		if (this->sign == MINUS)
			this->sign = PLUS;
		else
			this->sign = MINUS;
	}
	void multiplyBy(SignedNumber other) {
		PositiveNumber::multiplyBy(other);
		this->sign = (this->sign == other.sign) ? PLUS : MINUS;
	}
};