#include <cstdio>
#include <cstdlib>
int main()
{
	int a=154;
	char b[5]={ };
	char* c;
	c=b;
	itoa(a,c,10);
	while ( *c>0 )
	{
		printf("%c",*c);
		c++;
	}
}
