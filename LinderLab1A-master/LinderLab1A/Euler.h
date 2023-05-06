#pragma once
#include "Pollard.h"
#include "Exponent.h"

PositiveNumber EulerForPrimeValues(PositiveNumber number, PositiveNumber degree = PositiveNumber("1"))
{
    PositiveNumber one = PositiveNumber("1");

    if (number == one)
    {
        return number;
    }

    if (degree > one)
    {
        Exponentiation exp;
        return (exp.fastExponention(number, degree) - exp.fastExponention(number, degree - 1));
    }

    else
    {
        return (number - 1);
    }
}

PositiveNumber Euler(PositiveNumber number)
{
    if (number.is_prime())
        return EulerForPrimeValues(number);

    else
    {
        PositiveNumber answer("1");
        int counter = 1;
        std::vector<PositiveNumber> primes = naiveFactorization(number);

        for (int i = 0; i < primes.size(); i += counter, counter = 1)
        {
            for (int k = i; k < (primes.size() - 1) && primes[k] == primes[k + 1]; k++)
            {
                counter++;
            }
            answer *= EulerForPrimeValues(primes[i], PositiveNumber(counter));

        }

        return answer;
    }
}