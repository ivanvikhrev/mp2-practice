#include "table.h"

template <typename T>
class OrdTable : public Table<T>
{
protected:
	void Realloc();
public:
	// Конструкторы и деструктор
	OrdTable(unsigned int i = 10);
	OrdTable(const OrdTable<T>& TabToCopy);
	~OrdTable() {};
	//Методы
	void Insert(const T Data, const string Key);
	T* Search(const string Key);
	void Delete(const string Key);
	template<class T> friend std::ostream& operator<< (std::ostream& os, const OrdTable<T>& Tab);

};

//............................................................................
template <typename T>
OrdTable<T>::OrdTable(unsigned int i) : Table(i)
{
}
//............................................................................
template <typename T>
OrdTable<T>::OrdTable(const OrdTable<T>& TabToCopy) : Table(TabToCopy)
{
	
}
//............................................................................
template <typename T>
void OrdTable<T>::Realloc()
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
void OrdTable<T>::Insert(const T Data, const string Key)
{
	if (IsFull())
		Realloc();

	TabRecord<T>* Row = new TabRecord<T>(Key, Data);
	Reset();
	
	Reset();
	while (!IsTabEnded() && Row->Key >= Rows[CurrIndex]->Key)
	{
		if (Rows[CurrIndex]->Key == Row->Key) 
		{
			string s = "Key: " + Key + " - isn`t unique";
			throw s;
		}
		CurrIndex++;
	}
	if (IsEmpty())
		CurrIndex++;
	CurrRecords++;
	for (int i = CurrRecords-1; i > CurrIndex; i--)
	{
		Rows[i] = Rows[i - 1];

	}
	Rows[CurrIndex] = Row; 
	Reset();
	
}
//............................................................................
template <typename T>
T* OrdTable<T>::Search(const string Key)
{
	Reset();
	T* tmp = nullptr;

	if (!IsEmpty())
	{	
		int i = -1, j = CurrRecords;
		int mid;
		while (i < j -1 ) //
		{	
			mid = (j + i) / 2;
			if (Key >= Rows[mid]->Key)
			{
				i = mid;
			}
			else
			{
				j = mid;
			}

		}
		if (Key == Rows[i]->Key)
		{
			CurrIndex = i;
			tmp = &(Rows[CurrIndex]->Data);
		}
		else
		{
			string s = Key + " Not Found";
			throw s;
		}
	}
	else
		throw (string)"Table Is Empty";
	return tmp;
}
//............................................................................
template <typename T>
void OrdTable<T>::Delete(const string Key)
{
	Reset();
	if (IsEmpty())
		throw (string)"Cant Delete From Empty Table";
	Search(Key);
	if (CurrRecords > 1)
	{	
		CurrRecords--;
		for (int i = CurrIndex; i < CurrRecords; i++)
		{
			Rows[i] = Rows[i + 1];

		}
		Reset();
	}
	else
		CurrRecords = 0;



}
//............................................................................
template <typename T>
std::ostream& operator<< (std::ostream& os, const OrdTable<T>& Tab)
{
	unsigned int i = 0;

	while (i < Tab.CurrRecords)
	{
		os << i << ". " << Tab.Rows[i]->Key << "  |   " << Tab.Rows[i]->Data << std::endl;
		i++;
	}
	if (Tab.CurrRecords == 0)
		os << "Table is Empty";
	return os;
}