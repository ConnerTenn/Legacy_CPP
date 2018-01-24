
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <queue>


bool state[1000][1000];
std::string object[1000];

struct Pos
{
	int X;
	int Y;
	int Type; //0 else  //1 door
};

void Init()
{
	for (int y = 0; y < 1000; y++)
	{
		object[y] = "";
		for (int x = 0; x < 1000; x++)
		{
			state[y][x] = 0;
		}
	}
}

/*void Floodfill()
{
	for (int )
}*/

bool GetToPos(Pos target, int keys, int n)
{
	if (target.X >= 0 && target.X < n && target.Y >= 0 && target.Y < n)
	{
		if (object[target.Y][target.X] == 'S') { return true; }
		if (object[target.Y][target.X] == '.') { return true; }
		if (object[target.Y][target.X] == 'T') { return true; }
		if (object[target.Y][target.X] == 'K') { return true; }
		if (object[target.Y][target.X] >= '0' && object[target.Y][target.X] <= '9')
		{
			if (object[target.Y][target.X] - '0' <= keys)
			{
				return true;
			}
		}
	}
	return false;
}

bool OnlyDoors(std::queue<Pos> Q)
{
	while (Q.size())
	{
		if (Q.front().Type != 1) { return false; }
		Q.pop();
	}
	return true;
}

