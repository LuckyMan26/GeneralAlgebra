#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
/**
* Class for number in infinite field
*
*
*/
//Created by M.Tyshchenko
class PositiveNumber {
private:
	static const int vectorP = 10;


	PositiveNumber trim() {
		while (digits.size() != 0 && digits.back() == 0) {
			this->digits.pop_back();
		}
		return (*this);
	}

protected:
	std::vector<int> digits; //digits as decimal numbers

	std::vector<int> parseDigits(std::string str) {
		std::vector<int> digits;
		std::size_t size = str.size();
		reverse(str.begin(), str.end());
		for (char ch : str) {
			digits.push_back(ch - '0');
		}
		return digits;
	}

	/**
	* Multiplies number by other using primitive algorithm
	*/
	virtual PositiveNumber simpleMultiplication(PositiveNumber other) const {
		PositiveNumber product;
		int offsite = 0;
		for (int i : digits) {
			PositiveNumber term;
			int toAdd = 0;
			for (int j = 0; j < offsite; j++)
				term.digits.push_back(0);
			for (int j : other.digits) {
				int v = i * j + toAdd;
				term.digits.push_back(v % vectorP);
				toAdd = v / vectorP;
			}
			if (toAdd != 0) {
				term.digits.push_back(toAdd);
			}
			product.addTo(term);
			offsite++;
		}
		return product.trim();
	}


public:
	PositiveNumber() {
	}
	PositiveNumber(std::string digitsString) {
		this->digits = parseDigits(digitsString);
	}
	int& operator[](int i) {
		return digits[i];
	}
	int& operator[](std::size_t i) {
		return digits[i];
	}


	friend PositiveNumber operator+(PositiveNumber left, const PositiveNumber& n) {
		left.addTo(n);
		return left;
	}
	PositiveNumber& operator+=(const PositiveNumber& n) {
		this->addTo(n);
		return *this;
	}
	PositiveNumber operator*(const PositiveNumber& n) {
		return simpleMultiplication(n);
	}
	PositiveNumber operator*=(const PositiveNumber& n) {
		this->multiplyBy(n);
		return *this;
	}
	friend PositiveNumber operator-(PositiveNumber left, const PositiveNumber& n) {
		left.substract(n);
		return left;
	}
	PositiveNumber& operator-=(const PositiveNumber& n) {
		this->substract(n);
		return *this;
	}
	bool operator==(PositiveNumber& n) const {
		return equals(n);
	}
	bool operator!=(PositiveNumber& n) const {
		return !equals(n);
	}
	bool equals(PositiveNumber& n) const {
		if (digits.size() != n.digits.size())
			return false;
		for (int i = 0; i < digits.size(); i++) {
			if (digits[i] != n[i])
				return false;
		}
		return true;
	}

	//Note by Vlad Avramenko
	//Possible bug, implemented fix
	// Numbers were compared from end to start, changed to comparison from start to end
	bool operator>(PositiveNumber& n) const {
		if (digits.size() > n.digits.size())
			return true;
		if (digits.size() < n.digits.size())
			return false;
		for (int i = digits.size() - 1; i >= 0; i--) {
			if (digits[i] == n[i])
				continue;
			return digits[i] > n[i];
		}
		return false;
	}

	bool operator>=(PositiveNumber& n) const {
		if (digits.size() > n.digits.size())
			return true;
		if (digits.size() < n.digits.size())
			return false;
		for (int i = digits.size() - 1; i >= 0; i--) {
			if (digits[i] == n[i])
				continue;
			return digits[i] > n[i];
		}
		return true;
	}
	bool operator<(PositiveNumber& n) const {
		if (digits.size() < n.digits.size())
			return true;
		if (digits.size() > n.digits.size())
			return false;
		for (int i = digits.size() - 1; i >= 0; i--) {
			if (digits[i] == n[i])
				continue;
			return digits[i] < n[i];
		}
		return false;
	}
	bool operator<=(PositiveNumber& n) const {
		if (digits.size() < n.digits.size())
			return true;
		if (digits.size() > n.digits.size())
			return false;
		for (int i = digits.size()-1; i >= 0; i--) {
			if (digits[i] == n[i])
				continue;
			return digits[i] < n[i];
		}
		return true;
	}
	//Division with remainder 
	//Implemented by Artem Volyk
	int operator % (int& n) const {
		int size = digits.size();
		std::vector<int> parts(0, size / 6 + 1);
		for (int i = 0; i < size / 6; i++) {
			for (int j = 0; j < 6; j++) {
				parts[i] += pow(10, j) * digits[i + j];
			}
		}
		int rest = 0;
		for (int i = 0; i < parts.size(); i++) {
			rest += int((pow(10,6*i)*parts[i])) % n;
		}
		return int(rest) % n;
	}
	/**
	* Adds two positive numbers
	*/

