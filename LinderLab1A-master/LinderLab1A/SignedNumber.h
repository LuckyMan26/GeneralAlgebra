#pragma once
#include "PositiveNumber.h"
//Created by M.Tyshchenko
enum Sign {PLUS, MINUS};

class SignedNumber : public PositiveNumber {
private:
	Sign sign = PLUS;


	void zeroSignCheck() {
		if (isZero()) {
			sign = PLUS;
		}
	}

public:
	SignedNumber() : PositiveNumber() {
		sign = PLUS;
	}
	friend SignedNumber operator+(SignedNumber left, const SignedNumber& n) {
		left.addTo(n);
		return left;
	}
	SignedNumber& operator+=(const SignedNumber& n) {
		this->addTo(n);
		return *this;
	}
	SignedNumber operator*(const SignedNumber& n) {
		PositiveNumber p = PositiveNumber::simpleMultiplication(*this, n);
		SignedNumber result = SignedNumber(p, (this->sign == n.sign) ? PLUS : MINUS);
		result.zeroSignCheck();
		return result;
	}
	SignedNumber operator*(const PositiveNumber& n) {
		SignedNumber result = SignedNumber(PositiveNumber::simpleMultiplication(*this, n), this->sign);
		result.zeroSignCheck();
		return result;
	}
	SignedNumber operator*=(const SignedNumber& n) {
		this->multiplyBy(n);
		return *this;
	}
	friend PositiveNumber operator-(SignedNumber left, const SignedNumber& n) {
		left.substractFrom(n);
		return left;
	}
	PositiveNumber& operator-=(const SignedNumber& n) {
		this->substractFrom(n);
		return *this;
	}
	bool isPositive() {
		return this->sign == PLUS;
	}
	bool isNegative() {
		return this->sign == MINUS;
	}
	bool operator==(SignedNumber& n) const {
		return equals(n);
	}
	bool operator!=(SignedNumber& n) const {
		return !equals(n);
	}
	bool operator>(SignedNumber& n) const {
		if (n.sign == PLUS && this->sign == MINUS)
			return false;
		else if (this->sign == PLUS && n.sign == MINUS) {
			return true;
		}
		return PositiveNumber::operator>(n);
	}

	bool operator>=(SignedNumber& n) const {
		if (n.sign == PLUS && this->sign == MINUS)
			return false;
		else if (this->sign == PLUS && n.sign == MINUS) {
			return true;
		}
		return PositiveNumber::operator<=(n);
	}
	bool operator<(SignedNumber& n) const {
		if (n.sign == PLUS && this->sign == MINUS)
			return true;
		else if (this->sign == PLUS && n.sign == MINUS) {
			return false;
		}
		return PositiveNumber::operator<(n);
	}
	bool operator<=(SignedNumber& n) const {
		if (n.sign == PLUS && this->sign == MINUS)
			return true;
		else if (this->sign == PLUS && n.sign == MINUS) {
			return false;
		}
		return PositiveNumber::operator<=(n);
	}

	bool equals(SignedNumber n) const {
		if (this->sign != n.sign)
			return false;
		return PositiveNumber::equals(n);
	}
	void addTo(SignedNumber other) {
		if (this->sign == other.sign) {
			PositiveNumber::addTo(other);
		}
		else {
			this->sign = PositiveNumber::operator>(other) ? this->sign : other.sign;
			PositiveNumber::substract(other);	
		}

	}
	void substractFrom(SignedNumber other) {
		if (this->sign == other.sign) {
			PositiveNumber::substract(other);
			if (PositiveNumber::operator<(other)) {
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
		this->trim();
	}
	SignedNumber(PositiveNumber absolute, Sign sign) {
		this->sign = sign;
		this->digits = absolute.getDigits();
		this->trim();
	}
	std::string toString() {
		std::string s = sign == PLUS ? "" : "-";
		s += PositiveNumber::toString();
		return s;
	}
	void flipSign() {
		if (this->digits.size() == 0) //is zero
			this->sign = PLUS;
		if (this->sign == MINUS)
			this->sign = PLUS;
		else
			this->sign = MINUS;
	}
	void multiplyBy(SignedNumber other) {
		PositiveNumber::multiplyBy(other);
		this->sign = (this->sign == other.sign) ? PLUS : MINUS;
	}

	/*
	* Implemented by Vlad Avramenko
	*/

	//Division for SignedNumbers
	SignedNumber operator/(SignedNumber& other) {
		return divide(*this, other);
	}

	PositiveNumber toUnsigned() {
		if (this->sign == MINUS) {
			return PositiveNumber(this->toString().substr(1, this->digits.size()));
		}
		else {
			return PositiveNumber(this->toString());
		}
	}

	SignedNumber divide(SignedNumber n1, SignedNumber n2) {
		PositiveNumber p1 = n1.toUnsigned();
		PositiveNumber p2 = n2.toUnsigned();
		PositiveNumber num = PositiveNumber::divide(p1, p2);
		if (n1.sign != n2.sign && num.toString() != "0") {
			return SignedNumber(num, MINUS);
		}
		else {
			return SignedNumber(num, PLUS);
		}
	}

	SignedNumber operator%(SignedNumber& other) {
		return remainder(*this, other);
	}

	SignedNumber remainder(SignedNumber n1, SignedNumber n2) {
		PositiveNumber p1 = n1.toUnsigned();
		PositiveNumber p2 = n2.toUnsigned();
		PositiveNumber num = PositiveNumber::remainder(p1, p2);
		if (n1.sign == MINUS && num.toString() != "0") {
			return SignedNumber(num, MINUS);
		}
		else {
			return SignedNumber(num, PLUS);
		}
	}

	Sign getSign() {
		return this->sign;
	}
};
