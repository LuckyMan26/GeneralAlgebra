#pragma once
#include <type_traits>
#include <cassert>

#include "PositiveNumber.h"
#include "SignedNumber.h"

// Implemented by M.Tyshchenko, Y. Kishchuk and V.Horbanov
template<typename TCoefficient>
class PolynomialElement {
    // Implemented by Y. Kishchuk
    static_assert(std::is_member_function_pointer<decltype(&TCoefficient::toString)>::value,
        "Type TCoefficient does not have a toString member function.");
    static_assert(std::is_same<decltype(std::declval<TCoefficient>() + std::declval<TCoefficient>()), TCoefficient>::value,
        "Type TCoefficient does not have an operator+ defined.");
    static_assert(std::is_same<decltype(std::declval<TCoefficient>() - std::declval<TCoefficient>()), TCoefficient>::value,
        "Type TCoefficient does not have an operator- defined.");
    static_assert(std::is_same<decltype(std::declval<TCoefficient>()* std::declval<TCoefficient>()), TCoefficient>::value,
        "Type TCoefficient does not have an operator* defined.");
    /*static_assert(std::is_same<decltype(std::declval<TCoefficient>() / std::declval<TCoefficient>()), TCoefficient>::value,
        "Type TCoefficient does not have an operator/ defined.");*/


private:
    // Implemented by M.Tyshchenko
    PositiveNumber degree;
    TCoefficient coefficient;

    std::string formatCoefficient() {
        std::string coef = coefficient.toString();
        if (coef == "1")
            coef = "";
        else if (coef == "-1")
            coef = "-";
        return coef;
    }

public:
    PolynomialElement(TCoefficient coefficient, PositiveNumber degree) {
        this->degree = degree;
        this->coefficient = coefficient;
    }
    void setDegree(PositiveNumber degree) {
        this->degree = degree;
    }
    PositiveNumber getDegree() const {
        return this->degree;
    }
    void setCoefficient(TCoefficient coefficient) {
        this->coefficient = coefficient;
    }
    TCoefficient getCoefficient() const {
        return this->coefficient;
    }

    std::string toString() {
        PositiveNumber zero = PositiveNumber("0");
        if (this->degree == zero) {
            return coefficient.toString();
        }
        PositiveNumber one = PositiveNumber("1");
        if (this->degree == one) {
            std::string coef = formatCoefficient();
            return coef + "x";
        }
        std::string coef = formatCoefficient();
        return coef + "x^" + degree.toString();
    }

    // Implemented by Y. Kishchuk 
    PolynomialElement operator+(const PolynomialElement& right) const {
        //assert(this->degree == right.degree, "Elements have different degree");
        return PolynomialElement(this->coefficient + right.coefficient, this->degree);
    }

    PolynomialElement operator-(const PolynomialElement& right) const {
        //assert(this->degree == right.degree, "Elements have different degree");
        return PolynomialElement(this->coefficient - right.coefficient, this->degree);
    }

    PolynomialElement operator*(const PolynomialElement& right) const {
        return PolynomialElement(this->coefficient * right.coefficient, this->degree + right.degree);
    }

    PolynomialElement operator/(const PolynomialElement& right) const{
        return PolynomialElement(this->coefficient / right.coefficient, this->degree - right.degree);
    }
};
