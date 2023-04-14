#pragma once
#include "FiniteNumber.h"

class Exponentiation {
private:
	PositiveNumber* fieldN = nullptr;

	FiniteNumber toMontgomery(FiniteNumber x, PositiveNumber R) {
		return FiniteNumber::tempMultiply(x, R);
	}
	FiniteNumber fromMontgomery(FiniteNumber x, PositiveNumber R) {
		return FiniteNumber::tempMultiply(x, FiniteNumber(R, x.getP()).inverse());
	}
	FiniteNumber montgomeryMultiplication(FiniteNumber a, FiniteNumber b) {
		PositiveNumber rNum = PositiveNumber("1048576"); //2^20; 
		int shift = 20;
		PositiveNumber p = a.getP();
		while (rNum < p) { //r has to be greater than p
			rNum *= PositiveNumber("2");
			shift++;
		}
		PositiveNumber k = (rNum * FiniteNumber(rNum, a.getP()).inverse() - FiniteNumber("1")); // / p;
		FiniteNumber aM = toMontgomery(a, rNum);
		FiniteNumber bM = toMontgomery(b, rNum);
		PositiveNumber x = aM * bM;
		FiniteNumber s = FiniteNumber(x * k, rNum);
		PositiveNumber t = x + s * p;
		PositiveNumber u = t; // / rNum;
		FiniteNumber cM = FiniteNumber(u, p); // origin: u < n ? u : u - n
		return fromMontgomery(cM, rNum);
	}
	PositiveNumber redc(PositiveNumber R, PositiveNumber N, PositiveNumber Ninv, PositiveNumber T) {
		FiniteNumber m = FiniteNumber(FiniteNumber(T, R) * Ninv, R);
		PositiveNumber t = (T + m * N); // / R;
		return t < N ? t : N - t;
	}

public:
	Exponentiation(PositiveNumber* fieldN) {
		this->fieldN = fieldN;
	}
	FiniteNumber pow(FiniteNumber base, PositiveNumber power) {
		return FiniteNumber("0");
	}
};