	virtual void addTo(PositiveNumber other) {
		std::size_t minSize = std::min(digits.size(), other.digits.size());
		bool addOne = false;
		int i = 0;
		for (; i < minSize; i++) {
			int v = digits[i] + other[i] + addOne;
			addOne = v >= vectorP;
			digits[i] = (v - vectorP * addOne);
		}
		while (i < other.digits.size()) {
			int v = other[i] + addOne;
			addOne = v >= vectorP;
			digits.push_back(v - vectorP * addOne);
			i++;
		}
		while (addOne) {
			if (i < this->digits.size()) {
				int v = digits[i] + 1;
				addOne = v >= vectorP;
				digits[i] = (v - vectorP * addOne);
				i++;
			}
			else {
				digits.push_back(1);
				return;
			}
		}
	}

	/**
	* Adds two positive numbers
	*/
	virtual PositiveNumber add(PositiveNumber n2) const {
		n2.addTo(*this);
		return n2;
	}
	/**
	*
	* Subsracts two numbers. Returns the module of the result.
	*/
	virtual void substract(PositiveNumber other) {
		std::vector<int>* bigger = (*this > other) ? &this->digits : &other.digits;
		std::vector<int>* smaller = (*this <= other) ? &this->digits : &other.digits;
		bool substractOne = false;

		std::size_t minSize = smaller->size();
		PositiveNumber dif = PositiveNumber();
		int i = 0;
		for (; i < minSize; i++) {
			int v = bigger->at(i) - smaller->at(i) - substractOne;
			substractOne = v < 0;
			dif.digits.push_back(v + vectorP * substractOne);
		}
		while (i < bigger->size()) {
			int v = bigger->at(i) - substractOne;
			substractOne = v < 0;
			dif.digits.push_back(v + vectorP * substractOne);
			i++;
		}
		this->digits = dif.trim().digits;
	}
	/**
	* Substracts max of n1 and n2 from min of n1 and n2
	*/
	PositiveNumber substractFrom(PositiveNumber n2) const {
		PositiveNumber n = PositiveNumber();
		n.digits = this->digits;
		n.substract(n2);
		return n;
	}
	/**
	* Shows number as printable string
	*/
	virtual std::string toString() {
		std::string result = "";
		if (digits.empty())
			return "0";
		for (int i : digits) {
			result += (i + '0');
		}
		reverse(result.begin(), result.end());
		return result;
	}

	/**
	* Multiplies number by other using primitive algorithm
	*/
	virtual void multiplyBy(PositiveNumber other) {
		this->digits = simpleMultiplication(other).digits;
	}

	/**
	* Multiplies number by other using primitive algorithm
	*/
	virtual PositiveNumber multiply(PositiveNumber other) const {
		other.multiplyBy(*this);
		return other;
	}

	/*
	* Implemented by Vlad Avrmenko
	*/
	//Function for finding Greatest Common Divisor for 2 PositiveNumbers 
	PositiveNumber GCD(PositiveNumber n1, PositiveNumber n2) {
		while (n1 != n2) {
			if (n1 > n2) {
				n1 -= n2;
			}
			else {
				n2 -= n1;
			}
		}
		return n1;
	}

	/*std::vector<std::pair<PositiveNumber, int>> factorise() {
		std::vector<std::pair<PositiveNumber, int>> v;
		int n;
		for (int i = 0; i < digits.size(); i++) {
			n+= std::pow(vectorP, digits.size() - i - 1) * digits[i];
		}
		 uint64_t square = static_cast<uint64_t>(std::sqrt(n));
	for (std::size_t i = 2; i <= square && i <= n; ++i)
	{	
		PositiveNumber ii = PositiveNumber(std::to_string(i));
		bool isPrime = true;
		for (auto p : v)
		{
			if (p.first * p.first > ii)
			{
				break;
			}
			if (i % p.first == 0u)
			{
				isPrime = false;
				break;
			}
		}

		if (isPrime)
		{
			uint64_t count = 0;
			while (n % i == 0)
			{
				++count;
				n /= i;
			}
			v.emplace_back(ii, count);
			if (count != 0)
			{
				square = static_cast<uint64_t>(std::sqrt(n));
			}
		}
	}
	if (n != 1)
	{
		v.emplace_back(n, 1);
	}
	}
	PositiveNumber phi() {
		
	}*/

};
