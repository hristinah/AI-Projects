#include "Classificator.h"

#include <fstream>
#include <string>
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <math.h>       /* log  exp */
#include <iostream>

using namespace std;

Classificator::Classificator(const char* filename,int n1)
{
   n = n1;
   indtestdata=-1;
   rep=0;
   dem=0;
   attr_class=new Probab[a];


   fstream fs (filename, std::fstream::in);
   string line;
   vector<Instance> data;
   srand ( unsigned ( time(0) ) );
    if (fs.is_open())
  {
    while ( getline (fs,line) )
    {
      Instance d;
      size_t pos = line.find(',');
      if (pos != std::string::npos)
        {
            d.clss=line.substr(0, pos);
            pos++;
        }
      for (int i=0;i<a;i++)
        {
                d.attr[i]=line[pos];
                pos+=2;
        }
        data.push_back(d);
    }
    fs.close();
  }


	// determine size of sub-vectors
  int size = data.size()/ n ;
  int s;//actual size
  int rem=data.size()% n;
  auto start_itr = data.cbegin();
  datavec = new vector<Instance>[n];
  random_shuffle ( data.begin(), data.end() ); //shuffle the examples

	for (int k = 0; k < n; ++k)
	{
	    s=size;
		if(k<rem)s++; //bigger by one so that all elements are distributed as equaly as possible

		auto end_itr = std::next(start_itr, s);

		// allocate memory for the sub-vector
		datavec[k].resize(s);

		// copy elements from the input range to the sub-vector
		copy(start_itr, end_itr, datavec[k].begin());

		start_itr =end_itr;
	}
data.clear();
}

Classificator::~Classificator()
{
    for(int k=0;k<n;k++)
    {
        datavec[k].clear();
    }
    delete[] datavec;
    delete[] attr_class;
}

void Classificator::print()
{

   /*
    int size=0;
    for(int k=0;k<n;k++)
    {

       for (auto it = datavec[k].begin(); it != datavec[k].end(); it++)
        {
            cout << it->clss ;
            for (int i=0;i<a;i++)
            {
                    cout << " "<< it->attr[i] ;
            }
            cout<<endl;
        }
        cout<<datavec[k].size()<<endl;
        if(k!=indtestdata)
        size+=datavec[k].size();
    }

cout<<"Total size: "<<size<<endl<<endl;
*/
  /* for (int i = 0; i < a; ++i)
   {
       cout<<"attr "<<i+1<<endl;
       cout<<"      republicans   democrats"<<endl;
       cout<<"yes:     "<<attr_class[i].votesparty[0].yes<<"             "<<attr_class[i].votesparty[1].yes<<endl;
       cout<<"no:      "<<attr_class[i].votesparty[0].no<<"             "<<attr_class[i].votesparty[1].no<<endl;
       cout<<"unknown: "<<attr_class[i].votesparty[0].unknown<<"             "<<attr_class[i].votesparty[1].unknown<<endl;
       cout<<endl;
   }
*/
   cout<<"Republicans : "<<rep<<"          Democrats : "<<dem<<endl;

   for (int i = 0; i < a; ++i)
   {
       cout<<"attr "<<i+1<<endl;
       cout<<"      republicans   democrats"<<endl;
       cout<<"yes:     "<<exp(attr_class[i].votesparty[0].yes)<<"             "<<exp(attr_class[i].votesparty[1].yes)<<endl;
       cout<<"no:      "<<exp(attr_class[i].votesparty[0].no)<<"             "<<exp(attr_class[i].votesparty[1].no)<<endl;
       cout<<"unknown: "<<exp(attr_class[i].votesparty[0].unknown)<<"             "<<exp(attr_class[i].votesparty[1].unknown)<<endl;
       cout<<endl;
   }

}

