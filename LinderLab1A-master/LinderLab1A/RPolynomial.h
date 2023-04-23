#pragma once
#include "PolynomialElement.h"
#include <string>
#include <list>
/*
* Class for Polynomial Ring
*/
class RPolynomial
{
private:
	std::list<PolynomialElement> coefficients;
	RPolynomial() {
		
	}

	std::string replaceAll(std::string origin, std::string target, std::string replacement) {
		int length = target.size();	
		int replacementSize = replacement.size();
		std::size_t pos = origin.find(target);
		while (pos != std::string::npos)
		{
			origin.replace(pos, length, replacement);
			pos = origin.find(target, pos+replacementSize);
		}
		return origin;
	}

	void emplaceDegree(SignedNumber coefficient, PositiveNumber degree) {
		PolynomialElement toAdd = PolynomialElement(coefficient, degree);
		if (coefficients.empty()) {
			coefficients.push_back(toAdd);
			return;
		}
		for (std::list<PolynomialElement>::iterator iterator = coefficients.begin(); iterator != coefficients.end(); iterator++) {
			PolynomialElement element = *iterator;
			if (element.getDegree() == degree) {
				element.setCoefficient(element.getCoefficient() + coefficient); //add coefficients with same degree
				return;
			}
			else if (element.getDegree() < degree) { //push new degree
				coefficients.emplace(iterator, toAdd);
				return;
			}
		}
		PolynomialElement element = coefficients.back();
		if (element.getDegree() == degree) {
			element.setCoefficient(element.getCoefficient() + coefficient); //add coefficients with same degree
			return;
		}
		else if (element.getDegree() > degree) {
			coefficients.emplace(--coefficients.end(), toAdd);
			return;
		}
		coefficients.emplace_back(toAdd);
	}
	/*Removes all elements, where coefficient equals zero*/
	void trim() {
		std::list<PolynomialElement> newList;
		SignedNumber zero = SignedNumber();
		for (PolynomialElement element : coefficients) {
			if (element.getCoefficient() == zero)
				continue;
			newList.push_back(element);
		}
		this->coefficients = newList;
	}

public:
	/*
	* Input string format Ax^B-Cx^D+Ex^F+G
	* 
	*/
	RPolynomial(std::string s) {
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
				emplaceDegree(SignedNumber(coefficient), PositiveNumber(degree));
			}
			pos = s.find("+", 1);
		}
		trim();
	}
	/**
	* Returns string of coefficients, separated with spaces
	* { 4 + x^3 } = 4 0 0 1
	*/
	std::string toString() {
		if (coefficients.empty())
			return "0";
		std::string result = "";
		for (PolynomialElement n : coefficients) {
			if (n.getCoefficient().isPositive())
				result += '+';
			result += n.toString();
		}
		if (result[0] == '+')
			result = result.substr(1);
		return result;
	}

	RPolynomial derivative() {
		RPolynomial deriv = RPolynomial();
		for (std::list<PolynomialElement>::iterator iterator = coefficients.begin(); iterator != coefficients.end(); iterator++) {
			PolynomialElement element = *iterator;
			SignedNumber coefficient = element.getCoefficient() * element.getDegree();
			deriv.coefficients.push_back(PolynomialElement(coefficient, element.getDegree() - PositiveNumber("1")));
		}
		PositiveNumber zero = PositiveNumber("0");
		PolynomialElement back = coefficients.back();
		if (back.getDegree() != zero) {
			SignedNumber coefficient = back.getCoefficient() * back.getDegree();
			deriv.coefficients.push_back(PolynomialElement(coefficient, back.getDegree() - PositiveNumber("1")));
		}
		return deriv;
	}
	SignedNumber valueAt(SignedNumber x) {
		
		SignedNumber current = coefficients.front().getCoefficient();
		//PositiveNumber prevDegree = PositiveNumber();
		//for (std::list<PolynomialElement>::iterator iterator = ++coefficients.begin(); iterator != coefficients.end(); iterator++) {
			//current = (x * current) + coefficients[i];
		//}

		return current;
	}
};

