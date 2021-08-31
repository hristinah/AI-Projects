#include <iostream>
#include "Field.h"
#include "ABP.h"
using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    Field f;
    f.print();
    int b; //decised which player is the computer
    int ans;
    cout<<"Player - O"<<endl<<"Computer - X"<<endl;
    char s;
    int x,y;
    cout<<"Do you want to be player one?"<<endl;
    cout<<"1 - yes       else - no"<<endl;
    cin>>ans;
    if(ans==1) b=0;
    else b=1;

    for(int i=0;i<9;i++)
    {
        if(f.victory()!=0) break;
        if(i%2==b) //Human plays
            {
                s='O';
                 cout<<"Input row,col: ";
                 cin>>x>>y;
                 while(x<1||x>3||y<1||y>3||!f.add(x,y,s))
                 {
                     cout<<"Another input needed: ";
                      cin>>x>>y;
                 }
                 f.print();
            }
        else{
                s='X';
                ABP a(f);
                int ind=a.minimax(10-i);
                f.addind(ind,s);
                f.print();
            }


       // while(x<1||x>3||y<1||y>3||!f.add(x,y,s)){cout<<"Another input needed: ";
       // cin>>x>>y;}


    }

   int result= f.victory();
   cout<<endl;
   if (result==0) cout <<"DRAW";
   if (result==-1) cout <<"PLAYER WINS";
   if (result==1) cout <<"AI WINS";




    return 0;
}
