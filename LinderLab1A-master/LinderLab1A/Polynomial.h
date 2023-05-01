#pragma once

#include <list>
#include <string>
#include <type_traits>
#include "PolynomialElement.h"

template <typename T>
class has_isPositive;


// Implemented by V.Avramenko, M.Tyshchenko, Y. Kishchuk and V.Horbanov
template<typename TCoefficient>
class Polynomial {
protected:
	std::list<PolynomialElement<TCoefficient>> coefficients;

	Polynomial() {}

	/*Removes all elements, where coefficient equals zero*/
	virtual void trim() {
		std::list<PolynomialElement<TCoefficient>> newList;

		for (auto element : coefficients) {
			if (element.getCoefficient().isZero())
				continue;
			newList.push_back(element);
		}
		this->coefficients = newList;
	}


	PositiveNumber degree() const {
		if (coefficients.empty()) {
			return PositiveNumber("0");
		}
		return coefficients.front().getDegree();
	}

	static std::string replaceAll(std::string origin, std::string target, std::string replacement) {
		int length = target.size();
		int replacementSize = replacement.size();
		std::size_t pos = origin.find(target);
		while (pos != std::string::npos)
		{
			origin.replace(pos, length, replacement);
			pos = origin.find(target, pos + replacementSize);
		}
		return origin;
	}
	/*
	* Adds a new node to the polynomial in descending order of degree. 
	* If such a degree already exists, the coefficients are summed
	*/
	void emplaceDegree(TCoefficient coefficient, PositiveNumber degree) {
		auto toAdd = PolynomialElement<TCoefficient>(coefficient, degree);
		if (coefficients.empty()) {
			coefficients.push_back(toAdd);
			return;
		}
		if (coefficients.back().getDegree() > degree) {
			coefficients.push_back(toAdd);
			return;
		}
		for (auto iterator = coefficients.begin(); iterator != coefficients.end(); iterator++) {
			auto element = *iterator;
			if (element.getDegree() == degree) {
				iterator->setCoefficient(element.getCoefficient() + coefficient);
				return;
			}
			else if (element.getDegree() < degree) { //push new degree
				coefficients.emplace(iterator, toAdd);
				return;
			}
		}
		auto element = coefficients.back();
		if (element.getDegree() == degree) {
			element.setCoefficient(element.getCoefficient() + coefficient); //add coefficients with same degree
			return;
		}
		coefficients.emplace(--coefficients.end(), toAdd);
	}

	// Parses PolynomialElements from the given string (string must be formatted, see Polynomial(std::string s) constructor)
	virtual std::list<PolynomialElement<TCoefficient>> parseTerms(std::string s) const {
		std::list<PolynomialElement<TCoefficient>> coefficients;

		size_t pos = s.find("+", 1);
		while (pos != std::string::npos)
		{
			std::string token = s.substr(1, pos - 1);
			s = s.substr(pos);
			std::size_t degreePos = token.find('^');
			if (degreePos == std::string::npos) { //no degree sign found : special case
				if (token[token.size() - 1] == 'x') {
					std::string coefficient = token.substr(0, token.size() - 1);
					if (coefficient.empty()) // x ~ 1 * x
						coefficient = "1";
					else if (coefficient == "-") // -x ~ -1 * x
						coefficient = "-1";
					coefficients.push_back({ genCoefficient(coefficient), PositiveNumber("1") });
				}
				else {
					coefficients.push_back({ genCoefficient(token), PositiveNumber("0") });
				}
			}
			else {
				std::string coefficient = token.substr(0, degreePos - 1); //x exclusive
				if (coefficient.empty()) // x ~ 1 * x
					coefficient = "1";
				else if (coefficient == "-") // -x ~ -1 * x
					coefficient = "-1";
				std::string degree = token.substr(degreePos + 1);
				coefficients.push_back({ genCoefficient(coefficient), PositiveNumber(degree) });
			}
			pos = s.find("+", 1);
		}
		return coefficients;
	}

	virtual TCoefficient genZeroCoefficient() const {
		return TCoefficient();
	}

	virtual TCoefficient genCoefficient(const std::string& str) const {
		return TCoefficient(str);
	}

