#ifndef ABP_H
#define ABP_H
#include "Field.h"

class Field;

class ABP
{
    public:

        ABP(Field &f);
        ~ABP();
         void print();
        int minimax(int depth);
    private:
         Field playtest;
         int maxnode(int depth,int alpha,int beta);
         int minnode(int depth,int alpha,int beta);

};

#endif // ABP_H
