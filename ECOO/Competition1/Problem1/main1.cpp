
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>


void main()
{
	FILE *file = fopen("DATA11.txt", "r");
	int cost, students;
	float y1, y2, y3, y4;
	for (int i = 0; i < 10; i++)
	{
		fscanf(file, "%d\n%f %f %f %f\n%d\n", &cost, &y1, &y2, &y3, &y4, &students);

		if (y1 * students * 12 + y2 * students * 10 + y3 * students * 7 + y4 * students * 5 < cost)
		{
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
		}
	}
	char a[1];
	scanf(a);
}