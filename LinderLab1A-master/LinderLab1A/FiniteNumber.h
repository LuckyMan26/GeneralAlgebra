#pragma once
#include "PositiveNumber.h"
#include <cassert>
#include "FiniteField.h"
//Created by M.Tyshchenko
//Modified by A.Volyk
//Modified by V.Horbanov

class FiniteNumber : public PositiveNumber {
private: 
	//p stands for field (����)
	FiniteField f;
	void setP(PositiveNumber p, bool gotNegativeBase = false) {
		f.setP(p);
		toFieldSize(gotNegativeBase);
	}

public:
	FiniteNumber() {}

	FiniteNumber(PositiveNumber base, PositiveNumber p) {
		f = (FiniteField(p));
		this->digits = base.getDigits();
		toFieldSize();
	}
	FiniteNumber(std::vector<int> v, FiniteField f_) : f(f_.getP()) {
		digits = v;
		toFieldSize();

	}
	FiniteNumber(std::string from, PositiveNumber p) {
		bool negativeBase = parseIsNegative(from);
		this->digits = parseDigits(from);
		setP(p, negativeBase);
	}

	FiniteNumber(long long a, long long p) : PositiveNumber(a) {
		this->f = FiniteField(PositiveNumber(p));
		toFieldSize();
	}

	FiniteNumber(long long a, long long p) : PositiveNumber(a) {
		this->f = FiniteField(PositiveNumber(p));
		toFieldSize();
	}
	/**
	* Input: string of value "xP N", where P - is field size, N - positive integer
	* Alternative: "N xP"
	* Alternative: "P N"
	*/
	FiniteNumber(std::string from) {
		std::string partOne = from.substr(0, from.find_first_of(' '));
		std::string partTwo = from.substr(from.find_first_of(' ') + 1);
		std::string p;
		std::string n;
		if (partOne[0] == 'x') {
			p = partOne.substr(1);
			n = partTwo;
		}
		else if (partTwo[0] == 'x') {
			p = partTwo.substr(1);
			n = partOne;
		}
		else {
			p = partOne;
			n = partTwo;
		}
		bool negativeBase = parseIsNegative(from);
		this->digits = parseDigits(n);
		setP(p, negativeBase);
	}

	PositiveNumber getP() const {
		return f.getP();
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
	friend FiniteNumber operator*(FiniteNumber left, const FiniteNumber& n) {
		return left.toFinite(left.simpleMultiplication(n));
	}
	//FiniteNumber operator*(const FiniteNumber& n) {
	//	return this->toFinite(simpleMultiplication(n));
	//}
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
	bool operator>(FiniteNumber& n) const {
		PositiveNumber p1 = getP();
		PositiveNumber p2 = n.getP();
		if (p1 != p2)
			return false;
		return PositiveNumber::operator>(n);
	}

	bool operator>=(FiniteNumber& n) const {
		PositiveNumber p1 = getP();
		PositiveNumber p2 = n.getP();
		if (p1 != p2)
			return false;
		return PositiveNumber::operator<=(n);
	}
	bool operator<(FiniteNumber& n) const {
		PositiveNumber p1 = getP();
		PositiveNumber p2 = n.getP();
		if (p1 != p2)
			return false;
		return PositiveNumber::operator<(n);
	}
	bool operator<=(FiniteNumber& n) const {
		PositiveNumber p1 = getP();
		PositiveNumber p2 = n.getP();
		if (p1 != p2)
			return false;
		return PositiveNumber::operator<=(n);
	}


	bool operator==(FiniteNumber& n) const {
		return equals(n);
	}
	bool operator!=(FiniteNumber& n) const {
		return !equals(n);
	}
	bool equals(FiniteNumber& n) const {
		PositiveNumber p1 = getP();
		PositiveNumber p2 = n.getP();
		if (p1 != p2)
			return false;
		return PositiveNumber::equals(n);
	}


	/*
	* Find inverse number
	* if inverse number exists - finds inverse, else - returns 1
	*/
	FiniteNumber inverse() {
		PositiveNumber p = getP();
		PositiveNumber n = getP();
		PositiveNumber g(this->toString());
		PositiveNumber gcd = GCD(n, g);
		if (g.toString() == "1" || gcd.toString() != "1") {
			return FiniteNumber("1", getP());
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
			return FiniteNumber((p - s1_pos), p);
		}
		else {
			return FiniteNumber(s1, p);
		}
	}

	void divideBy(FiniteNumber num) {
		PositiveNumber p1 = getP();
		PositiveNumber p2 = num.getP();
		if (p1 != p2) {
			return;
		}
		*this *= num.inverse();
	}

	FiniteNumber divide(FiniteNumber num) {
		PositiveNumber p1 = getP();
		PositiveNumber p2 = num.getP();
		if (p1 != p2) {
			return FiniteNumber("1", this->getP());
		}
		return *this * num.inverse();
	}
	//Converts PositiveNumber to field size
	void toFieldSize(bool gotNegativeBase = false) {
		PositiveNumber p = getP();

		if (gotNegativeBase) { //Negative base
			PositiveNumber t = PositiveNumber(*this);
			if (t == p) {
				t = t % (p);
			}
			else {
				t = p - (t % (p));
			}
			this->digits = t.getDigits();
		}
		else { //Positive base
			if (p > *this) { //mod is greater than base
				return;
			}
			else { //otherwise
				PositiveNumber t = PositiveNumber(*this);
				t = t % (p);
				this->digits = t.getDigits();
			}
		}
	}
	// Converts PositiveNumber to FiniteNumber
	FiniteNumber toFinite(PositiveNumber num) {
		PositiveNumber p = getP();
		FiniteNumber res(num.toString(), p);
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
			n = n % p;
			this->digits = n.getDigits();
		}
	}

