#include "polinom.h"


const string xyz = "xyz";
//............................................................................
Polinom::Polinom(const string Line)
{
	Pol_List = Parsing(Line);
	Pol_List = FindSimilar(Pol_List);
}
//............................................................................
Rlist<Monom> Polinom::FindSimilar(Rlist<Monom> POL)
{
	Rlist<Monom> res;
	POL.Reset(); // устанавливаем указатель current в начало списка
	res.Reset();
	Node<Monom> tmp(POL.GetCurr()->data); // создаем звено со значением data от сurrent &

	while (!(POL.IsEnded()))
	{
		if (POL.GetCurr()->data.abc == POL.GetCurr()->next->data.abc)
		{
			tmp.data.coeff += POL.GetCurr()->next->data.coeff;
			tmp.data.abc = POL.GetCurr()->next->data.abc;
		}
		else
		{
			if (tmp.data.coeff)
			{
				res.InsertAfter(res.GetCurr(), tmp.data);
				res.GetNext();
			}
			tmp.data.coeff = POL.GetCurr()->next->data.coeff;
			tmp.data.abc = POL.GetCurr()->next->data.abc;
		}
		POL.GetNext();
	}
	return res;
}
//............................................................................