#pragma once 
#include <string>
#include <iostream>

using std::string;
using std::endl;
using std::cout;

template <typename T>
class TabRecord
{
	public:
		string Key;
		T*	Data; // сделать указателем
		TabRecord() { Key = "EMPTY RECORD"; Data = new T(NULL); }
		TabRecord(string K , T D ) { Key = K; Data = new T(D);} //
		TabRecord(const TabRecord& TR) { Key = TR.Key; Data = new T(*(TR.Data)); }
		
		TabRecord<T>& operator=(const TabRecord<T>& TabR) { Data = new T(*(TabR.Data)); Key = TabR.Key; return *this; }
};

template <typename T>
class Table
{
	protected:
			TabRecord<T>** Rows; // массив указателей
			unsigned int MaxRecords;
			unsigned int CurrRecords;
			int CurrIndex;
			virtual void Realloc() = 0;
	public:
			Table(unsigned int i = 10);
			virtual ~Table() { delete[] Rows; }; //?
			//ќбщие методы
			virtual void Insert(const T Data, const string Key) = 0;
			virtual void Delete(const string key) = 0;
			virtual	 T* Search(const string Key) = 0;
			//ћетоды навигации
			virtual	void Reset();
			virtual bool IsTabEnded() const { return CurrIndex == CurrRecords || CurrIndex == -1; };
			bool IsFull() const { return CurrRecords == MaxRecords; };
			bool IsEmpty() const { return CurrRecords == 0; };
			virtual void SetNext();
			virtual T* GetCurr() const;
			int GetCurrRecords() const { return CurrRecords; };
			int GetMaxRecords() const { return MaxRecords; };
			//переделать навигацию
};
//..........................................................
template<typename T>
Table<T>::Table(unsigned int i)
{
	MaxRecords = i;
	CurrRecords = 0;
	CurrIndex = -1;
	Rows = new TabRecord<T>*[MaxRecords];
}
//..........................................................
template<typename T>
void Table<T>::Reset()
{
	if(CurrRecords > 0)
		CurrIndex = 0;
	else
		CurrIndex = -1;
}
//..........................................................
template<typename T>
T* Table<T>::GetCurr() const
{
	T* tmp;
	if (CurrIndex >= 0 && CurrIndex<CurrRecords)
	{
		tmp = Rows[CurrIndex]->Data;
	}
	else
	{
		throw (string)"Table Is Empty";
	}
	return tmp;
}
//..........................................................
template<typename T>
void Table<T>::SetNext()
{
	if (CurrIndex != -1)
		CurrIndex++;
	else
		throw (string)"Table Is Empty";
	if (IsTabEnded())
		Reset();
}