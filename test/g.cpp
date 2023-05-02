#include <iostream>
#include <fstream>
using namespace std;
int main()
{
	char a;
	ifstream f;
	f.open("g.txt", ios::in);
	while (!f.eof() )
	{
		a=f.get();
		if (a=='\t' || a==';')
			cout << "\n";
		else
			cout << a;
	}
}
