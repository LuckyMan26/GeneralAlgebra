#pragma once
#include <vector>

// Wrapper around miller_rabin_do
template <typename NumberType>
bool miller_rabin(NumberType num, int max_iterations = 4)
{
	static NumberType zero = NumberType(0), one = NumberType(1), two = NumberType(2), four = NumberType(4);

	if (num < two || num == four)  return false;
	if (num < four) return true;

	// Find r such that  num - 1 = (2^d) * r  and r is odd
	NumberType d = num - one;
	while (d % two == zero)
	{
		d = d / two;
	}

	for (int i = 0; i < max_iterations; i++)
		if (!miller_rabin_do(d, num))
			return false;

	return true;
}

// (x^y) % p
template <typename NumberType>
NumberType power(NumberType x, NumberType y, NumberType p)
{
	NumberType res = NumberType(1);
	static NumberType zero = NumberType(0), two = NumberType(2);
	x = x % p;

	while (y > zero)
	{
		// If y is odd, multiply x with result
		if (y % two != zero)
			res = (res * x) % p;

		// y must be even now
		y = y / two; // y = y/2
		x = (x * x) % p;
	}

	return res;
}


template <typename NumberType>
bool miller_rabin_do(NumberType r, NumberType n)
{
	static NumberType one = NumberType(1), two = NumberType(2);

	// a = random number from [2, n-2]
	NumberType random_num = NumberType(2) + two % (n - NumberType(4));

	// y = (random_num ^ r) mod n
	NumberType y = power(random_num, r, n);

	while (r != n - one)
	{
		y = (y * y) % n;
		r *= two;

		NumberType temp = NumberType(n - 1);

		if (y == one)      return false;
		if (y == temp)    return true;
	}

	// Return composite
	return false;
}