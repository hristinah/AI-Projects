#ifndef CLASSIFICATOR_H
#define CLASSIFICATOR_H
#include <vector>
#include <string>
using namespace std;

const int a=16;//atribute count

struct Instance{
string clss;
char attr[a];
};

struct Votes{ //first we write the number of examples that have the attribute values we want, then turn this into probability and finaly write it as log for easier calculation in the end
  double yes;
  double no;
  double unknown;
};

struct Probab{
    Votes votesparty[2]; //0-rep/1-dem
};

class Classificator
{
    public:
        Classificator(const char* filename,int n1);
       ~Classificator();
       void print();
       void calcprob(int indtest); //calculates probabilites without the training subset
       double test(); //test on test data and return accuaracy

    private:
        int indtestdata; //what subset will be used for testing. if its -1 we cant test
        int n; //how many data subsets
        vector<Instance> * datavec; //array of data subsets
        Probab * attr_class; //probab for the types of votes for an atributes by members of a class
        int rep; //count rep
        int dem; //count dem
        string prediction(char attr[]); //returns rep or dem based on total probability

};

#endif // CLASSIFICATOR_H
