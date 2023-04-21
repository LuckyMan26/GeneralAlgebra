#pragma once
#include "FiniteNumber.h"
#include <vector>

template<typename NumberType>
class PollardFactorization {

public:

	bool isPrime(NumberType a) {
		return false;
	}

	
	NumberType modular_pow(NumberType base, NumberType exponent, NumberType modulus) {

		NumberType result = NumberType(1);

		while (exponent > NumberType(0))
		{
			/* if y is odd, multiply base with result */
			if (exponent % NumberType(2) == NumberType(0))
				result = (result * base) % modulus;

			/* exponent = exponent/2 */
			exponent = exponent/NumberType(2);

			/* base = base * base */
			base = (base * base) % modulus;
		}
		return result;
	}



	std::vector<NumberType> pollardRho(NumberType n) {
		std::srand(time(NULL));
		std::vector<NumberType> result;

		if (n == 1) {
			result.push_back(n);
			return result;
		}
	
		NumberType x = NumberType(rand()) % ((n - NumberType(2))) + NumberType(2);
		NumberType y = x;
		NumberType c = (NumberType(rand()) % (n - NumberType(2))) + NumberType(1);
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
			if (d == n) return pollardRho(n);
		}

		result.push_back(d);

		n /= d;

		//TODO (isPrimeCheck)
		if (isPrime(n)) {
			result.push_back(d);
		}
		else {
			std::vector<NumberType> add = pollardRho(n);
			add.insert(result.end(), add.begin(), add.end());
		}

		return result;

	}

	


};