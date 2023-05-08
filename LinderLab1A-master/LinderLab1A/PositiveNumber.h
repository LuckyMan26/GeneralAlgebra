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
//Created by M.Tyshchenko and V. Avramenko
//Edited by V.Horbanov
class PositiveNumber {
private:
	static const int vectorP = 10;
	
protected:

	PositiveNumber trim() {
		while (digits.size() != 0 && digits.back() == 0) {
			this->digits.pop_back();
		}
		
		return (*this);
	}

	std::vector<int> digits; //digits as decimal numbers

	static std::vector<int> parseDigits(std::string str) {
		std::vector<int> digits;
		reverse(str.begin(), str.end());
		for (char ch : str) {
			if(ch >= '0' && ch <= '9')
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
	/**
	* Multiplies number by other using primitive algorithm
	*/
	static PositiveNumber simpleMultiplication(PositiveNumber a, PositiveNumber b) {
		return a.simpleMultiplication(b);
	}

public:
	std::vector<int> getDigits() const {
		return digits;
	}
	PositiveNumber() {
	}
	PositiveNumber(std::string digitsString) {
		this->digits = parseDigits(digitsString);
		this->trim();
	}
	PositiveNumber(long long a) {
		this->digits = parseDigits(std::to_string(a));
		this->trim();
	}
	int operator[](int i) const{
		return digits[i];
	}
	int operator[](std::size_t i) const {
		return digits[i];
	}


	bool isZero() const {
		return digits.empty();
	}
	friend PositiveNumber operator+(PositiveNumber left, const PositiveNumber& n) {
		left.addTo(n);
		return left;
	}
	PositiveNumber& operator+=(const PositiveNumber& n) {
		this->addTo(n);
		return *this;
	}
	PositiveNumber operator*(const PositiveNumber& n) const{
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
	bool operator==(const PositiveNumber& n) const {
		return equals(n);
	}
	bool operator!=(const PositiveNumber& n) const {
		return !equals(n);
	}
	bool equals(const PositiveNumber& n) const {
		
		if (digits.size() != n.digits.size())
			return false;
		for (int i = 0; i < digits.size(); i++) {
			if (digits[i] != n[i])
				return false;
		}
		return true;
	}
	//Implemented by Artem Volyk
	void operator >>= (const int i) {
		std::rotate(digits.begin(), digits.begin() + 1, digits.end());
		digits[0] = 0;
	}
	//Implemented by Vlad Avramenko, edited by V.Horbanov
	//Division for PositiveNumbers

	PositiveNumber operator/(const PositiveNumber& other) const{
		return divide(const_cast<PositiveNumber&>(*this), const_cast<PositiveNumber&>(other));
	}

	PositiveNumber divide(PositiveNumber& n1, PositiveNumber& n2) const{
		if (n1 < n2) {
			return PositiveNumber("0");
		}
		int i = n2.digits.size()-1;
		PositiveNumber part(n1.toString().substr(0, i+1));
		std::string result;
		while (i < n1.digits.size()) {
			if (part < n2) {
				i++;
				if (i >= n1.digits.size()) {
					return PositiveNumber(result);
				}
				else {
					//part = PositiveNumber(part.toString() + n1.toString()[i]);
					part.digits.insert(part.digits.begin(), n1.digits.end()[-i - 1]);
					part.trim();
				}
			}
			while (part < n2) {
				i++;
				if (i >= n1.digits.size()) {
					result.append("0");
					return PositiveNumber(result);
				}
				else {
					result.append("0");
					part.digits.insert(part.digits.begin(), n1.digits.end()[-i - 1]);
					part.trim();
					//part = PositiveNumber(part.toString() + n1.toString()[i]);
				}
			}
			int j = 0;
			while (part >= n2) {
				j++;
				part -= n2;
			}
			result.append(std::to_string(j));
		}
		return PositiveNumber(result);
	}

	PositiveNumber remainder(const PositiveNumber& n1, const PositiveNumber& n2) const{
		/*PositiveNumber rem((n2 * (n1 / n2)));*/
		return n1 - (n2 * (n1 / n2));
	}

	PositiveNumber operator%(const PositiveNumber& other) const {
		return remainder(*this, other);
	}
	//By V. Avramenko
	//Inefficient, did not find a way of getting square root (efficiently) in long arithmetics
	bool is_prime() {
		PositiveNumber two = PositiveNumber("2");
		PositiveNumber zero = PositiveNumber("0");
		PositiveNumber one = PositiveNumber("1");
		for (PositiveNumber i = two; i < *this; i += 1) {
			if (remainder(*this, i) == zero) {
				return false;
			}
			if (i * i >= *this) {
				break;
			}
		}
		return true;
	}


	bool operator>(const PositiveNumber& n) const {
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

	bool operator>=(const PositiveNumber& n) const {
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
	bool operator<(const PositiveNumber& n) const {
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
	bool operator<=(const PositiveNumber& n) const {
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

	//Implemented by Y. Kishchuk


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
	virtual std::string toString() const{
		std::string result = "";
		if (isZero())
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
	* Modified by Oleksii Onishchenko
	*/
	//Function for finding Greatest Common Divisor for 2 PositiveNumbers 
	static PositiveNumber GCD(PositiveNumber n1, PositiveNumber n2) {
		if (n1 == 0)
			return n2;

		return GCD(n2 % n1, n1);
	}
	//Implemented by A.Volyk
	static PositiveNumber LCM(PositiveNumber n1, PositiveNumber n2) {
		PositiveNumber gcd = GCD(n1, n2);
		PositiveNumber res = (n1 * n2) / gcd;
		return res;
	}
	/*
	* Shifting number left or right (% 10)
	* Examples: 
	* 5.shift(2): 5 => 500
	* 100.shift(-1): 100 => 10
	* 
	* Implemented by M. Tyshechenko
	*/
	PositiveNumber shift(int numDigits) {
		PositiveNumber number = PositiveNumber(*this);
		if (numDigits < 0) {
			if (-numDigits < number.digits.size()) {
				for (int i = 0; i < -numDigits ; i++) {
					number.digits.erase(number.digits.begin());
				}
			}
			else {
				number.digits.clear();
			}
		}
		else {
			for (int i = 0; i < numDigits; i++) {
				number.digits.insert(number.digits.begin(), 0);
			}
		}
		return number;
	}

	PositiveNumber first(int numDigits) {
		PositiveNumber number = PositiveNumber(*this);
		if (numDigits < number.digits.size()) {
			number.digits.assign(number.digits.begin(), number.digits.begin() + numDigits);
		}
		return number.trim();
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
	std::string bits() {
		std::string result = bitsReverse();
		reverse(result.begin(), result.end());
		return result;
	}
	std::string bitsReverse() {
		PositiveNumber divideBy = PositiveNumber("2");
		std::string result = "";
		PositiveNumber current = *this;
		PositiveNumber zero = PositiveNumber("0");
		if (digits.empty())
			return "0";
		while (current != zero) {
			if (current.digits[0] % 2) {
				result += "1";
			}
			else {
				result += "0";
			}
			current = current / divideBy;
		}
		return result;
	}
};
