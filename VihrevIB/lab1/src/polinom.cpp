#include "polinom.h"
//............................................................................
Polinom::Polinom(const string Line)
{   
	Monoms = Parsing(Line);
    Monoms = Simplify(Monoms);
}
//............................................................................
Rlist<Monom> Polinom::Simplify(Rlist<Monom> POL)
{
	Rlist<Monom> res;
	POL.Reset(); // устанавливаем указатели current в начало списка
	res.Reset();
	Monom tmp;              
    // проверяем, что полином не состоит из одного звена - иначе нет смысла упрощать
	Node<Monom>* p = POL.GetCurr();
	POL.SetNext();
	
	if (!(POL.IsEnd()))
	{
		POL.Reset();

		while (!(POL.IsEnd()))
		{
			tmp.coeff = POL.GetCurr()->data.coeff;
			tmp.abc = POL.GetCurr()->data.abc;

			while ((POL.GetCurr()->data.abc == POL.GetCurr()->next->data.abc) && !(POL.IsEnd()))
			{
				tmp.coeff += POL.GetCurr()->next->data.coeff;
				POL.SetNext();
			}

			if (tmp.coeff)
			{
				res.OrderedInsert(tmp);
				res.SetNext();
			}

			if (!(POL.IsEnd()))
				POL.SetNext();
		}
		res.Reset();
		//если при упрощении получился 0
		if (res.GetCurr()->data.abc == 0 && res.GetCurr()->data.coeff == 0)
		res.InsertAfter(res.GetCurr(), NULL);
	}
	else
		res = POL;
	
	return res;
}
	
//............................................................................
Polinom Polinom::operator+(const Polinom& POL) const
{
	Polinom res;
	Rlist<Monom> P1 = Monoms;
	Rlist<Monom>  P2 = POL.Monoms;

	P1.Reset();
	P2.Reset();

	res.Monoms.Reset();
	// складываем мономы 
	while (!P1.IsEnd() && !P2.IsEnd())
	{
		if ((P1.GetCurr()->data > P2.GetCurr()->data) && P1.GetCurr()->data.coeff) // сравниваем мономы
		{  
			res.Monoms.InsertAfter(res.Monoms.GetCurr(), P1.GetCurr()->data);
			P1.SetNext();
			res.Monoms.SetNext();
		}
		else
			if ((P1.GetCurr()->data < P2.GetCurr()->data) && P2.GetCurr()->data.coeff)
			{
				res.Monoms.InsertAfter(res.Monoms.GetCurr(), P2.GetCurr()->data);
				P2.SetNext();
				res.Monoms.SetNext();
			}
			else // случай равенства степеней мономов
			{
				double cf = P1.GetCurr()->data.coeff + P2.GetCurr()->data.coeff;
				
				if (cf) // если коэфф не ноль
				{
					Monom temp(cf, P1.GetCurr()->data.abc);
					res.Monoms.InsertAfter(res.Monoms.GetCurr(), temp);

					res.Monoms.SetNext();
				}

				P1.SetNext();
				P2.SetNext();
			}
	}
	//добавляем оставшиеся
	while (!P1.IsEnd())
	{	
		if (P1.GetCurr()->data.coeff)
		{
			res.Monoms.InsertAfter(res.Monoms.GetCurr(), P1.GetCurr()->data);
			res.Monoms.SetNext();
		}
		P1.SetNext();
	}

	while (!P2.IsEnd())
	{
		if (P2.GetCurr()->data.coeff)
		{
			res.Monoms.InsertAfter(res.Monoms.GetCurr(), P2.GetCurr()->data);
			res.Monoms.SetNext();
		}
		P2.SetNext();
	}
	res.Monoms.Reset();
	//если при сложении получился 0
	if (res.Monoms.GetCurr()->data.abc == 0 && res.Monoms.GetCurr()->data.coeff == 0)
		res.Monoms.InsertAfter(res.Monoms.GetCurr(), NULL);
	
	return res;
}
//............................................................................

