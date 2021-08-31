#ifndef BOARD_H
#define BOARD_H
#include<utility>
using namespace std;
class Board
{
    public:
        Board(int n=1);
        ~Board();
        void print();
        void minprint(); /* only coordinates */
        bool minConflictS();


    private:
        int n; /*number of queens/row/col*/
        pair<int, int> *rows; /* rows[i]=<x,c> means that the i row(the y in our grid - from 0 to n-1) of the board has its queen on the x column and that queen has c conflicts */
        int *col; /*col[i] s value is the num of queens in col i*/
        int *d1; /* the \ diagonals   d1[0] is where y-x=-n+1  d1[2*n-2] is where y-x=n-1    so if y-x=k it is on the d1[k+n-1]   and d1[i] is how many queens there are on that diagonal     */
        int *d2; /* the / diagonals   d1[0] is where y+x=0  d1[2*n-2] is where y+x=2*n-2     and d2[i] is how many queens there are on that diagonal         */
        int allconf; /*total conflicts*/
        int lastmoved; /*index of last moved queen*/
        int worstqueen; /*index of the queen with the most conflicts ! if its too slow remove this optimisation */


        void getallconf(); /* recalculates the conflicts  finds the total and finds the 'worst' queen*/
        int findminconf(int y);  /* get the index of the best possible position for queen y*/
        int calcqueenconf(int y,int x,bool in); /*conflicts of queen y in col x  ! if in==1 the queen is in that possition, otherwise she is not */
        pair<int,int> getindd1d2(int y,int x);/* getting the indexes of queen y s diagonals if she is in collumn x */
        void moveq(int y); /*moves the y queen to its best possible column and updates the conf*/
};

#endif // BOARD_H
