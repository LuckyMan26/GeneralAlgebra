#pragma once


#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>

#include "FiniteNumber.h"


//Created by Y.Kishchuk
class Group {
public:
    Group() {};

    // Constructor takes a vector of elements and a binary operation
    // May thow exceptions
    Group(std::vector<FiniteNumber> elements, std::function<FiniteNumber(const FiniteNumber&, const FiniteNumber&)> op) {
        assert(elements.size() > 0);

        this->elements = elements;
        this->op = op;
        this->p = elements[0].getP();

        if (hasDuplicates()) {
            throw std::runtime_error("Dublicates are found");
        }
        if (!checkP(this->p)) {
            throw std::runtime_error("Group has different P");
        }

        // Check if group properties are accepted, otherwise throw exception with details
        this->checkGroupProperties();

    }

    // Binary operation method
    FiniteNumber operate(FiniteNumber a, FiniteNumber b) const {
        assert(op, "Binary operation didn't set");
        auto tp = this->p;
        assert(a.getP().equals(tp) && b.getP().equals(tp));

        return op(a, b);
    }

    std::vector<FiniteNumber> getElements() const noexcept {
        return elements;
    }

    FiniteNumber getIdentity() const noexcept {
        return identity;
    }

    PositiveNumber getP() const noexcept {
        return p;
    }

    size_t getGroupSize() const noexcept {
        return elements.size();
    }

    void setElements(std::vector<FiniteNumber> elements) {
        assert(elements.size() > 0);
        this->elements = elements;
        this->p = elements[0].getP();

        // Check if group properties are accepted, otherwise throw exception with details
        if (hasDuplicates()) {
            throw std::runtime_error("Dublicates are found");
        }
        if (!checkP(this->p)) {
            throw std::runtime_error("Group has different P");
        }

        if (this->op)
            this->checkGroupProperties();
    }

    void setGroupBinaryOperation(std::function<FiniteNumber(FiniteNumber, const FiniteNumber&)> op)
    {
        this->op = op;

        if (elements.size() > 0) {
            // Check if group properties are accepted, otherwise throw exception with details
            this->checkGroupProperties();
        }
    }

private:
    // Check the correctness of the group properties. Sets identity element if found
    void checkGroupProperties() {
        if (!hasIdentity()) {
            throw std::runtime_error("Group does not have an identity element");
        }

        this->setIdentity();

        if (!isClosed()) {
            throw std::runtime_error("Group is not closed");
        }
        if (!isAssociative()) {
            throw std::runtime_error("Group is not associative");
        }
        if (!hasInverse()) {
            throw std::runtime_error("Not every element in the group has an inverse");
        }
    }


    // Check if the group is closed
    bool isClosed() const {
        for (const FiniteNumber& a : elements) {
            for (const FiniteNumber& b : elements) {
                if (std::find(elements.begin(), elements.end(), op(a, b)) == elements.end()) {
                    return false;
                }
            }
        }
        return true;
    }

    // Check if the group is associative
    bool isAssociative() const  {
        for (const FiniteNumber& a : elements) {
            for (const FiniteNumber& b : elements) {
                for (const FiniteNumber& c : elements) {
                    if (op(op(a, b), c) != op(a, op(b, c))) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    // Check if the group has an identity element
    bool hasIdentity() const {
        for (const FiniteNumber &a : elements) {
            bool is_identity = true;
            for (const FiniteNumber &b : elements) {
                if (op(a, b) != b || op(b, a) != b) {
                    is_identity = false;
                    break;
                }
            }
            if (is_identity) {
                return true;
            }
        }
        return false;
    }

    // Sets the group identity element
    void setIdentity() {
        bool is_identity = true;
        for (const FiniteNumber& a : elements) {
            is_identity = true;
            for (const FiniteNumber& b : elements) {
                if (op(a, b) != b || op(b, a) != b) {
                    is_identity = false;
                    break;
                }
            }
            if (is_identity) {
                identity = a;
                return;
            }
        }
        assert(is_identity, "indentity element not set");
    }

    // Check if every element in the group has an inverse
    bool hasInverse() const {
        for (const FiniteNumber& a : elements) {
            bool has_inverse = false;
            for (const FiniteNumber& b : elements) {
                if (op(a, b) == identity && op(b, a) == identity) {
                    has_inverse = true;
                    break;
                }
            }
            if (!has_inverse) {
                return false;
            }
        }
        return true;
    }


    // Check if the elements vector contains any duplicates
    bool hasDuplicates() const {
        std::vector<FiniteNumber> sortedElements = elements; 
        std::sort(sortedElements.begin(), sortedElements.end());

        // Check if any adjacent elements are equal
        for (size_t i = 1; i < sortedElements.size(); ++i) {
            if (sortedElements[i] == sortedElements[i - 1]) {
                return true;
            }
        }

        return false;
    }

    // Checks elements for the same P
    bool checkP(PositiveNumber p) const {
        for (const auto& elem : elements)
            if (elem.getP() != p)
                return false;
        return true;
    }

    PositiveNumber p;
    std::vector<FiniteNumber> elements;
    std::function<FiniteNumber(const FiniteNumber&, const FiniteNumber&)> op; // Group binary function
    FiniteNumber identity = FiniteNumber("10x 1"); // HACK: Make a default (or nil) constructor for the FiniteNumber class
};
