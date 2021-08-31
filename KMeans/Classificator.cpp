#include "Classificator.h"
#include <vector>
#include <fstream>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <set>
#include <math.h>
#include <utility>
#include <iostream>

using namespace std;

double distance(Instance i1, Center i2)
{
    // Calculating distance
    return pow(i1.x - i2.x, 2) +  pow(i1.y - i2.y, 2) * 1.0;
}

Classificator::Classificator(const char* filename,int n1,int a,int t,int c)
{
   n = n1;
   maxcycles=c;
   after=a;
   int p=1;//what we multiply the coordinates by
   for (int i=0;i<after;i++)
   {
       p*=10;
   }
   centroid=new Center[n];
   mininst=LONG_MAX;
   maxinst=0;
   fstream fs (filename, std::fstream::in);
   double x;
   double y;
   int j=0;
    while (fs >> x)
    {
        x=x*p;
        if(x<mininst) mininst=x;
        if(x>maxinst) maxinst=x;

        if (fs >> y)
        {
            y=y*p;
            if(y<mininst) mininst=y;
            if(y>maxinst) maxinst=y;
            j++;
            Instance d;
            d.cluster=0;
            d.x=x;
            d.y=y;
            datavec.push_back(d);
        }
    }

    fs.close();


    //create centroids
    create_centroid(t);


     calculate_cluster();
     recalc_centr();

}

void Classificator::reset(int t)
{
    create_centroid(t);


     calculate_cluster();
     recalc_centr();
}

Classificator::~Classificator()
{
        datavec.clear();
        delete[] centroid;
}

void Classificator::print()
{
    int j=0;
       for (auto it = datavec.begin(); it != datavec.end(); it++)
        {
            cout << it->cluster<< " "<< it->x<< " "<< it->y<<endl ;
            j++;
        }
        cout<<"DATA SIZE :"<<j<<endl;
        cout<<"Min "<<mininst<<"   Max "<<maxinst<<endl;
        cout<<"Centroids "<<endl;
         for (int i=0;i<n;i++)
            {
              cout << centroid[i].cluster<< " "<< centroid[i].x<< " "<< centroid[i].y<<endl;
            }

}

long int Classificator::getmin()
{
    return mininst;
}

long int Classificator::getmax()
{
    return maxinst;
}

vector<Instance> Classificator::getdatavec()
{
    return datavec;
}

double Classificator::cost()
{

    double c=0;
    double dist;

    for (auto it = datavec.begin(); it != datavec.end(); it++)
        {
                    dist=distance(*it,centroid[it->cluster]);
                    //cout<<it->cluster<<"  "<<dist;

                   c+=dist;
                  // cout<<"   "<<c<<endl;
        }
    return c;
}

void Classificator::kmeans(int iteration)// calculates clusters and if changes are more than one, recalculate centroids. if iterations are more than max cycles,or changes are less than one - end
{
     int res=calculate_cluster();
     //cout<<iteration<<"    changes "<<res<<"    "<<cost()<<endl;
     if(res>0&&iteration<maxcycles)
     {
         recalc_centr();
         kmeans(++iteration);
     }

}

int Classificator::calculate_cluster()
{
     //calculate what clucter an example is from
    double mindistance;
    double dist;
    int indmin;
    int changes=0;
    for (auto it = datavec.begin(); it != datavec.end(); it++)
        {
            //cout << it->cluster<< " "<< it->x<< " "<< it->y<<endl ;
            mindistance=LLONG_MAX;
            indmin=0;
            for (int i=0;i<n;i++)
                {
                    dist=distance(*it,centroid[i]);
                    //cout<<i<<"  "<<dist<<endl;
                    if(dist<mindistance){mindistance=dist; indmin=i;}
                }
          /*      cout<<"Min is"<<endl;
            cout<<indmin<<"   "<<mindistance<<endl<<endl;*/
               if(it->cluster!=indmin) changes++;
                it->cluster=indmin;
        }
      return changes;
}


void Classificator::recalc_centr()
{
   pair<double,double> * cenxy=new pair<double,double>[n]; //sum of x of examples in cluster i ,sum of y
   int * counters=new int[n];  //count of examples in cluster i
   for (int i=0;i<n;i++)
        {
            cenxy[i].first=0;
            cenxy[i].second=0;
            counters[i]=0;
        }
   for (auto it = datavec.begin(); it != datavec.end(); it++)
        {
            cenxy[it->cluster].first+=it->x;
            cenxy[it->cluster].second+=it->y;
            counters[it->cluster]++;
        }

     /*for (int i=0;i<n;i++)
        {
            cout<<counters[i]<<"  "<<cenxy[i].first<<"  "<<cenxy[i].second<<endl;

        }*/

    //new centroids
         for (int i=0;i<n;i++)
            {
              centroid[i].x=(double)cenxy[i].first/counters[i];
              centroid[i].y=(double)cenxy[i].second/counters[i];
            }

    delete [] cenxy;
    delete [] counters;
}

void Classificator::create_centroid(int t)
{
    srand(time(0)+t);
    set <int> centind;  //what examples are already centroids
    int s=datavec.size();
    for (int i=0;i<n;i++)
        {
        int v=rand() % s;
        while(centind.count(v)!=0){v=rand() % s;}
        centind.insert(v);
        centroid[i].x=datavec[v].x;
        centroid[i].y=datavec[v].y;
        centroid[i].cluster=i;
        }
}

