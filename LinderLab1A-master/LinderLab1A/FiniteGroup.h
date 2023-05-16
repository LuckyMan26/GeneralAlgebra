#pragma once

#include <vector>
#include <algorithm>
#include <cassert>
#include <exception>

#include "FiniteNumber.h"
#include "Pollard.h"
#include "MillerRabin.h"
#include "Exponent.h"
#include "Euler.h"


// Created by Y.Kishchuk and T.Pysarenkov
class FiniteGroup {
public:
    FiniteGroup(const FiniteField& f) : factorization(*(new std::map<PositiveNumber, int>()))
    {
        this->f = f;
        this->identitySet = true;
        this->identity = FiniteNumber(PositiveNumber("1"), f.getP());
        this->order = Euler(f.getP());
        this->factorization = map_factors(order, PollardFactorization::pollardRho<PositiveNumber>);
    }

    // Binary operation method
    FiniteNumber operate(const FiniteNumber& a, const FiniteNumber& b) const {
        auto temp_p = this->getP();
        //assert(a.getP().equals(temp_p) && b.getP().equals(temp_p), "Elements have different P");
        return a * b;
    }

    FiniteNumber getIdentity() const {
        //assert(identitySet, "Identity element is not set");
        return identity;
    }

    PositiveNumber getP() const {
        return f.getP();
    }

    void setIdentity(const FiniteNumber& element) {
        //assert(element.getP().equals(this->getP()), "Element has different P");
        identity = element;
        identitySet = true;
    }

    // Determining the order of a group element (currently multiplicative)
    PositiveNumber ElementOrder(const FiniteNumber& element) const {
        assert(identitySet);
        assert(element.getP() == this->getP());

        auto n = order;
        auto t = n;
        
        Exponentiation exp;
        for (const auto& mult : factorization) {
            t = t / exp.fastExponentiation(mult.first, mult.second);
            FiniteNumber elem1;

            elem1 = exp.fastExponentiation(element, t);

            while (elem1 != identity) {
                elem1 = exp.fastExponentiation(elem1, mult.first);

                t = t * mult.first;

                if (t > n)
                    throw std::overflow_error("Infinite order");
            }
        }

        return t;
    }

    //Determining whether the input element is a generator of a multiplicative group modulo p
    bool isGenerator(const FiniteNumber& element) const {
        assert(identitySet);
        assert(element.getP() == this->getP());
        if (element.toString() == "" || element.toString() == "0" || element.GCD(element, this->getP()) != 1)
            throw std::runtime_error("Element is not a member of the group");

        auto n = order;

        Exponentiation exp;
        for (const auto& mult : factorization)//for every prime factor of n
        {
            auto b = exp.fastExponentiation(element, n / mult.first);
            if (b == identity)
                return false;//the element is a generator if and only if (element)^(n/q) and 1 are not congruent modulo p,
                //where n is order of the group, q is (any) prime factor of n
        }
        return true;
    }

private:
    FiniteNumber identity = FiniteNumber("1 x10"); // Identity element
    bool identitySet = false; // Flag to indicate if the identity element is set
    bool orderSet = false;
    FiniteField f;
    PositiveNumber order; // Order of the group

    // Prime factorization of the group order
    std::map<PositiveNumber, int>& factorization;
};
