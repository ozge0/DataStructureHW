#include <iostream>
#include<windows.h>
#include<conio.h>
#include <ctime>
#include "Queue.h"

using namespace std;

class Snake{

public:
 Queue<char> yilan;
    char oyunAlani[20][20];
    bool oyunBitti;//oyunun bitisinin kontrolunu saglayacak
    int xKor,yKor,yemXkor,yemYkor,yemBoyutu;
    int yilanX[100],yilanY[100];
    int uzunluk;//queue'den yilanin uzunlugunu tutacak uzunluk=yilan.size();
    char select;//secilen tusu tutacak
    void getDisplay();
    void gameLoop();//kontrolu bu fonksiyon saglayacak
    void baslangic();
    void alanHazirla();//oyun için zemini,yemi ve y?lan? haz?rlayacak
    void veriGirisi();//w a s d tu?lar?n?n giri?ini kontrol edecek
    void hareketEttir();//yilanin hareket etmesini bu sinif ile kontrol edecegiz
    int sayac;//alinan score tutulacak

private:
    int sizeOfTheSnake=uzunluk;
    int counter=sayac;
    int nextSizeUpValue=yemBoyutu;
    void display();//anlik oyunu gosterece
};

///////DÝSPLAY//////
void Snake::display(){// Bu metod alani yazdiracak  
for(int i=0;i<20;i++){
        for(int j=0;j<20;j++){
            cout<<oyunAlani[i][j];
        }cout<<endl;
    }
}
/////END DÝSPLAY//////////////////

////getDisplay////////////////////
void Snake::getDisplay(){//private olan display() metodunu cagirmak icin kullanilacak metod
        display();
}
////END getDisplay///////////////////////////

//////GAMELOOP//////////////
void Snake::gameLoop(){//Oyunun sonlanip sonlanmadigini kontrol ve oyunun yonetildigi metod

    baslangic();
    while(!oyunBitti){
        alanHazirla();
        getDisplay();
        veriGirisi();
        hareketEttir();
        Sleep(100);
    }
    cout<<"SCORE:"<<sayac;
}
////////END GAMELOOP///////////////

/////BASLANGÝC//////////////
void Snake::baslangic(){//Oyun baslamadan gerekli degerlerin atanacagi metod

    oyunBitti=false;//oyunu bitirmek icin kullanilacak
    xKor=5,yKor=5;//y?lan?n ilk baslayacag? konum
    yemXkor=rand()%20,yemYkor=rand()%20;//ilk yemin olusturulacagi koordinat
    yemBoyutu=(1+rand()%5);//1 ile 5 arasýnda bir yem boyutu oluþturur
    sayac=0;//sayac
    uzunluk=0;
    yilan.add(-78);
}
//////END BASLANGÝC///////////////

//////ALANHAZÝRLA///////////////
void Snake::alanHazirla(){//oyun alaninin hazirlanacagi metod
    system("CLS");// konsolu temizler
    for(int i=0; i<20; i++)
    {
        for(int j=0; j<20; j++)
        {
            if(i==yKor && j==xKor){
                oyunAlani[i][j]=-78;
            }
            else if(i==yemYkor && j==yemXkor){
                oyunAlani[i][j]=-78;
            }
            else
            {
                bool print=false;
                for(int k=0;k<uzunluk;k++)
                {
                    if(yilanX[k]==j && yilanY[k]==i)
                    {
                        oyunAlani[i][j]=-78;
                        print=true;
                    }
                }
                    if(!print){
                         oyunAlani[i][j]=-80;
                    }
            }
        }
    } 
}
//////END ALANHAZÝRLA////////////////  

//////VERÝGÝRÝSÝ///////////////////
void Snake::veriGirisi(){//Klavyeden veri alacak metod
    if(_kbhit())//herhangi bir tusa basildiginda buraya girecek
    {
        switch(getch())//basilan tus ile buraya girecek
        {
        case 'a':
            select=97;
            break;
        case 'd':
            select=100;
            break;
        case 'w':
            select=119;
            break;
        case 's':
            select=115;
            break;
        case 'x':
            oyunBitti=true;
            break;
        }
    }
}
/////END VERÝGÝRÝSÝ////////////////

/////HAREKETETTÝR/////////////
void Snake::hareketEttir(){//yilanin hareketlerini ve yeni kuyruk eklenmesini saglayacak metod
    int prevX=yilanX[0];
    int prevY=yilanY[0];
    int prev2X,prev2Y;
    yilanX[0]=xKor;
    yilanY[0]=yKor;

    for(int i=1;i<uzunluk;i++)
    {
        prev2X=yilanX[i];
        prev2Y=yilanY[i];
        yilanX[i]=prevX;
        yilanY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }
    switch(select)
    {
    case 97:
        xKor--;
        break;
    case 100:
        xKor++;
        break;
    case 119:
        yKor--;
        break;
    case 115:
        yKor++;
        break;
    }
    if(xKor>19 || xKor<0 || yKor>19 || yKor<0)
        oyunBitti=true;
    if(xKor>=20)
        xKor=0;
    else if(xKor<0)
        xKor=19;
    if(yKor>=20)
        yKor=0;
    else if(yKor<0)
        yKor=19;

    for(int i=0;i<uzunluk;i++)
    {
        if(yilanX[i]==xKor && yilanY[i]==yKor){
            oyunBitti=true;
        }
    }
    if(xKor==yemXkor && yKor==yemYkor)//yilan yem ile ayni konuma geldiginde yeni kuyruk ve yem olusturacak
    {
        yilan.add(-78);
        srand(time(0));
        sayac+=yemBoyutu;
        yemXkor=rand()%20;
        yemYkor=rand()%20;
        yemBoyutu=(1+rand()%5);
        uzunluk=yilan.size();
    }
}
//////END HAREKET ETTÝR//////////////

int main()
{
    Snake s;
    s.gameLoop();
    return 0;
}

