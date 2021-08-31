#include "Classificator.h"

#include <fstream>
#include <string>
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <math.h>       // log2
#include <map>
#include <set>
#include <utility>
#include <iostream>

using namespace std;

Classificator::Classificator(const char* filename,int n1)
{
   n = n1;
   indtestdata=-1;
    dectree=new Tree;

   fstream fs (filename, std::fstream::in);
   string line;
   vector<Instance> data;
   srand ( unsigned ( time(0) ) );
    if (fs.is_open())
  {
    while ( getline (fs,line) )
    {
      Instance d;
      size_t pos1=0;
      size_t pos2 = line.find(',');
          if (pos2 != std::string::npos)
            {
                d.clss=line.substr(pos1, pos2);
                pos1=pos2+1;

                for (int i=0;i<a-1;i++)
                {
                        pos2 = line.find(',',pos1);
                        if (pos2 != std::string::npos)
                            {
                                    d.attr[i]=line.substr(pos1, pos2-pos1);
                                    pos1=pos2+1;
                            }
                        else{d.attr[i]="?";}
                }
                d.attr[a-1]=line.substr(pos1);
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
}

void Classificator::print()
{
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

}

void Classificator::createtree(int indtest,int k)
{
    if(indtest>=0&&indtest<10)
    {
        indtestdata=indtest;
        set<int> used;//indexes of attributes, already used in the tree
        vector<Instance> data;//data for the algorithm to learn from
        for(int k=0;k<n;k++)
        {
           if(k!=indtestdata)
            data.insert( data.end(), datavec[k].begin(), datavec[k].end() );
        }

        /*for (auto it = data.begin(); it != data.end(); it++)
        {
            cout << it->clss ;
            for (int i=0;i<a;i++)
            {
                    cout << " "<< it->attr[i] ;
            }
            cout<<endl;
        }
*/

        dectree->destroy_tree();
        node *parrent=dectree->getroot();
        pcreatetree(data,k,used,parrent);
        //dectree->print();
    }
}



void Classificator::pcreatetree(const vector<Instance> & data,int k, set<int> used,node *parrent)
    {
                int s=a-used.size(); //how many attributes we have left to check
                vector<devData> devd=createdevd(data,used);

                //cout<<"actual calculations with "<<data.size()<<endl;

                /*for(auto i = devd.begin(); i != devd.end(); i++) //print devd
                        {
                            cout<<"index "<<i->indattr+1<<endl;
                            for(auto it = i->indval.begin(); it != i->indval.end(); it++)
                            {
                                cout<<it->first<<"   "<<it->second<<endl;
                            }
                            for(int j=0;j<15;j++)
                            {
                                cout<<i->probarray[j].first<<"   "<<i->probarray[j].second<<endl;
                            }
                            cout<<endl;
                       }*/

                pair<int,double> * atrgain=new pair<int,double> [s];//the index and gain ratio for each remaining attribute
                int ind=0;
                    for(auto i = devd.begin(); i != devd.end(); i++) //calculate gain  for each attribute
                        {
                            atrgain[ind].first=i->indattr;
                            int yes=0; //total yes and no
                            int no=0;
                            int total;
                            double g=0;//gain
                            int c=i->indval.size();
                            //cout<<c<<endl;
                            int *examforvalue=new int[c]; //examples with specific value of the attribute
                            pair<double,double> * prob=new pair<double,double> [c];//probabilities
                            for(int j=0;j<c;j++)
                            {
                                pair<double,double> p(i->probarray[j].first,i->probarray[j].second);
                                if(i->probarray[j].first==0)p.first++;
                                if(i->probarray[j].second==0)p.second++;
                                yes+=p.first;
                                no+=p.second;
                                examforvalue[j]=p.first+ p.second;
                                prob[j].first=(double)p.first/examforvalue[j];
                                prob[j].second=(double)p.second/examforvalue[j];
                                g+=(-prob[j].first*log2(prob[j].first)-prob[j].second*log2(prob[j].second))*examforvalue[j];

                                //cout<<"value "<<j<<" prob : "<<prob[j].first<<" "<<prob[j].second<<endl;
                            }
                            total=yes+no;
                            double py=(double)yes/total;
                            double pn=(double)no/total;
                            //cout<<"py "<<py<<"  pn "<<pn<<endl;
                            double g1=-py*log2(py)-pn*log2(pn); //entropy before split
                            g=g/total;
                            //cout<<"entropy " <<g<<endl;
                            //cout<<"g1 " <<g1<<endl;
                            g=g1-g;
                             //cout<<"index "<<i->indattr<<"   entropy " <<g1<<"   gain " <<g<<endl;
                            atrgain[ind].second=g;
                            /*double split=0;  //info split for this attribute
                             for(int j=0;j<c;j++)
                            {
                               double e=(double)examforvalue[j]/total;
                               split=-e*log2(e);
                            }
                             cout<<"split " <<split<<endl;
                             cout<<"gain ratio" <<g/split<<endl;
                             */
                            //clean things up and move to next attr
                           delete[] examforvalue;
                           delete[] prob;
                           //cout<<"clear"<<endl;
                            ind++;
                        }

                 pair<int,double> maxgain(-1,-1);
                 ind=0;//index of attr with max in devd
                 for(int i=0;i<s;i++)
                    {
                        if(maxgain.second<atrgain[i].second)
                            {
                                maxgain.second=atrgain[i].second;
                                maxgain.first=atrgain[i].first;
                                ind=i;
                            }
                    }
             // cout<<endl<<"max gain "<<maxgain.first<<" "<<maxgain.second<<endl;
              used.insert(maxgain.first);
              map<string, int> maxindval=devd[ind].indval;//map of indexes of attributes for max gain attribute
              pair<int,int> * prob=devd[ind].probarray;
              int c=devd[ind].indval.size();

              node * us=dectree->insert(maxgain.first,parrent); //we are creating the node

              if(a-used.size()==1||maxgain.second==0)
              {
              //create leafs and if entropy =1 for one value, then the parent node will be a leaf
                            int yes=0; //total yes and no
                            int no=0;
                            bool problemchild=false;//true if a child has entropy 1
                            for(int j=0;j<c;j++)//find problem children and what class the parent has to be if there are such
                            {
                                if(prob[j].first==prob[j].second){problemchild=true;}
                                yes+=prob[j].first;
                                no+=prob[j].first;
                            }
                if(maxgain.second==0||problemchild==true)//us is a leaf
                {
                    if(yes>=no)us->key=11;
                    else us->key=12;
                }
                else//create leafs
                {
                    us->indval=maxindval;
                            for(int j=0;j<c;j++)
                            {
                                if(prob[j].first>=prob[j].second){dectree->insert(11,us);}
                                else dectree->insert(12,us);
                            }
                }


              }
              else
                {
                  us->indval=maxindval;
                  vector<Instance> * datav=new vector<Instance>[c]; //spliting the data by atribut value

                    for(auto it = data.begin(); it != data.end(); it++)
                    {
                             string exattr=it->attr[maxgain.first];
                             if(exattr!="?")
                             {
                             auto f=maxindval.find(exattr); //finds the attr value's index
                             datav[f->second].push_back(*it);
                             }
                    }

                            for(int j=0;j<c;j++)
                        {
                            //cout<<datav[j].size()<<endl<<endl;
                            //creates children and if entropy of the child is 0 or subset is <k child is a leaf
                            if(datav[j].size()<k)
                                {
                                    if(prob[j].first>=prob[j].second){dectree->insert(11,us);}
                                    else dectree->insert(12,us);
                                }
                            else
                                {
                                    if(prob[j].first==0||prob[j].second==0)
                                    {
                                        if(prob[j].first>=prob[j].second){dectree->insert(11,us);}
                                        else dectree->insert(12,us);
                                    }
                                   else {
                                        //cout<<"subtree for attribute"<<maxgain.first<<"value "<<j<<endl;
                                        pcreatetree(datav[j],k,used,us);

                                   }
                                }


                        }

                    for(int i=0;i<c;i++) datav[i].clear();
                    delete [] datav;
                }

                //delete and clean things up

                delete[] atrgain;
                for(auto it = devd.begin(); it != devd.end(); it++)
                {
                    it->indval.clear();
                    delete[] it->probarray;
                }
                devd.clear();
    }

 vector<devData> Classificator::createdevd(const vector<Instance> & data,const set<int> & used)
 {
        int s=a-used.size(); //how many attributes we have left to check
        vector<devData> devd;
        devd.reserve(s);
        for(int i=0;i<a;i++) //find what attributes have not yet been used in the tree
        {
            if (used.count(i)==0)
            {
                devData d;
                d.indattr=i;
                d.probarray=new pair<int,int>[15];
                devd.push_back(d);

            }
        }

        int * ind=new int[a]{0}; //numbers of different attr values for each attr. it beggins as 0 and increases for each unique value in the data
        for(auto it = data.begin(); it != data.end(); it++) //find size of subsets based on attribute and attr value  for each class
        {
            int yes,no; //what class the example is from
            if (it->clss=="recurrence-events") {yes=1; }
             else yes=0;

             if (it->clss=="no-recurrence-events") {no=1; }
             else no=0;


             for(auto i = devd.begin(); i != devd.end(); i++)
             {
                 string exattr=it->attr[i->indattr];
                 if(exattr!="?")
                 {
                 auto f=i->indval.find(exattr); //checks if this attr value is already in the devd
                 if (f== i->indval.end()) //not in
                     {
                         i->indval.insert({exattr, ind[i->indattr]});
                         i->probarray[ind[i->indattr] ].first+=yes;
                         i->probarray[ind[i->indattr] ].second+=no;
                         ind[i->indattr]++;
                     }
                     else //already have such a value
                        {
                           i->probarray[f->second].first+=yes;
                           i->probarray[f->second].second+=no;
                        }
                 }
             }


        }
   return devd;
 }


 string Classificator::prediction(string attr[])
 {
     if (indtestdata==-1) return "Classificator is not ready";

     int res=dectree->find(attr);
     //if res is 11 class is recurrence-events ,if its 12 - no-recurrence-events
     if(res==11) return "recurrence-events";
     else return "no-recurrence-events";
 }

 double Classificator::test()
{
   if (indtestdata==-1) return 0;
   //use prediction for all test data examples
   int count_true=0;
   for (auto it = datavec[indtestdata].begin(); it != datavec[indtestdata].end(); it++)
   {
      // cout<<it->clss<<"    "<<prediction(it->attr)<<endl;
       if(it->clss==prediction(it->attr)) count_true++;

   }
   return (double)count_true/datavec[indtestdata].size();
}
