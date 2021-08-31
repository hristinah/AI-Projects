#ifndef CLASSIFICATOR_H
#define CLASSIFICATOR_H
#include <vector>
using namespace std;


struct Center{
int cluster; //what cluster it belongs to
double x,y;  //x,y
};

struct Instance{
int cluster; //what cluster it belongs to
long int x,y;  //x,y
};

class Classificator
{
    public:
        Classificator(const char* filename,int n1,int a,int t,int c); //t adds to time  c - max num cycles
       ~Classificator();
       long int getmin();
       long int getmax();
       vector<Instance> getdatavec();
       double cost();
       void print();
       void kmeans(int iteration);// calculates clusters and if changes are more than one, recalculate centroids. if iterations are more than max cycles,or changes are less than one - end
        void reset(int t);//return to base state


    private:
        vector<Instance> datavec; //data
        Center * centroid;  //Data for the diferent centroids  . cluster is the clusters index and attr are the cordinates of the cluster's centroid
        int n;  //number of clusters
        int after; //how many numbers after ,
        int maxcycles;
        long int mininst;  //min and max values for x and y that will serve as boundries
        long int maxinst;
        int calculate_cluster(); //returns how many changed values
        void recalc_centr();  //finalise changes
        void create_centroid(int t); //random examples


};
#endif // CLASSIFICATOR_H
