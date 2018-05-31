#include <conio.h>
#include "unord_table.h"
#include "ord_table.h"
#include "hash_table.h"
#include "polinom.h"

int main()
{	 
	system("color F0");
	UnordTable<Polinom> Utab;
	OrdTable<Polinom> Otab;
	HashTable<Polinom> Htab;
	string Key,Str;
	Polinom P;
	char  ch = 0;
	while (ch != 27)
	{	
		system("cls");
		cout << "UnordTable: " << endl << Utab << endl;
		cout << "OrdTable :" << endl << Otab << endl;
		cout << "HashTable :" << endl << Htab << endl << endl;
		cout << "You can insert/delete and find in tables" << endl;
		cout << "What will you do?" << endl << "1. Insert" << endl << "2. Delete" <<endl <<  "3. Search" << endl;
		cin >> Str;
		int i = 0;
		if (isdigit(Str[0]))
			i = stoi(Str);
		switch (i)
		{ 
			case 1: 
			{
				while(true)
				{
					cout << "Input Polinom" << endl;
					cin >> Key;
					if (Key == "end") break;
					P = Polinom(Key);
					try
					{
						system("cls");
						Utab.Insert(P, Key);
						Otab.Insert(P, Key);
						Htab.Insert(P, Key);
						cout << "UnordTable: " << endl << Utab << endl;
						cout << "OrdTable :" << endl << Otab << endl;
						cout << "HashTable :" << endl << Htab << endl << endl;
					}
					catch (string s)
					{
						cout << "UnordTable: " << endl << Utab << endl;
						cout << "OrdTable :" << endl << Otab << endl;
						cout << "HashTable :" << endl << Htab << endl << endl;
						cout << "Error :" << s << endl;
					} 
					
				} 
			}
			break;
			case 2:
			{
				while (true)
				{
					cout << "Input Polinom" << endl;
					cin >> Key;
					if (Key == "end") break;
					try
					{	
						system("cls");
						Utab.Delete(Key);
						Otab.Delete(Key);
						Htab.Delete(Key);
						cout << "UnordTable: " << endl << Utab << endl;
						cout << "OrdTable :" << endl << Otab << endl;
						cout << "HashTable :" << endl << Htab << endl << endl;
					}
					catch (string s)
					{
						cout << "UnordTable: " << endl << Utab << endl;
						cout << "OrdTable :" << endl << Otab << endl;
						cout << "HashTable :" << endl << Htab << endl << endl;
						cout << "Error :" << s << endl;
					}
				}
			}
			break;
			case 3:
			{
				while (true)
				{
					cout << "Input Polinom" << endl;
					cin >> Key;
					if (Key == "end") break;
					system("cls");
					cout << "UnordTable: " << endl << Utab << endl;
					cout << "OrdTable :" << endl << Otab << endl;
					cout << "HashTable :" << endl << Htab << endl << endl;
					try
					{
						cout << "Search in UnordTable : " << *(Utab.Search(Key)) << endl;
						cout << "Search in OrdTable : " << *(Otab.Search(Key)) << endl;
						cout << "Search in HashTable : " << *(Htab.Search(Key)) << endl;
					}
					catch (string s)
					{
						cout << "Error :" << s << endl;
					}
				}
			}
			break;
			default:
				cout << "try again" << endl;
			break;
		}
		
		cout << "-----------------------------------------------------------------------------" << endl;
		cout << "Esc to exit " << endl;
		ch = _getch();
	}
	return 0;
}

