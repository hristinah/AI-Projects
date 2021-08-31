#include <iostream>
#include "Classificator.h"
#include "Tree.h"
#include <string>
using namespace std;

int main()
{
    Classificator c("breast-cancer.data",10);
    //c.print();
    double avg=0;
    double acc;
    for(int i=0;i<10;i++)
    {
    c.createtree(i,3);
       acc=c.test();
       cout<<" accuracy : "<<acc<<endl;
       avg+=acc;
    }
    cout<<endl<<endl<<"Avearge accuracy is : "<<avg/10<<endl;

    return 0;
}
/*
//recurrence-events,40-49,premeno,25-29,0-2,no,3,left,right_up,no
    string a[9] ={"40-49","premeno","25-29","0-2","no","3","left","right_up","no"};
    cout<<endl<<endl<<"prediction is  "<<c.prediction(a)<<endl;
    //no-recurrence-events,50-59,premeno,25-29,0-2,no,1,left,left_low,no
    string b[9] ={"50-59","premeno","25-29","0-2","no","1","left","left_low","no"};
    cout<<endl<<endl<<"prediction is  "<<c.prediction(b)<<endl;
*/
/*Tree t;
    node *r=t.getroot();
    node *n=t.insert(2,r);
    node *n1=t.insert(6,n);
    node *n2=t.insert(20,n);
    node *n11=t.insert(0,n2);
    node *n110=t.insert(5,n11);
    t.print();
    */
