#include "GA.h"
#include "Map.h"
#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>
#include <set>
#include<utility>
#include <ctime>        // std::time
#include <cstdlib>
#include <math.h>
#include <random>
using namespace std;

bool sortdecresingord(const pair<float,vector<int> > &a,
              const pair<float,vector<int> > &b)
{
    return (a.first > b.first);
}

GA::GA(int pop,int ps,Map* m1)
{
    m=m1; //points to our travel map
    popsize=pop;
    psize=ps;
    n=m->n;
    vector<int> base;
    for (int i=0; i<n; ++i) base.push_back(i);

    for (int i=0; i<popsize; ++i)
    {
       float sum=0;
       random_shuffle (base.begin(), base.end() );
        for(int j=0;j<(n-1);j++)
        {
            sum+=m->getdist(base[j],base[j+1]);
        }
       population.push_back(make_pair(n/sum,base));
    }
    sort(population.begin(), population.end(),sortdecresingord);
bestnow=population[0];

}

GA::~GA()
{
    for (int i=0;i<popsize;i++)
    {
        population[i].second.clear();
    }
    population.clear();
}

 pair<vector <int>,vector <int> > GA::children(int a,int b)
 {
    pair<int,int> i=genindex();
    vector<int> c1(n,-1),c2(n,-1);
    set<int> c1set, c2set;
    for(int j=i.first;j<i.second;j++) //we copy the part between the indexes
    {
        c1[j]=population[a].second[j];
         c1set.insert(population[a].second[j]);
        c2[j]=population[b].second[j];
         c2set.insert(population[b].second[j]);
    }
    int c1index=i.second;
    int c2index=i.second;

    for(int j=i.second;j<n;j++) //put the rest to the right from the other parrent, without redundancy
    {
        if(c1set.count(population[b].second[j])==0)
        {
          c1[c1index]=population[b].second[j];
          c1set.insert(population[b].second[j]);
          c1index++;
        }

        if(c2set.count(population[a].second[j])==0)
        {
          c2[c2index]=population[a].second[j];
          c2set.insert(population[a].second[j]);
          c2index++;
        }

    }

    for(int j=0;j<i.second;j++) //put the rest to the left from the other parrent, without redundancy
    {
        if(c1index==n) c1index=0;
        if(c2index==n) c2index=0;
        if(c1set.count(population[b].second[j])==0)
        {
          c1[c1index]=population[b].second[j];
          c1set.insert(population[b].second[j]);
          c1index++;
        }

        if(c2set.count(population[a].second[j])==0)
        {
          c2[c2index]=population[a].second[j];
          c2set.insert(population[a].second[j]);
          c2index++;
        }
    }

   /*     cout<<endl;
        for(auto it =  c1.begin(); it !=  c1.end(); ++it)
        cout << *it << " ";
        cout<<endl;
        for(auto it =  c2.begin(); it !=  c2.end(); ++it)
        cout << *it << " ";
        cout<<endl;*/
       return make_pair(c1,c2) ;
 }

pair<int,int> GA::genindex()
{
     int i1=rand()%n;
     int i2=rand()%n;
     while(i1==i2||(n>3&&abs(i1-i2)==1)||(n>3&&abs(i1-i2)==(n-1))){i2=rand()%n;}
     if(i1>i2) swap(i1,i2);
    /* cout<<endl<< i1<<" "<<i2<<endl;*/
     return make_pair(i1,i2);
}

