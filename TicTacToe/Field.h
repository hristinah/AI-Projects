#ifndef FIELD_H
#define FIELD_H
#include <iostream>
#include <set>

using namespace std;

class Field
{
    public:
        Field();
        ~Field();
        Field(const Field& other);
        Field& operator=(const Field& other);
        void print();
        bool add(int x,int y,char s); //x line y column
        bool addind(int i,char s);
        void rem(int ind); //removes sybom on index ind
        int victory(); //returns -1 if O(player) wins ,1 if X(comp) wins, and 0 otherwise

    private:
        char * board;
        set<int> moves;


};

#endif // FIELD_H
