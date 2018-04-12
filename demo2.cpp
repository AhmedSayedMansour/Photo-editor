// Program: demo2.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
// Author:  Mohammad El-Ramly
// Date:    30 March 2018
// Version: 1.0

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];

void loadImage ();
void saveImage ();
void blackandwhite ();
void invertimage ();
void mergeimage ();
void flipimage ();
void rotateimage ();
void darkenandlightenimage ();
void detectimageedges ();
void enlargeimage ();
void shrinkimage ();
void mirrorimage ();
void shuffleimage ();
void blurimage ();

int main()
{
    char choose;
    cout<<"Ahalan ya user ya habibi\n";
    loadImage();
    while(true){
        cout<<"Please select a filter to apply or 0 to exit:\n\n";
        cout<<"1-Black and White Filter\n2-Invert Filter\n3-Merge Filter\n4-Flip Filter\n5-Rotate Image";
        cout<<"\n6-Darken and Lighten Image\n7-Detect Image Edges\n8-Enlarge Image";
        cout<<"\n9-Shrink Image\na-Mirror 1/2 Image";
        cout<<"\ns-Save the image to a file\n0-EXIT\nchoose :";
        cin>>choose;
        switch(choose){
            case '1':
                blackandwhite();
                break;
            case '2':
                invertimage();
                break;
            case '3':
                mergeimage ();
                break;
            case '4':
                flipimage();
                break;
            case '5':
                rotateimage();
                break;
            case '6':
                darkenandlightenimage ();
                break;
            case '7':
                detectimageedges();
                break;
            case '8':
                enlargeimage ();
                break;
            case '9':
                shrinkimage ();
                break;
            case 'a':
                mirrorimage();
                break;
            case 's':
                saveImage();
                cout<<endl<<"photo saved successfully"<<endl;
                break;
            case '0':
                return 0;
        }
    }
    return 0;
}

//_________________________________________
void loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, image);
}

//_________________________________________
void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image);
}

//_________________________________________
void blackandwhite() {
    int sum=0,average;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++)
            sum+=image[i][j];
    }
    average=sum/(SIZE*SIZE);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            if(image[i][j]>=average) image[i][j]=255;
            if(image[i][j]<average) image[i][j]=0;
        }
    }
}

void invertimage (){
    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            image[i][j] = 255-image[i][j];
        }
    }
}

void mergeimage (){
    for (int i=0; i<SIZE; i++){
        for (int j=0; j<SIZE; j++){
            image2[i][j] = image[i][j];
        }
    }
    cout <<"Enter the file name of the second photo :";
    loadImage();
    for (int i=0; i<SIZE; i++){
        for (int j=0; j<SIZE; j++){
            image[i][j] = (image2[i][j]+image[i][j])/2;
        }
    }
}

void flipimage (){
    char choose4;
    cout<<"Flip (h)orizontally or (v)ertically : ";
    cin>>choose4;
    if(choose4=='h'){
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j< SIZE/2; j++){
                swap(image[i][j],image[i][SIZE-j]);
            }
        }
    }
    else if(choose4=='v'){
        for (int i = 0; i < SIZE/2; i++){
            for (int j = 0; j< SIZE; j++){
                swap(image[i][j],image[SIZE-i][j]);
            }
        }
    }
    else cout<<"ERROR INVALID CHOOSE";
}

void rotateimage (){
    int choose5;
    for (int i = 0; i < (SIZE); i++){
        for (int j =i+1; j< (SIZE); j++) {
            swap(image[i][j],image[j][i]);
        }
    }
    cout<<"Rotate (90), (180) or (270) degrees : ";
    cin>>choose5;
    if(choose5==90){
        for (int i = 0; i < SIZE; i++ ){
            for (int j = 0; j < SIZE/2; j += 1){
                swap(image[j][i], image[SIZE-j-1][i]);
            }
        }
    }
    else if(choose5==180){
        for (int i = 0; i < (SIZE); i++){
            for (int j =0; j< (SIZE-i); j++){
            swap(image[i][j],image[SIZE-j-1][SIZE-i-1]);
            }
        }
    }
    else if(choose5==270){
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE/2; j += 1){
                swap(image[i][j], image[i][SIZE-j-1]);
            }
        }
    }
    else cout<<"ERROR INVALID CHOOSE";
}

void darkenandlightenimage (){
    char choose6;
    cout<<"Do you want to (d)arken or (l)ighten :";
    cin>>choose6;
    if(choose6=='d'){
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j< SIZE; j++){
                image[i][j]=image[i][j]/2;
            }
        }
    }
    else if(choose6=='l'){
        int num=0;
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j< SIZE; j++){
                num=image[i][j]+image[i][j]*0.5;
                if (num>255)    num=255;
                image[i][j]=num;
            }
        }
    }
    else cout<<"ERROR INVALID CHOOSE";
}

void detectimageedges(){
    for (int i=0; i<SIZE-1; i++){
        for (int j=0; j<SIZE-1; j++){
            if((abs(image[i][j]-image[i][j+1])>=40)||(abs(image[i][j]-image[i+1][j])>=40)) image[i][j]=0;
            else image[i][j]=255;
        }
    }
}

