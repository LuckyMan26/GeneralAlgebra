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
    Group(std::vector<FiniteNumber> elements, std::function<FiniteNumber(FiniteNumber, const FiniteNumber&)> op) {
        this->elements = elements;
        this->op = op;

        assert(hasIdentity(), "Group does not have an identity element");
        this->setIdentity();

        assert(isClosed(), "Group is not closed");
        assert(isAssociative(), "Group is not associative");
        assert(hasInverse(), "Not every element in the group has an inverse");
        assert(!hasDuplicates(), "Dublicates are found");


        // Check modulo
        // TODO:

        /*
        // Check if group properties are accepted, otherwise throw exception with details
        if (!isClosed()) {
            throw std::runtime_error("Group is not closed");
        }
        if (!isAssociative()) {
            throw std::runtime_error("Group is not associative");
        }
        if (!hasIdentity()) {
            throw std::runtime_error("Group does not have an identity element");
        }
        this->setIdentity();

        if (!hasInverse()) {
            throw std::runtime_error("Not every element in the group has an inverse");
        }
        if (hasDuplicates())
            throw std::runtime_error("Dublicates are found");
        */
    }

    // Binary operation method
    FiniteNumber operate(FiniteNumber a, FiniteNumber b) const {
        return op(a, b);
    }

    std::vector<FiniteNumber> getElements() const noexcept {
        return elements;
    }

    FiniteNumber getIdentity() const noexcept {
        return identity;
    }

    void setElements(std::vector<FiniteNumber> elements) {
        this->elements = elements;

        // Сopying twice is not a crime
        assert(hasIdentity(), "Group does not have an identity element");
        this->setIdentity();

        assert(isClosed(), "Group is not closed");
        assert(isAssociative(), "Group is not associative");
        assert(hasInverse(), "Not every element in the group has an inverse");
        assert(!hasDuplicates(), "Dublicates are found");
    }

    void setGroupBinaryOperation(FiniteNumber(*op)(FiniteNumber, const FiniteNumber&))
    {
        this->op = op;

        // Сopying twice is not a crime
        assert(hasIdentity(), "Group does not have an identity element");
        this->setIdentity();

        assert(isClosed(), "Group is not closed");
        assert(isAssociative(), "Group is not associative");
        assert(hasInverse(), "Not every element in the group has an inverse");
        assert(!hasDuplicates(), "Dublicates are found");
    }

    // Add an element to the group
    void addElement(const FiniteNumber& element) {

        assert(std::find(elements.begin(), elements.end(), element) == elements.end(), "Element already exists in the group");
        assert(isClosedWithElement(element), "Adding the element breaks the closure property of the group");
        assert(isAssociativeWithElement(element), "Adding the element breaks the associativity property of the group");
        assert(hasIdentityWithElement(element), "Adding the element breaks the identity property of the group");
        assert(hasInverseWithElement(element), "Adding the element breaks the inverse property of the group");


        /*// Check if the element already exists in the group
        if (std::find(elements.begin(), elements.end(), element) != elements.end()) {
            throw std::runtime_error("Element already exists in the group");
        }


        // Check if adding the element breaks group properties
        if (!isClosedWithElement(element)) {
            throw std::runtime_error("Adding the element breaks the closure property of the group");
        }
        if (!isAssociativeWithElement(element)) {
            throw std::runtime_error("Adding the element breaks the associativity property of the group");
        }
        if (!hasIdentityWithElement(element)) {
            throw std::runtime_error("Adding the element breaks the identity property of the group");
        }
        if (!hasInverseWithElement(element)) {
            throw std::runtime_error("Adding the element breaks the inverse property of the group");
        }*/


        elements.push_back(element);
    }

private:
    // Check if the group is closed with an element
    bool isClosedWithElement(const FiniteNumber& element) const {
        for (const FiniteNumber& a : elements) {
            if (std::find(elements.begin(), elements.end(), op(a, element)) == elements.end()) {
                return false;
            }
            if (std::find(elements.begin(), elements.end(), op(element, a)) == elements.end()) {
                return false;
            }
        }
        return true;
    }

    // Check if the group is associative with an element
    bool isAssociativeWithElement(const FiniteNumber& element) const {
        for (const FiniteNumber& a : elements) {
            for (const FiniteNumber& b : elements) {
                if (op(op(a, b), element) != op(a, op(b, element))) {
                    return false;
                }
                if (op(element, op(a, b)) != op(op(element, a), b)) {
                    return false;
                }
            }
        }
        return true;
    }

    // Check if the group has an identity element with an element
    bool hasIdentityWithElement(const FiniteNumber& element) const {
        FiniteNumber result = element;
        for (const FiniteNumber& a : elements) {
            if (op(a, element) != a || op(element, a) != a) {
                return false;
            }
        }
        return true;
    }

    // Check if the group has an inverse for every element with an element
    bool hasInverseWithElement(const FiniteNumber& element) const {
        for (const FiniteNumber& a : elements) {
            bool hasInverse = false;
            for (const FiniteNumber& b : elements) {
                if (op(a, b) == element && op(b, a) == element) {
                    hasInverse = true;
                    break;
                }
            }
            if (!hasInverse) {
                return false;
            }
        }
        return true;
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

    PositiveNumber p;
    std::vector<FiniteNumber> elements;
    std::function<FiniteNumber(FiniteNumber, const FiniteNumber&)> op; // Group binary function
    FiniteNumber identity = FiniteNumber("10x 1");
};
