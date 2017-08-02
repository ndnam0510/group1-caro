#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <dos.h>
#include <string.h>

int X[19][19]= {0};
int Y[19][19]= {0};

/// Console function
void gotoxy(int x,int y){
    COORD coordinate= {0,0};
    coordinate.X=x;
    coordinate.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinate);
}

void SetColor (int value){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}

void XYinput(int x,int y){
    COORD input= {17,9};
    input.X=x*4+13;
    input.Y=y*2+7;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),input);
}

/// Game function and declaration
char upleft=   218,    row=196,    up=   194, //ASCII Code
     upright=  191,    col=179,    down= 193,
     downleft= 192,    mid=197,    left= 195,
     downright=217,                right=180;

/// Win condition will run after input
bool isXwin(){
    for (int x=1; x<=19; x++) {
        for (int y=1; y<=19; y++){
            if (X[ x ][ y ]==1 && X[x+1][ y ]==1 && X[x+2][ y ]==1 && X[x+3][ y ]==1 && X[x+4][ y ]==1) return true; ///Horizontal
            if (X[ x ][ y ]==1 && X[ x ][y+1]==1 && X[ x ][y+2]==1 && X[ x ][y+3]==1 && X[ x ][y+4]==1) return true; ///Vertical
            if (X[ x ][ y ]==1 && X[x+1][y+1]==1 && X[x+2][y+2]==1 && X[x+3][y+3]==1 && X[x+4][y+4]==1) return true; ///Diagonal left
            if (X[ x ][y+4]==1 && X[x+1][y+3]==1 && X[x+2][y+2]==1 && X[x+3][y+1]==1 && X[x+4][ y ]==1) return true; ///Diagonal right
        }
    }
    return false;
}

bool isYwin(){ //Similar to isXWin()
    for (int x=1; x<=19; x++){
        for (int y=1; y<=19; y++){
            if (Y[ x ][ y ]==1 && Y[x+1][ y ]==1 && Y[x+2][ y ]==1 && Y[x+3][ y ]==1 && Y[x+4][ y ]==1) return true; ///Horizontal
            if (Y[ x ][ y ]==1 && Y[x  ][y+1]==1 && Y[ x ][y+2]==1 && Y[ x ][y+3]==1 && Y[ x ][y+4]==1) return true; ///Vertical
            if (Y[ x ][ y ]==1 && Y[x+1][y+1]==1 && Y[x+2][y+2]==1 && Y[x+3][y+3]==1 && Y[x+4][y+4]==1) return true; ///Diagonal left
            if (Y[ x ][y+4]==1 && Y[x+1][y+3]==1 && Y[x+2][y+2]==1 && Y[x+3][y+1]==1 && Y[x+4][ y ]==1) return true; ///Diagonal right
        }
    }
    return false;
}

void ClearInputBoard(){
    gotoxy(1,48); printf("                                 ");
    gotoxy(1,49); printf("                                 "); //Clear the board
    gotoxy(1,50); printf("                                 ");
}

void InputO(){
    int x,y;
    ClearInputBoard();

    while ((x<1) || (x>19) || (y<1) || (y>19) || (X[x][y] != 0 || Y[x][y] != 0) ){
        ClearInputBoard();
        gotoxy(1,48); printf(" Turn O");
        gotoxy(1,49); printf(" X = ");  scanf("%d",&x);
        gotoxy(1,50); printf(" Y = ");  scanf("%d",&y);
    }

    XYinput(x,y);
    Y[x][y]=1;

    SetColor(11);
    printf("O");
    SetColor(15);
    ClearInputBoard();

    if (isYwin()) {
        gotoxy(97,28);
        printf("O Win");
        system("pause");
        void EndGame();
        exit(0);
    }
}

void InputX(){  //Similar to InputO()
    int x,y;
    ClearInputBoard();

    while ((x<1) || (x>19) || (y<1) || (y>19) || (X[x][y] != 0 || Y[x][y] != 0) ){
        ClearInputBoard();
        gotoxy(1,48); printf(" Turn X");
        gotoxy(1,49); printf(" X = "); scanf("%d",&x);
        gotoxy(1,50); printf(" Y = "); scanf("%d",&y);
    }
    XYinput(x,y);
    X[x][y]=1;

    SetColor(12);
    printf("X");
    SetColor(15);
    ClearInputBoard();

    if (isXwin()){
        gotoxy(97,28);
        printf("X Win");
        system("pause");
        void EndGame();
        exit(0);
    }
}

void EndGame(){
    char ch;
    gotoxy(30,49);
    printf("Do you want to play again? (y/n)");
    scanf("%c",&ch);
}

void Turn(){
    int turn;

    for (turn=1; turn<=19*19; turn++){
        gotoxy(97,27); printf("         ");
        gotoxy(97,27); printf("Turn %d",turn);

        if (turn%2==1) InputO();
        else           InputX();
    }
}

