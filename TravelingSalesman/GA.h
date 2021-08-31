#ifndef GA_H
#define GA_H
#include "Map.h"
#include <vector>
#include<utility>
using namespace std;

class Map;

class GA
{
    public:
        GA(int pop,int ps, Map* m1);
        ~GA();
        void print();
        pair <float,vector<int> > genalg(int & prints);
        pair<vector <int>,vector <int> > children(int a,int b); //generates children 2 with 2 point crossover from elements of the population with index a and b
    private:
        int t; //addition to the seed
        int popsize;
        int psize; //num of members from the old generation we want to keep/num of children that mutate
        int n;
        Map* m;
        pair <float,vector<int> > bestnow;
        vector< pair <float,vector<int> > > population;  //float = fittnes where fitness=num of cities/(sum of ( lenght of the paths between the cities we take)^2
        pair<int,int> genindex();
        vector<pair <float,vector<int> > > merges(vector<pair <float,vector<int> > >left, vector<pair <float,vector<int> > > right);


};

#endif // GA_H
