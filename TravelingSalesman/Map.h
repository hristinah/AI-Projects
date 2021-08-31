#ifndef MAP_H
#define MAP_H
#include<utility>
#include <vector>
#include <map>
#include "GA.h"
using namespace std;

struct city{
float x;
float y;
map<int,float> neighbours;  //the distance to a town with index=key from our current town
};


class Map
{
    public:
        Map(int n=1);
        ~Map();
        Map(const Map& other);
        Map& operator=(const Map& other);
        float getdist(int a, int b);
        void print();
    private:
        int n;
        city * cities;
        float calcdist(int a, int b);
        friend class GA;
};

#endif // MAP_H
