#pragma once
#include "FiniteNumber.h"
#include<chrono>
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

	FiniteNumber montgomeryMultiplication2(FiniteNumber a, FiniteNumber b) {
		PositiveNumber rNum = PositiveNumber("10000");
		int shift = 4;
		PositiveNumber p = a.getP();
		while (rNum < p) { //r has to be greater than p
			rNum = rNum.shift(1);
			shift++;
		}
		FiniteNumber rInv = FiniteNumber(rNum, p).inverse();
		PositiveNumber rInvPositive = rInv;
		PositiveNumber k = (rInvPositive.shift(shift) - FiniteNumber("1")) / p;
		PositiveNumber aM = toMontgomery(a, shift);
		PositiveNumber bM = toMontgomery(b, shift);
		PositiveNumber x = aM * bM;
		PositiveNumber s = redc2(rNum, p, k, x, shift);
		return FiniteNumber(s * rInv, p);
	}
	/**
	* Eponention using montgomery algorithm
	* Problem: for-loop in montgomery form definitely works faster, but initialization takes too much time
	*/
	FiniteNumber montgomeryExponention(FiniteNumber base, PositiveNumber power) {
		//std::chrono::steady_clock::time_point t1= std::chrono::steady_clock::now();
		PositiveNumber rNum = PositiveNumber("10000");
		int shift = 4;
		PositiveNumber p = base.getP();
		int sizeDifference = p.getDigits().size() - 4;
		rNum = rNum.shift(sizeDifference);
		shift += sizeDifference;
		
		PositiveNumber res = rNum % p;
		FiniteNumber rInv = FiniteNumber(res, p).inverse();
		PositiveNumber rInvPositive = rInv;
		PositiveNumber k = (rInvPositive.shift(shift) - FiniteNumber("1")) / p;
		
		PositiveNumber baseShifted = toMontgomery(base, shift);
		//std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
		std::string powerBits = power.bitsReverse();
		//std::chrono::steady_clock::time_point t4 = std::chrono::steady_clock::now();
		//std::chrono::steady_clock::time_point t3 = std::chrono::steady_clock::now();
		//std::cout << "PreSet up = " << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << " ms" << std::endl;
		//std::cout << "Set up = " << std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count() << " ms" << std::endl;
		//std::cout << "Sum = " << std::chrono::duration_cast<std::chrono::microseconds>(t3 - t1).count() << " ms" << std::endl << std::endl;
		//std::cout << "Bits = " << std::chrono::duration_cast<std::chrono::microseconds>(t4 - t2).count() << " ms" << std::endl << std::endl;
		for (int i = 0; i < powerBits.length(); i++) {
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