	FiniteNumber shift(int numDigits) {
		PositiveNumber p = getP();
		FiniteNumber number = FiniteNumber(*this);
		if (numDigits < 0) {
			for (int i = 0; i < -numDigits && number.digits.size()>0; i++) {
				number.digits.erase(number.digits.begin());
			}
		}
		else {
			for (int i = 0; i < numDigits; i++) {
				number.digits.insert(number.digits.begin(), 0);
			}
		}
		return FiniteNumber(number, p);
	}

	static bool parseIsNegative(std::string str) {
		
		bool gotMinus = false;

		for (char ch : str) {
			if (ch == '-') {
				if (gotMinus) {
					throw std::runtime_error("Incorrect argument syntax");
				}
				else {
					gotMinus = true;
				}
			}
		}

		return gotMinus;
    
	// Calculates a^b mod n
	FiniteNumber power_mod(PositiveNumber b) {     // power_mod modulo exponentiation calculation
		FiniteNumber a(*this);
		FiniteNumber res("1", f.getP());
		FiniteNumber zero("0");
		PositiveNumber zeroPositive(0);
		PositiveNumber two(2);
		while (b > zero) {
			if ((b % two) != zero) {
				res = (res * a);
			}
			a = (a * a);
			a.toFieldSize();
			b = b / two;
		}
		res.toFieldSize();
		return res;
	}
    
	// Finds a^((p+1)/2) mod p, where p is a prime number
	FiniteNumber tonelli_shanks() {            // tonelli_shanks to calculate the square root
		PositiveNumber q = f.getP() - 1;      // long long: represents an integer in the range from -9223372036854775808 to +9223372036854775807.
		PositiveNumber two(2);
		PositiveNumber zero("0");
		PositiveNumber four("4");
		FiniteNumber zeroFinite("0", f.getP());
		FiniteNumber oneFinite("1", f.getP());
		int s = 0;
		FiniteNumber temp(f.getP() - 1, f.getP());
		while ((q % two).isZero() || (q % two) == zero) {
			q = q / two;
			s += 1;
		}
		if (s == 1) {
			return this->power_mod((f.getP() + PositiveNumber("1")) / four);
		}
		FiniteNumber h("2", f.getP());
		for (; h.power_mod((f.getP() - 1) / two) != temp; h = h + oneFinite) {}
		FiniteNumber c = h.power_mod(q);
		FiniteNumber r = power_mod((q + oneFinite) / two);
		FiniteNumber t = power_mod(q);
		int n = s;
		while (t != oneFinite) {
			FiniteNumber tt = t;
			int i;
			for (i = 1; i < n; i++) {
				tt = (tt * tt);

				if (tt == oneFinite) {
					break;
				}
			}
			FiniteNumber b = c.power_mod(n - i - 1);
			r = (r * b);
			c = (b * b);
			t = (t * c);
			n = i;
		}
		return r;

	}
};