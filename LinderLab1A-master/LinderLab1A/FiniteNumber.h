#pragma once
#include "PositiveNumber.h"
//Created by M.Tyshchenko
class FiniteNumber : public PositiveNumber {
private: 
	//p stands for field (поле)
	PositiveNumber p = PositiveNumber("10");
	void setP(PositiveNumber p) {
		this->p = p;
		toFieldSize(p.toString(), this->toString());
	}

public:

	FiniteNumber(PositiveNumber base, PositiveNumber p) {
		this->p = p;
		this->digits = base.getDigits();
		this->toFieldSize();
	}

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

	/*
	* overloaded operators
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

	friend FiniteNumber operator/(FiniteNumber left, const FiniteNumber& n) {
		return left.divide(n);
	}

	/*
	* Find inverse number
	* if inverse number exist - finds inverse, else - returns 1
	*/
	FiniteNumber inverse() {
		PositiveNumber n = p;
		PositiveNumber g(this->toString());
		PositiveNumber gcd = GCD(n, g);
		if (g.toString() == "1" || gcd.toString() != "1") {
			return FiniteNumber("1", p);
		}
		// remainder = (t0*n + s0*g) + d*(t1*n + s1*g)
		// t0 and t1 are omitted because we don`t need them
		SignedNumber s0("0"), s1("1");
		while (true) {
			SignedNumber d("0");
			
			while (n >= g) {
				n -= g;
				d.addTo(SignedNumber("-1"));
			}
			SignedNumber temp_s = s0;
			s0 = s1;
			d.multiplyBy(s1);
			s1 = temp_s;
			s1.addTo(d);
			if (n.toString() == "1") {
				break;
			}
			else {
				PositiveNumber temp = n;
				n = g;
				g = temp;
			}
		}
		if (s1.getSign() == MINUS) {
			PositiveNumber s1_pos(s1);
			while (s1_pos > p) {
				s1_pos -= p;
			}
			return FiniteNumber((p - s1_pos).toString(), this->p);
		}
		else {
			return FiniteNumber(s1.toString(), this->p);
		}
	}

	void divideBy(FiniteNumber num) {
		if (this->p != num.p) {
			return;
		}
		*this *= num.inverse();
	}

	FiniteNumber divide(FiniteNumber num) {
		if (this->p != num.p) {
			return FiniteNumber("1", this->p);
		}
		return *this*num.inverse();
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
	// Converts PositiveNumber to FiniteNumber
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

	static FiniteNumber tempMultiply(FiniteNumber a, FiniteNumber b) {
		FiniteNumber s = (a * b);
		s.toFieldSize();
		return s;
	}
};

