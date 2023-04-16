#pragma once
#include "FiniteNumber.h"

class Exponentiation {
private:

	PositiveNumber toMontgomery(FiniteNumber x, int shiftBy) {
		return x.shift(shiftBy);
	}

	FiniteNumber fromMontgomery(FiniteNumber x, int shiftBy, PositiveNumber P) {
		return FiniteNumber(x.shift(-shiftBy), P);
	}
	
	PositiveNumber redc(PositiveNumber R, PositiveNumber N, PositiveNumber Ninv, PositiveNumber T, int shiftBy) {
		FiniteNumber m = FiniteNumber(FiniteNumber(T, R) * FiniteNumber(Ninv, R), R);
		PositiveNumber t = (T + N * m).shift(-shiftBy);
		return t < N ? t : N - t;
	}

public:
	Exponentiation() {
	}

	FiniteNumber montgomeryMultiplication(FiniteNumber a, FiniteNumber b) {
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
		return FiniteNumber(redc(rNum, p, k, s, shift), p);
	}

	FiniteNumber montgomeryExponention(FiniteNumber base, PositiveNumber power) {
		PositiveNumber p = base.getP();
		FiniteNumber res = FiniteNumber("1", p);
		std::string powerBits = power.bits();
		reverse(powerBits.begin(), powerBits.end());
		for (int i = 0; i < powerBits.length(); i++) {
			if (powerBits[i] == '1') {
				res = montgomeryMultiplication(base, res);
			}
			base = montgomeryMultiplication(base, base);
		}
		return res;
	}
	/**
	* Exponentation without using montgomery form (for timing test)
	*/
	FiniteNumber fastExponention(FiniteNumber base, PositiveNumber power) {
		PositiveNumber p = base.getP();
		FiniteNumber res = FiniteNumber("1", p);
		std::string powerBits = power.bits();
		reverse(powerBits.begin(), powerBits.end());
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
};