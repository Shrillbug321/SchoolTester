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
			cout << "  le\n";
			return 0;
		}
	}
	while (1)
	{
		if (user_answer==good_answer)	//jeœli u¿ytkownik wpisa³ dok³adnie tak, jak w pliku
		{
			cout << "  Dobrze\n";
			return 1;
		}
		else 							//jeœli u¿ytkownik wpisa³ inaczej
		{
			if ( !is_digit(good_answer[0]) )	//to sprawdŸ czy dobra odpowiedŸ nie jest liczb¹
			{									//gdyby by³a to nie ma co sprawdzaæ literówek -> 51
				to_lower(user_answer, good_answer);	//u¿ytkownik móg³ wszystko wpisaæ ma³ymi literami
				if (user_answer==good_answer)
				{	
					cout << "  Dobrze\n";
					return 1;
				}
				else  if ( misspell( user_answer, good_answer ) )	//sprawdzenie literówki
				{
					cout << "  Prawdobodobnie pope³niono literówkê. Proszê wpisaæ odpowiedŸ jeszcze raz.\n  ";
					cin.clear();
					getline (cin, user_answer);
				}
				else
				{
					cout << "  le\n";
					return 0;
				}
			}
			else						//
			{
				cout << "  le\n";
				return 0;
			}
		}
	}
}

bool check::selecting(string user_answer, string good_answer)
{	//gdy by³ signed int kompilator marudzi³ (d³. stringa)
	unsigned int j=0;				//do sprawdzenia odpowiedzi u¿ytkownika (j=0 poniewa¿ nie ma znaku kontrolnego)
	to_lower(user_answer, good_answer);
	for (unsigned int i=1; i<=good_answer.length()+1; i+=2)	//od jedynki poniewa¿ 0 to znak kontrolny |
	{												//co dwa aby omin¹æ odstêp
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
			if (user_answer[i]!=good_answer[i])		//jeœli napotkano inn¹ literê (1)
			{
				if ( i==good_answer.length()-1 )	//sprawdŸ czy to koniec
				{
					return 1;
				}									//dopóki kolejne litery s¹ przesuniête o jeden
				while ( user_answer[i]==good_answer[j] && j<good_answer.length() )
				{	
					i++;
					j++;
				}
				if (i==good_answer.length()-1)		//np d³.=5, przed (1) i=2 (czyli dwie by³y dobre)
					return 1;						//to w (1) powinno sprawdziæ tê (tj. 3.) i dwie kolejne (i=4)
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
			if (user_answer[i]!=good_answer[i])		//jeœli napotkano inn¹ literê
			{
				if ( i==good_answer.length()-1 )	//sprawdŸ czy to koniec
				{
					return 1;
				}		//dopóki kolejna litera u¿ytkownika == obecnej w dobrej odpowiedzi
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