void X_axis(){
    int x;
    for (x=1; x<10; x++)   { gotoxy((x*4+12),7); printf("0%d",x); }
    for (x=10; x<=19; x++) { gotoxy((x*4+12),7); printf("%d",x);  }
}

void Y_axis(){ //Similar to Y_axis()
    int y;
    for (y=1; y<10; y++)   { gotoxy(13,y*2+7); printf("0%d",y); }
    for (y=10; y<=19; y++) { gotoxy(13,y*2+7); printf("%d",y); }
}

void DisplayBoard(){
    int length, lmax=20, //SIZE 19x19
        width,  wmax=38;

    for(width=1; width<=wmax; width++){
        //I used gotoxy(x,y) to move to board into center of the Background.
        for(length=1; width==1; length++){   //first line
            if (length==1)                 { gotoxy(15,width+7); printf("%c%c",upleft,row); }
            if ((length>1)&&(length<lmax)) { printf("%c%c%c%c",row,row,up,row); }
            if (length==lmax)              { printf("%c%c%c\n",row,row,upright); width++; }
        }

        for(length=1; ((width>1)&&(width<wmax)); length++){
            //Check even or odd width
            for(length=1; width%2==0; length++){     //If even, print line within box
                if (length==1)                { gotoxy(15,width+7); printf("%c",col); }
                if((length>1)&&(length<lmax)) { printf("   %c",col); }
                if (length==lmax)             { printf("   %c\n",col); width++; }
            }

            for(length=1; width%2==1; length++){     //If odd, print line without box
                if (length==1)                 { gotoxy(15,width+7); printf("%c%c",left,row); }
                if((length>1)&&(length<lmax))  { printf("%c%c%c%c",row,row,mid,row); }
                if (length==lmax)              { printf("%c%c%c\n",row,row,right); width++; }
            }
        }

        for(length=1; length<=lmax; length++){  //Fix the last line bug
            if (length==1 || length==wmax){ gotoxy(15,width+7); printf("%c",col); }
            else printf("   %c",col);
        }
        printf("\n");

        for(length=1; width==wmax; length++){   //Print last line
            if (length==1)                 { gotoxy(15,width+8); printf("%c%c",downleft,row); }
            if ((length>1)&&(length<lmax)) { printf("%c%c%c%c",row,row,down,row); }
            if (length==lmax)              { printf("%c%c%c\n",row,row,downright); width++; }
        }
    }
}

void Background(){  //Similar to DisplayBoard()
    int length, lmax=28,
        width,  wmax=52;
    ///Big hollow square
    for(width=1; width<=wmax; width++){
        for(length=1; width==1; length++){
            if (length==1)                 { printf("%c%c",upleft,row); }
            if ((length>1)&&(length<lmax)) { printf("%c%c%c%c",row,row,row,row); }
            if (length==lmax)              { printf("%c%c%c\n",row,row,upright); width++; }
        }

        for(length=1; ((width>1)&&(width<wmax)); length++){
            for(length=1; width%2==0; length++){
                if (length==1)               { printf("%c",col); }
                if((length>1)&&(length<lmax)){ printf("    "); }
                if (length==lmax)            { printf("   %c\n",col); width++; }
            }

            for(length=1; width%2==1; length++){
                if (length==1)                { printf("%c",col); }
                if((length>1)&&(length<lmax)) { printf("    "); }
                if (length==lmax)             { printf("   %c\n",col); width++; }
            }
        }
        for(length=1; width==wmax; length++){
            if (length==1)                { printf("%c%c",downleft,row); }
            if ((length>1)&&(length<lmax)){ printf("%c%c%c%c",row,row,row,row); }
            if (length==lmax)             { printf("%c%c%c\n",row,row,downright); width++; }
        }
    }
    ///Game title
    gotoxy(35,1); printf("  ____  ___  __  __  ___  _  ___   _     ");
    gotoxy(35,2); printf(" / ___|/ _ \\|  \\/  |/ _ \\| |/ / | | | ");
    gotoxy(35,3); printf("| |  _| | | | |\\/| | | | | ' /| | | |   ");
    gotoxy(35,4); printf("| |_| | |_| | |  | | |_| | . \\| |_| |   ");
    gotoxy(35,5); printf(" \\____|\\___/|_|  |_|\\___/|_|\\_\\____/");
    gotoxy(0,0);
}

void DisplayTime(){
    time_t t;
    time(&t);
    gotoxy(70,51);
    printf("%s",ctime(&t));
}

/// Module
void gameFrontEnd(){
    Background();
    X_axis();
    Y_axis();
    DisplayBoard();
    DisplayTime();
}

/// Main
int main(){
    gameFrontEnd();
    gotoxy(0,0);

    Turn();
    InputO();
    InputX();

    //EndGame();
    return 0;
}