	/*
	* Input string format Ax^B-Cx^D+Ex^F+G
	* if degrees of some terms in sum are identical, their coefficients will be added
	* Order of terms does not affect the constructor
	* Zero coefficients will be removed
	*/
	Polynomial(std::string s) {
		s=replaceAll(s, " ", ""); //no spaces
		s=replaceAll(s, "-", "+-"); //for split
		
		if (s[0]!='+')
			s = "+" + s;
		s = s + '+';

		auto coefficients = parseTerms(s);
		for (auto& term : coefficients) {
			emplaceDegree(term.getCoefficient(), term.getDegree());
		}

		trim();
	}

	Polynomial(std::list<PolynomialElement<TCoefficient>> elementList) {
		this->coefficients = elementList;
		this->emplaceDegree();
	}

public:
	/**
	* Returns string representation of the polynomial with degrees in descending oreder.
	* Example:
	* x^4-9x^3+x-11
	*/
	std::string toString() {
		if (coefficients.empty())
			return "0";
		std::string result = "";
		for (auto &n : coefficients) {
			// HACK: crutch
			if constexpr (has_isPositive<TCoefficient>::value) { 
				if (n.getCoefficient().isPositive())
					result += '+';
			}
			else {
				result += '+';
			}

			result += n.toString();
		}
		if (result[0] == '+')
			result = result.substr(1);
		return result;
	}

	// Implemented by Y. Kishchuk

	virtual Polynomial operator+(const Polynomial& right) const {
		Polynomial<TCoefficient> result;
		auto leftIter = coefficients.begin();
		auto rightIter = right.coefficients.begin();

		while (leftIter != coefficients.end() && rightIter != right.coefficients.end()) {
			if (leftIter->getDegree() == rightIter->getDegree()) {
				auto newElement = *leftIter + *rightIter;
				result.coefficients.push_back(newElement);
				leftIter++;
				rightIter++;
			}
			else if (leftIter->getDegree() > rightIter->getDegree()) {
				result.coefficients.push_back(*leftIter);
				leftIter++;
			}
			else {
				result.coefficients.push_back(*rightIter);
				rightIter++;
			}
		}

		while (leftIter != coefficients.end()) {
			result.coefficients.push_back(*leftIter);
			leftIter++;
		}

		while (rightIter != right.coefficients.end()) {
			result.coefficients.push_back(*rightIter);
			rightIter++;
		}

		result.trim();
		return result;
	}

	virtual Polynomial operator-(const Polynomial& right) const {
		Polynomial<TCoefficient> result;
		auto leftIter = coefficients.begin();
		auto rightIter = right.coefficients.begin();

		while (leftIter != coefficients.end() && rightIter != right.coefficients.end()) {
			PolynomialElement<TCoefficient> e = *leftIter, e2 = *rightIter;

			std::string left = e.toString(), right = e2.toString();


			if (leftIter->getDegree() == rightIter->getDegree()) {
				auto newElement = *leftIter - *rightIter;
				result.coefficients.push_back(newElement);
				leftIter++;
				rightIter++;
			}
			else if (leftIter->getDegree() > rightIter->getDegree()) {
				result.coefficients.push_back(*leftIter);
				leftIter++;
			}
			else {
				auto newCoefficient = rightIter->getCoefficient() * genCoefficient("-1");
				result.coefficients.push_back(PolynomialElement<TCoefficient>(newCoefficient, rightIter->getDegree()));
				rightIter++;
			}
		}

		while (leftIter != coefficients.end()) {
			result.coefficients.push_back(*leftIter);
			leftIter++;
		}

		while (rightIter != right.coefficients.end()) {
			auto newCoefficient = rightIter->getCoefficient() * genCoefficient("-1");
			result.coefficients.push_back(PolynomialElement<TCoefficient>(newCoefficient, rightIter->getDegree()));
			rightIter++;
		}

		result.trim();
		return result;
	}

	virtual Polynomial operator*(const Polynomial& right) const {
		Polynomial<TCoefficient> result;

		for (auto leftIter = coefficients.begin(); leftIter != coefficients.end(); leftIter++) {
			for (auto rightIter = right.coefficients.begin(); rightIter != right.coefficients.end(); rightIter++) {
				auto newCoefficient = leftIter->getCoefficient() * rightIter->getCoefficient();
				auto newDegree = leftIter->getDegree() + rightIter->getDegree();
				result.emplaceDegree(newCoefficient, newDegree);
			}
		}

		result.trim();
		return result;
	}
};


// SFINAE test
template <typename T>
class has_isPositive
{
	typedef char one;
	struct two { char x[2]; };

	template <typename C> static one test(decltype(&C::isPositive));
	template <typename C> static two test(...);

public:
	enum { value = sizeof(test<T>(0)) == sizeof(char) };
};