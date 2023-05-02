#include <iostream>
#include <fstream>
using namespace std;
int main()
{
	char a;
	ifstream f;
	f.open("l.txt", ios::in);
	while (!f.eof())
	{
		a=f.get();
		if (a>47 && a<=59)
		cout << (int) a;
		else
		cout << a;
	}
}
