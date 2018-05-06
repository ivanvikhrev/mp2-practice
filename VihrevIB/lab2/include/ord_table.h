#include "table.h"

template <typename T>
class OrdTable : Table<T>
{
protected:
	vector<TabRecord<T>> Rows;
	void Realloc();//?
public:
	// Конструкторы и деструктор
	OrdTable();
	OrdTable(const OrdTable<T>& TabToCopy);
	~OrdTable() { Clean(); };
	//Методы
	void Insert(T Row, string Key);
	int Search(string Key);
	void Delete(string Key);
	void Clean() { Rows.clear(); CurrIndex = -1; CurrRecords = 0; };
	template<class T2> friend std::ostream& operator<< (std::ostream& os, const OrdTable<T2>& Tab);

};

//............................................................................
template <typename T>
OrdTable<T>::OrdTable() : Table()
{
	Rows.reserve(MaxRecords);
}
//............................................................................
template <typename T>
OrdTable<T>::OrdTable(const OrdTable<T>& TabToCopy)
{
	Rows = TabToCopy.Rows;
	MaxRecords = TabToCopy.MaxRecords;
	CurrIndex = TabToCopy.CurrIndex;
	CurrRecords = TabToCopy.CurrRecords;
}
//............................................................................
template <typename T>
void OrdTable<T>::Realloc()
{
	MaxRecords *= 2;
	Rows.reserve(MaxRecords);
}
//............................................................................
template <typename T>
void OrdTable<T>::Insert(T Data, string Key)
{
	if (IsFull())
		Realloc();

	TabRecord<T> Row(Data, Key);
	
	if (!IsEmpty())
	{
		Reset();
		while (CurrIndex < CurrRecords - 1 && !IsEmpty() && Row.Name > Rows[CurrIndex].Name)
		{
			CurrIndex++;
		}
		Rows.insert(Rows.begin() + CurrIndex + 1, Row);
		CurrRecords = Rows.size();
		
	}
	else
	{
		Rows.push_back(Row);
		CurrRecords = Rows.size();
	}
}
//............................................................................
template <typename T>
int OrdTable<T>::Search(string Key)
{
	Reset();
	int i = 0 , j = CurrRecords;

	if (IsEmpty())
		i = -1;
	
	while (j-i > 0)
	{
		if (Key > Rows[i+(j-i)/ 2].Name)
		{
			i += (j-i) / 2 + 1 ;
		}
		else
		{
			j /= 2;
		}
	
	}

	if (IsTabEnded())
		i = -1;
	Reset();
	return i;
}
//............................................................................
template <typename T>
void OrdTable<T>::Delete(string Key)
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
std::ostream& operator<< (std::ostream& os, const OrdTable<T2>& Tab)
{
	unsigned int i = 0;

	while (i < Tab.CurrRecords)
	{
		os << i << "." << Tab.Rows[i].Name << "  |   " << Tab.Rows[i].Data << std::endl;
		i++;
	}
	if (Tab.CurrRecords == 0)
		os << "Table is Empty";
	return os;
}