#include <iostream>
#include "Board.h"
using namespace std;

int main()
{
    int n=0;
    int pr=4;  //if pr is 0 only minprint will activate , if its 1 print will activate and if its 2 both will activate ;
    while(n<4)
   {
    cout<<"How many queens? ";
    cin>>n;
   }
   while(pr>=3)
   {
    cout<<"How do you want to print the answer? \n0 - coordinates of the queens only (x,y) * better for bigger n \n1 - with a grid of - and * \n2 -both ways "<<endl;
    cin>>pr;
   }


    bool found=false;
    while(!found)
    {
    Board b(n);
    found=b.minConflictS();
    if(found)
        {
            if(pr==1||pr==2)
             b.print();
            if(pr==0||pr==2)
             b.minprint();
    }
    }
    return 0;
}
