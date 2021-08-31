#include "Node.h"
#include "Tile.h"
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

Node::Node(int n1, int ind0, int* a) {
	n = n1;
	table = new Tile * [n];
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		table[i] = new Tile[n];
		for (int j = 0; j < n; j++)
		{
			table[i][j] = Tile(j, i, a[k], n, ind0);
			if (a[k] == 0)
			{
				y0 = i;
				x0 = j;
			}
			k++;
		}
	}


}

Node::~Node()
{
	for (int i = 0; i < n; i++)
	{
		delete[]table[i];
	}
	delete[]table;

}

Node::Node(const Node& o)
{
	n = o.n;
	table = new Tile * [n];
	y0 = o.y0;
	x0 = o.x0;
	for (int i = 0; i < n; i++)
	{
		table[i] = new Tile[n];
		for (int j = 0; j < n; j++)
		{
			table[i][j] = o.table[i][j];
		}
	}

}

Node& Node::operator=(const Node& o)
{
	if (this == &o) return *this;
	for (int i = 0; i < n; i++)
	{
		delete[]table[i];
	}
	delete[]table;
	n = o.n;
	table = new Tile * [n];
	y0 = o.y0;
	x0 = o.x0;
	for (int i = 0; i < n; i++)
	{
		table[i] = new Tile[n];
		for (int j = 0; j < n; j++)
		{
			table[i][j] = o.table[i][j];
		}
	}

	return *this;
}

void Node::Print()
{
	cout << "Your table is " << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << table[i][j].get_value() << " ";
		}
		cout << endl;
	}

	/* for(int i=0;i<n;i++)
	 {
		 for(int j=0;j<n;j++)
		 {
			 table[i][j].Print();
		 }
		cout<<endl;
	 }
	 */


}

int Node::get_whole_Mh()
{
	int mh = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			mh += table[i][j].get_mh();
		}
	}
	return mh;
}

bool Node::Move_Empty_Up()
{
	if (y0 == 0) return false; //not able to move
	int x1 = x0;
	int y1 = y0 - 1;
	table[y0][x0].Swap_Values(table[y1][x1]);
	y0 = y1;
	return true; //moved successfully

}

bool Node::Move_Empty_Down()
{
	if (y0 == (n - 1)) return false; //not able to move
	int x1 = x0;
	int y1 = y0 + 1;
	table[y0][x0].Swap_Values(table[y1][x1]);
	y0 = y1;
	return true; //moved successfully
}
bool Node::Move_Empty_Left()
{
	if (x0 == 0) return false; //not able to move
	int x1 = x0 - 1;
	int y1 = y0;
	table[y0][x0].Swap_Values(table[y1][x1]);
	x0 = x1;
	return true; //moved successfully
}

bool Node::Move_Empty_Right()
{
	if (x0 == (n - 1)) return false; //not able to move
	int x1 = x0 + 1;
	int y1 = y0;
	table[y0][x0].Swap_Values(table[y1][x1]);
	x0 = x1;
	return true; //moved successfully
}

void Node::IDA()
{
	vector<char> path;
	path.push_back('o'); //beggining of the path
	int cost = 0;
	int i = get_whole_Mh();
	if (i == 0)   // if we have an already solved puzzle
	{
		cout << "Solution cost is 0" << endl;
		return;
	}
	while (i > 0 && i < (n * n * 10))
	{
		cost = 0;
		i = IDA_Search(i, cost, path);
	}
	if (i == 0)
	{
		cout << "Solution cost is " << cost << endl;
		auto it = path.begin();
		it++; //skip the o
		while (it != path.end())
		{
			if (*it == 'u')  //write the direction of the swith as the direction of the slide
			{
				cout << "down" << endl;
			}
			else
				if (*it == 'd')
				{
					cout << "up" << endl;
				}
				else
					if (*it == 'l')
					{
						cout << "right" << endl;
					}
					else
						if (*it == 'r')
						{
							cout << "left" << endl;
						}

			it++;
		}
	}
	else
	{
		cout << "cannot solve it" << endl;
	}
	return;
}


int Node::IDA_Search(int i, int& cost, vector<char>& path)
{
	int mh = get_whole_Mh();
	if (mh == 0) return 0; //solution reached
	int estimatedcost = cost + mh;
	if (estimatedcost > i) return estimatedcost; //cant go farther this iteration



	int estimatedmin = std::numeric_limits<int>::max();
	bool b; //checking if move is succesfull
	int res; //result of deepening

	if (path.back() != 'd') //attempting an up movement if the last move wasnt down
	{
		b = Move_Empty_Up();
		if (b == true)
		{
			path.push_back('u');
			cost++;
			res = IDA_Search(i, cost, path);
			if (res == 0) { return 0; }
			else   // return to previous state
			{
				Move_Empty_Down();
				path.pop_back();
				cost--;
				if (res < estimatedmin)
				{
					estimatedmin = res;
				}
			}
		}
	}

	if (path.back() != 'u') //attempting a down movement if the last move wasnt up
	{
		b = Move_Empty_Down();
		if (b == true)
		{
			path.push_back('d');
			cost++;
			res = IDA_Search(i, cost, path);
			if (res == 0) { return 0; }
			else  // return to previous state
			{
				Move_Empty_Up();
				path.pop_back();
				cost--;
				if (res < estimatedmin)
				{
					estimatedmin = res;
				}
			}
		}
	}

	if (path.back() != 'r') //attempting a left movement if the last move wasnt right
	{
		b = Move_Empty_Left();
		if (b == true)
		{
			path.push_back('l');
			cost++;
			res = IDA_Search(i, cost, path);
			if (res == 0) { return 0; }
			else  // return to previous state
			{
				Move_Empty_Right();
				path.pop_back();
				cost--;
				if (res < estimatedmin)
				{
					estimatedmin = res;
				}
			}
		}
	}

	if (path.back() != 'l') //attempting a right movement if the last move wasnt left
	{
		b = Move_Empty_Right();
		if (b == true)
		{
			path.push_back('r');
			cost++;
			res = IDA_Search(i, cost, path);
			if (res == 0) { return 0; }
			else  // return to previous state
			{
				Move_Empty_Left();
				path.pop_back();
				cost--;
				if (res < estimatedmin)
				{
					estimatedmin = res;
				}
			}
		}
	}

	return estimatedmin;
}
