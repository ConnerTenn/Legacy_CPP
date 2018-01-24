#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <iostream>
using namespace std;
int charToCode(char l, char r)
{
	if (l == 'G')
	{
		if (r == 'W')
			return 2;
		else
			return 3;
	}
	else if (r == 'G')
		return 1;
	else
		return 0;
}
int main()
{
	ifstream f;
	f.open("DATA11.txt");
	int t = 10;
	while (t--)
	{
		int n, m;
		f >> n >> m;
		string comb("    "); //0: WW 1: WG 2: GW 3: GG
		for (int i = 0; i < 4; ++i)
		{
			string cmb; char res;
			f >> cmb >> res;
			comb[charToCode(cmb[0], cmb[1])] = res;
			/*
			if (cmb[0] = 'G')
			{
				if (cmb[1] == 'G')
					comb[3] = res;
				else
					comb[2] = res;
			}
			else if (cmb[1] = 'G')
				comb[1] = res;
			else
				comb[0] = res;
				*/
		}
		string cur, nxt, dummy;
		nxt.resize(n);
		f >> cur;
		f >> dummy;
		m--;
		while (m--)
		{
			nxt[0] = comb[charToCode(cur[n - 1], cur[1])];
			nxt[n - 1] = comb[charToCode(cur[n - 2], cur[0])];
			for (int i = 1; i < n - 1; ++i)
			{
				nxt[i] = comb[charToCode(cur[i - 1], cur[i + 1])];
			}
			cur = nxt;
		}
		cout << cur << "\n";
	}
	std::string out;
	std::getline(std::cin, out);
}
