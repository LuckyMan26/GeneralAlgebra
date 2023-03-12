#pragma once
#include "PositiveNumber.h"

class FiniteNumber : public PositiveNumber {
private: 
	PositiveNumber p = PositiveNumber("10");
	void setP(PositiveNumber p) {
		this->p = p;
		toFieldSize(p.toString(), this->toString());
	}

public:
	FiniteNumber(std::string from, PositiveNumber p) {
		this->digits = parseDigits(from);
		setP(p);
	}
	/**
	* Input: string of value "xP N", where P - is field size, N - positive integer
	*
	*/
	FiniteNumber(std::string from) {
		if (from[0] == 'x') {
			from = from.substr(1);
		}
		std::string p = from.substr(0, from.find_first_of(' '));
		std::string n = from.substr(from.find_first_of(' ')+1);
		this->digits = parseDigits(n);
		setP(p);
	}

	/*
	* Find multiplicative inverse number
	*/

	PositiveNumber inverse() const {

	}

	void toFieldSize() {
		//TODO
		if (p > *this) {
			return;
		}
		else {
			PositiveNumber t = PositiveNumber(*this);
			while (t >= p) {
				t -= p;
			}
			this->digits = parseDigits(t.toString());
		}
	}

	void toFieldSize(std::string p_str, std::string n_str) {
		PositiveNumber p = PositiveNumber(p_str);
		PositiveNumber n = PositiveNumber(n_str);
		if (p > n) {
			return;
		}
		else {
			while (n >= p) {
				n -= p;
			}
			this->digits = parseDigits(n.toString());
		}
	}
};

