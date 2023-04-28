#pragma once
#include "FiniteNumber.h"

class Exponentiation {
private:

	FiniteNumber toMontgomery(FiniteNumber x, int shiftBy) {
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

public:
	Exponentiation() {
	}
	/**
	* Deprecated;
	* Use montgomery multiplication instread
	*/
	FiniteNumber montgomeryMultiplicationDeprecated(FiniteNumber a, FiniteNumber b) {
		PositiveNumber rNum = PositiveNumber("10000");
		int shift = 4;
		PositiveNumber p = a.getP();
		while (rNum < p) { //r has to be greater than p
			rNum = rNum.shift(1);
			shift++;
		}
		FiniteNumber rInv = FiniteNumber(rNum, p).inverse();
		PositiveNumber k =  (rNum * FiniteNumber(rNum, p).inverse() - FiniteNumber("1")) / p;
		PositiveNumber aM = toMontgomery(a, shift);
		PositiveNumber bM = toMontgomery(b, shift);
		PositiveNumber x = aM * bM;
		PositiveNumber s = x * rInv;
		return FiniteNumber(redcSlow(rNum, p, k, s, shift), p);
	}

	FiniteNumber montgomeryMultiplication(FiniteNumber a, FiniteNumber b) {
		PositiveNumber rNum = PositiveNumber("10000");
		int shift = 4;
		PositiveNumber p = a.getP();
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
	FiniteNumber montgomeryExponention(FiniteNumber base, PositiveNumber power) {
		//Initializing variables
		PositiveNumber rNum = PositiveNumber("10000");
		int shift = 4;
		PositiveNumber p = base.getP();

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
	FiniteNumber fastExponention(FiniteNumber base, PositiveNumber power) {
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
	FiniteNumber slowExponention(FiniteNumber base, PositiveNumber power) {
		PositiveNumber p = base.getP();
		FiniteNumber res = FiniteNumber("1", p);
		PositiveNumber one = PositiveNumber("1");
		PositiveNumber zero = PositiveNumber("0");

		for (PositiveNumber i = zero; i < power; i = i + one) {
			res = res * base;
		}
		return res;
	}

	SignedNumber fastExponention(SignedNumber base, PositiveNumber power) {
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

	PositiveNumber fastExponention(PositiveNumber base, PositiveNumber power) {
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