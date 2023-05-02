#include <iostream>
#include <fstream>
#include <cstdlib>
#include "program.hpp"
#include "students.hpp"
#include "errors.hpp"
using namespace std;

bool error::error()
{
	bool found;
	error::questions();
	found=error::password();
	error::config();
	return found;
}

void error::questions()
{
	int i=0;
	string file="Pliki/";
	string list[3]= {"easy.txt", "medium.txt", "hard.txt"};
	ifstream f;
	for (int j=0; j<3; j++)
	{
		string pom=file+list[j];
		f.open(pom.c_str(), ios::in);
		if ( f.fail() )
		{
			cout << "Brak pliku " << list[j] << "\n";
			error::logs(1, list[j]);
		}
		else
		{
			i=count(pom);
			if (i< student::how_many())
				cout << "Za ma�o pyta� w pliku " << list[j] << "\n";
		}
		f.close();
		list[j].insert(list[j].length()-4, "_wyniki");
		pom=file+list[j];
		f.open(pom.c_str(), ios::in);
		if ( f.fail() )
		{
			cout << "Brak pliku " << list[j] << "\n";
			error::logs(1, list[j]);
		}
		f.close();
	}	
}

bool error::password()
{
	ifstream f;
	f.open("Pliki/password.txt", ios::in);
	if ( f.fail() )
	{
		cout << "Brak pliku z has�ami.\n";
		f.close();
		f.open("Pliki/password.bak", ios::in);
		if ( f.good() )
		{
			cout << "Przywracanie kopii zapasowej.\n";
			back_up("Pliki/password.txt");
			error::logs(2, "1");
		}
		else
		{
			cout << "Kopii zapasowej r�wnie� brak.\n";
			error::logs(2, "2");
			return 0;
		}
	}
	f.close();
	return 1;
}
void error::config()
{
	string pom;
	ifstream f;
	f.open("Pliki/config.ini", ios::in);
	if ( f.fail() )
	{
		ofstream g;
		cout << "Brak pliku z ustawieniami.\n";
		f.close();
		g.open("Pliki/config.ini", ios::out);
		pom="4 0 1 25 30 35 45 50 55 70 75 80 85 90 91 100 101";
		g << pom;
		g.close();
		cout << "Przywr�cono ustawienia domy�lne.\n";
		error::logs(3);
	}
	f.close();
}

void error::logs( int a, string b )
{
	string pom;
	ofstream g;
	g.open("Pliki/logs.txt", ios::app);
	switch(a)
	{
	case 1:
	{
		g << "Brak pliku " << b << "\n";
		break;
	}
	case 2:
	{
		g << "Nie znaleziono pliku z has�ami.\n";
		if (b=="1")
			g << " Przywr�cono z kopii zapasowej.\n";
		else
			g << " Kopii zapasowej r�wnie� nie znaleziono.\n";
		break;
	}
	case 3:
	{	
		g << "Brak pliku z ustawieniami.\n"
		<< " Przywr�cono ustawienia domy�lne.\n";
		break;
	}
	case 4:
	{	
		g << "Pomy�lnie zalogowano ";
		if (b=="u")
			g << "ucznia/uczenninc�.\n";
		else
			g << "nauczyciela/nauczycielk�.\n";
		break;
	}
	case 5:
	{	
		g << "Nieudana pr�ba logowania.\n"
		<< "Przerwano prac� programu.\n\n";
		break;
	}
	case 6:
	{	
		g << "Dodano u�ytkownika.\n" 
		<< "Utworzono kopi� zapasow� bazy u�ytkownik�w. \n";
		break;
	}
	case 7:
	{	
		g << "Prawid�owo zamkni�to program.\n\n";
		break;
	}
	case 8:
	{	
		g << "Dodano pytanie/a do pliku " << b << ".\n";
		break;
	}
	case 9:
	{	
		g << "Zaimportowano pytanie/a do pliku " << b << ".\n";
		break;
	}
	case 10:
	{	
		g << "Usuni�to pytanie/a z pliku " << b <<".\n";
		break;
	}
	case 11:
	{	
		g << "Zmieniono ustawienia.\n";
		break;
	}
	case 12:
	{
		g << "Pomy�lnie przeprowadzono test.\n" 
		<< " Zadano pytania z \"" << b << "\".\n";
		break;
	}
	case 13:
	{	
		b.insert(b.length()-4, "_wyniki");
		g << "Zapisano wynik do pliku \"" << b << "\".\n";
		break;
	}
	}
	g.close();
	
}
