#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
int main()
{
	int a;
	char b;
	ifstream f;
	f.open("stats.txt", ios::in);
	ofstream g;
	g.open("stats.txt", ios::app);
	f >> a;
	cout << a << " ";
	a+=1;
	cout << a << " ";
	itoa(a, &b, 10);
	cout << b << " ";
	g.seekp(0, ios::beg);
	g.put(b);
}
