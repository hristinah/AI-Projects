#include "Map.h"
#include "GA.h"
#include <iostream>
#include<utility>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <algorithm>    // std::random_shuffle
#include <vector>
#include <map>
#include <iterator>
Map::Map(int n1)
{
    n=n1;
    srand(time(0));
    cities = new city[n];
    for (int i=0;i<n;i++)
    {
      cities[i].x = (rand() % (n*1000)) / 1000.0;
      cities[i].y = (rand() % (n*1000)) / 1000.0;
    }
    float d;
    for (int i=0;i<n;i++)
    {
    for(int j=0;j<n;j++)
        {
         d=calcdist(i,j);
         cities[i].neighbours.insert(pair<int, float>(j,d));
         cities[j].neighbours.insert(pair<int, float>(i,d));
        }
    }
}

Map::~Map()
{
    for (int i=0;i<n;i++)
    {
        cities[i].neighbours.clear();
    }
    delete [] cities;
}

Map::Map(const Map& o)
{
    n=o.n;
    cities = new city[n];
    for (int i=0;i<n;i++)
    {
        cities[i].x=o.cities[i].x;
        cities[i].y=o.cities[i].y;
        cities[i].neighbours=o.cities[i].neighbours;
    }
}

Map& Map::operator=(const Map& o)
{
    if (this == &o) return *this;
     n=o.n;
    cities = new city[n];
    for (int i=0;i<n;i++)
    {
        cities[i].x=o.cities[i].x;
        cities[i].y=o.cities[i].y;
        cities[i].neighbours=o.cities[i].neighbours;
    }
    return *this;
}

void Map::print()
{
    cout<<n<<" cities:"<<endl;
    for (int i=0;i<n;i++)
    {
      cout<<"city "<<i+1<<" : "<<cities[i].x<<"  "<<cities[i].y<<endl;
      for (map<int,float>::iterator it=cities[i].neighbours.begin(); it!=cities[i].neighbours.end(); ++it)
      cout<< "To " << it->first+1 <<" : " << it->second << "    ";
      cout<<endl;
    }
}

float Map::calcdist(int a, int b)
{
    if(a<0||a>(n-1)||b<0||b>(n-1)) return 0;
    float x=cities[a].x-cities[b].x;
    float y=cities[a].y-cities[b].y;
    return (float)(x*x+y*y);
}

float Map::getdist(int a, int b)
{
    return cities[a].neighbours[b];
}

