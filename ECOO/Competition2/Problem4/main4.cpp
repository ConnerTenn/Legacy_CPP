#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	fstream file;
	file.open("DATA41.txt");
	int t = 10;
	while (t--)
	{
		int n;
		file >> n;
		if (n < 3)
			cout << 1 << endl;
		else
		{
			unsigned long long int p = 1;
			for (int i = 2; i <= n; ++i)
				p = (i - 2) * p + 1;
			cout << p % 1000000007 << endl;
		}
	}
	int a;
	cin >> a;
	return 0;
}
