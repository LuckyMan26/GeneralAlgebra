#pragma once
#include "PositiveNumber.h"
//Created by M.Tyshchenko
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
		* Implemented by Vlad Avramenko
	*/

	friend FiniteNumber operator+(FiniteNumber left, const FiniteNumber& n) {
		left.addTo(n);
		left.toFieldSize();
		return left;
	}
	FiniteNumber& operator+=(const FiniteNumber& n) {
		this->addTo(n);
		this->toFieldSize();
		return *this;
	}
	FiniteNumber operator*(const FiniteNumber& n) {
		return this->toFinite(simpleMultiplication(n));
	}
	FiniteNumber operator*=(const FiniteNumber& n) {
		this->multiplyBy(n);
		this->toFieldSize();
		return *this;
	}
	friend FiniteNumber operator-(FiniteNumber left, const FiniteNumber& n) {
		left.substract(n);
		left.toFieldSize();
		return left;
	}
	FiniteNumber& operator-=(const FiniteNumber& n) {
		this->substract(n);
		this->toFieldSize();
		return *this;
	}

	/*
	* Find inverse number
	*/
	FiniteNumber inverse() const {
		
	}
	//Converts PositiveNumber to field size
	void toFieldSize() {
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

	FiniteNumber toFinite(PositiveNumber num) {
		FiniteNumber res(num.toString(), this->p);
		res.toFieldSize();
		return res;
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

