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
    
        return (exp.fastExponentiation(number, degree) - exp.fastExponentiation(number, degree - 1));
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
PositiveNumber CarmichelForPrimePower(PositiveNumber prime,PositiveNumber degree) {
    if (prime == PositiveNumber("2") && prime == PositiveNumber("2") || prime == PositiveNumber("4"))
        return (EulerForPrimeValues(prime, degree));
    if (prime != PositiveNumber("2") || prime == PositiveNumber("2") || prime == PositiveNumber("4"))
        return (EulerForPrimeValues(prime, degree));
}
PositiveNumber Carmichel(PositiveNumber number) {

    std::map<PositiveNumber, int> factorization = map_factors(number, PollardFactorization::pollardRho<PositiveNumber>);

    if (factorization.size()==1  && factorization.begin()->first == PositiveNumber("2") && factorization.begin()->second > 2)
        return (EulerForPrimeValues(PositiveNumber("2"), factorization.begin()->second)/2);
    if (factorization.size() == 1 && factorization.begin()->first != PositiveNumber("2") || number==PositiveNumber("2") || number == PositiveNumber("4"))
        return (EulerForPrimeValues(factorization.begin()->first, factorization.begin()->second));

    else
    {
        PositiveNumber answer("1");
        int counter = 1;

        for (auto it = factorization.begin(); it != factorization.end(); ++it)
        {

            answer = PositiveNumber::LCM(CarmichelForPrimePower(it->first,it->second), answer);

        }

        return answer;
    }
}