#pragma once

#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>

#include "FiniteNumber.h"
#include "FiniteGroup.h"

// Created by Y.Kishchuk
class FiniteGroup {
public:
    FiniteGroup(const FiniteField& f, std::function<FiniteNumber(const FiniteNumber&, const FiniteNumber&)> op = [](const FiniteNumber& a, const FiniteNumber& b) {
        return FiniteNumber(a * b);})
    {
        this->op = op;
        this->f = f;
        this->identitySet = false;
    }

    // Binary operation method
    FiniteNumber operate(const FiniteNumber& a, const FiniteNumber& b) const {
        auto temp_p = this->getP();
        assert(op != nullptr, "Binary operation is not set");
        assert(a.getP().equals(temp_p) && b.getP().equals(temp_p), "Elements have different P");
        return op(a, b);
    }

    FiniteNumber getIdentity() const {
        assert(identitySet && "Identity element is not set");
        return identity;
    }

    PositiveNumber getP() const noexcept {
        return f.getP();
    }

    void setIdentity(const FiniteNumber& element) {
        assert(element.getP().equals(this->getP()) && "Element has different P");
        identity = element;
        identitySet = true;
    }

    void setGroupBinaryOperation(std::function<FiniteNumber(const FiniteNumber&, const FiniteNumber&)> op) {
        this->op = op;
        identitySet = false;
    }

    // Determining the order of a group element
    size_t ElementOrder(const FiniteNumber& element) const {
        // TODO:
        return -1;
    }

private:

    std::function<FiniteNumber(const FiniteNumber&, const FiniteNumber&)> op; // Binary operation
    FiniteNumber identity = FiniteNumber("1 x10"); // Identity element
    bool identitySet = false; // Flag to indicate if the identity element is set
    FiniteField f;
};
