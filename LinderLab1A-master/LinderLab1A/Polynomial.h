#pragma once

#include <list>
#include <string>
#include "PolynomialElement.h"

// Implemented by V.Avramenko and M.Tyshchenko
// Modified by Y. Kishchuk
template<typename TCoefficient>
class Polynomial {
protected:
	std::list<PolynomialElement<TCoefficient>> coefficients;

	Polynomial() {}

private:
	/*Removes all elements, where coefficient equals zero*/
	void trim() {
		std::list<PolynomialElement<TCoefficient>> newList;
		TCoefficient zero = TCoefficient();
		for (auto element : coefficients) {
			if (element.getCoefficient() == zero)
				continue;
			newList.push_back(element);
		}
		this->coefficients = newList;
	}

	std::string replaceAll(std::string origin, std::string target, std::string replacement) {
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

public:
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
		size_t pos = s.find("+", 1);
		while (pos != std::string::npos)
		{
			std::string token = s.substr(1, pos-1);
			s = s.substr(pos);
			std::size_t degreePos = token.find('^');
			if (degreePos == std::string::npos) { //no degree sign found : special case
				if (token[token.size() - 1] == 'x') {
					std::string coefficient = token.substr(0, token.size() - 1);
					if (coefficient.empty()) // x ~ 1 * x
						coefficient = "1";
					else if (coefficient == "-") // -x ~ -1 * x
						coefficient = "-1";
					emplaceDegree(coefficient, PositiveNumber("1"));
				}
				else {
					emplaceDegree(token, PositiveNumber("0"));
				}
			}
			else {
				std::string coefficient = token.substr(0, degreePos - 1); //x exclusive
				if (coefficient.empty()) // x ~ 1 * x
					coefficient = "1";
				else if (coefficient == "-") // -x ~ -1 * x
					coefficient = "-1";
				std::string degree = token.substr(degreePos + 1);
				emplaceDegree(TCoefficient(coefficient), PositiveNumber(degree));
			}
			pos = s.find("+", 1);
		}
		trim();
	}

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
			if (n.getCoefficient().isPositive())
				result += '+';
			result += n.toString();
		}
		if (result[0] == '+')
			result = result.substr(1);
		return result;
	}
};