#include <iostream>
#include <string.h>
int main()
{
	char src[40]="destination";
	char dst[100]="okay";
	memset(dst,'\0',sizeof(dst));
	std::cout<<dst;
	strcpy(dst,src);
	std::cout<<dst;
	return 0;
}

