#include <iostream>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <iomanip>
#include "students.hpp"
using namespace std;
//extern int difficulty;
extern ifstream f;
int a;
clock_t start, stop;
void load();
void check();

struct q_a
{
	string question;
	string answer;
} q_a1;

string student::select()
{
	string pom;
	system("cls");
/*	cout << "Witaj.";
	Sleep(150);
	system("cls");
	cout << "Za chwilê rozpocznie siê test z jêzyka polskiego.\n";
	Sleep(250);
	system("cls");
	cout << "Proszê wybraæ poziom trudnoœci:\n"
	<< "1. £atwy\n"
	<< "2. Œredni\n"
	<< "3. Trudny\n";
	//cin >> a;*/
	a=1;
	switch (a)
	{
		case 1:
			{
				pom="Pliki/easy — kopia.txt";
				return pom;
				break;
			}
		case 2:
			{
				pom="Pliki/medium.txt";
				return pom;
				break;
			}
		case 3:
			{
				pom="Pliki/hard.txt";
				return pom;
				break;
			}
		default:
			{
				cout << "Nie ma takiej mo¿liwoœci.\n"
				<< "Proszê wybraæ poziom trudnoœci:\n";
				cin.ignore();
				cin.clear();
				cin >> a;
			}
	}
			
}

int student::count(string b)
{
	
	int i=0;	//liczy pytania
	string c;
	float d;
	for (int j=0; j<10000; j++)
	{
		f.open(b.c_str(), ios::binary);
		i=0;
		start=clock();//cout <<"a";
		f.seekg(20);
		while(!f.eof())
		{
			getline(f,c);
		}
		//cout << f.get();
		stop=clock();
		f.close();
		cout << j << ".\n";
	d+=(float) (stop-start)/CLOCKS_PER_SEC;
	}
	cout << setprecision (10) << d/10000 << "\n"; 
	//return (i+1)/2;
}
/*
void ask(string b)
{
	for (int i=0; i<10; i++)
	{
		a=rand();
	}
}
}*/
