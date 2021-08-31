#include "Tile.h"
#include <stdlib.h>     /* abs */
#include <iostream>
using namespace std;


Tile::Tile(int x1,int y1,int value1,int n,int ind0) {
	x = x1;
	y = y1;
	value = value1;
	
    int v = value;
	int gx;
	int gy;
	if (value != 0) { // empty tile
		if (ind0 > value) { v--; }
		gy = v / n;
		gx = v % n;
	} else { // number tile
		ind0--;
		gy = ind0 / n;
		gx = ind0 % n;
	}

	goal_x = gx;
	goal_y = gy;

	Recalculate_Mh_Dist();
}


Tile::Tile(const Tile& o) {
	x = o.x;
	y = o.y;
	value = o.value;
	goal_x = o.goal_x;
	goal_y = o.goal_y;
	Recalculate_Mh_Dist();
}

Tile& Tile::operator=(const Tile& o) {
	if (this == &o) return *this;

	x = o.x;
	y = o.y;
	value = o.value;
	goal_x = o.goal_x;
	goal_y = o.goal_y;
	Recalculate_Mh_Dist();
	return *this;
}

void Tile::Swap_Values(Tile& o) {
	swap(value, o.value);
	swap(goal_x, o.goal_x);
	swap(goal_y, o.goal_y);
	Recalculate_Mh_Dist();
	o.Recalculate_Mh_Dist();

}

void Tile::Print() {
	cout << x << " " << y << endl;
	cout << value << endl;
	cout << mh_dist << endl;
	cout << goal_x << " " << goal_y << endl;
}

int Tile::get_value() {
 return value;
}

int Tile::get_mh() {
    return mh_dist;
}

void Tile::Recalculate_Mh_Dist() {
	mh_dist = 0;
	mh_dist += abs(x - goal_x);
	mh_dist += abs(y - goal_y);
}


