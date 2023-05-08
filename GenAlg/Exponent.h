#pragma once
#include "FiniteNumber.h"
#include "SignedNumber.h"

class Exponentiation {
private:
	PositiveNumber toMontgomery(FiniteNumber x, int shiftBy) {
		return x.shift(shiftBy);
	}
	
	PositiveNumber redcSlow(PositiveNumber R, PositiveNumber N, PositiveNumber Ninv, PositiveNumber T, int shiftBy) {
		FiniteNumber m = FiniteNumber(FiniteNumber(T, R) * FiniteNumber(Ninv, R), R);
		PositiveNumber t = (T + N * m).shift(-shiftBy);
		return t < N ? t : N - t;
	}
	PositiveNumber redc2(PositiveNumber x, PositiveNumber k,PositiveNumber R, PositiveNumber p, int shiftBy) {
		PositiveNumber s = (x * k);
		s = s.first(shiftBy);
		PositiveNumber t = x + s * p;
		PositiveNumber u = t.shift(-shiftBy);
		return u < p ? u : u - p;
	}

	FiniteNumber twoMultiplication(FiniteNumber a, FiniteNumber b) {
		if (a.isZero())
			return a;
		if (b.isZero())
			return b;
		return a;
		
	}

	FiniteNumber twoExponentiation(FiniteNumber base, PositiveNumber power) {
		if (power == PositiveNumber("0")) {
			return FiniteNumber("x2 1");
		}
		return base;

	}


public:
	Exponentiation() {
	}

	FiniteNumber montgomeryMultiplication(FiniteNumber a, FiniteNumber b) {
		PositiveNumber p = a.getP();
		if (p == PositiveNumber("5")) { //gcd(R, N) must be 1, but for gcd(10^N, 5) it is 5; Therefore using standart multiplication here
			return FiniteNumber(a*b, p);
		}
		if (p == PositiveNumber("2")) {
			return twoMultiplication(a, b); //10 is divisible by 2, using special function for this case
		}
		PositiveNumber rNum = PositiveNumber("10000");
		int shift = 4;
		int sizeDifference = p.getDigits().size() - 4;
		rNum = rNum.shift(sizeDifference);
		shift += sizeDifference;
		FiniteNumber rInv = FiniteNumber(rNum, p).inverse();
		PositiveNumber rInvPositive = rInv;
		PositiveNumber k = (rInvPositive.shift(shift) - PositiveNumber("1")) / p;
		PositiveNumber aM = toMontgomery(a, shift);
		PositiveNumber bM = toMontgomery(b, shift);
		PositiveNumber x = aM * bM;
		PositiveNumber s = redc2(x, k, rNum, p, shift);
		return FiniteNumber(s * rInv, p);
	}
	/**
	* Eponention using Montgomery algorithm
	* Implemented by M. Tyshchenko
	*/
	FiniteNumber montgomeryExponentiation(FiniteNumber base, PositiveNumber power) {
		//Initializing variables
		PositiveNumber rNum = PositiveNumber("10000");
		int shift = 4;
		PositiveNumber p = base.getP();
		if (p == PositiveNumber("5")) {
			return fastExponentiation(base, power); //if we used binary system insted of decimal, working with R = 2^N would be easier
		}
		if (p == PositiveNumber("2")) {
			return twoExponentiation(base, power);
		}
		//Setting R greater than P
		int sizeDifference = p.getDigits().size() - shift;
		rNum = rNum.shift(sizeDifference);
		shift += sizeDifference;
		
		//Initializing k and R^-1 mod P
		PositiveNumber res = rNum % p;
		FiniteNumber rInv = FiniteNumber(res, p).inverse();
		PositiveNumber rInvPositive = rInv;
		PositiveNumber k = (rInvPositive.shift(shift) - PositiveNumber("1")) / p;
		
		//Initializing a*R mod N
		PositiveNumber baseShifted = toMontgomery(base, shift);
		std::string powerBits = power.bitsReverse();
		int length = powerBits.length();
		for (int i = 0; i < length; i++) {
			if (powerBits[i] == '1') {
				res = res * baseShifted;
				res = redc2(res, k, rNum, p, shift);
			}
			baseShifted = baseShifted * baseShifted;
			baseShifted = redc2(baseShifted, k, rNum, p, shift);
		}
		return FiniteNumber(res * rInv, p);
	}
	/**
	* Exponentation without using montgomery form (for timing test)
	*/
	FiniteNumber fastExponentiation(FiniteNumber base, PositiveNumber power) {
		PositiveNumber p = base.getP();
		FiniteNumber res = FiniteNumber("1", p);
		std::string powerBits = power.bitsReverse();
		for (int i = 0; i < powerBits.length(); i++) {
			if (powerBits[i] == '1') {
				res = base * res;
			}
			base = base * base;
		}
		return res;
	}
	/**
	* Exponentation without using fast algorithm (for timing test)
	*/
	FiniteNumber slowExponentiation(FiniteNumber base, PositiveNumber power) {
		PositiveNumber p = base.getP();
		FiniteNumber res = FiniteNumber("1", p);
		PositiveNumber one = PositiveNumber("1");
		PositiveNumber zero = PositiveNumber("0");

		for (PositiveNumber i = zero; i < power; i = i + one) {
			res = res * base;
		}
		return res;
	}

	SignedNumber fastExponentiation(SignedNumber base, PositiveNumber power) {
		SignedNumber res = SignedNumber("1");
		std::string powerBits = power.bitsReverse();
		for (int i = 0; i < powerBits.length(); i++) {
			if (powerBits[i] == '1') {
				res = base * res;
			}
			base = base * base;
		}
		return res;
	}

	PositiveNumber fastExponentiation(PositiveNumber base, PositiveNumber power) {
		PositiveNumber res = PositiveNumber("1");
		std::string powerBits = power.bitsReverse();
		for (int i = 0; i < powerBits.length(); i++) {
			if (powerBits[i] == '1') {
				res = base * res;
			}
			base = base * base;
		}
		return res;
	}

	
};
