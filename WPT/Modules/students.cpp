#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include "program.hpp"
#include "errors.hpp"
#include "students.hpp"
#include "checks.hpp"
using namespace std;

struct person
{
	string name;
	string surname;
	string class_;
} p;

void student::student()
{
	int q_in_file, q2a, points=0;			//q2a — questions_to_answer
	string user_answer, pom, file_name, grade;
	while (1)
	{
		q2a=student::how_many();
		student::get_name();
		file_name=student::difficulty();
		q_in_file=count(file_name);
		points=student::ask(file_name, q_in_file, q2a);
		grade=student::mark(points, q2a);
		student::save(file_name, points, q2a, grade);
		if ( student::next() ==0 )
		{
			clear();
			break;
		}
		points=0;
	}
}

int student::how_many()
{
	int q2a;
	ifstream f;
	f.open("Pliki/config.ini", ios::in);
	f >> q2a;
	f.close();
	return q2a;
}

void student::get_name()
{
	clear();
	cout << "Podaj imiê: ";
	cin >> p.name;
	cout << "Podaj nazwisko: ";
	cin >> p.surname;
	cout << "Podaj klasê: ";
	cin >> p.class_;
}

string student::difficulty()
{
	int a=0;
	string pom;
	clear();
	cout << "Proszê wybraæ poziom trudnoœci:\n"
	<< "1. £atwy\n"
	<< "2. Œredni\n"
	<< "3. Trudny\n"
	<< "4. Jak odpowiadaæ?\n";
	do
	{
		cin >> a;
		switch (a)
		{
		case 1:
		{
			pom="Pliki/easy.txt";
			return pom;
		}
		case 2:
		{
			pom="Pliki/medium.txt";
			return pom;
		}
		case 3:
		{
			cout << "Poziom trudny zawiera szczególarskie pytania.\n";
			if ( are_you_sure()== 1)
			{
				pom="Pliki/hard.txt";
				return pom;
			}
			else
				a=-1;
		}
		case 4:
		{
			help();
		}
		default:
		{
			cout << "Proszê wybraæ poziom trudnoœci:\n";
			cin.clear();
			cin.ignore();
		}
		}
	} while (a<1 || a>3);
}

void student::help()
{
	ifstream f;
	string pom;
	f.open("Pliki/instrukcja.txt", ios::in);
	while ( !f.eof() )
	{
		getline(f,pom);
		cout << pom << "\n";
	}
	f.close();
}

int student::ask(string file_name, int q_in_file, int q2a)
{
	int *tab=new int[q2a], points=0, a;
	string user_answer, pom;
	ifstream f;
	f.open(file_name.c_str(), ios::in);
	srand(time(NULL));
	cin.ignore();
	cout << "Zadanych zostanie " << q2a << " pytañ\n";
	pause();
	clear();
	for (int i=1; i<=q2a; i++)
	{
		do
		{
			a=rand()%q_in_file+1;
			if ( reply(tab, a, i) == 0)
			{
				tab[i]=a;
				break;
			}
		} while (1);
		int j=2*a-1;	//musi skakaæ po dwie linijki
		while (j>1)
		{
			getline (f,pom);
			j--;
		}
		getline(f,pom);
		cout << i << "." << pom << "\n" << "  ";
		getline(f,pom);
		cin.clear();
		getline (cin, user_answer);
		points+=check::check(user_answer, pom);
		f.seekg(0);
	}
	delete []tab;
	f.close();
	error::logs(12, file_name);
	return points;
}

bool student::reply(int *tab, int randomized, int i)
{
	for (int k=0; k<i; k++)
	{
		if (tab[k]==randomized)
			return 1;
	}
	return 0;
}


void student::load_grade( int grade_percent[] )
{
	int a;
	ifstream f;
	f.open("Pliki/config.ini", ios::in);
	f >> a;
	for (int i=0; i<=16; i++)
	{
		f >> grade_percent[i];
	}
	f.close();
}

string student::mark(int points, int q2a) 
{
	int grade_percent[16];
	string suffix;
	string grade[16]={ "1!", "1", "1+", "2-", "2", "2+", "3-", "3",
	"3+", "4-", "4", "4+", "5-", "5", "5+", "6" };
	load_grade( grade_percent );
	if ( (p.name[p.name.length()-1]=='a' && p.name!="Barnaba") || p.name=="Beatrycze")
		suffix="aœ";
	else
		suffix="eœ";
	int i=0, percent=points*100/q2a;
	while ( grade_percent[i] < percent )
	{
		i++;
	}
	cout << "\nZdoby³" << suffix << " " << points << " punktów (" << percent << "%)\n\n";
	cout << "Dosta³" << suffix << " " << grade[i] <<".";
	return grade[i];
}

void student::save(string file_name, int points, int q2a, string grade)
{
	ofstream s;
	if (file_name=="Pliki/easy.txt")
	{
		s.open("Pliki/easy_wyniki.txt", ios::app);
	}	
	if (file_name=="Pliki/medium.txt")
	{
		s.open("Pliki/medium_wyniki.txt", ios::app);
	}
	if (file_name=="Pliki/hard.txt")
	{
		s.open("Pliki/hard_wyniki.txt", ios::app);
	}
	s << "\n" << setw(15) << left << p.name
	<< setw(25) << left << p.surname
	<< setw(6) << left << p.class_ 
	<< setw(2) << right << points << "/"
	<< setw(3) << left << q2a
	<< setw(4) << left << points*100/q2a
	<< setw(2) << left << grade;
	error::logs(13, file_name);
	s.close();
}

bool student::next()
{
	int a;
	cout << "\nCo dalej?\n" 
	<< "1.Rozpocznij kolejny test\n"
	<< "0.Wróæ do menu\n";
	cin >> a;
	while (a>1 || a<0)
	{
		cout << "WprowadŸ 1 albo 0\n";
		cin.clear();
		cin.ignore();
		cin >> a;
	}
	return a;
}
