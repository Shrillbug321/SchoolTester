#include <iostream>
#include <fstream>
using namespace std;
int main()
{
	ifstream f;
	f.open("l.txt", ios::in);
	for (int i=0; i<23; i++)
	{
		f.seekg(i);
		cout << f.get() << " ";
	}
		
}
