#include <iostream>
#include <fstream>
#include "program.hpp"
#include "checks.hpp"
using namespace std;

bool check::check(string user_answer, string good_answer)
{
	if (good_answer[0]=='|')
	{
		if ( selecting(user_answer, good_answer) )
		{
			cout << "  Dobrze\n";
			return 1;
		}
		else
		{
			cout << "  �le\n";
			return 0;
		}
	}
	while (1)
	{
		if (user_answer==good_answer)	//je�li u�ytkownik wpisa� dok�adnie tak, jak w pliku
		{
			cout << "  Dobrze\n";
			return 1;
		}
		else 							//je�li u�ytkownik wpisa� inaczej
		{
			if ( !is_digit(good_answer[0]) )	//to sprawd� czy dobra odpowied� nie jest liczb�
			{									//gdyby by�a to nie ma co sprawdza� liter�wek -> 51
				to_lower(user_answer, good_answer);	//u�ytkownik m�g� wszystko wpisa� ma�ymi literami
				if (user_answer==good_answer)
				{	
					cout << "  Dobrze\n";
					return 1;
				}
				else  if ( misspell( user_answer, good_answer ) )	//sprawdzenie liter�wki
				{
					cout << "  Prawdobodobnie pope�niono liter�wk�. Prosz� wpisa� odpowied� jeszcze raz.\n  ";
					cin.clear();
					getline (cin, user_answer);
				}
				else
				{
					cout << "  �le\n";
					return 0;
				}
			}
			else						//
			{
				cout << "  �le\n";
				return 0;
			}
		}
	}
}

bool check::selecting(string user_answer, string good_answer)
{	//gdy by� signed int kompilator marudzi� (d�. stringa)
	unsigned int j=0;				//do sprawdzenia odpowiedzi u�ytkownika (j=0 poniewa� nie ma znaku kontrolnego)
	to_lower(user_answer, good_answer);
	for (unsigned int i=1; i<=good_answer.length()+1; i+=2)	//od jedynki poniewa� 0 to znak kontrolny |
	{												//co dwa aby omin�� odst�p
		if (user_answer[j]==good_answer[i])
		{
			j+=2;
			if ( j==good_answer.length() )
				return 1;
			i=-1;									//-1+2=1
		}
	}
	return 0;
}

bool check::is_digit(char good_answer)
{
	if (good_answer>47 && good_answer<58)
		return 1;
	return 0;
}

bool check::misspell(string user_answer, string good_answer)
{
	unsigned int j=0;
	if (user_answer.length()==good_answer.length()-1 )
	{
		for (unsigned int i=0; i<good_answer.length(); i++)
		{
			j=i+1;
			if (user_answer[i]!=good_answer[i])		//je�li napotkano inn� liter� (1)
			{
				if ( i==good_answer.length()-1 )	//sprawd� czy to koniec
				{
					return 1;
				}									//dop�ki kolejne litery s� przesuni�te o jeden
				while ( user_answer[i]==good_answer[j] && j<good_answer.length() )
				{	
					i++;
					j++;
				}
				if (i==good_answer.length()-1)		//np d�.=5, przed (1) i=2 (czyli dwie by�y dobre)
					return 1;						//to w (1) powinno sprawdzi� t� (tj. 3.) i dwie kolejne (i=4)
				return 0;
			}
		}
		
	}
	if (user_answer.length()==good_answer.length() )
	{
		for (unsigned int i=0; i<good_answer.length(); i++)
		{
			if (user_answer[i]!=good_answer[i])
				j++;
		}
		if (j==1)
			return 1;
		return 0;
	}
	if ( user_answer.length()==good_answer.length()+1 )
	{
		for (unsigned int i=0; i<good_answer.length()+1; i++)
		{
			j=i+1;
			if (user_answer[i]!=good_answer[i])		//je�li napotkano inn� liter�
			{
				if ( i==good_answer.length()-1 )	//sprawd� czy to koniec
				{
					return 1;
				}		//dop�ki kolejna litera u�ytkownika == obecnej w dobrej odpowiedzi
				while ( user_answer[j]==good_answer[i] && j<=good_answer.length()+1 )
				{	
					i++;
					j++;
				}
				if (i==good_answer.length()+1)
					return 1;
				return 0;
			}
		}
	}
}
