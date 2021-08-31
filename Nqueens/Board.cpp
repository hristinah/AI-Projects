#include "Board.h"
#include <iostream>
#include<utility>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;
Board::Board(int n1)
{
   n=n1;
   rows= new pair<int, int>[n];
   col=new int [n] {};
   d1=new int [2*n-1] {};
   d2=new int [2*n-1]{};
   lastmoved=-1;
   // int a[5]={2,4,1,3,0}; //testing
   srand(time(0)); /*sets the seed for possition generation*/
   for (int i=0;i<n;i++)  /*giving random possitions to the queens */
   {
       int x=rand()%n; //in what column the queen on i row will be
       //x=a[i];
       rows[i]=make_pair(x,0);
       pair<int,int> p=getindd1d2(i,x);
       col[x]+=1;  /* add 1 to the cod/diags the queen is in */
       d1[p.first]+=1;
       d2[p.second]+=1;

   }
   getallconf();

}

Board::~Board()
{
delete [] rows;
delete [] col;
delete [] d1;
delete [] d2;
}


pair<int,int> Board::getindd1d2(int y,int x)
{
       int ymx=(y-x)+n-1;
       int ypx=y+x;
       pair<int,int> p=make_pair(ymx,ypx);
       return p;
}

int Board::calcqueenconf(int y,int x,bool in)
{
     pair<int,int> p=getindd1d2(y,x);
     int c=0;
     if(col[x]>0&&in==1) c+=col[x]-1;  /*excluding queen y*/
      else c+=col[x] ;  /*the queen isnt in the col yet*/
     if(d1[p.first]>0&&in==1) c+=d1[p.first]-1;
      else c+=d1[p.first];
     if(d2[p.second]>0&&in==1) c+=d2[p.second]-1;
       else c+=d2[p.second];
     return c;
}


void Board::print()
{
  for (int i=0;i<n;i++)
  {
      int x=rows[i].first;
      for (int j=0;j<n;j++)
      {
          if(j!=x) cout<<" - ";
          else cout<<" * ";
      }
    cout<<endl;
  }
 /* cout<<"col:"<<endl;
  int s=0;
  for (int i=0;i<n;i++)
  {
      s+=col[i];
      cout<<col[i]<<" ";
  }
   cout<<endl<<"Total is "<<s<<endl<<"d1 \\:"<<endl;
   s=0;
  for (int i=0;i<(2*n-1);i++)
  {
      s+=d1[i];
      cout<<d1[i]<<" ";
  }
    cout<<endl<<"Total is "<<s<<endl<<"d2 /:"<<endl;
     s=0;
  for (int i=0;i<(2*n-1);i++)
  {
      s+=d2[i];
      cout<<d2[i]<<" ";
  }
   cout<<endl<<"Total is "<<s<<endl;
*/
 /*  cout<<"Conflicts are "<<allconf<<endl;
   cout<<"Last moved was "<<lastmoved<<endl;
   cout<<"Worst queen in "<<worstqueen<<endl;
   */

}
void Board::minprint()
{
    for (int i=0;i<n;i++)
  {
      int x=rows[i].first;
    cout<<"( "<<x<<" , "<<i<<" ) ";
  }

}

void Board::getallconf()
{
  allconf=0;
  int maxconf=0;
  vector<int> qwithmax;
  for (int i=0;i<n;i++)
   {
     rows[i].second=calcqueenconf(i,rows[i].first,1);
     if(i!=lastmoved)  //no repeats of worst queen
     {
        if(rows[i].second==maxconf) qwithmax.push_back(i);
        else
            if(rows[i].second>maxconf)
              {
                 maxconf=rows[i].second;
                 qwithmax.clear();
                 qwithmax.push_back(i);
              }
    }
     allconf+=rows[i].second;
   }
   int j=rand()%qwithmax.size();
   worstqueen=qwithmax[j];
  /*for (int i=0;i<qwithmax.size();i++)
   {
       cout<<"  "<<qwithmax[i];
   }
   cout<<endl;
  */
   qwithmax.clear();
}

int Board::findminconf(int y)
{
    int conf;
    int x=rows[y].first;
    int minconf=3*n;
    vector<int> pmin;
    for (int i=0;i<n;i++)
   {
     if(i!=x)  //no repeats
     {
        conf=calcqueenconf(y,i,0);
        if(conf==minconf) pmin.push_back(i);
        else
            if(conf<minconf)
              {
                 minconf=conf;
                 pmin.clear();
                 pmin.push_back(i);
              }
      }
    }
   int j=rand()%pmin.size();
   int m=pmin[j];

   /*cout<<"Min conf are "<<minconf<<" and are in :"<<endl;

   for (int i=0;i<pmin.size();i++)
   {
       cout<<"  "<<pmin[i];
   }
   cout<<endl;
   */

   pmin.clear();
   return m;

}


void Board::moveq(int y)
{
    int x1=rows[y].first;
    int x2=findminconf(y); //best move possition
    rows[y].first=x2;
    pair<int,int> p1=getindd1d2(y,x1); //old diagonals
    pair<int,int> p2=getindd1d2(y,x2); //new diagonals
    col[x1]-=1;  /* update old diagonals and col */
    d1[p1.first]-=1;
    d2[p1.second]-=1;

    col[x2]+=1;  /* update new diagonals and col */
    d1[p2.first]+=1;
    d2[p2.second]+=1;
    lastmoved=y;
    getallconf(); /*recalculate conf */

}

bool Board::minConflictS()
{
    int i=0;
    int limit=3*n;
    while(i<limit&&allconf!=0)
    {
     moveq(worstqueen);
     i++;
    }
    if (allconf==0) return true;
    else return false;

}