void main()
{
	std::ifstream file;
	file.open("DATA22.txt");
	int t = 10;
	while (t--)
	{
		std::string nstr;
		std::getline(file, nstr);
		int n = std::stoi(nstr);

		for (int i = 0; i < n; i++)
		{
			std::getline(file, object[i]);
		}

		Pos Start;
		for (int y = 0; y < n; y++)
		{
			for (int x = 0; x < n; x++)
			{
				if (object[y][x] == 'S')
				{
					Start = { x, y , 0};
					x = n; y = n;
					//state[Start.Y][Start.X] = 1;
				}
			}
		}
		
		std::queue<Pos> Q; 
		/*for (int y = 0; y < n; y++)
		{
			for (int x = 0; x < n; x++)
			{

			}
		}*/
		Q.push(Start);
		state[Start.Y][Start.X] = 1;

		int keys = 0;
		int treasure = 0;

		while (Q.size() > 0)
		{
			Pos current = Q.front();
			Q.pop();

			if (GetToPos(current, keys, n))
			{
				//top
				if (GetToPos({ current.X, current.Y - 1, 0 }, keys, n) && state[current.Y - 1][current.X] == 0)
				{
					if (object[current.Y - 1][current.X] >= '0' && object[current.Y - 1][current.X] <= '9') { Q.push({ current.X, current.Y - 1, 1 }); }//keys -= object[current.Y - 1][current.X] - '0'; }
					else { Q.push({ current.X, current.Y - 1, 0 }); }
					state[current.Y - 1][current.X] = 1;
					if (object[current.Y - 1][current.X] == 'K') { keys++; }
					if (object[current.Y - 1][current.X] == 'T') { treasure++; }
				}
				//bottom
				if (GetToPos({ current.X, current.Y + 1, 0 }, keys, n) && state[current.Y + 1][current.X] == 0)
				{
					if (object[current.Y + 1][current.X] >= '0' && object[current.Y + 1][current.X] <= '9') { Q.push({ current.X, current.Y + 1, 1 }); }//keys -= object[current.Y - 1][current.X] - '0'; }
					else { Q.push({ current.X, current.Y + 1, 0 }); }
					state[current.Y + 1][current.X] = 1;
					if (object[current.Y + 1][current.X] == 'K') { keys++; }
					if (object[current.Y + 1][current.X] == 'T') { treasure++; }
				}
				//left
				if (GetToPos({ current.X - 1, current.Y, 0 }, keys, n) && state[current.Y][current.X - 1] == 0)
				{
					if (object[current.Y][current.X - 1] >= '0' && object[current.Y][current.X - 1] <= '9') { Q.push({ current.X - 1, current.Y, 1 }); }//keys -= object[current.Y - 1][current.X] - '0'; }
					else { Q.push({ current.X - 1, current.Y, 0 }); }
					state[current.Y][current.X - 1] = 1;
					if (object[current.Y][current.X - 1] == 'K') { keys++; }
					if (object[current.Y][current.X - 1] == 'T') { treasure++; }
				}
				//right
				if (GetToPos({ current.X + 1, current.Y, 0 }, keys, n) && state[current.Y][current.X + 1] == 0)
				{
					if (object[current.Y][current.X + 1] >= '0' && object[current.Y][current.X + 1] <= '9') { Q.push({ current.X + 1, current.Y, 1 }); }//keys -= object[current.Y - 1][current.X] - '0'; }
					else { Q.push({ current.X + 1, current.Y, 0 }); }
					state[current.Y][current.X + 1] = 1;
					if (object[current.Y][current.X + 1] == 'K') { keys++; }
					if (object[current.Y][current.X + 1] == 'T') { treasure++; }
				}
			}
			else if (current.Type == 1 && !OnlyDoors(Q))
			{
				Q.push(current);
			}
			

			/*if (GetToPos(current))//if not at door
			{
				//left
				if (current.X - 1 >= 0 && object[current.Y][current.X - 1] != '#')
				{
					if (object[current.Y][current.X - 1] == 'K') { keys++; }
					if (object[current.Y][current.X - 1] == 'T') { treasure++; }
					if (object[current.Y][current.X - 1] == '.')
					{
						if (state[current.Y][current.X - 1] == 0)
						{
							Q.push({ current.X - 1, current.Y });
						}
					}//visit empty
					if (object[current.Y][current.X - 1] >= '0' && object[current.Y][current.X - 1] <= '9')
					{
						if (object[current.Y][current.X - 1] - '0' <= keys)
						{
							Q.push({ current.X - 1, current.Y });//visit door
						}
					}
				}
				//right
				if (current.X + 1 < n && object[current.Y][current.X + 1] != '#')
				{
					if (object[current.Y][current.X + 1] == 'K') { keys++; }
					if (object[current.Y][current.X + 1] == 'T') { treasure++; }
					if (object[current.Y][current.X + 1] == '.') { Q.push({ current.X + 1, current.Y }); }//visit empty
					if (object[current.Y][current.X + 1] >= '0' && object[current.Y][current.X + 1] <= '9')
					{
						if (object[current.Y][current.X + 1] - '0' <= keys)
						{
							Q.push({ current.X + 1, current.Y });//visit door
							again = true;
						}
					}
				}
				//top
				if (current.Y - 1 >= 0 && object[current.Y - 1][current.X] != '#')
				{
					if (object[current.Y - 1][current.X] == 'K') { keys++; }
					if (object[current.Y - 1][current.X] == 'T') { treasure++; }
					if (object[current.Y - 1][current.X] == '.') { Q.push({ current.X, current.Y - 1 }); }//visit empty
					if (object[current.Y - 1][current.X] >= '0' && object[current.Y - 1][current.X] <= '9')
					{
						if (object[current.Y - 1][current.X] - '0' <= keys)
						{
							Q.push({ current.X, current.Y - 1 });//visit door
							again = true;
						}
					}
				}
				//bottom
				if (current.Y + 1 < n && object[current.Y + 1][current.X] != '#')
				{
					if (object[current.Y + 1][current.X] == 'K') { keys++; }
					if (object[current.Y + 1][current.X] == 'T') { treasure++; }
					if (object[current.Y + 1][current.X] == '.') { Q.push({ current.X, current.Y - 1 }); }//visit empty
					if (object[current.Y + 1][current.X] >= '0' && object[current.Y + 1][current.X] <= '9')
					{
						if (object[current.Y + 1][current.X] - '0' <= keys)
						{
							Q.push({ current.X, current.Y + 1 });//visit door
						}
					}
				}
			}*/
		}

		std::cout << treasure << "\n";

		/*for (int y = 0; y < n; y++)
		{
			for (int x = 0; x < n; x++)
			{
				//std::cout << (state[y][x] ? (object[y][x] == 'T' ? 'T' : '='): '.');
				if (state[y][x])
				{
					if (object[y][x] == 'T') { std::cout << "T"; }
					else if (object[y][x] == 'K') { std::cout << "K"; }
					else { std::cout << "="; }
				}
				else { std::cout << "."; }
			}
			std::cout << "\n";
		}*/

		Init();
	}

	std::string out;
	std::getline(std::cin, out);
}
