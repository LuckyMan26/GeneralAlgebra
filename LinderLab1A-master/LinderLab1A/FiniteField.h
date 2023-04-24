#pragma once
#include "PositiveNumber.h"
//Created by M.Tyshchenko
class FiniteField
{
private:
	PositiveNumber p;
public:
	PositiveNumber getP() {
		return p;
	}
	void setP(PositiveNumber p) {
		this->p = p;
	}
};

