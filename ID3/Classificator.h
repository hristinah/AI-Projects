#ifndef CLASSIFICATOR_H
#define CLASSIFICATOR_H
#include "Tree.h"
#include <vector>
#include <string>
#include <map>
#include <set>
#include <utility>
using namespace std;

const int a=9;//atribute count

struct node;

class Tree;

struct Instance{
string clss;
string attr[a];
};

struct devData  //data devided according to values of an attr
{
    int indattr; //index of the attribute
     map<string, int> indval; //attrvalue and its index. index is the index in the array of subvectors and of the child node in the tree
     pair<int,int> * probarray; //array of pairs how many of the examples with that specific att value are class1 and class2. max num of values is 15 first is yes, second is no
};



class Classificator
{
    public:
        Classificator(const char* filename,int n1);
       ~Classificator();
       void print();
       void createtree(int indtest,int k); //use all data but the ones in subset indtest, with treshhold for min data in a subset = k
       double test(); //test on test data and return accuaracy
       string prediction(string attr[]);
    private:
        int indtestdata; //what subset will be used for testing. if its -1 we cant test
        int n; //how many data subsets
        vector<Instance> * datavec; //array of data subsets
        Tree * dectree;
        void pcreatetree(const vector<Instance> & data,int k, set<int> used,node *parrent);
        vector<devData> createdevd(const vector<Instance> & data,const set<int> & used); //calculate probabilities and weather we have entropy 0
};

#endif // CLASSIFICATOR_H
