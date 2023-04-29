#pragma once
#include <vector>


/*
	Implemented by Dmytro Mandziuk and Oleksii Onishchenko
*/
template <typename NumberType>
NumberType mod_power(NumberType base, NumberType exp, NumberType mod)
{
	NumberType res = NumberType(1);
	base = base % mod;

	while (exp > NumberType(0))
	{
		// If y is odd, multiply x with result
		if (exp % NumberType(2) != NumberType(0))
			res = (res * base) % mod;

		// y must be even now
		exp = exp / NumberType(2); // y = y/2
		base = (base * base) % mod;
	}

	return res;
}

namespace MillerRabin {
	// (base^exp) % mod
	template <typename NumberType>
	bool miller_rabin_do(NumberType r, NumberType n)
	{
		// a = random number from [2, n-2]
		NumberType random_num = NumberType(2) + NumberType(rand()) % (n - NumberType(4));

		// y = (random_num ^ r) mod n
		NumberType y = mod_power(random_num, r, n);

		if (y == 1 || y == n - 1)
			return true;

		while (r != n - NumberType(1))
		{
			y = (y * y) % n;
			r *= NumberType(2);

			if (y == NumberType(1))      return false;
			if (y == NumberType(n - 1))    return true;
		}

		// Return composite
		return false;
	}

	// Wrapper around miller_rabin_do
	template <typename NumberType>
	bool miller_rabin(NumberType num, int max_iterations = 4)
	{
		std::srand(time(NULL));

		if (num <= NumberType(1) || num == NumberType(4))  return false;
		if (num <= NumberType(3)) return true;

		// Find r such that  num - 1 = (2^d) * r  and r is odd
		NumberType d = num - NumberType(1);
		while (d % NumberType(2) == NumberType(0))
		{
			d = d / NumberType(2);
		}

		for (int i = 0; i < max_iterations; i++)
			if (!miller_rabin_do(d, num))
				return false;

		return true;
	}
}