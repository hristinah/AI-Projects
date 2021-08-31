#ifndef NODE_H
#define NODE_H
#include "Tile.h"
#include <vector>
using namespace std;



class Node
{
    public:
        Node(int n1=1,int ind0=1,int * a=nullptr);
        ~Node();
        Node(const Node& other);
        Node& operator=(const Node& other);
        void print();
        int getwholemh();
        void ida();


    private:
        int n; //col/row size
        Tile ** table;
        int x0; //place of 0;
        int y0;
        bool moveup(); //swith empty with its upper tile
        bool movedown(); //swith empty with its down tile
        bool moveright(); //swith empty with its right tile
        bool moveleft(); //swith empty with its left tile

        int idasearch(int i,int &cost,vector<char> &path);



};

#endif // NODE_H
