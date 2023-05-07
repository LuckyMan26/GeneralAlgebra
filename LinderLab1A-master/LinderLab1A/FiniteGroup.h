#pragma once

#include <vector>
#include <algorithm>
#include <cassert>
#include <exception>

#include "FiniteNumber.h"
#include "Pollard.h"
#include "MillerRabin.h"
#include "Exponent.h"


// Created by Y.Kishchuk and T.Pysarenkov
class FiniteGroup {
public:
    FiniteGroup(const FiniteField& f) : factorization(*(new std::map<PositiveNumber, int>()))
    {
        this->f = f;
        this->identitySet = true;
        this->identity = FiniteNumber(PositiveNumber("1"), f.getP());
    }

    // Binary operation method
    FiniteNumber operate(const FiniteNumber& a, const FiniteNumber& b) const {
        auto temp_p = this->getP();
        assert(a.getP().equals(temp_p) && b.getP().equals(temp_p), "Elements have different P");
        return a * b;
    }

    FiniteNumber getIdentity() const {
        assert(identitySet, "Identity element is not set");
        return identity;
    }

    PositiveNumber getP() const {
        return f.getP();
    }

    void setIdentity(const FiniteNumber& element) {
        assert(element.getP().equals(this->getP()), "Element has different P");
        identity = element;
        identitySet = true;
    }

    // Determining the order of a group element (currently multiplicative)
    PositiveNumber ElementOrder(const FiniteNumber& element) const {
        assert(identitySet);
        assert(element.getP() == this->getP());

        if (element.toString() == "" || element.toString() == "0")
            throw std::runtime_error("Element is not a member of the group");

        auto n = this->getP() - PositiveNumber("1"); // order of the group
        
        if (factorization.empty())
            factorization = map_factors(n, PollardFactorization::pollardRho<PositiveNumber>);

        auto t = n;
        Exponentiation exp;
        for (const auto& mult : factorization) {

            t = t / exp.fastExponention(mult.first, mult.second);
            auto elem1 = exp.montgomeryExponention(element, t);
            while (elem1 != identity) {
                elem1 = exp.montgomeryExponention(elem1, mult.first);
                t = t * mult.first;

                if (t > n)
                    throw std::overflow_error("Infinite order");
            }
        }

        return t;
    }

    //Determining whether the input element is a generator of a multiplicative group
    bool isGenerator(const FiniteNumber& element) const {
        assert(identitySet);
        assert(element.getP() == this->getP());
        if (element.toString() == "" || element.toString() == "0")
            throw std::runtime_error("Element is not a member of the group");

        auto n = this->getP() - PositiveNumber("1");

        if (factorization.empty())
            factorization = map_factors(n, PollardFactorization::pollardRho<PositiveNumber>);

        auto t = n;
        Exponentiation exp;
        for (const auto& mult : factorization) {
            auto b = exp.montgomeryExponention(element, n / mult.first);
            if (b == 1)
                return false;
        }
        return true;
    }

private:
    FiniteNumber identity = FiniteNumber("1 x10"); // Identity element
    bool identitySet = false; // Flag to indicate if the identity element is set
    FiniteField f;
    PositiveNumber order; // Order of the group

    // Prime factorization of the group order
    std::map<PositiveNumber, int>& factorization;

    void setGroupOrder() {
        if (MillerRabin::miller_rabin(f.getP()))
            order = f.getP() - PositiveNumber("1");
        else {
            // TODO: Needs euler funtion
        }
    }
};
