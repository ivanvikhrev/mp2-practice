#pragma once
#include "table.h"

template <typename T>
class UnordTable : Table<T>
{
	protected:
		vector<TabRecord<T>> Rows;
		void Realloc();//?
	public:
		//  онструкторы и деструктор
		UnordTable();
		UnordTable(const UnordTable<T>& TabToCopy);
		~UnordTable() { Clean(); };
		//ћетоды
		void Insert(T Row, string Key);
		int Search(string Key);
		void Delete(string Key);
		void Clean() { Rows.clear(); Table<T>::CurrIndex = -1; Table<T>::CurrRecords = 0; };
		template<class T2> friend std::ostream& operator<< (std::ostream& os, const UnordTable<T2>& Tab);

};
//............................................................................
template <typename T>
UnordTable<T>::UnordTable() : Table()
{	
	Rows.reserve(MaxRecords);
}
//............................................................................
template <typename T>
UnordTable<T>::UnordTable(const UnordTable<T>& TabToCopy)
{
	Rows = TabToCopy.Rows;
	MaxRecords = TabToCopy.MaxRecords;
	CurrIndex = TabToCopy.CurrIndex;
	CurrRecords = TabToCopy.CurrRecords;
}
//............................................................................
template <typename T>
void UnordTable<T>::Realloc()
{
	MaxRecords *= 2;
	Rows.reserve(MaxRecords);
}
//............................................................................
template <typename T>
void UnordTable<T>::Insert(T Data, string Key)
{	
	if (IsFull())
		Realloc();
	TabRecord<T> Row(Data, Key); 
	Rows.push_back(Row); // вставка в динамический массив
	CurrRecords = Rows.size();
}
//............................................................................
template <typename T>
int UnordTable<T>::Search(string Key)
{	
	Reset();
	int i = 0;
	
	if (IsEmpty())
		i = -1;

	while (!IsTabEnded())
	{
		if (Rows[CurrIndex].Name == Key)
		{
			i = CurrIndex;
			break;
		}

		CurrIndex++;
	}
	
	if (IsTabEnded())
		i = -1;
	Reset();
	return i ;
}
//............................................................................
template <typename T>
void UnordTable<T>::Delete(string Key)
{
	Reset();
	int K = Search(Key);
	if (K != -1)
	{
		Rows.erase(Rows.begin() + K);
		CurrRecords = Rows.size();
	}
	else
		return;
	
}
//............................................................................
//спросить почему так
template <typename T2>
std::ostream& operator<< (std::ostream& os, const UnordTable<T2>& Tab)
{	
	unsigned int i = 0;

	while(i < Tab.CurrRecords)
	{
		os << i << "." << Tab.Rows[i].Name << "  |   " << Tab.Rows[i].Data << std::endl;
		i++;
	}
	if (Tab.CurrRecords == 0)
		os << "Table is Empty";
	return os;
}