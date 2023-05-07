#pragma once
#include "Pollard.h"
#include "Exponent.h"
//Created mt V.Harlov
//Improoved by Artem Volyk
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
    if (MillerRabin::miller_rabin(number))
        return EulerForPrimeValues(number);

    else
    {
        PositiveNumber answer("1");
        int counter = 1;
       
        std::map<PositiveNumber, int> factorization = map_factors(number, PollardFactorization::pollardRho<PositiveNumber>);
        for (auto it = factorization.begin(); it != factorization.end(); ++it)
        {
            
            answer *= EulerForPrimeValues(it->first, PositiveNumber(it->second));

        }

        return answer;
    }
}
