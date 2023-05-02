#include <iostream>
#include <fstream>
#include <conio.h>
#include "program.hpp"
#include "errors.hpp"
#include "teachers.hpp"
#include "settings.hpp"
using namespace std;

void setting::setting()
{
	cout << "1. Liczba pyta�\n"
	<< "2. Procenty ocen\n"
	<< "3. Dodaj u�ytkownika\n"
	<< "4. Wy�wietl u�ytkownik�w\n"
	<< "0. Wr��\n";
	char a=-1;
	while ( a<48 || a>52 )
	{
		a=getch();
	}
	clear();
	switch (a)
	{
	case '1':
		set_answer();
		break;
	case '2':
		set_grade();
		break;
	case '3':
		encryption();
		break;
	case '4':
		show_u();
		break;
	}
}

void setting::set_answer()
{
	int a;
	string pom;
	ifstream f;
	f.open("Pliki/config.ini", ios::in);
	f >> a;
	getline (f,pom);
	f.close();
	cout <<"Obecna liczba pyta�: " << a << "\nNowa liczba pyta�: ";
	cin >> a;
	if ( cin.fail() )
	{
		while( cin.fail() )
		{
			cout << "Niepoprawna dana.\nNowa liczba pyta�: ";
			cin.clear();
			cin.ignore();
			cin >> a;
		}	
	}
	if (a==0)
	{
		clear();
		return;
	}
	ofstream g;
	g.open("Pliki/new.ini", ios::out);
	g << a << pom;
	g.close();
	remove("Pliki/config.ini");
	rename("Pliki/new.ini", "Pliki/config2.ini");
	error::logs(11);
	clear();
}

void setting::set_grade()
{
	int a;
	string pom;
	string grade[16]={ "1!", "1", "1+", "2-", "2", "2+", "3-", "3",
	"3+", "4-", "4", "4+", "5-", "5", "5+", "6" };
	ifstream f;
	f.open("Pliki/config.ini", ios::in);
	ofstream g;
	g.open("Pliki/new.ini", ios::out);
	f >> a;
	g << a << " ";
	f.close();
	for (int i=0; i<16; i++)
	{
		cout << grade[i] << " � ";
		cin >> a;
		if ( cin.fail() )
		{
			while( cin.fail() )
			{
				cout << "Niepoprawna dana.\nNowa warto�� procentowa dla " << grade[i] << ": ";
				cin.clear();
				cin.ignore();
				cin >> a;
			}	
		}
		g << a << " ";
	}
	g.close();
	remove("Pliki/config.ini");
	rename("Pliki/new.ini", "Pliki/config.ini");
	error::logs(11);
	clear();
}

void setting::show_u()
{
	char a;
	string pom;
	ifstream f;
	f.open("Pliki/password.txt", ios::in);
	if (f.fail())
		return;
	else
	{
		do
		{
			pom=decryption(f);		//tutaj jest getline()
			cout << pom << "\n";
			getline(f,pom);				//pomija linijk� z has�em
		} while ( !f.eof() );
		do
		{
			a=getch();
		} while (a!='0');
		clear();
	}
}
