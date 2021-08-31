#include <iostream>
#include "Tile.h"
#include "Node.h"
#include <math.h>
using namespace std;

void start();

int main()
{
     start();

    return 0;
}

void start()
{

    int n,n1,n0;
    cout<<"Numbered tiles?"<<endl;
    cin>>n;
    cout<<"Index 0?"<<endl;
    cin>>n0;
    n=n+1;
    if(n0==(-1)) //wanted index of 0 becomes the last tile
    {n0=n;}
    n1=sqrt(n); //col/row
    int *a=new int [n];
    cout<<"Put in the tiles:"<<endl;
    for (int i=0;i<n;i++)
    {
       cin>>a[i];
    }
    Node t(n1,n0,a);
    t.print();


     t.ida();
  return;
}