void Classificator::calcprob(int indtest)
{
    if(indtest>=0&&indtest<10)
    {
        indtestdata=indtest;
        rep=0;
        dem=0;
      //initialize all probabilities as 0
       for (int i = 0; i < a; ++i)
       {
          attr_class[i]=  {{0,0,0,0,0,0}};
       }

       int c;//what class the example belongs to

           for(int k=0;k<n;k++)
        {
           if(k!=indtestdata)
           for (auto it = datavec[k].begin(); it != datavec[k].end(); it++) //count votes for examples
            {
                if(it->clss=="republican" ) {c=0; rep++;}
                else {c=1; dem++;}
                for (int i=0;i<a;i++)
                {
                        if(it->attr[i]=='y') attr_class[i].votesparty[c].yes++;
                        if(it->attr[i]=='n') attr_class[i].votesparty[c].no++;
                        if(it->attr[i]=='?') attr_class[i].votesparty[c].unknown++;
                }
            }

        }
           /*          for (int i = 0; i < a; ++i)
               {
                   cout<<"attr "<<i+1<<endl;
                   cout<<"      republicans   democrats"<<endl;
                   cout<<"yes:     "<<attr_class[i].votesparty[0].yes<<"             "<<attr_class[i].votesparty[1].yes<<endl;
                   cout<<"no:      "<<attr_class[i].votesparty[0].no<<"             "<<attr_class[i].votesparty[1].no<<endl;
                   cout<<"unknown: "<<attr_class[i].votesparty[0].unknown<<"             "<<attr_class[i].votesparty[1].unknown<<endl;
                   cout<<endl;
               }
            */



        //calculate propability, and then make it log
        int total; //votes from party on attribute
         for (int i = 0; i < a; ++i)
                       {
                         for(int j=0;j<=1;j++)//for the parties
                         {
                             //check for 0
                             if(attr_class[i].votesparty[j].yes==0) attr_class[i].votesparty[j].yes++;
                             if(attr_class[i].votesparty[j].no==0) attr_class[i].votesparty[j].no++;
                             if(attr_class[i].votesparty[j].unknown==0) attr_class[i].votesparty[j].unknown++;


                             total=0;
                             total+=attr_class[i].votesparty[j].yes;
                             total+=attr_class[i].votesparty[j].no;
                             total+=attr_class[i].votesparty[j].unknown;


                             attr_class[i].votesparty[j].yes=log(attr_class[i].votesparty[j].yes/total);
                             attr_class[i].votesparty[j].no=log(attr_class[i].votesparty[j].no/total);
                             attr_class[i].votesparty[j].unknown=log(attr_class[i].votesparty[j].unknown/total);
                         }
                       }


    }
}

string Classificator::prediction(char attr[])
{
    if (indtestdata==-1) return "Classificator is not ready";
    //initialise variables for probability
    double prep=0;
    double pdem=0;

            for (int i = 0; i < a; ++i)
            {
                if(attr[i]=='y')  prep+=attr_class[i].votesparty[0].yes;
                if(attr[i]=='n')  prep+=attr_class[i].votesparty[0].no;
                if(attr[i]=='?')  prep+=attr_class[i].votesparty[0].unknown;
            }
            prep=exp(prep);
            prep=prep*rep/(rep+dem);



            for (int i = 0; i < a; ++i)
            {
                if(attr[i]=='y')  pdem+=attr_class[i].votesparty[1].yes;
                if(attr[i]=='n')  pdem+=attr_class[i].votesparty[1].no;
                if(attr[i]=='?')  pdem+=attr_class[i].votesparty[1].unknown;
            }
            pdem=exp(pdem);
            pdem=pdem*dem/(rep+dem);


    if(pdem<prep) return "republican";
    else return "democrat";

}


double Classificator::test()
{
   if (indtestdata==-1) return 0;
   //use prediction for all test data examples
   int count_true=0;
   for (auto it = datavec[indtestdata].begin(); it != datavec[indtestdata].end(); it++)
   {
      // cout<<it->clss<<"     "<<prediction(it->attr)<<endl;
       if(it->clss==prediction(it->attr)) count_true++;

   }
   return (double)count_true/datavec[indtestdata].size();
}

