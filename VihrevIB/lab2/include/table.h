#pragma once 
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

template <typename T>
class TabRecord
{
	public:
		T	Data;
		string Name;
		TabRecord(T D = NULL, string N = NULL) { Data = D; Name = N; }
		bool operator> (const TabRecord<T>& R) const { return (Data < R.Data); }
		bool operator< (const TabRecord<T>& R) const { return (Data > R.Data); }
		bool operator== (const TabRecord<T>& R) const { return (Data == R.Data); }
		bool operator!= (const TabRecord<T>& R) const { return !(*this == R); }
		 
		TabRecord<T>& operator=(const TabRecord<T>& Tab) { Data = Tab.Data; Name = Tab.Name; return *this; }
};

template <typename T>
class Table
{
	protected:
			unsigned int MaxRecords;
			unsigned int CurrRecords;
			int CurrIndex;
	public:
			Table() { MaxRecords = 1; CurrRecords = 0; CurrIndex = -1; };
			//Общие методы
			virtual void Insert(T Row, string Key) = 0;
			virtual void Delete(string key) = 0;
			virtual	 int Search(string Key) = 0;
			//Методы навигации
			void Reset() { if (!IsEmpty()) CurrIndex = 0; }; //?
			bool IsTabEnded() { return CurrIndex == CurrRecords ; };
			bool IsFull() { return CurrRecords == MaxRecords; };
			bool IsEmpty() {return CurrRecords == 0;};
			//virtual TabRecord<T> GetNext() = 0;
			//virtual TabRecord<T> GetCurr() = 0;
			virtual void Realloc() = 0;
		};

