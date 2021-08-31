#include <iostream>
#include "Classificator.h"
using namespace std;

int main()
{
    Classificator c("house-votes-84.data",10);
    double avg=0;// average accuracy
    double acc;
    for(int i=0;i<10;i++)
   {
       c.calcprob(i); //decide what part is for testing and calculate
       acc=c.test();
       cout<<i+1<<" accuracy : "<<acc<<endl;
       avg+=acc;
   }
   cout<<endl<<endl<<"Avearge accuracy is : "<<avg/10<<endl;

    return 0;
}



// char a[16] ={'n','n','y','n','n','n','y','y','y','y','n','n','n','n','n','y'};

   // cout<<c.prediction(a)<<endl;
