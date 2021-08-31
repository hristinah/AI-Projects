#include "Tree.h"

#include <vector>
#include <string>
#include <queue>
#include <map>
#include <iostream>

using namespace std;

Tree::Tree()
{
	root = nullptr;


}

Tree::~Tree(){
	destroy_tree();
}

void Tree::destroy_tree(node *leaf)
{
	if(leaf!=nullptr&&leaf->children.empty()!=true)
        {
            for (auto it = leaf->children.begin(); it != leaf->children.end(); it++)
                {
                    destroy_tree(*it);
                }
            leaf->children.clear();
            leaf->indval.clear();
            delete leaf;
        }

}

void Tree::destroy_tree()
{
	destroy_tree(root);
	root=nullptr;
}

node * Tree::insert(int key, node *leaf)
{
    node * n = new node;
	n->key=key;
	if(leaf==nullptr) root=n;
	else
    leaf->children.push_back(n);
    return n;
}

node * Tree::getroot()
{
    return root;
}


void Tree::print()
{
	print(root);

}

void Tree::print(node *leaf)
{
	if(leaf != NULL)
        {
            queue<node *> q;  // Create a queue
            q.push(leaf);
            while (!q.empty())
            {
                int n = q.size();

                // print all parents
                while (n > 0)
                {
                    // Dequeue an item from queue and print it
                    node * p = q.front();
                    q.pop();
                    cout << p->key << " ";


                    // Enqueue all children of the dequeued item
                     for (auto it = p->children.begin(); it != p->children.end(); it++)
                        {
                            q.push(*it);
                        }
                    n--;
                }

                cout << endl<<endl; // Print new line between two levels
            }
        }
}

int Tree::find (string attr[])
{
  return find (attr,root);
}

int Tree::find (string attr[],node *leaf)
{
    if(leaf->key>=11) {
            //cout<<"class is "<<leaf->key<<endl;
             return leaf->key; }//we are in a leaf
    else
    {
        string a=attr[leaf->key];
        //cout<<"attribute value is "<<a<<endl;
        auto f=leaf->indval.find(a); //finds the attr value's index
        if (f==leaf->indval.end()) //not in . so we get the moda of the subtrees
        {
           // cout<<"unknown value"<<a<<endl;
         int count11=0;
         int count12=0;
         int i;
           for (auto it = leaf->children.begin(); it != leaf->children.end(); it++)
                        {
                           i=find (attr,*it);
                           if(i==11) count11++;
                           else count12++;
                        }
             if(count11>count12) return 11;
             else return 12;
        }
        else //we know what child to search next
            {
                return find (attr,leaf->children[f->second]);
            }
    }
}

