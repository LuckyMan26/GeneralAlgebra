#pragma once
#include "PositiveNumber.h"
//Created by M.Tyshchenko
//Modified by A.Volyk
class FiniteField
{
private:
	PositiveNumber p;
public:
	//Constructor
	FiniteField() {
		

	}
	FiniteField(PositiveNumber p_) {
		p = p_;
	}
	//Getter
	PositiveNumber getP() const{
		return p;
	}
	//Setter
	void setP(PositiveNumber p) {
		this->p = p;
	}
	//Check whether it is the same field
	bool operator == (FiniteField& left) const{
		if (p != left.p) {
			return false;
		}
		return true;
	}
};

