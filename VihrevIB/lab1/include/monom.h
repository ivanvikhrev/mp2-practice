#pragma once
// Моном
class Monom
{
public:
	double coeff; //коэффициент
	unsigned int abc; // степень
	Monom() { coeff = 0; abc = 0; } //конструктор по умолчанию
	Monom(double COEFF, unsigned int ABC) { coeff = COEFF; abc = ABC; }

};