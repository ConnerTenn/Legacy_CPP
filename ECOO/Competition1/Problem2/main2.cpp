//
//#define _CRT_SECURE_NO_WARNINGS
//
////#include <stdio.h>
//#include <iostream>
//#include <string>
//#include <fstream>
//
//
//void main()
//{
//	//FILE *file = fopen("DATA21.txt", "r");
//	
//	//fscanf(file, "%d\n%f %f %f %f\n%d\n", &cost, &y1, &y2, &y3, &y4, &students);
//	
//	std::ifstream file;
//	file.open("DATA22.txt");
//	
//	for (int t = 0; t < 10; t++)
//	{
//		int p, f, g;
//
//		int P[100] = {};
//		int F[100] = {};
//		int G[100] = {};
//		int S[100] = {};
//		std::string N[100];
//
//		int num;
//		//fscanf(file, "%d", &num);
//		file >> num; file.ignore();
//
//		for (int c = -1; c < num;)
//		{
//			std::string name;
//			//fscanf(file, "%s", &(name.c_str()));
//			std::getline(file, name);
//
//			if (name[0] == 'J')
//			{
//				//judge
//				//fscanf(file, "%d %d %d", p, f, g);
//				//file >> p >> f >> g; file.ignore();
//				p = std::stoi(std::string(1, name[2]));
//				f = std::stoi(std::string(1, name[4]));
//				g = std::stoi(std::string(1, name[6]));
//				P[c] += p;
//				F[c] += f;
//				G[c] += g;
//				S[c] += p + f + g;
//			}
//			else if (name[0] == '*')
//			{
//				c = num;
//			}
//			else
//			{
//				c++;
//				N[c] = name;
//			}
//		}
//
//		int maxi = -1;
//		int max = -1;
//		for (int i = 0; i < num; i++)
//		{
//			if (S[i] > max)
//			{
//				maxi = i;
//				max = S[i];
//			}
//			else if (S[i] == max)
//			{
//				if (G[i] > G[maxi])
//				{
//					maxi = i;
//					max = S[i];
//				}
//				else if (G[i] == G[maxi] && F[i] > F[maxi])
//				{
//					maxi = i;
//					max = S[i];
//				}
//				else if (F[i] == F[maxi] && P[i] > P[maxi])
//				{
//					maxi = i;
//					max = S[i];
//				}
//			}
//		}
//
//		std::cout << N[maxi] << "\n";
//	}
//
//	std::string out;
//	std::getline(std::cin, out);
//}