#include <iostream>
#include <windows.h>
#include <wchar.h>
using namespace std;
int main()
{
	CONSOLE_FONT_INFOEX font;
	font.cbSize=sizeof (font);
	font.nFont=0;
	font.dwFontSize.X=7;
	font.dwFontSize.Y=12;
	font.FontFamily=FF_DONTCARE;
	font.FontWeight=FW_NORMAL;
	wcscpy(font.FaceName, L"Comic Sans");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &font);
	cout << "ghghh";
	system("pause");
}
