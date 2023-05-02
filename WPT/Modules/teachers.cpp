#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include "program.hpp"
#include "errors.hpp"
#include "teachers.hpp"
#include "settings.hpp"
using namespace std;
void teacher::menu()
{
	char a=-1;
	string file_name;
	clear();
	while ( a!='0' )
	{
		cout << "Pytania\n"
		<< " 1. Wyœwietl\n"
		<< " 2. Dodaj\n"
		<< " 3. Usuñ\n"
		<< "4. Wyœwietl wyniki\n"
		<< "5. Ustawienia\n"
		<< "0. Wróæ do menu\n";
		a=getch();
		while ( a<48 || a>53 )		//brak defaulta poniewa¿
		{							//pêtla nie przepuœci gdy Ÿle
			a=getch();
		}
		clear();
		switch (a)
		{
			case '1':
				file_name=difficulty();
				show_a(file_name);
				break;
			case '2':
				add_a();
				break;
			case '3':
				file_name=difficulty();
				delete_a(file_name);
				break;
			case '4':
				file_name=difficulty();
				show_s(file_name);
				break;
			case '5':
				setting::setting();
				break;
		}
	}
}

string teacher::difficulty()
{
	int a=-1;
	string pom;
	cout << "Wybierz poziom trudnoœci:\n"
	<< "1. £atwy\n"
	<< "2. Œredni\n"
	<< "3. Trudny\n";
	while (a<49 || a>51)
	{
		a=getch();
	}
	switch (a)
	{
	case '1':
		pom="Pliki/easy.txt";
		break;
	case '2':
		pom="Pliki/medium.txt";
		break;
	case '3':
		pom="Pliki/hard.txt";
		break;
	}
	clear();
	return pom;
}

void teacher::show_a(string file_name)
{
	int a, i;
	string pom="a";
	ifstream f;
	do
	{
		clear();
		i=1;
		f.open(file_name.c_str(), ios::in);
		while (!f.eof())	
		{	
			getline(f,pom);	
			cout << i << ". " << pom << "\n";
			getline(f,pom);
			cout << " " << pom << "\n";
			i++;
		}
		f.close();
		cout << "1.£atwy 2.Œredni 3.Trudny 0.Wróæ";
		do
		{
			a=getch();
		} while ( a<48 || a>51 );
		if (a>=49)
		{
			switch (a)
			{
			case '1':
				file_name="Pliki/easy.txt";
				break;
			case '2':
				file_name="Pliki/medium.txt";
				break;
			case '3':
				file_name="Pliki/hard.txt";
				break;
			}
		}
	} while ( a!='0' );
	clear();
}

void teacher::add_a()
{
	char a;
	string file_name;
	cout << "1. Wpisz\n" << "2. Z pliku\n";
	do
	{
		a=getch();
	} while (a<49 || a>50);	
	file_name=difficulty();	//tu jest bru¿dz¹cy getline()
	clear();
	if ( a=='1' )
		write_a(file_name);
	else
		import_a(file_name);
}

void teacher::write_a(string file_name)
{
	string question, answer;
	ofstream g;
	cin.clear();
	cin.ignore();
	g.open(file_name.c_str(), ios::app);
	while ( 1 )
	{
		cout << "Pytanie: ";
		getline(cin, question);
		if (question=="0")
			break;
		if (question.length()==0)
			continue;
		g << "\n" << question;
		cout << "OdpowiedŸ: ";
		getline(cin, answer);
		if (answer.length()==0)
			continue;
		g << "\n" << answer;
	}
	g.close();
	error::logs(8, file_name.c_str());
	clear();
}

void teacher::import_a(string file_name)
{
	char letter;
	string pom;
	ifstream f;
	ofstream g;
	do
	{
		cout << "Podaj œcie¿kê dostêpu: ";
		getline(cin,pom);
		if (pom=="0")
		{
			clear();
			return ;
		}
		pom+=".txt";
		f.open(pom.c_str(), ios::in);
	} while ( f.fail() );
	g.open(file_name.c_str(), ios::app);
	while ( !f.eof() )
	{
		pom="";
		while(1)
		{
			letter=f.get();
			if (letter=='\t'  || letter=='\n' || letter==';' || letter==EOF)
			{
				g << "\n" << pom;
				break;
			}
			pom=pom+letter;
		}
	}
	f.close();
	g.close();
	clear();
	error::logs(9);
}

void teacher::delete_a(string file_name)	//raczej przepisz, nie usuñ
{
	bool bad, all;
	int a, i, j;
	string pom;
	ifstream f;
	ofstream g;
	while ( 1 )
	{
		i=count(file_name);
		j=1;
		cout << "Wpisz numer pytania, które chcesz usun¹æ: ";
		do
		{
			cin >> a;
			bad=cin.fail();
			if ( bad || a<0 || a>i )
			{
				cout << "Nie ma takiego pytania. ";
				cin.clear();
				cin.ignore();
			}
		} while ( bad || a<0 || a>i );
		if (a==0)
			break;
		if (all==0)
		{
			int b;
			b=are_you_sure(1);
			if (b==0)
				continue;
			if (b==2)		//1 to tak czyli dalej
				all=1;
		}
		f.open(file_name.c_str(), ios::in);
		g.open("Pliki/new.txt", ios::out);
		while( j<i )
		{
			if ( j==a )
			{
				getline(f,pom);
				getline(f,pom);
			}
			getline(f,pom);
			g << pom << "\n";
			getline(f,pom);
			g << pom;
			if ( j!=i-1 ) 			// \n na koñcu pliku tworzy pytanie-widmo,
				g << "\n";			// które przy kolejnych usuniêciach siê nawarstwia
			j++;
		}
		f.close();
		g.close();
		remove(file_name.c_str());
		rename("Pliki/new.txt", file_name.c_str());
	}
	error::logs(10, file_name);
	clear();
}

void teacher::show_s(string file_name)
{
	int i=1;
	char a=-1;
	string pom="_wyniki";
	ifstream f;
	file_name.insert( file_name.length()-4, pom );
	f.open( file_name.c_str(), ios::in );
	cout << setw(4) << right << "Lp."
	<< setw(15) << left << "Imiê"
	<< setw(25) << left << "Nazwisko"
	<< setw(6) << left << "Kl."
	<< setw(2) << right << "Zd" << "/"
	<< setw(3) << left << "P"
	<< setw(4) << left << "%"
	<< setw(2) << left << "Ocena";
	while (!f.eof())
	{
		getline(f,pom);
		cout << "\n" << setw(3) << right << i << "." << pom;
		i++;
	}
	f.close();
	while (a!=48)
		a=getch();
	clear();
}

