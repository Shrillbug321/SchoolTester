#include <iostream>
#include <fstream>
#ifndef program
#define program

void clear();
void pause();
int main_menu();
	void draw(int, char);
	void draw(int, char, std:: string);
bool logon(int);
	void encryption();
	void back_up(std::string);
	std::string decryption( std::ifstream& );
void to_lower(std::string&, std::string&);
void to_lower(std::string&);
int are_you_sure(int=0);
int count(std::string);

#endif
