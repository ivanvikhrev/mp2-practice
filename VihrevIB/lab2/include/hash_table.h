#pragma once
#include "table.h"
template <typename T>
class HashTable : public Table<T> 
{
protected:
	int* flag;
	int HashFunc(string Key) const;
	void Realloc();
public:
	// Конструкторы и деструктор
	HashTable(unsigned int i = 10);
	HashTable(const HashTable<T>& TabToCopy);
	~HashTable() { delete[] flag;};
	//Общие Методы
	void Insert(const T Data, const string Key);
	T* Search(const string Key);
	void Delete(const string Key);
	//Методы навигации
	void SetNext();
	T* GetCurr() const;
	void Reset();
	bool IsTabEnded() const { return false; };
	template<class T> friend std::ostream& operator<< (std::ostream& os, const HashTable<T>& Tab);

};
//............................................................................
template <typename T>
HashTable<T>::HashTable(unsigned int i) : Table(i)
{	
	flag = new int[i];
	for (int j = 0; j < i; j++)
		flag[j] = 0; // 0 пустые ячейки, 1 -занято, -1 - удалено
}
//............................................................................
template <typename T>
HashTable<T>::HashTable(const HashTable<T>& TabToCopy)
{
	MaxRecords = TabToCopy.MaxRecords;
	CurrIndex = TabToCopy.CurrIndex;
	CurrRecords = TabToCopy.CurrRecords;
	delete[] Rows;
	delete[] flag;
	Rows = new TabRecord<T>*[MaxRecords];
	flag = new int[MaxRecords];
	
	for (int j = 0; j < MaxRecords; j++)
		flag[j] = TabToCopy.flag[j];

	if (!IsEmpty())
		for (int i = 0; i < MaxRecords; i++)
		{	
			if(flag[i] == 1)
				Rows[i] = new TabRecord<T>(*(TabToCopy.Rows[i]));
		}
}
//............................................................................
template <typename T>
void HashTable<T>::Reset()
{	
	if (!IsEmpty())
	{	
		CurrIndex = 0;
		while (flag[CurrIndex] != 1)
			CurrIndex++;
	}
	else
		CurrIndex = -1;
}
//............................................................................
template <typename T>
T* HashTable<T>::GetCurr()  const
{
	T* tmp = nullptr;

	if(!IsEmpty())
	{	
		tmp = &(Rows[CurrIndex]->Data);
	}
	else
	{
		throw (string)"Table Is Empty";
	}
	return tmp;
}

//............................................................................
template <typename T>
void HashTable<T>::SetNext()
{
	if (!IsEmpty())
	{	
		CurrIndex++;
		while (flag[CurrIndex] != 1)
			CurrIndex = (CurrIndex+1) % MaxRecords;
	}
	else
		throw (string)"Table Is Empty";
	
}
//............................................................................
template <typename T>
void HashTable<T>::Realloc()
{
	unsigned int OldMaxRecords = MaxRecords;
	MaxRecords *= 1.5;
	TabRecord<T>** tmp = new TabRecord<T>*[OldMaxRecords];
	for (int i = 0; i < OldMaxRecords; i++)
	{
		tmp[i] = Rows[i];
	}

	delete[] Rows;
	CurrRecords = 0;
	CurrIndex = -1;
	delete[] flag;
	flag = new int[MaxRecords];
	for (int i = 0; i < MaxRecords; i++)
		flag[i] = 0;
	Rows = new TabRecord<T>*[MaxRecords];
	for (int i = 0; i < OldMaxRecords; i++)
	{
		Insert(tmp[i]->Data, tmp[i]->Key); // ? 
	}
}
//............................................................................
template<typename T>
int HashTable<T>::HashFunc(string Key) const
{	
	unsigned int i= 0;
	for (int j = 0; j < Key.length(); j++)
		i += (char)Key[j];
	for (int j = 0; j < Key.length(); j++)
		i *= 13;
	srand(i);
	unsigned int h = rand();
	return h % MaxRecords;
}
//............................................................................
template <typename T>
void HashTable<T>::Insert(const T Data, const string Key)
{
	if (IsFull())
		Realloc();
	TabRecord<T>* Row = new TabRecord<T>(Key, Data);
	Reset();
	CurrIndex = HashFunc(Key);
	if (flag[CurrIndex] == 0 || flag[CurrIndex] == -1 )
	{
		Rows[CurrIndex] = Row; 
		CurrRecords++;
		flag[CurrIndex] = 1;
		Reset();
	}
	else
	{
		if (Rows[CurrIndex]->Key != Key)
		{	
			int ind = CurrIndex;
			while (flag[CurrIndex] == 1 && CurrIndex+1 != ind)
				CurrIndex = (CurrIndex+1)  % MaxRecords; 
			Rows[CurrIndex] = Row; 
			CurrRecords++;
			flag[CurrIndex] = 1;
			Reset();
		}
		else 
		{	
			Reset();
			string s = "Key: " + Key + " - isn`t unique";
			throw s;
		}
	}
}
//............................................................................
template <typename T>
T* HashTable<T>::Search(const string Key)
{
	Reset();
	T* tmp = nullptr;
	if (IsEmpty())
		throw (string)"Cant Search In Empty Table";
	CurrIndex = HashFunc(Key);
	
	if(Rows[CurrIndex]->Key == Key)
		tmp = &(Rows[CurrIndex]->Data);
	else
	{	
		int ind = CurrIndex;
		while (flag[CurrIndex] == 1 && CurrIndex+1 != ind)
		{
			CurrIndex = (CurrIndex + 1) % MaxRecords;
			if (Rows[CurrIndex]->Key == Key)
					{
						tmp = &(Rows[CurrIndex]->Data);
						break;
					}
		}

			

		if (tmp == nullptr)
		{
			Reset();
			string s = Key + " Not Found";
			throw s;
		}

	}
	return tmp;
}
//............................................................................
template <typename T>
void HashTable<T>::Delete(string Key)
{
	Reset();
	if (IsEmpty())
		throw (string)"Cant Delete From Empty Table";
	Search(Key);

	TabRecord<T> A;
	flag[CurrIndex] = -1;
	Rows[CurrIndex] = new TabRecord<T>(A);
	CurrRecords--;

	Reset();
}
//............................................................................
//спросить почему так
template <typename T>
std::ostream& operator<< (std::ostream& os, const HashTable<T>& Tab)
{
	unsigned int i = 0;

	while (i < Tab.MaxRecords)
	{	
		if (Tab.flag[i] == 1)
		{
			os << i << ". " << Tab.Rows[i]->Key << "  |   " << Tab.Rows[i]->Data << std::endl;
		}
		i++;
	}
	if (Tab.CurrRecords == 0)
		os << "Table is Empty";
	return os;
}
