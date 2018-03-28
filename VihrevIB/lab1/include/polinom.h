#pragma once

#include <iostream>
#include <string>
#include "Monom.h"
#include "list.h"

using std::string;
using std::ostream;
using std::cout;
using std::endl;

class Polinom {

private:
	
	Rlist<Monom> Pol_List;

public:
	
	//Конструкторы
	Polinom(const string expr);
	Polinom(const Polinom& POL);
	
	//Операторы
	Polinom operator+ (const Polinom&) const;
	Polinom operator- (const Polinom& POL) const { return (*this + POL*(-1)); }
	Polinom operator* (const Polinom&) const;// умножение полинома на полином
	Polinom operator* (const double) const; // умножение полинома на константу справа
	

	
	bool operator== (const Polinom& POL) const { return Pol_List == POL.Pol_List; }
	bool operator!= (const Polinom& POL) const { return Pol_List != POL.Pol_List; }

	Rlist <Monom> FindSimilar (Rlist <Monom> POL); // привести подобные слагаемые
    Rlist<Monom> Parsing (const string);// разбитие строки на мономы


	friend Polinom operator* (const double CONST , const Polinom& POL) { return POL*CONST; } // умножение полинома на константу слева
	friend ostream& operator<< (ostream& os, const Polinom&);
};