Rlist<Monom> Polinom::Parsing(const string Line)
{   
	Rlist<Monom> List;
	string SMonom, SPol = Line;
	int k = 1;
	int d[] = { 100,10,1 };

	while (SPol.length())
	{   
		Monom tmp;
		k = 1;
		// выделяем моном
		while (SPol[k] != '-' && SPol[k] != '+' && k < SPol.length())
			k++;
		
		SMonom = SPol.substr(0, k);
		SPol.erase(0, k);
	    // проверяем наличие + или - в начале
		if (SMonom[0] == '-')
		{
			tmp.coeff = -1;
			SMonom.erase(0, 1);

		}
		else 
		{
			tmp.coeff = 1;
			if (SMonom[0] == '+')
				SMonom.erase(0, 1);
		}
		//преобразуем коэффициент
		if (isdigit(SMonom[0]))
		{   
			k = 0;
			while (isdigit(SMonom[k]) || SMonom[k] == '.' )
				k++;
			tmp.coeff *= std::stod(SMonom.substr(0, k));
			SMonom.erase(0, k);
		}
		//находим степени
		for (int i = 0; i < 3; i++)
		{   
			int pos = SMonom.find("xyz"[i]);
			if (pos != -1)
				if (SMonom[pos + 1] == '^')
				{
					tmp.abc += d[i] * std::stoi(SMonom.substr(pos + 2, 1));
				}
				else
					tmp.abc += d[i];
		}
		
		List.OrderedInsert(tmp);
	}
	return List;
}
//............................................................................

Polinom Polinom::operator*(const double c) const 
{

	Polinom res;
	
	if (c)
	{
		res = *this;
		res.Monoms.Reset();
		while (!(res.Monoms.IsEnd()))
		{
			res.Monoms.GetCurr()->data.coeff *= c;
			res.Monoms.SetNext();
		}
	}
	else
	{
		res.Monoms.InsertAfter(res.Monoms.GetCurr(), NULL);
	}
	
	return res;
}
//............................................................................
Polinom Polinom::operator*(const Polinom& POL) const {

	Polinom res;
	Polinom P1 = Monoms, P2 = POL;
	int abc;
	double coeff;

	P1.Monoms.Reset();
	P2.Monoms.Reset();

	while (!P2.Monoms.IsEnd())
	{
		Monom tmp;
		P1.Monoms.Reset();
		while (!P1.Monoms.IsEnd())
		{   
			abc = P1.Monoms.GetCurr()->data.abc;
			coeff = P1.Monoms.GetCurr()->data.coeff;
			tmp = P2.Monoms.GetCurr()->data;
			if ( (tmp.abc % 10 + abc % 10) < 10 && (tmp.abc /10 % 10 + abc / 10 % 10) < 10 && (tmp.abc / 100  + abc / 100 ) <10)
			{
				tmp.coeff *= coeff;
				tmp.abc += abc;
				res = res + tmp;
			}
			else
			{
				throw "Degree>10";
			}
			P1.Monoms.SetNext();
		}
		P2.Monoms.SetNext();
	}
	return res;
}
//............................................................................

ostream& operator<<(ostream& os, const Polinom& POL)
{ 
	Polinom tmpPol = POL;
	tmpPol.Monoms.Reset();
	
	Node<Monom>* FirstNode =tmpPol.Monoms.GetCurr(); // указатель на первое звено спика
	Node<Monom>  tmpMon;
	while (!(tmpPol.Monoms.IsEnd()))
	{
		tmpMon = tmpPol.Monoms.GetCurr()->data;
		if (tmpMon.data.coeff > 0 && tmpPol.Monoms.GetCurr() != FirstNode)
			os << '+';
		if (tmpMon.data.coeff != 1 && tmpMon.data.coeff != -1 && tmpMon.data.coeff !=0)
			os << tmpMon.data.coeff;
		else
			if (tmpMon.data.coeff == -1 && tmpMon.data.abc != 0)
				os << '-';
			else 
				if  ((tmpMon.data.coeff == 1 || tmpMon.data.coeff == -1 )&& tmpMon.data.abc == 0)
					os << tmpMon.data.coeff;
		int d[3] = { 100,10,1 };
		for (int i = 0; i < 3; i++)
		{
			if (tmpMon.data.abc / d[i] % 10 != 0)
			{
				os << "xyz"[i];
				if (tmpMon.data.abc / d[i] % 10 != 1)
					os << '^' << tmpMon.data.abc / d[i] % 10;
			}
		}
		tmpPol.Monoms.SetNext();
	}
	tmpPol.Monoms.Reset();
	
	if (tmpPol.Monoms.GetCurr()->data.abc == 0 && tmpPol.Monoms.GetCurr()->data.coeff == 0 && !(tmpPol.Monoms.IsEnd()))
	{
		os << "0";
	}
	return os;
}

// ............................................................................

