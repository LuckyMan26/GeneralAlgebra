#pragma once
#include "FiniteNumber.h"
#include "MillerRabin.h"
#include <vector>

/*
	Implemented by Oleksii Onishchenko and Dmytro Mandziuk 
*/
namespace PollardFactorization {
	template<typename NumberType>
	NumberType modular_pow(NumberType base, NumberType exponent, NumberType modulus) {

		NumberType result = NumberType(1);

		while (exponent > NumberType(0))
		{
			/* if y is odd, multiply base with result */
			if (exponent % NumberType(2) == NumberType(0))
				result = (result * base) % modulus;

			/* exponent = exponent/2 */
			exponent = exponent / NumberType(2);

			/* base = base * base */
			base = (base * base) % modulus;
		}
		return result;
	}

	template<typename NumberType>
	std::vector<NumberType> pollardRho(NumberType n) {
		std::vector<NumberType> result;

		if (n == NumberType(1)) {
			result.push_back(n);
			return result;
		}

		NumberType x = NumberType(rand()) % ((n - NumberType(2))) + NumberType(2);
		//NumberType x = (NumberType(2));
		NumberType y = x;
		NumberType c = (NumberType(rand()) % (n - NumberType(1))) + NumberType(1);
		//NumberType c = (NumberType(1));
		NumberType d = NumberType(1);

		while (d == NumberType(1))
		{
			/* Tortoise Move: x(i+1) = f(x(i)) */
			x = (modular_pow(x, NumberType(2), n) + c + n) % n;

			/* Hare Move: y(i+1) = f(f(y(i))) */
			y = (modular_pow(y, NumberType(2), n) + c + n) % n;
			y = (modular_pow(y, NumberType(2), n) + c + n) % n;

			/* check gcd of |x-y| and n */
			if(x > y)
				d = NumberType::GCD(x - y, n);
			else
				d = NumberType::GCD(y - x, n);

			/* retry if the algorithm fails to find prime factor
			 * with chosen x and c */
			if (d == n) break;
		}

		if (MillerRabin::miller_rabin(d)) {
			result.push_back(d);
		}

		else {
			std::vector<NumberType> add = pollardRho(d);
			result.insert(result.end(), add.begin(), add.end());
		}

		n = n / d;

		if (MillerRabin::miller_rabin(n)) {
			result.push_back(n);
		}

		else {
			std::vector<NumberType> add = pollardRho(n);
			result.insert(result.end(), add.begin(), add.end());
		}

		return result;
	}

	template<typename NumberType>
	std::map<NumberType, int> factorizePoll(NumberType n) {
		std::srand(time(NULL));
		std::vector<NumberType> result = pollardRho(n);
		std::sort(result.begin(), result.end());
		std::map<NumberType, int> mapOfFactors;
		for (NumberType item : result) {
			if (item != NumberType(1)) {
				if (mapOfFactors.find(item) == mapOfFactors.end()) {
					mapOfFactors.insert(std::pair<NumberType, int>(item, 1));
				}
				else {
					mapOfFactors[item]++;
				}
			}
		}
		return mapOfFactors;
	}
};