pair <float,vector<int> > GA::genalg(int & prints)
{
   vector<float> p; //probability vector
   for (int j=0;j<popsize;j++)
   {
       p.push_back(population[j].first);
   }
   default_random_engine eng{static_cast<long unsigned int>(time(0))};
   discrete_distribution<int> distr (p.begin(),p.end());

  vector< pair <float,vector<int> > > newpop;

  int noimprovement=0; //num of cycles without improvement
  int cycles=0;
       while(noimprovement<10&&cycles<5*popsize) //stops if there is no improvement for a few cycles or we have cycled enough on this population
       {
             int mutations=0;
                              for(int i=0;i<popsize/2;i++)
                              {
                                int ind1 = distr(eng); //choose parents1
                                int ind2 = distr(eng);
                                while(ind1==ind2) {ind2 = distr(eng);}
                                pair<vector <int>,vector <int> >c=children(ind1,ind2);
                                if(mutations<psize)
                                {
                                    int a=rand() % n;
                                    int b=rand() % n;
                                    swap(c.first[a],c.first[b]);
                                    mutations++;
                                    if(mutations<psize)
                                     {
                                        a=rand() % n;
                                        b=rand() % n;
                                        swap(c.second[a],c.second[b]);
                                        mutations++;
                                     }
                                }
                                float sum1=0,sum2=0;
                                         for(int j=0;j<(n-1);j++)
                                           {
                                             sum1+=m->getdist(c.first[j],c.first[j+1]);
                                             sum2+=m->getdist(c.second[j],c.second[j+1]);
                                           }
                                        newpop.push_back(make_pair(n/sum1,c.first));
                                        newpop.push_back(make_pair(n/sum2,c.second));
                              }

                              sort(newpop.begin(), newpop.end(),sortdecresingord);

                              if(newpop[0].first>bestnow.first){bestnow=newpop[0]; noimprovement=0;} //do we have better children
                                  else {noimprovement++;}

                             /* cout<<endl<<"Children"<<endl;
                              for (int j=0;j<popsize;j++)
                                {
                                    cout<<endl<<"n/Lenght ="<<newpop[j].first<<" for  : ";
                                    for(auto i =  newpop[j].second.begin(); i !=  newpop[j].second.end(); ++i)
                                    cout << *i << " ";
                                }
                                */
                 vector< pair <float,vector<int> > > pop=merges(population,newpop);
                                population.clear();
                                population=pop;
                                newpop.clear();


              /* cout<<endl<<"New pop"<<endl;
                              for (int j=0;j<population.size();j++)
                                {
                                    cout<<endl<<"n/Lenght ="<<population[j].first<<" for  : ";
                                    for(auto i =  population[j].second.begin(); i !=  population[j].second.end(); ++i)
                                    cout << *i << " ";
                                }*/
          cycles++;
                      if(cycles==10&&prints<=1) //print 10th cycle
                        {
                          float sum=0;
                          for(int j=0;j<(n-1);j++)
                    {
                        sum+=sqrt(m->getdist(bestnow.second[j],bestnow.second[j+1]));
                    }
                       cout<<endl<<"Length : "<<sum<< "  for ";
                       for(auto i = bestnow.second.begin(); i !=  bestnow.second.end(); ++i)
                                                cout << *i << " ";
                         prints++;
                         cout<<endl;

                       }
       }
       float sum=0;
                          for(int j=0;j<(n-1);j++)
                    {
                        sum+=sqrt(m->getdist(bestnow.second[j],bestnow.second[j+1]));
                    }
    return make_pair(sum,bestnow.second);
}

void GA::print()
{
  for (int j=0;j<popsize;j++)
    {
        cout<<endl<<"n/Lenght ="<<population[j].first<<" for  : ";
        for(auto i =  population[j].second.begin(); i !=  population[j].second.end(); ++i)
        cout << *i << " ";
    }
    /*cout<<" Best is "<<bestnow.first<<" ";
    for(auto it =  bestnow.second.begin(); it !=  bestnow.second.end(); ++it)
        cout << *it << " ";
        cout<<endl;*/
}

vector<pair <float,vector<int> > > GA:: merges(vector<pair <float,vector<int> > >left, vector<pair <float,vector<int> > >right) {
	size_t ileft = 0, iright = 0;
	size_t rsize=0;
	vector<pair <float,vector<int> > >results;
	while (ileft < left.size() && iright < right.size()&& rsize<(popsize-psize)) //fill with the best from both
	    if (left[ileft].first > right[iright].first)
	        { results.push_back(left[ileft++]); rsize++;}
	    else
	        { results.push_back(right[iright++]); rsize++;}
	if(ileft<psize)
    {
        while(rsize<popsize)
        {
            results.push_back(left[ileft++]); rsize++;
        }
    }

    if(iright<psize)
    {
        while(rsize<popsize)
        {
            results.push_back(right[iright++]); rsize++;
        }
    }

    if(rsize<popsize)
        while (ileft < left.size() && iright < right.size()&& rsize<popsize) //fill with the best from both
	    if (left[ileft].first > right[iright].first)
	        { results.push_back(left[ileft++]); rsize++;}
	    else
	        { results.push_back(right[iright++]); rsize++;}
	return results;
}
