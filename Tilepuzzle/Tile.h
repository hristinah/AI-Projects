#ifndef TILE_H
#define TILE_H


class Tile {
    public:
        //n is the number of row/col , and  ind0 is the index of 0
        Tile(int x1=0,int y1=0,int value=0,int n=1,int ind0=0); 
        ~Tile() {}
        Tile(const Tile& other);
        Tile& operator=(const Tile& other);

        void Swap_Values(Tile&);
        void Print();

        int get_value();
        int get_mh();

    private:
        void Recalculate_Mh_Dist(); // used after move of a number tile

        int x; //column
        int y;  //row
        int value;
        int goal_x;  //the position the value needs to have - changes after a Swap_Values
        int goal_y;
        int mh_dist;

};

#endif 
