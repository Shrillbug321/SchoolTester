#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include "program.hpp"
#include "errors.hpp"
using namespace std;

void clear()
{
	system("cls");
}

void pause()
{
	cout << "Naciœnij dowolny klawisz aby kontynuowaæ...";
	system("pause>nul");
}

int main_menu()
{
	int columns=84;
	string pom="Sprawdzian z jêzyka polskiego";
	draw(columns+2, '-');
	cout << "\n|";
	draw(columns, ' ');
	cout << "|\n|";
	
	draw( (columns-pom.length()) /2, ' ');
	cout << pom;
	draw( (columns-pom.length()) /2+1, ' ');
	cout << "|\n|";
	
	draw(columns, ' ');
	cout << "|\n";
	draw(columns+2, '-');
	cout << "\n\n\n";
	
	pom="|                  |";
	draw(columns,  ' ', "--------------------");
	draw(columns,  ' ', "|                  |");
	draw(columns,  ' ', "|  1. Sprawdzian   |");
	draw(columns,  ' ', "|  2. Nauczyciel   |");
	draw(columns,  ' ', "|  0. Wyjd¿        |");
	draw(columns,  ' ', "|                  |");
	draw(columns,  ' ', "--------------------");
	
	int a;
	cin >> a;
	if	(a<0 || a>1 || cin.fail() )	//aby komunikaty siê nie powtarza³y
	{
		cout << "Brak takiej mo¿liwoœci.\nProszê wybraæ prawid³ow¹ opcjê.\n";
		while (a<0 || a>2 || cin.fail() )
		{
			cin.clear();
			cin.ignore();
			cin >> a;
		}
	}
	if (a==0)
	{
		error::logs(7);
		exit(EXIT_SUCCESS);
	}
	clear();
	return a;
}

void draw(int columns, char sign)
{
	for (int i=0; i<columns; i++)
	{
		cout << sign;
	}
}

void draw(int columns, char sign, string pom)
{
	for (unsigned int i=0; i< ( columns-pom.length() )/2 ; i++)
	{
		cout << sign;
	}
	cout << pom;
	for (unsigned int i=0; i< ( columns-pom.length() )/2 ; i++)
	{
		cout << sign;
	}
	cout << "\n";
}

bool logon( int found)
{
	int i=0;
	string user, password, pom;
	ifstream f;
	f.open("Pliki/password.txt");
	while ( i<5 )
	{
		cout << "U¿ytkownik: ";
		cin >> user;
		cout << "Has³o: ";
		cin >> password;
		if ( found==0 )
		{
			if ( user=="admin" && password=="systemu")
				return 1;
		}
		else
		{
			while ( !f.eof() )
			{
				pom=decryption( f );
				if (user==pom)
				{
					pom=decryption( f );
					if (password==pom)
					{
						f.close();
						error::logs(4);
						return 1;
					}
				}
			}
		}
		cout << "Niepoprawne dane logowania. \n";
		f.clear();
		f.seekg(0);
		i++;
		clear();
		if (i==4)
			cout << "Ostania próba. \n";
	}
	f.close();
	cout << "Odmowa dostêpu.";
	error::logs(5);
	pause();
	exit(EXIT_FAILURE);
}

void to_lower(string &user_answer, string &good_answer)
{
	for (unsigned int i=0; i<user_answer.length(); i++)
	{
		if (user_answer[i]>64 && user_answer[i]<91)
			user_answer[i]+=32;
	}
	for (unsigned int i=0; i<good_answer.length(); i++)
	{
		if (good_answer[i]>64 && good_answer[i]<91)
			good_answer[i]+=32;
	}
}

void to_lower(string &user_answer)
{
	for (unsigned int i=0; i<user_answer.length(); i++)
	{
		if (user_answer[i]>64 && user_answer[i]<91)
			user_answer[i]+=32;
	}
}

void encryption()
{
	string pom;
	ofstream g;
	g.open("Pliki/password.txt", ios::app);
	cout << "Podaj nazwê u¿ytkownika: "; 
	cin >> pom;
	if (pom=="0")
	{
		clear();
		return;
	}
	for (unsigned int i=0; i<pom.length(); i++)
	{
		pom[i]+=3;
		g << (int) pom[i] << ' ';
	}
	g << '\n';
	cout << "Podaj has³o: ";
	do
	{
		cin >> pom;
		if (pom.length()<4)
			cout << "U¿ytkownik nie mo¿e mieæ tak krótkiego has³a.\n";
	} while (pom.length()<4);
	for (unsigned int i=0; i<pom.length(); i++)
	{
		pom[i]+=3;
		g << (int) pom[i] << ' ';
	}
	g << '\n';
	g.close();
	back_up("Pliki/password.bak");
	error::logs(6);
	clear();
}

void back_up(string file_name)
{
	string pom;
	ifstream f;
	ofstream g;
	if (file_name[file_name.length()-1]=='k')
	{
		f.open("Pliki/password.txt", ios::in);
		g.open("Pliki/password.bak", ios::out);
	}
	else
	{
		f.open("Pliki/password.bak", ios::in);
		g.open("Pliki/password.txt", ios::out);
	}
	while ( !f.eof() )
	{
		getline(f,pom);
		g << pom << '\n';
	}
	f.close();
	g.close();
}

string decryption( ifstream &f)
{
	int a, i=0;
	char b;
	string pom;
	getline(f,pom);
	stringstream str(pom);
	while ( str )
	{
		str >> a;
		a-=3;
		b= (char) a;
		pom[i]=b;
		i++;
	}
	pom.erase(i-1, pom.length() );
	return pom;
}

int are_you_sure(int a)
{
	string pom;
	if (a==1)
		cout << "Na pewno? (Tak/Nie/Dla wszystkich) ";
	else
		cout << "Na pewno? (Tak/Nie) ";
	while (1)
	{	
	getline(cin, pom);
	to_lower(pom);
	if (pom=="tak" || pom=="t")
		return 1;
	if (pom=="nie" || pom=="n")
		return 0;
	if (pom=="dla wszystkich" || pom=="wszystkie" || pom=="w")
		return 2;
	if (pom=="nie wiem")
		cout << "Ja te¿ nie\n";
	}
}

int count(string name)
{
	int i=0;	//liczy pytania
	string pom;
	ifstream f;
	f.open(name.c_str(), ios::in);
	while(!f.eof())
	{
		getline(f,pom);
		i++;
	}
	f.close();
	return i/2;
}

