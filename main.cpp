#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Modules/program.hpp"
#include "Modules/errors.hpp"
#include "Modules/students.hpp"
#include "Modules/teachers.hpp"
using namespace std;

int main()
{
	bool found;
	int n=-1;
	system("chcp 1250>nul");
	found=error::error();
	pause();
	clear();
	while ( n!=0 )
	{
		n=main_menu();
		if ( n ==2)
		{
			clear();
			logon( found );
			teacher::menu();
			continue;
		}
		if ( n ==1)
		{
			error::logs(4, "u");
			student::student();
		}
	}
	error::logs(7);
	exit(EXIT_SUCCESS);
}
