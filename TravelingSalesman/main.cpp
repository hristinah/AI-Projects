#include <iostream>
#include "Map.h"
#include "GA.h"
#include<utility>
#include <vector>
using namespace std;

int main()
{
    int n=0;
    cout<<"How many cities? ";
    cin>>n;
    Map m(n);
    GA g(30,5,&m);
    int prints=0;
    pair <float,vector<int> > best=g.genalg(prints);
     cout<<endl<<"Length : "<<best.first<< "  for ";
                       for(auto i = best.second.begin(); i !=  best.second.end(); ++i)
                                                cout << *i << " ";
         cout<<endl;
                         prints++;
     int i=40;
     while (prints<4) //starts the algorithm again with a bigger population
     {
       GA g(i,5,&m);
         pair <float,vector<int> > b1=g.genalg(prints);
         cout<<endl<<"Length : "<<b1.first<< "  for ";
                       for(auto i = b1.second.begin(); i !=  b1.second.end(); ++i)
                                                cout << *i << " ";
              cout<<endl;
                         prints++;
         if(best.first>b1.first) best=b1;
      i=i+10;
     }

      cout<<endl<<"Best Length : "<<best.first<< "  for ";
                       for(auto i = best.second.begin(); i !=  best.second.end(); ++i)
                                                cout << *i << " ";
     return 0;
}
 //best population size=30?
