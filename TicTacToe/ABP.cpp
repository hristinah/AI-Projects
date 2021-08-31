#include "ABP.h"
#include "Field.h"
#include <algorithm>
#include <iostream>

using namespace std;

ABP::ABP(Field &f)
{
    //ctor
    playtest=f;
}

ABP::~ABP()
{
    //dtor
    playtest.~Field();

}

void ABP::print()
{

    playtest.print();
}

int ABP::maxnode(int depth,int alpha,int beta)
{
   //test if we are in a winning state or a leaf
   if(depth==1) return playtest.victory();
   int v=playtest.victory();
   if(v!=0)return depth*v;

   //continue down the tree
   int bestVal=-10;

   for (int i=0;i<9;i++)
   {
      if(playtest.addind(i,'X')) //we can add in that possition
      {
      int value=minnode(depth-1,alpha,beta); //check that childtree
      playtest.rem(i); //clear
      bestVal=max(bestVal, value);
      alpha = max( alpha, bestVal);
      if (beta <= alpha)
        return bestVal;
      }
   }
   return bestVal;
}

int ABP::minnode(int depth,int alpha,int beta)
{
   //test if we are in a winning state or a leaf
   if(depth==1) return playtest.victory();
   int v=playtest.victory();
   if(v!=0) return depth*v;

   //continue down the tree
   int bestVal=10;

   for (int i=0;i<9;i++)
   {
      if(playtest.addind(i,'O')) //we can add in that possition
      {
      int value=maxnode(depth-1,alpha,beta); //check that childtree
      playtest.rem(i); //clear
      bestVal=min(bestVal, value);
      beta = min( beta, bestVal);
      if (beta <= alpha)
        return bestVal;
      }
   }
   return bestVal;
}

 int ABP::minimax(int depth)
 {
     int alpha=-10;
     int beta=10;
     int bestVal=-10;
     int indexBest;

     for (int i=0;i<9;i++)
        {
         if(playtest.addind(i,'X')) //we can add in that possition
          {
          int value=minnode(depth-1,alpha,beta); //check that childtree
          playtest.rem(i); //clear
          if(value>bestVal)
          {
             bestVal=value;
             indexBest=i;
             alpha = bestVal;
          }

          }
        }
   return indexBest;
 }
