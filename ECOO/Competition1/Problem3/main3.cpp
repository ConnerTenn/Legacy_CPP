
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
int main()
{
	FILE *file = fopen("DATA32.txt", "r");
	for (int i = 0; i < 10; ++i)
	{
		int m[10000] = { 0 };
		int s[10000] = { 0 };
		int n;
		fscanf(file, "%d\n", &n);
		for (int a = 0; a < n; ++a)
			fscanf(file, "%d", &m[a]);

		for (int c = 0; c < n; ++c)
		{
			double sr = -100000.0;
			for (int a = c + 1; a < n; ++a)
			{
				double cs = (double)(m[a] - m[c]) / (double)(a - c);
				if (cs > sr)
				{
					s[c]++;
					sr = cs;
				}
			}
			double sl = -100000.0;
			for (int a = c - 1; a >= 0; --a)
			{
				double cs = (double)(m[a] - m[c]) / (double)(c - a);
				if (cs > sl)
				{
					s[c]++;
					sl = cs;
				}
			}
		}
		int b = 0, bi = 0;
		for (int a = 0; a < n; ++a)
		{
			if (s[a] > b)
			{
				bi = a;
				b = s[a];
			}
		}
		printf("%d\n", bi+1);
	}
	char a[1];
	scanf(a);
	return 0;
}