void enlargeimage (){
    int choose8;
    cout<<"Which quarter to enlarge 1, 2, 3 or 4 : ";
    cin>>choose8;
    if(choose8==1){
        for (int i = 0; i < (SIZE/2); i++){
            for (int j =0 ; j <(SIZE/2); j++){
                image2[(i*2)][(j*2)]=image[i][j];
                image2[(i*2)+1][(j*2)]=image[i][j];
                image2[(i*2)][(j*2)+1]=image[i][j];
                image2[(i*2)+1][(j*2)+1]=image[i][j];
            }
        }
        for (int i = 0; i < (SIZE); i++){
            for (int j =0 ; j <(SIZE); j++){
                image[i][j]=image2[i][j];
            }
        }
    }
    else if(choose8==2){
        for (int i = 0; i < (SIZE/2); i++){
            for (int j =0 ; j <(SIZE/2); j++){
                image2[i*2][j*2]=image[i][j+128];
                image2[(i*2)+1][(j*2)]=image[i][j+128];
                image2[(i*2)][(j*2)+1]=image[i][j+128];
                image2[(i*2)+1][(j*2)+1]=image[i][j+128];
            }
        }
        for (int i = 0; i < (SIZE); i++){
            for (int j =0 ; j <(SIZE); j++){
                image[i][j]=image2[i][j];
            }
        }
    }
    else if(choose8==3){
        for (int i = 0; i < (SIZE/2); i++){
            for (int j =0 ; j <(SIZE/2); j++){
                image2[i*2][j*2]=image[i+128][j];
                image2[(i*2)+1][(j*2)]=image[i+128][j];
                image2[(i*2)][(j*2)+1]=image[i+128][j];
                image2[(i*2)+1][(j*2)+1]=image[i+128][j];
            }
        }
        for (int i = 0; i < (SIZE); i++){
            for (int j =0 ; j <(SIZE); j++){
                image[i][j]=image2[i][j];
            }
        }
    }
    else if(choose8==4){
        for (int i = 0; i < (SIZE/2); i++){
            for (int j =0 ; j <(SIZE/2); j++){
                image2[i*2][j*2]=image[i+128][j+128];
                image2[(i*2)+1][(j*2)]=image[i+128][j+128];
                image2[(i*2)][(j*2)+1]=image[i+128][j+128];
                image2[(i*2)+1][(j*2)+1]=image[i+128][j+128];
            }
        }
        for (int i = 0; i < (SIZE); i++){
            for (int j =0 ; j <(SIZE); j++){
                image[i][j]=image2[i][j];
            }
        }
    }
    else cout<<"ERROR INVALID CHOOSE";
}

void shrinkimage (){
    float choose9;
    cout<<"1-Shrink to (1/2)\n2-Shrink to (1/3) \n3-Shrink to (1/4) \nchoose :";
    cin>>choose9;
    if (choose9==1){
        for (int i = 0; i < SIZE; i++){
            for (int j =0 ; j <SIZE; j++){
                image[i/2][j/2]=image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++){
            for (int j =SIZE/2 ; j <SIZE; j++){
                image[i][j]=255;
            }
        }
        for (int i = SIZE/2; i < SIZE; i++){
            for (int j =0 ; j <SIZE; j++){
                image[i][j]=255;
            }
        }
    }
    if (choose9==2){
        for (int i = 0; i < SIZE; i++){
            for (int j =0 ; j <SIZE; j++){
                image[i/3][j/3]=image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++){
            for (int j =SIZE/3 ; j <SIZE; j++){
                image[i][j]=255;
            }
        }
        for (int i = SIZE/3; i < SIZE; i++){
            for (int j =0 ; j <SIZE; j++){
                image[i][j]=255;
            }
        }
    }
    if (choose9==3){
        for (int i = 0; i < SIZE; i++){
            for (int j =0 ; j <SIZE; j++){
                image[i/4][j/4]=image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++){
            for (int j =SIZE/4 ; j <SIZE; j++){
                image[i][j]=255;
            }
        }
        for (int i = SIZE/4; i < SIZE; i++){
            for (int j =0 ; j <SIZE; j++){
                image[i][j]=255;
            }
        }
    }
}

void mirrorimage() {
    char choosea;
    cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side :";
    cin>>choosea;
    if (choosea=='l'){
        for (int i = 0; i < SIZE; i++){
            for (int j =0 ; j <SIZE/2; j++){
                image[i][SIZE-j]=image[i][j];
            }
        }
    }
    if (choosea=='r'){
        for (int i = 0; i < SIZE; i++){
            for (int j =0 ; j <SIZE/2; j++){
                image[i][j]=image[i][SIZE-j];
            }
        }
    }
    if (choosea=='u'){
        for (int i = 0; i < SIZE/2; i++){
            for (int j =0 ; j <SIZE; j++){
                image[SIZE-i][j]=image[i][j];
            }
        }
    }
    if (choosea=='d'){
        for (int i = 0; i < SIZE/2; i++){
            for (int j =0 ; j <SIZE; j++){
                image[i][j]=image[SIZE-i][j];
            }
        }
    }
}
