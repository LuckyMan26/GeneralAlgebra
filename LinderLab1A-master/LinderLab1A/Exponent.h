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
	FiniteNumber pow(FiniteNumber base, PositiveNumber power) {
		return FiniteNumber("0");
	}

	FiniteNumber montgomeryMultiplication(FiniteNumber a, FiniteNumber b) {
		PositiveNumber rNum = PositiveNumber("10000");
		int shift = 4;
		PositiveNumber p = a.getP();
		while (rNum < p) { //r has to be greater than p
			rNum = rNum.shift(1);
			shift++;
		}
		std::cout << FiniteNumber(rNum, p).inverse().toString() << std::endl;
		PositiveNumber k =  (rNum * FiniteNumber(rNum, p).inverse() - FiniteNumber("1")) / p;
		std::cout << k.toString() << std::endl;
		PositiveNumber aM = toMontgomery(a, shift);
		PositiveNumber bM = toMontgomery(b, shift);
		PositiveNumber x = aM * bM;
		FiniteNumber s = FiniteNumber(x * k, rNum);
		PositiveNumber t = x + p * s;
		PositiveNumber u = t.shift(shift);
		// origin: u < n ? u : u - n
		return FiniteNumber(redc(rNum, p, k, t, shift), p);
	}
};