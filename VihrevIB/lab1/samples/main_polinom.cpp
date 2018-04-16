#include "polinom.h"
#include <conio.h>
#include <Windows.h>
int main()
{
	char  ch = 0;
	string exp1;
	string exp2;
	system("color F0");

	cout << "Use only: " << endl << " letters x,y,z" << endl << " numbers 0...9" << endl << " symblols . ,^ , +, -" << endl ;

	while (ch != 27)
	{   
		cout << "Enter first polinom: " << endl;
		cin >> exp1;
		Polinom A(exp1);
		cout << "A = " <<A << endl;

		cout << "Enter second polinom: " << endl;
		cin >> exp2;
		Polinom B(exp2);
		cout <<"B = " << B << endl << "-----------------------------------------------------------------------------" << endl;
		Polinom res = A + B;
		cout << " A + B = ";
		cout << res << endl;

		res = A - B;
		cout << " A - B = ";
		cout << res << endl;

		res = B - A;
		cout << " B - A = ";
		cout << res << endl;

		res = A * B;
		cout << " A * B = ";
		cout << res << endl;
		cout << "-----------------------------------------------------------------------------" << endl;
		cout << "Esc to exit " << endl;
		
		ch = _getch();
	}



	return 0;
}