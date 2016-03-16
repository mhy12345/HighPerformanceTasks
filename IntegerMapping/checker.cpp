#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

int main()
{
		while (true)
		{
				system("./data");
				system("./skiplist >a.txt");
				if (system("./paralleltreap >b.txt"))break;
				if (system("diff a.txt b.txt"))break;
				system("cat a.txt");
		}
}
