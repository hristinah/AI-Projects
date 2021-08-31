#include "Field.h"
#include <iostream>
#include <set>
#include <iterator>

using namespace std;

Field::Field()
{
    //ctor
    board=new char[9];
    for(int i=0;i<9;i++)
    {
        board[i]='*';
    }
}

Field::~Field()
{
    //dtor
    delete [] board;
    moves.clear();

}

Field::Field(const Field& o)
{
    //copy ctor
    board=new char[9];
    for(int i=0;i<9;i++)
    {
        board[i]=o.board[i];
    }
     for (auto itr =o.moves.begin(); itr != o.moves.end(); ++itr)
    {
       moves.insert(*itr);
    }

}

Field& Field::operator=(const Field& o)
{
    if (this == &o) return *this; // handle self assignment

    //assignment operator
     moves.clear();
    for(int i=0;i<9;i++)
    {
        board[i]=o.board[i];
    }
     for (auto itr =o.moves.begin(); itr != o.moves.end(); ++itr)
    {
       moves.insert(*itr);
    }
    return *this;
}

void Field::print()
{
    cout<<"Board State: "<<endl;
    cout<<endl;
    for(int i=0;i<3;i++)
    {
        cout<<"     "<<board[i]<<"     ";
    }
    cout<<endl<<endl;
    for(int i=3;i<6;i++)
    {
        cout<<"     "<<board[i]<<"     ";
    }
    cout<<endl<<endl;
    for(int i=6;i<9;i++)
    {
       cout<<"     "<<board[i]<<"     ";
    }
    cout<<endl<<endl;

}

bool Field::add(int x,int y,char s)
{
int i=(x-1)*3+(y-1);
if(moves.count(i)==1||i<0||i>8) return false;
board[i]=s;
moves.insert(i);
return true;
}

bool Field::addind(int i,char s)
{
if(moves.count(i)==1||i<0||i>8) return false;
board[i]=s;
moves.insert(i);
return true;
}

void Field::rem(int ind)
{
   if(ind>=0&&ind<9)
   {
   board[ind]='*';
   moves.erase(ind);
   }
}

int Field::victory()
{
    char winner='*';
    //check rows
    for (int i=0;i<3;i++)
    {
        if(board[i*3]!='*'&&board[i*3]==board[i*3+1]&&board[i*3+1]==board[i*3+2])
        {
            winner=board[i*3];
        }
    }

    //check columns
    for (int i=0;i<3;i++)
    {
        if(board[i]!='*'&&board[i]==board[i+3]&&board[i+3]==board[i+6])
        {
            winner=board[i];
        }
    }
    //check diagonal 1
    if(board[0]!='*'&&board[0]==board[4]&&board[4]==board[8])
        {
            winner=board[0];
        }
     //check diagonal 2
    if(board[2]!='*'&&board[2]==board[4]&&board[4]==board[6])
        {
            winner=board[2];
        }

     if(winner=='O') return -1;
     if(winner=='X') return 1;
     return 0;
}
