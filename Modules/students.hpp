#include <iostream>
#ifndef students
#define students

namespace student
{

void student();
int how_many();	//liczba pytañ do zadania
void get_name();
std::string difficulty();//poziom trudnoœci
void help();
int ask(std::string, int, int);
	bool reply(int*, int, int);
std::string mark(int, int);
void load_grade(int*);
void save(std::string, int, int, std::string);
bool next();
}
#endif
