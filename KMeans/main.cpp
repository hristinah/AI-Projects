#include <iostream>
#include "Classificator.h"
using namespace std;

#include <stdio.h>
#include <vector>

const int bytesPerPixel = 3; /// red, green, blue
const int fileHeaderSize = 14;
const int infoHeaderSize = 40;

void generateBitmapImage(unsigned char *image, int height, int width, char* imageFileName);
unsigned char* createBitmapFileHeader(int height, int width, int paddingSize);
unsigned char* createBitmapInfoHeader(int height, int width);

int color[7][3]{
   {0, 0, 0},
   {255, 0, 0},
   {0, 255, 0},
   {0, 0, 255},
   {255, 255, 0},
   {255, 0, 255},
   {0, 255, 255}
};

int main(){
        int index;//what file
        int n;  //number of clusters
        int maxcycles;
        const char* filename[2]={"normal.txt","unbalance.txt"};
        cout<<"Which file?"<<endl;
        cout<<filename[0]<<" - 0"<<endl<<filename[1]<<" - 1"<<endl;
        cin>>index;
        while(index!=0&&index!=1) {cout<<"Invalid number, try again"<<endl; cin>>index;}
         cout<<"How many clusters?"<<endl;
        cout<<"2 - 7"<<endl;
        cin>>n;
        while(n<2&&n>7) {cout<<"Invalid number, try again"<<endl; cin>>n;}
        cout<<"How many cycles max?"<<endl;
         cout<<"1 - 50"<<endl;
         cin>>maxcycles;
         while(n<1&&n>50) {cout<<"Invalid number, try again"<<endl; cin>>maxcycles;}



 Classificator c(filename[index],n,3*(1-index),0,maxcycles);
 //c.print();
 long int m=c.getmin();
 long int d=c.getmax()-c.getmin();
 cout.precision(17);
 c.kmeans(0);
 double mincost=c.cost();
 cout<<"Cost "<<mincost<<endl;
 vector<Instance> v=c.getdatavec();

 for(int i=1;i<20;i++)
 {
   c.reset(i);

   cout.precision(17);
   c.kmeans(0);
   double cost=c.cost();
   if(cost<mincost)
   {
       mincost=cost;
       v=c.getdatavec();
   }
     cout<<"Cost "<<cost<<endl;
 }






    int height = 620;
    int width = 620;
    unsigned char image[height][width][bytesPerPixel];
    char* imageFileName = "bitmapImage.bmp";

    int i, j;
    for(i=0; i<height; i++){
        for(j=0; j<width; j++){
            image[i][j][2] = (unsigned char)((double)255); ///red
            image[i][j][1] = (unsigned char)((double)255); ///green
            image[i][j][0] = (unsigned char)((double)255); ///blue
        }
    }
        int x,y;
    for (auto it = v.begin(); it != v.end(); it++)
        {
             x=(600*(it->x -m)/d)+2;
             y=(600*(it->y -m)/d)+2;
             //cout<<x<<"  "<<y<<endl;
            for(i=-2; i<=2; i++)
                    for(j=-2; j<=2; j++)
                    {
                        image[x+i][y+j][2] = (unsigned char)((double)color[it->cluster][0]); ///red
                        image[x+i][y+j][1] = (unsigned char)((double)color[it->cluster][1]); ///green
                        image[x+i][y+j][0] = (unsigned char)((double)color[it->cluster][2]); ///blue
                    }

        }


v.clear();

    generateBitmapImage((unsigned char *)image, height, width, imageFileName);
    cout<<"Image generated!!"<<endl<<"It's  name is : bitmapImage.bmp"<<endl;
}


void generateBitmapImage(unsigned char *image, int height, int width, char* imageFileName){

    unsigned char padding[3] = {0, 0, 0};
    int paddingSize = (4 - (width*bytesPerPixel) % 4) % 4;

    unsigned char* fileHeader = createBitmapFileHeader(height, width, paddingSize);
    unsigned char* infoHeader = createBitmapInfoHeader(height, width);

    FILE* imageFile = fopen(imageFileName, "wb");

    fwrite(fileHeader, 1, fileHeaderSize, imageFile);
    fwrite(infoHeader, 1, infoHeaderSize, imageFile);

    int i;
    for(i=0; i<height; i++){
        fwrite(image+(i*width*bytesPerPixel), bytesPerPixel, width, imageFile);
        fwrite(padding, 1, paddingSize, imageFile);
    }

    fclose(imageFile);
}

unsigned char* createBitmapFileHeader(int height, int width, int paddingSize){
    int fileSize = fileHeaderSize + infoHeaderSize + (bytesPerPixel*width+paddingSize) * height;

    static unsigned char fileHeader[] = {
        0,0, /// signature
        0,0,0,0, /// image file size in bytes
        0,0,0,0, /// reserved
        0,0,0,0, /// start of pixel array
    };

    fileHeader[ 0] = (unsigned char)('B');
    fileHeader[ 1] = (unsigned char)('M');
    fileHeader[ 2] = (unsigned char)(fileSize    );
    fileHeader[ 3] = (unsigned char)(fileSize>> 8);
    fileHeader[ 4] = (unsigned char)(fileSize>>16);
    fileHeader[ 5] = (unsigned char)(fileSize>>24);
    fileHeader[10] = (unsigned char)(fileHeaderSize + infoHeaderSize);

    return fileHeader;
}

unsigned char* createBitmapInfoHeader(int height, int width){
    static unsigned char infoHeader[] = {
        0,0,0,0, /// header size
        0,0,0,0, /// image width
        0,0,0,0, /// image height
        0,0, /// number of color planes
        0,0, /// bits per pixel
        0,0,0,0, /// compression
        0,0,0,0, /// image size
        0,0,0,0, /// horizontal resolution
        0,0,0,0, /// vertical resolution
        0,0,0,0, /// colors in color table
        0,0,0,0, /// important color count
    };

    infoHeader[ 0] = (unsigned char)(infoHeaderSize);
    infoHeader[ 4] = (unsigned char)(width    );
    infoHeader[ 5] = (unsigned char)(width>> 8);
    infoHeader[ 6] = (unsigned char)(width>>16);
    infoHeader[ 7] = (unsigned char)(width>>24);
    infoHeader[ 8] = (unsigned char)(height    );
    infoHeader[ 9] = (unsigned char)(height>> 8);
    infoHeader[10] = (unsigned char)(height>>16);
    infoHeader[11] = (unsigned char)(height>>24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(bytesPerPixel*8);

    return infoHeader;
}
