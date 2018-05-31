#pragma once
#include "table.h"

template <typename T>
class UnordTable : public Table<T> 
{
	protected:
		void Realloc();
	public:
		// Конструкторы и деструктор
		UnordTable(unsigned int i = 10) : Table(i) {};
		UnordTable(const UnordTable<T>& TabToCopy);
		~UnordTable() { };
		//Общие Методы
		void Insert(const T Data, const string Key);
		T* Search(const string Key);
		void Delete(const string Key);
	
		template<class T> friend std::ostream& operator<< (std::ostream& os, const UnordTable<T>& Tab);

};
//............................................................................
template <typename T>
UnordTable<T>::UnordTable(const UnordTable<T>& TabToCopy) : Table(TabToCopy)
{
	
}
//............................................................................
template <typename T>
void UnordTable<T>::Realloc()
{
	unsigned int NewMaxRecords = (unsigned int)(MaxRecords*1.5);
	TabRecord<T>** tmp = new TabRecord<T>*[NewMaxRecords];
	for (int i = 0; i < MaxRecords; i++)
		tmp[i] = Rows[i];
	MaxRecords = NewMaxRecords;
	delete[] Rows;
	Rows = tmp;
}
//............................................................................
template <typename T>
void UnordTable<T>::Insert(const T Data, const string Key)
{
	if (IsFull())
		Realloc();
	TabRecord<T>* Row = new TabRecord<T>(Key, Data);
	Reset();
	while (!IsTabEnded() && Key != Rows[CurrIndex]->Key)
		CurrIndex++;
	if (IsEmpty())
	{
		CurrIndex++;
	}
	if (CurrIndex == CurrRecords)
	{
		Rows[CurrIndex] = Row;
		CurrRecords++;
		Reset();
	}
	else
	{
		Reset();
		string s = "Key: " + Key + " - isn`t unique";
		throw s;
	}
}
//............................................................................
template <typename T>
T* UnordTable<T>::Search(const string Key)
{	
	Reset();
	T* tmp = nullptr;
	if (IsEmpty())
		throw (string)"Cant Search In Empty Table";
	while (!IsTabEnded() && Key != Rows[CurrIndex]->Key)
		CurrIndex++;
	if (!IsTabEnded())
		tmp = &(Rows[CurrIndex]->Data);
	else
	{	
		string s = Key + " Not Found";
		throw s;
	}
	return tmp;
}
//............................................................................
template <typename T>
void UnordTable<T>::Delete(string Key)
{
	Reset();
	if (IsEmpty())
		throw (string)"Cant Delete From Empty Table";
	Search(Key);
	if (CurrRecords > 1)
		Rows[CurrIndex] = Rows[--CurrRecords];
	else
		CurrRecords = 0;
}
//............................................................................
//спросить почему так
template <typename T>
std::ostream& operator<< (std::ostream& os, const UnordTable<T>& Tab)
{	
	unsigned int i = 0;

	while(i < Tab.CurrRecords)
	{
		os << i << ". " << Tab.Rows[i]->Key<< "  |   " << Tab.Rows[i]->Data << std::endl;
		i++;
	}
	if (Tab.CurrRecords == 0)
		os << "Table is Empty";
	return os;
}