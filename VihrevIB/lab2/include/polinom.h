#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include "Monom.h"
#include "list.h"


using std::string;
using std::ostream;
using std::cout;
using std::cin;
using std::endl;

class Polinom {

protected:
	
	Rlist<Monom> Monoms;
	string name;
	//вспомогательные методы
	Rlist <Monom> Simplify(Rlist <Monom> POL); // привести подобные слагаемые
	Rlist<Monom> Parsing(const string Line);// разбитие строки на мономы

public:
	
	//Конструкторы
	Polinom(const string Line = "" ); // конструктор по строке
	Polinom(const int A) { Monoms.InsertAfter(Monoms.GetCurr(), A); };
	Polinom(const Monom m) { Monoms.InsertAfter(Monoms.GetCurr(),m); }// конструктор  преобразования типа: от монома
	Polinom(const Rlist<Monom> &P2) : Monoms(P2) {}; // конструктор преобразования типа: от списка 
	Polinom(const Polinom& POL) : Monoms(POL.Monoms) {};  //конструктор копирования
	
	//Операторы
	Polinom operator+ (const Polinom&) const;
	Polinom operator- (const Polinom& POL) const { return (*this + POL*(-1.0)); }
	Polinom operator* (const Polinom& POL) const;// умножение полинома на полином
	Polinom operator* (const double c) const; // умножение полинома на константу справа
	
	bool operator== (const Polinom& POL) const { return Monoms == POL.Monoms; }
	bool operator!= (const Polinom& POL) const { return Monoms != POL.Monoms; }

	friend Polinom operator* (const double C , const Polinom& POL) { return POL*C; } // умножение полинома на константу слева
	friend ostream& operator<< (ostream& os, const Polinom&);
};