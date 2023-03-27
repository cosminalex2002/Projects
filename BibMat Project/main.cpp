#pragma GCC diagnostic ignored "-Wwrite-strings"   ///sau faceam peste tot ca la linia 788 in suma_diag_secundara(); //vezi link 1 in link
#include <iostream>
#include <graphics.h>
#include <iostream>
#include <stdio.h>

using namespace std;


struct matriceFloat
{
    int nrLinii;
    int nrColoane;
    float mat[100][100];
};

struct matrice
{
    int nrLinii;
    int nrColoane;
    int mat[100][100];
};

struct vect
{
    int nrElemente;
    int v[101];
};
matrice A,B,C,At;
vect W,a;
vect R,Q;
DWORD screenWidth=GetSystemMetrics(SM_CXSCREEN);
DWORD screenHeight=GetSystemMetrics(SM_CYSCREEN);
void deseneaza_matrice_float(matriceFloat a,int x, int y);
void paginaDespreProiect();
void deciziePagina1();
void inmultire_matrice_cu_sclar();
void adunare_matrice();
void afisareCoordonate();
void buton(char*a, int& yButon, int& yButonPrecedent);
void buton_fara_referinta(char* a, int yButon, int yButonPrecedent);
void centreazaText(char* a, int margineSt, int margineDr, int sus, int jos);
void citire_matrice(matrice& a);
void deciziePagina1();
void deciziePaginaMatrice();
void deciziePaginaVectori();
void deseneaza_matrice(matrice a, int x, int y);
void initializareFereastra();
void initializarePag1();
void inmultire_matrice();
void outintxy(int x, int y, int value);
void paginaMatrici();
void paginaVectori();
void restore(char* a, int x, int y);
void scadere_matrice();
void centreazaText2nivele(char* a, char* b, int margineSt, int margineDr, int sus, int jos);
void buton2nivele(char* a, char* b, int& yButonPrecedent, int& yButon);
void buton2nivele_fara_referinta(char* a, char* b, int yButonPrecedent, int yButon);
void deseneaza_plus(int x, int y);
void deseneaza_egal(int x,int y);
void deseneaza_minus(int x, int y);
void deseneaza_cerc(int x, int y);
void initializeaza_vector(matrice &a,int linii, int coloane, int* p);
void afiseaza_vector_folosind_pointeri(int r, int c, int *ptr);
int determinant(int m, int* p);
void determinant_matrice();
void loading();
void suma_diag_principala();
void suma_deasupra_diag_principala();
void suma_sub_diag_principala();
void suma_diag_secundara();
void suma_deasupra_diag_secundara();
void suma_sub_diag_secundara();
void arata_optiuni();
void decizieOptiuni();
void restore2niveleOptiuni(char* a, char* b, int stanga, int dreapta, int sus, int jos,int color);
void transpusa();
void initializeaza_vector_transpusa(matrice &A,int linii, int coloane, int* p, matrice &At, int &det);
void inversa();
void shiftStangaKpozitii();
void shiftDreaptaKpozitii();
void shiftStanga_1poz(vect &a,int k,int &primul);
void shiftDreapta_1poz(vect &a,int k,int &ultimul);
void sortareCrescatoare();
void sortareDescrescatoare();
void adunare_2_vectori();
void inmultire_vector_cu_scalar();

int main()
{
    initializareFereastra();

    initializarePag1();


    //afisareCoordonate();

    getch();
    closegraph();

    return 0;
}

void citire_vector(vect &l)
{
    cout<<"Introduceti dimensiunea vectorului:";
    cin>>l.nrElemente;
    cout<<endl;
    for( int i=1; i<=l.nrElemente; i++)
    {
        cout<<"Element vect["<<i<<"] :";
        cin>>l.v[i];
    }
}
void incadrare_int_in_casuta(int x,int xCont,int yCont)
{
    if(x<10&&x>=0)
    {
        outintxy(xCont+30,yCont+30,x);
    }
    if(x>9&&x<100)
    {
        outintxy(xCont+20,yCont+30,x);
    }
    if(x>99&&x<1000)
    {
        outintxy(xCont+17,yCont+30,x);
    }
    if(x>999&&x<10000)
    {
        outintxy(xCont+8,yCont+30,x);
    }
    if(x<0&&x>=-9)
    {
        outintxy(xCont+30,yCont+30,x);
    }
    if(x<-9&&x>-100)
    {
        outintxy(xCont+12,yCont+30,x);
    }
    if(x<-99&&x>-1000)
    {
        outintxy(xCont+2,yCont+30,x);
    }
}

void modificare_p(int &p, int x)
{
    if(x<10&&x>0||x<0&&x>-10)
    {
        p+=30;
    }
    if(x<100&&x>9||x<-9&&x>-100)
    {
        p+=55;
    }
    if(x<1000&&x>99||x<-99&&x>-1000)
    {
        p+=65;
    }
    if(x<10000&&x>999)
    {
        p+=85;
    }
}
void deseneaza_vector(vect &l, int x, int y)
{
    settextstyle(1,0,2);
    int xCont=x;
    int yCont=y;
    if(l.nrElemente<=16)
    {
        for(int i=1; i<=l.nrElemente; i++)
        {
            rectangle(xCont,yCont,xCont+80,yCont+80);
            incadrare_int_in_casuta(l.v[i],xCont,yCont);
            xCont+=80;
        }
    }
    else
    {
        for(int i=1; i<=7; i++)
        {
            rectangle(xCont,yCont,xCont+80,yCont+80);
            incadrare_int_in_casuta(l.v[i],xCont,yCont);
            xCont+=80;
        }
        settextstyle(0,0,4);
        outtextxy(2+x+80*7, y+50,".....");
        settextstyle(1,0,2);
        xCont=x+80*7+2*80;
        int cont=l.nrElemente-5;///desenam ultimele 6 patratele
        for(int i=cont; i<=l.nrElemente; i++)
        {
            rectangle(xCont,yCont,xCont+80,yCont+80);
            incadrare_int_in_casuta(l.v[i],xCont,yCont);
            xCont+=80;
        }
        line(x+80*7,y,x+80*7+80*2,y);///linia de sus de la ....
        line(x+80*7,y+80,x+80*7+80*2,y+80);///linia de jos
    }
}



void adunare_2_vectori()
{
    settextstyle(1,0,3);
    outtextxy(100,70,"Introduceti in consola elementele primului vector");

    setcolor(WHITE);
    settextstyle(1,0,2);
    citire_vector(W);
    delay(1500);
    bar(0,0,900,120);
    settextstyle(1,0,3);
    outtextxy(70,97,"V : ");
    settextstyle(1,0,2);
    deseneaza_vector(W,150,70);
    outtextxy(70,170,"Numarul elementelor:");
    outintxy(380,170,W.nrElemente);
    delay(1000);

    settextstyle(1,0,3);
    outtextxy(100,220,"Introduceti in consola elementele celui de al doilea vector");

    setcolor(WHITE);
    settextstyle(1,0,2);
    citire_vector(Q);
    delay(1500);
    bar(0,200,1100,320);
    settextstyle(1,0,3);
    outtextxy(70,297,"W : ");
    settextstyle(1,0,2);
    deseneaza_vector(Q,150,270);
    outtextxy(70,370,"Numarul elementelor:");
    outintxy(380,370,Q.nrElemente);
    delay(1000);

    if(W.nrElemente!=Q.nrElemente)
    {
        outtextxy(300,470,"Vectorii nu se pot aduna deoarece nu au acelasi numar de elemente");
    }
    else
    {
        outtextxy(20,497,"V + W :");
        for(int i=1;i<=Q.nrElemente;i++)
        {
            R.v[i]=Q.v[i]+W.v[i];
        }
        R.nrElemente=Q.nrElemente;
        deseneaza_vector(R,150,470);
        outtextxy(70,570,"Numarul elementelor:");
        outintxy(380,570,Q.nrElemente);
        delay(1000);
        settextstyle(1,0,3);
        outtextxy(20,650,"Adunarea vectorilor se realizeaza astfel:");
        delay(1000);
        int xa=150;
        int ya=70;
        int xb=150;
        int yb=270;
        int xc=150;
        int yc=470;
        if(Q.nrElemente<=16)
        {
            for(int i=1;i<=W.nrElemente;i++)
            {
                int p=700;
                setcolor(RED);
                rectangle(xa,ya,xa+80,ya+80);
                setcolor(WHITE);
                outintxy(p,650,W.v[i]);
                modificare_p(p,W.v[i]);
                delay(800);
                outtextxy(p,650,"+");
                p+=30;
                delay(800);

                setcolor(RED);
                rectangle(xb,yb,xb+80,yb+80);
                setcolor(WHITE);
                outintxy(p,650,Q.v[i]);
                modificare_p(p,Q.v[i]);
                delay(800);
                outtextxy(p,650,"=");
                p+=30;

                delay(800);
                setcolor(RED);
                rectangle(xc,yc,xc+80,yc+80);
                setcolor(WHITE);
                outintxy(p,650,R.v[i]);
                modificare_p(p,R.v[i]);
                delay(800);

                setcolor(WHITE);
                rectangle(xa,ya,xa+80,ya+80);
                rectangle(xb,yb,xb+80,yb+80);
                rectangle(xc,yc,xc+80,yc+80);
                setcolor(BLACK);
                bar(700,600,1100,800);
                xa+=80;
                xb+=80;
                xc+=80;
                delay(800);
            }
            setcolor(BLACK);
            bar(20,600,1100,800);
            setcolor(WHITE);

        }
        else
        {
            for(int i=1;i<=7;i++)
            {
                int p=700;
                setcolor(RED);
                rectangle(xa,ya,xa+80,ya+80);
                setcolor(WHITE);
                outintxy(p,650,W.v[i]);
                modificare_p(p,W.v[i]);
                delay(800);
                outtextxy(p,650,"+");
                p+=30;

                delay(800);
                setcolor(RED);
                rectangle(xb,yb,xb+80,yb+80);
                setcolor(WHITE);
                outintxy(p,650,Q.v[i]);
                modificare_p(p,Q.v[i]);
                delay(800);
                outtextxy(p,650,"=");
                p+=30;

                delay(800);
                setcolor(RED);
                rectangle(xc,yc,xc+80,yc+80);
                setcolor(WHITE);
                outintxy(p,650,R.v[i]);
                modificare_p(p,R.v[i]);
                delay(800);

                setcolor(WHITE);
                rectangle(xa,ya,xa+80,ya+80);
                rectangle(xb,yb,xb+80,yb+80);
                rectangle(xc,yc,xc+80,yc+80);
                setcolor(BLACK);
                bar(700,600,1100,800);
                xa+=80;
                xb+=80;
                xc+=80;
                delay(800);
            }
            int cont=W.nrElemente-5;
            xa+=160;
            xb+=160;
            xc+=160;
            for(int i=cont;i<=W.nrElemente;i++)
            {
                int p=700;
                setcolor(RED);
                rectangle(xa,ya,xa+80,ya+80);
                setcolor(WHITE);
                outintxy(p,650,W.v[i]);
                modificare_p(p,W.v[i]);
                delay(800);
                outtextxy(p,650,"+");
                p+=30;

                delay(800);
                setcolor(RED);
                rectangle(xb,yb,xb+80,yb+80);
                setcolor(WHITE);
                outintxy(p,650,Q.v[i]);
                modificare_p(p,Q.v[i]);
                delay(800);
                outtextxy(p,650,"=");
                p+=30;

                delay(800);
                setcolor(RED);
                rectangle(xc,yc,xc+80,yc+80);
                setcolor(WHITE);
                outintxy(p,650,R.v[i]);
                modificare_p(p,R.v[i]);
                delay(800);

                setcolor(WHITE);
                rectangle(xa,ya,xa+80,ya+80);
                rectangle(xb,yb,xb+80,yb+80);
                rectangle(xc,yc,xc+80,yc+80);
                setcolor(BLACK);
                bar(700,600,1100,800);
                xa+=80;
                xb+=80;
                xc+=80;
                delay(800);
            }
            setcolor(BLACK);
            bar(20,600,1100,800);
            setcolor(WHITE);
        }
    }

}






void inmultire_vector_cu_scalar()
{
    settextstyle(1,0,3);
    outtextxy(100,100,"Introduceti in consola elementele vectorului");

    setcolor(BLACK);
    setcolor(WHITE);
    settextstyle(1,0,2);
    citire_vector(W);
    delay(1000);

    bar(0,50,900,200);
    settextstyle(1,0,3);
    outtextxy(75,177,"V : ");
    settextstyle(1,0,2);
    deseneaza_vector(W,150,150);
    delay(1000);

    settextstyle(1,0,3);
    outtextxy(150,300,"Introduceti in consola scalarul");
    cout<<"Introduceti scalarul:";
    int scalar;
    cin>>scalar;
    delay(1000);
    setcolor(BLACK);
    bar(50,250,650,350);
    setcolor(WHITE);
    settextstyle(1,0,2);
    rectangle(150,300,230,380);
    incadrare_int_in_casuta(scalar,150,300);
    settextstyle(1,0,3);
    outtextxy(5,325,"Scalar : ");
    settextstyle(1,0,2);
    delay(1000);

    for(int i=1;i<=W.nrElemente;i++)
    {
        Q.v[i]=scalar*W.v[i];
    }
    Q.nrElemente=W.nrElemente;
    outtextxy(5,475,"Scalar*V:");
    delay(1000);
    deseneaza_vector(Q,150,450);
    delay(1000);
    settextstyle(1,0,3);
    outtextxy(50,600,"Inmultirea se realizeaza astfel:");
    delay(1000);
    int xa=150;
    int ya=150;
    int xc=150;
    int yc=450;
    if(W.nrElemente<=16)
    {
        for(int i=1;i<=W.nrElemente;i++)
        {
            int p=570;
            setcolor(GREEN);
            rectangle(xa,ya,xa+80,ya+80);
            setcolor(WHITE);
            outintxy(p,600,W.v[i]);
            modificare_p(p,W.v[i]);
            delay(800);
            outtextxy(p,600,"*");
            p+=30;
            delay(800);

            setcolor(GREEN);
            rectangle(150,300,150+80,300+80);
            setcolor(WHITE);
            outintxy(p,600,scalar);
            modificare_p(p,scalar);
            delay(800);
            outtextxy(p,600,"=");
            p+=30;

            delay(800);
            setcolor(GREEN);
            rectangle(xc,yc,xc+80,yc+80);
            setcolor(WHITE);
            outintxy(p,600,Q.v[i]);
            modificare_p(p,Q.v[i]);
            delay(800);

            setcolor(WHITE);
            rectangle(xa,ya,xa+80,ya+80);
            rectangle(150,300,150+80,300+80);
            rectangle(xc,yc,xc+80,yc+80);
            setcolor(BLACK);
            bar(550,550,1100,800);
            xa+=80;
            xc+=80;
            delay(800);
        }
    }
    else
    {
        for(int i=1;i<=7;i++)
        {
            int p=570;
            setcolor(GREEN);
            rectangle(xa,ya,xa+80,ya+80);
            setcolor(WHITE);
            outintxy(p,600,W.v[i]);
            modificare_p(p,W.v[i]);
            delay(800);
            outtextxy(p,600,"*");
            p+=30;
            delay(800);

            setcolor(GREEN);
            rectangle(150,300,150+80,300+80);
            setcolor(WHITE);
            outintxy(p,600,scalar);
            modificare_p(p,scalar);
            delay(800);
            outtextxy(p,600,"=");
            p+=30;

            delay(800);
            setcolor(GREEN);
            rectangle(xc,yc,xc+80,yc+80);
            setcolor(WHITE);
            outintxy(p,600,Q.v[i]);
            modificare_p(p,Q.v[i]);
            delay(800);

            setcolor(WHITE);
            rectangle(xa,ya,xa+80,ya+80);
            rectangle(150,300,150+80,300+80);
            rectangle(xc,yc,xc+80,yc+80);
            setcolor(BLACK);
            bar(550,550,1100,800);
            xa+=80;
            xc+=80;
            delay(800);
        }
        xa+=160;
        xc+=160;
        int cont=W.nrElemente-5;
        for(int i=cont;i<=W.nrElemente;i++)
        {
            int p=570;
            setcolor(GREEN);
            rectangle(xa,ya,xa+80,ya+80);
            setcolor(WHITE);
            outintxy(p,600,W.v[i]);
            modificare_p(p,W.v[i]);
            delay(800);
            outtextxy(p,600,"*");
            p+=30;
            delay(800);

            setcolor(GREEN);
            rectangle(150,300,150+80,300+80);
            setcolor(WHITE);
            outintxy(p,600,scalar);
            modificare_p(p,scalar);
            delay(800);
            outtextxy(p,600,"=");
            p+=30;

            delay(800);
            setcolor(GREEN);
            rectangle(xc,yc,xc+80,yc+80);
            setcolor(WHITE);
            outintxy(p,600,Q.v[i]);
            modificare_p(p,Q.v[i]);
            delay(800);

            setcolor(WHITE);
            rectangle(xa,ya,xa+80,ya+80);
            rectangle(150,300,150+80,300+80);
            rectangle(xc,yc,xc+80,yc+80);
            setcolor(BLACK);
            bar(550,550,1100,800);
            xa+=80;
            xc+=80;
            delay(800);
        }


        setcolor(BLACK);
        bar(20,600,1100,800);
        setcolor(WHITE);
}
}










void shiftStangaKpozitii()
{
    settextstyle(1,0,3);
    outtextxy(50,100,"Introduceti in consola elementele vectorului si apoi cate elemente doriti sa fie shiftate");

    setcolor(WHITE);
    settextstyle(1,0,2);
    citire_vector(a);
    //delay(1500);

    int k;
    cout<<endl;
    cout<<"Cate elemente doriti sa fie shiftate? ";
    cin>>k;
    bar(0,50,screenWidth-100,200);
    settextstyle(1,0,3);
    outtextxy(70,177,"V : ");
    settextstyle(1,0,2);
    int xVector=150;
    int yVector=150;
    deseneaza_vector(a,xVector,yVector);
    delay(1000);

    char digit_string[20];
    sprintf(digit_string, "%d", k);

    outtextxy(50,447,"Shiftare cu");


    if(k==1)
    {
        outtextxy(50+textwidth("Shiftare cu")+10,447,"o");
        outtextxy(50+textwidth("Shiftare cu")+textwidth("o")+10+10,447,"pozitie");///de 2 ori +10 pentru ca trebuie sa trecem si de spatiul dintre "shiftare cu" si "o"
    }
    else
    {
        outintxy(50+textwidth("Shiftare cu")+10,447,k);
        outtextxy(50+textwidth("Shiftare cu")+textwidth(digit_string)+20,447,"pozitii");
    }

    if(k>a.nrElemente)
    {
        int xEroare=50+textwidth("Shiftare cu")+textwidth(digit_string)+20+textwidth("pozitii");
        setcolor(CYAN);
        outtextxy(xEroare+15,447,"Eroare! => Numarul introdus depaseste dimensiune vectorului!!");
        return;
    }
    ///de facut cazul pentru >16 si de facut tot la fel pentru shiftare la dreapta
    int xdes=xVector;
    int ydes=yVector;

    int primul=0;
    int aux[100];
    for(int i=1; i<=a.nrElemente; i++)
        aux[i]=a.v[i];
    if(a.nrElemente<=16)
    {
        for(int i=1; i<=k; i++)
        {
            int n=a.nrElemente;

            setcolor(CYAN);
            rectangle(xdes,ydes+100,xdes+80,ydes+180);
            bar(xdes+1,ydes+101,xdes+79,ydes+179);
            incadrare_int_in_casuta(a.v[1],xdes,ydes+100);
            delay(1000);

            int salvat=a.v[1];

            shiftStanga_1poz(a,1,primul);
            setcolor(WHITE);
            bar(xdes,ydes,xdes+80*a.nrElemente,ydes+80);///curat spatiul unde era vectorul

            deseneaza_vector(a,xdes,ydes); ///in a este vectorul shiftat partial (fara sa punem primul element pe ultima pozitie)
            delay(1000);

            a.v[n]=aux[i];//se poate folosi si asa cu incadrare_int_in_casuta(a.v[n],xdes+(a.nrElemente-1)*80,ydes);

            setcolor(CYAN);
            rectangle(xdes+(a.nrElemente-1)*80,ydes,xdes+(a.nrElemente)*80,ydes+80);
            bar(xdes+(a.nrElemente-1)*80+1,ydes+1,xdes+(a.nrElemente)*80,ydes+80);///curat ce numar este acolo;
            incadrare_int_in_casuta(primul,xdes+(a.nrElemente-1)*80,ydes);
            delay(1000);

            setcolor(WHITE);
            rectangle(xdes+(a.nrElemente-1)*80,ydes,xdes+(a.nrElemente)*80,ydes+80);
            delay(1000);

            setcolor(WHITE);
            bar(xdes+1,ydes+101,xdes+79,ydes+179);
            incadrare_int_in_casuta(salvat,xdes,ydes+100);
            delay(2000);
        }

        setcolor(WHITE);
        deseneaza_vector(a,xdes,ydes);
        bar(xdes,ydes+100,xdes+80+1,ydes+180+1);///sterg casuta de jos unde se salveaza primul numar

        int yMesaj=447+textheight("Shiftare cu")+20;

        outtextxy(50,yMesaj,"Vectorul a fost shiftat cu");
        if(k==1)
        {
            outtextxy(50+textwidth("Vectorul a fost shiftat cu")+10,yMesaj,"o");
            int xMesaj=50+textwidth("Vectorul a fost shiftat cu")+textwidth("o")+20;
            outtextxy(xMesaj,yMesaj,"pozitie");
        }
        else
        {
            outintxy(50+textwidth("Vectorul a fost shiftat cu")+10,yMesaj,k);
            int xMesaj=50+textwidth("Vectorul a fost shiftat cu")+textwidth(digit_string)+20;
            outtextxy(xMesaj,yMesaj,"pozitii");
        }
    }
    else if(a.nrElemente>16)
    {

        int xDupaPuncte=xVector+80*7+2*80;
        int xUltimaCasuta=xDupaPuncte+80*5;///*5 pentru ca fac mereu 6 patrate dupa ....

        for(int i=1; i<=k; i++)
        {
            int n=a.nrElemente;

            setcolor(CYAN);
            rectangle(xdes,ydes+100,xdes+80,ydes+180);
            bar(xdes+1,ydes+101,xdes+79,ydes+179);
            incadrare_int_in_casuta(a.v[1],xdes,ydes+100);
            delay(1000);

            int salvat=a.v[1];

            shiftStanga_1poz(a,1,primul);
            setcolor(WHITE);
            bar(xdes,ydes,xdes+80*16,ydes+80);///curat spatiul unde era vectorul

            deseneaza_vector(a,xdes,ydes); ///in a este vectorul shiftat partial (fara sa punem primul element pe ultima pozitie)
            delay(1000);

            a.v[n]=aux[i];//se poate folosi si asa cu incadrare_int_in_casuta(a.v[n],xdes+(a.nrElemente-1)*80,ydes);

            setcolor(CYAN);
            rectangle(xUltimaCasuta,ydes,xUltimaCasuta+80,ydes+80);
            bar(xUltimaCasuta+1,ydes+1,xUltimaCasuta+79,ydes+79);///curat ce numar este acolo;
            incadrare_int_in_casuta(primul,xUltimaCasuta,ydes);
            delay(1000);

            setcolor(WHITE);
            rectangle(xUltimaCasuta,ydes,xUltimaCasuta+80,ydes+80);
            delay(1000);

            setcolor(WHITE);
            bar(xdes+1,ydes+101,xdes+79,ydes+179);///curat ce era in casuta de jos
            incadrare_int_in_casuta(salvat,xdes,ydes+100);
            delay(2000);

        }
        setcolor(WHITE);
        deseneaza_vector(a,xdes,ydes);
        bar(xdes,ydes+100,xdes+80+1,ydes+180+1);

        int yMesaj=447+textheight("Shiftare cu")+20;
        outtextxy(50,yMesaj,"Vectorul a fost shiftat cu");
        if(k==1)
        {
            outtextxy(50+textwidth("Vectorul a fost shiftat cu")+10,yMesaj,"o");
            int xMesaj=50+textwidth("Vectorul a fost shiftat cu")+textwidth("o")+20;
            outtextxy(xMesaj,yMesaj,"pozitie");
        }
        else
        {
            outintxy(50+textwidth("Vectorul a fost shiftat cu")+10,yMesaj,k);
            int xMesaj=50+textwidth("Vectorul a fost shiftat cu")+textwidth(digit_string)+20;
            outtextxy(xMesaj,yMesaj,"pozitii");
        }

    }
}

void shiftStanga_1poz(vect &a,int k,int &primul)
{
    primul=a.v[1];
    for(int i=1; i<a.nrElemente; i++)
        a.v[i]=a.v[i+1];

}






void shiftDreaptaKpozitii()
{
    settextstyle(1,0,3);
    outtextxy(50,100,"Introduceti in consola elementele vectorului si apoi cate elemente doriti sa fie shiftate");

    setcolor(WHITE);
    settextstyle(1,0,2);
    citire_vector(a);
    //delay(1500);

    int k;
    cout<<endl;
    cout<<"Cate elemente doriti sa fie shiftate? ";
    cin>>k;
    bar(0,50,screenWidth-100,200);
    settextstyle(1,0,3);
    outtextxy(70,177,"V : ");
    settextstyle(1,0,2);
    int xVector=150;
    int yVector=150;
    deseneaza_vector(a,xVector,yVector);
    delay(1000);

    char digit_string[20];
    sprintf(digit_string, "%d", k);

    outtextxy(50,447,"Shiftare cu");

    if(k==1)
    {
        outtextxy(50+textwidth("Shiftare cu")+10,447,"o");
        outtextxy(50+textwidth("Shiftare cu")+textwidth("o")+10+10,447,"pozitie");///de 2 ori +10 pentru ca trebuie sa trecem si de spatiul dintre "shiftare cu" si "o"
    }
    else
    {
        outintxy(50+textwidth("Shiftare cu")+10,447,k);
        outtextxy(50+textwidth("Shiftare cu")+textwidth(digit_string)+20,447,"pozitii");
    }

    if(k>a.nrElemente)
    {
        int xEroare=50+textwidth("Shiftare cu")+textwidth(digit_string)+20+textwidth("pozitii");
        setcolor(CYAN);
        outtextxy(xEroare+15,447,"Eroare! => Numarul introdus depaseste dimensiune vectorului!!");
        return;
    }

    int xdes=xVector;
    int ydes=yVector;

    int ultimul=0;
    int aux[100];
    for(int i=1; i<=a.nrElemente; i++)
        aux[i]=a.v[i];
    if(a.nrElemente<=16)
    {
        for(int i=1; i<=k; i++)
        {
            int n=a.nrElemente;

            setcolor(BLUE);///fac casuta in care se salveaza elementul care trebuie mutat
            rectangle(xdes+(n-1)*80,ydes+100,xdes+n*80,ydes+180);
            bar(xdes+(n-1)*80+1,ydes+101,xdes+n*80-1,ydes+180-1);
            incadrare_int_in_casuta(a.v[n],xdes+(n-1)*80,ydes+100);
            delay(1000);

            int salvat=a.v[n];

            shiftDreapta_1poz(a,1,ultimul);
            setcolor(WHITE);
            bar(xdes,ydes,xdes+80*a.nrElemente,ydes+80);///curat spatiul unde era vectorul

            deseneaza_vector(a,xdes,ydes); ///in a este vectorul shiftat partial (fara sa punem primul element pe ultima pozitie)
            delay(1000);

            a.v[1]=ultimul;//se poate scrie si a.v[1]=aux[n-i+1]

            setcolor(BLUE);
            rectangle(xdes,ydes,xdes+80,ydes+80);
            bar(xdes+1,ydes+1,xdes+80-1,ydes+80-1);///curat ce numar este in prima casuta;
            incadrare_int_in_casuta(ultimul,xdes,ydes);
            delay(1000);

            setcolor(WHITE);///refac prima casuta alba
            rectangle(xdes,ydes,xdes+80,ydes+80);
            delay(1000);

            setcolor(WHITE);
            bar(xdes+80*(n-1)+1,ydes+100+1,xdes+80*n-1,ydes+180-1);///curat ce era in casuta de jos
            incadrare_int_in_casuta(salvat,xdes+80*(n-1),ydes+100);
            delay(2000);

        }

        setcolor(WHITE);
        deseneaza_vector(a,xdes,ydes);
        bar(xdes+(a.nrElemente-1)*80,ydes+100,xdes+a.nrElemente*80+1,ydes+180+1);///sterg casuta in care se salveaza ultimul element

        int yMesaj=447+textheight("Shiftare cu")+20;

        outtextxy(50,yMesaj,"Vectorul a fost shiftat cu");
        if(k==1)
        {
            outtextxy(50+textwidth("Vectorul a fost shiftat cu")+10,yMesaj,"o");
            int xMesaj=50+textwidth("Vectorul a fost shiftat cu")+textwidth("o")+20;
            outtextxy(xMesaj,yMesaj,"pozitie");
        }
        else
        {
            outintxy(50+textwidth("Vectorul a fost shiftat cu")+10,yMesaj,k);
            int xMesaj=50+textwidth("Vectorul a fost shiftat cu")+textwidth(digit_string)+20;
            outtextxy(xMesaj,yMesaj,"pozitii");
        }
    }
    else if(a.nrElemente>16)
    {

        int xDupaPuncte=xVector+80*7+2*80;
        int xUltimaCasuta=xDupaPuncte+80*5;///*5 pentru ca fac mereu 6 patrate dupa ....

        for(int i=1; i<=k; i++)
        {
            int n=a.nrElemente;

            setcolor(BLUE);///fac casuta de sub ultimul element
            rectangle(xUltimaCasuta,ydes+100,xUltimaCasuta+80,ydes+180);
            bar(xUltimaCasuta+1,ydes+100+1,xUltimaCasuta+80-1,ydes+180-1);///curat ce era in casuta de jos
            incadrare_int_in_casuta(a.v[n],xUltimaCasuta,ydes+100);
            delay(1000);

            int salvat=a.v[n];

            shiftDreapta_1poz(a,1,ultimul);
            setcolor(WHITE);
            bar(xdes,ydes,xdes+80*16,ydes+80);///curat spatiul unde era vectorul

            deseneaza_vector(a,xdes,ydes); ///in a este vectorul shiftat partial (fara sa punem ultimul element pe prima pozitie)
            delay(1000);

            a.v[1]=ultimul;

            setcolor(BLUE);
            rectangle(xdes,ydes,xdes+80,ydes+80);
            bar(xdes+1,ydes+1,xdes+80-1,ydes+80-1);///curat ce numar este in prima casuta;
            incadrare_int_in_casuta(ultimul,xdes,ydes);
            delay(1000);

            setcolor(WHITE);
            rectangle(xdes,ydes,xdes+80,ydes+80);
            delay(1000);

            setcolor(WHITE);
            bar(xUltimaCasuta+1,ydes+100+1,xUltimaCasuta+80-1,ydes+180-1);///curat ce era in casuta de jos
            incadrare_int_in_casuta(salvat,xUltimaCasuta,ydes+100);
            delay(2000);


        }
        setcolor(WHITE);
        deseneaza_vector(a,xdes,ydes);
        bar(xdes+(a.nrElemente-1)*80,ydes+100,xdes+a.nrElemente*80+1,ydes+180+1);///sterg casuta in care se salveaza ultimul element

        int yMesaj=447+textheight("Shiftare cu")+20;
        outtextxy(50,yMesaj,"Vectorul a fost shiftat cu");
        if(k==1)
        {
            outtextxy(50+textwidth("Vectorul a fost shiftat cu")+10,yMesaj,"o");
            int xMesaj=50+textwidth("Vectorul a fost shiftat cu")+textwidth("o")+20;
            outtextxy(xMesaj,yMesaj,"pozitie");
        }
        else
        {
            outintxy(50+textwidth("Vectorul a fost shiftat cu")+10,yMesaj,k);
            int xMesaj=50+textwidth("Vectorul a fost shiftat cu")+textwidth(digit_string)+20;
            outtextxy(xMesaj,yMesaj,"pozitii");
        }

    }
}

void shiftDreapta_1poz(vect &a,int k,int &ultimul)
{
    ultimul=a.v[a.nrElemente];
    for(int i=a.nrElemente; i>1; i--)
        a.v[i]=a.v[i-1];
}




void sortareCrescatoare()
{
    settextstyle(1,0,3);
    outtextxy(50,100,"Introduceti in consola elementele vectorului");

    setcolor(WHITE);
    settextstyle(1,0,2);
    citire_vector(a);

    bar(0,50,screenWidth-100,200);
    settextstyle(1,0,3);
    outtextxy(70,177,"V : ");
    settextstyle(1,0,2);
    int xVector=150;
    int yVector=150;
    deseneaza_vector(a,xVector,yVector);
    delay(1000);

    int schimbare_are_loc=0,i,j;
    int n=a.nrElemente;
    if(n<=16)
    {
        for(i=1; i<=n-1; i++)
        {
            int index_minim=i;
            int nrMin=a.v[index_minim];

            setcolor(LIGHTMAGENTA);
            setlinestyle(DASHED_LINE,0,1);
            line(xVector+(i-1)*80,yVector-15,xVector+(i-1)*80,yVector+80+15);///fac linia punctata
            delay(1500);///desenez linia, pun delay, dupa refac linia punctata fara delay, (de ce? pentru ca vreau sa para ca patratul albastru nu se deseneaza pe linia punctata -> de fapt in spate se deseneaza patratul albastru si dupa refac linia punctata)

            settextstyle(SANS_SERIF_FONT,HORIZ_DIR,1);///fac textele din stanga si dreapta liniei punctate;
            char* s1="Vector sortat";
            char* s2="Vector nesortat";
            outtextxy(xVector+(i-1)*80-textwidth(s1)-10,yVector-15-textheight(s1)/2,s1);
            delay(500);
            outtextxy(xVector+(i-1)*80+10,yVector-15-textheight(s2)/2,s2);
            delay(2000);


            settextstyle(1,0,3);
            setlinestyle(0,0,0);///refac linestyle pentru desenarile viitoare

            setcolor(BLUE);
            rectangle(xVector+(i-1)*80,yVector,xVector+i*80,yVector+80);///fac primul albastru


            setcolor(LIGHTMAGENTA);
            setlinestyle(DASHED_LINE,0,1);
            line(xVector+(i-1)*80,yVector-15,xVector+(i-1)*80,yVector+80+15);///refac linia punctata pentru ca atunci cand am desenat patratul albastru (liniile de mai sus) s-a suprapus latura din stanga a patratului peste linia punctata

            setlinestyle(0,0,0);///refac linestyle pentru desenarile viitoare

            setcolor(BLUE);
            rectangle(xVector+(i-1)*80,yVector+100,xVector+i*80,yVector+180);///il fac pe cel de sub
            incadrare_int_in_casuta(a.v[index_minim],xVector+(i-1)*80,yVector+100);///pun numarul in
            delay(1000);

            bar(xVector+(i-1)*80-1,yVector+100-1,xVector+i*80+1,yVector+180+1);///il sterg pe cel de sub

            for(j=i+1; j<=n; j++)
            {

                if(a.v[j]<a.v[index_minim])
                {
                    schimbare_are_loc=1;

                    setcolor(GREEN);
                    rectangle(xVector+(j-1)*80,yVector,xVector+j*80,yVector+80); ///fac patratul al j-lea verde
                    delay(1000);

                    rectangle(xVector+(j-1)*80,yVector+100,xVector+j*80,yVector+180); ///il fac pe cel de sub
                    incadrare_int_in_casuta(a.v[index_minim],xVector+(j-1)*80,yVector+100);///pun minimul de dinainte
                    delay(2000);

                    ///sterg ce era in casuta de jos
                    index_minim=j;
                    nrMin=a.v[index_minim];

                    bar(xVector+(j-1)*80+1,yVector+100+1,xVector+j*80-1,yVector+180-1); ///sterg ce era in patrtul de jos
                    incadrare_int_in_casuta(a.v[index_minim],xVector+(j-1)*80,yVector+100); ///pun minimul actualizat
                    delay(1000);

                }
                else if(a.v[j]>nrMin)
                {
                    setcolor(RED);
                    rectangle(xVector+(j-1)*80,yVector,xVector+j*80,yVector+80);///fac patratul al j-lea rosu pt ca nu indeplineste conditia
                    delay(1000);

                    rectangle(xVector+(j-1)*80,yVector+100,xVector+j*80,yVector+180);///il fac pe cel de sub
                    incadrare_int_in_casuta(a.v[index_minim],xVector+(j-1)*80,yVector+100);///pun minimul de dinainte
                    delay(2000);
                }

                setcolor(WHITE);
                rectangle(xVector+(j-1)*80,yVector,xVector+j*80,yVector+80);///refac patratul al j-lea alb
                bar(xVector+(j-1)*80-1,yVector+100-1,xVector+j*80+1,yVector+180+1);///sterg patratul de jos
                delay(1000);

                //deseneaza_vector(a,xVector,yVector);
            }

            swap(a.v[index_minim],a.v[i]);

            if(schimbare_are_loc==1)
            {
                setcolor(WHITE);
                outtextxy(xVector,yVector+300,"Va rugam asteptati, se interschimba elementele...");
                delay(2000);

                bar(xVector,yVector+300,xVector+textwidth("Va rugam asteptati, se interschimba elementele..."),yVector+300+textheight("Va rugam"));
            }
            schimbare_are_loc=0;
            bar(xVector+(i-1)*80,yVector,xVector+i*80,yVector+80);///sterg orice era in patratul i, acolo unde are loc interschimbarea cu minimul gasit
            bar(xVector+(index_minim-1)*80,yVector,xVector+index_minim*80,yVector+80);///sterg orice era in patratul j,acolo unde are loc interschimbarea -> se putea si fara la ord cresc pentru ca un numar mai mic vine peste un numar mai mare (care l-am sters deja mai sus), iar cel mai mare(de obicei mai mare si in lungime, latime) il suprascrie pe cel mai mic
            deseneaza_vector(a,xVector,yVector);


            setcolor(WHITE);
            rectangle(xVector+(i-1)*80,yVector,xVector+i*80,yVector+80);///refac culoarea alb patratului alb
            delay(1000);

            setcolor(BLACK);
            setlinestyle(DASHED_LINE,0,3);
            line(xVector+(i-1)*80,yVector-15,xVector+(i-1)*80,yVector+80+15);///fac linia punctata sa nu se vada

            bar(0,0,screenWidth-100,yVector-1);///sterg textele


            setlinestyle(0,0,0); ///refac linestyle pentru desenarile viitoare
            setcolor(WHITE);///refac  linia din stanga a patratului i pentru ca linia magenta fiind fix pe deasupra ei, se sterge (cine? linia dinstanga patratului i) cand o fac neagra si raman doar niste punctulete albe in loc de linie(operatie facuta mai sus)
            line(xVector+(i-1)*80,yVector,xVector+(i-1)*80,yVector+80);

            rectangle(xVector,yVector,xVector+a.nrElemente*80,yVector+80);///cand se sterge linia punctata raman niste spatii intre casute, asa ca desenez inca o data linia de sus si de jos a vectorului
        }
    }
    else if(n>16)
    {
        for(int i=1;i<=n-1;i++)
            for(int j=i+1;j<=n;j++)
                if(a.v[i]>a.v[j])
                    swap(a.v[i],a.v[j]);
        delay(2000);
        bar(xVector,yVector,screenWidth-100,screenHeight);

        outtextxy(xVector,yVector+300,"Va rugam asteptati, se interschimba elementele...");
        delay(2000);
         bar(xVector,yVector+300,xVector+textwidth("Va rugam asteptati, se interschimba elementele..."),yVector+300+textheight("Va rugam"));

        deseneaza_vector(a,xVector,yVector);
    }

    outtextxy(xVector,yVector+300,"Vectorul a fost sortat crescator!");

}

void sortareDescrescatoare()
{
    settextstyle(1,0,3);
    outtextxy(50,100,"Introduceti in consola elementele vectorului");

    setcolor(WHITE);
    settextstyle(1,0,2);
    citire_vector(a);

    bar(0,50,screenWidth-100,200);
    settextstyle(1,0,3);
    outtextxy(70,177,"V : ");
    settextstyle(1,0,2);
    int xVector=150;
    int yVector=150;
    deseneaza_vector(a,xVector,yVector);
    delay(1000);

    int schimbare_are_loc=0,i,j;
    int n=a.nrElemente;
    if(n<=16)
    {
        for(i=1; i<=n-1; i++)
        {
            int index_minim=i;
            int nrMin=a.v[index_minim];

            setcolor(LIGHTMAGENTA);
            setlinestyle(DASHED_LINE,0,1);
            line(xVector+(i-1)*80,yVector-15,xVector+(i-1)*80,yVector+80+15);///fac linia punctata
            delay(1500);///desenez linia, pun delay, dupa refac linia punctata fara delay, (de ce? pentru ca vreau sa para ca patratul albastru nu se deseneaza pe linia punctata -> de fapt in spate se deseneaza patratul albastru si dupa refac linia punctata)

            settextstyle(SANS_SERIF_FONT,HORIZ_DIR,1);///fac textele din stanga si dreapta liniei punctate;
            char* s1="Vector sortat";
            char* s2="Vector nesortat";
            outtextxy(xVector+(i-1)*80-textwidth(s1)-10,yVector-15-textheight(s1)/2,s1);
            delay(500);
            outtextxy(xVector+(i-1)*80+10,yVector-15-textheight(s2)/2,s2);
            delay(2000);


            settextstyle(1,0,3);///refac textstyle pentru desenarile viitoare
            setlinestyle(0,0,0);///refac linestyle pentru desenarile viitoare

            setcolor(BLUE);
            rectangle(xVector+(i-1)*80,yVector,xVector+i*80,yVector+80);///fac primul albastru


            setcolor(LIGHTMAGENTA);
            setlinestyle(DASHED_LINE,0,1);
            line(xVector+(i-1)*80,yVector-15,xVector+(i-1)*80,yVector+80+15);///refac linia punctata pentru ca atunci cand am desenat patratul albastru (liniile de mai sus) s-a suprapus latura din stanga a patratului peste linia punctata

            setlinestyle(0,0,0);///refac linestyle pentru desenarile viitoare

            setcolor(BLUE);
            rectangle(xVector+(i-1)*80,yVector+100,xVector+i*80,yVector+180);///il fac pe cel de sub
            incadrare_int_in_casuta(a.v[index_minim],xVector+(i-1)*80,yVector+100);///pun numarul in
            delay(1000);

            bar(xVector+(i-1)*80-1,yVector+100-1,xVector+i*80+1,yVector+180+1);///il sterg pe cel de sub

            for(j=i+1; j<=n; j++)
            {

                if(a.v[j]>a.v[index_minim])
                {
                    schimbare_are_loc=1;

                    setcolor(GREEN);
                    rectangle(xVector+(j-1)*80,yVector,xVector+j*80,yVector+80); ///fac patratul al j-lea verde
                    delay(1000);

                    rectangle(xVector+(j-1)*80,yVector+100,xVector+j*80,yVector+180); ///il fac pe cel de sub
                    incadrare_int_in_casuta(a.v[index_minim],xVector+(j-1)*80,yVector+100);///pun minimul de dinainte
                    delay(2000);

                    ///sterg ce era in casuta de jos
                    index_minim=j;
                    nrMin=a.v[index_minim];

                    bar(xVector+(j-1)*80+1,yVector+100+1,xVector+j*80-1,yVector+180-1); ///sterg ce era in patrtul de jos
                    incadrare_int_in_casuta(a.v[index_minim],xVector+(j-1)*80,yVector+100); ///pun minimul actualizat
                    delay(1000);

                }
                else if(a.v[j]<nrMin)
                {
                    setcolor(RED);
                    rectangle(xVector+(j-1)*80,yVector,xVector+j*80,yVector+80);///fac patratul al j-lea rosu pt ca nu indeplineste conditia
                    delay(1000);

                    rectangle(xVector+(j-1)*80,yVector+100,xVector+j*80,yVector+180);///il fac pe cel de sub
                    incadrare_int_in_casuta(a.v[index_minim],xVector+(j-1)*80,yVector+100);///pun minimul de dinainte
                    delay(2000);
                }

                setcolor(WHITE);
                rectangle(xVector+(j-1)*80,yVector,xVector+j*80,yVector+80);///refac patratul al j-lea alb
                bar(xVector+(j-1)*80-1,yVector+100-1,xVector+j*80+1,yVector+180+1);///sterg patratul de jos
                delay(1000);

                //deseneaza_vector(a,xVector,yVector);
            }

            swap(a.v[index_minim],a.v[i]);

            if(schimbare_are_loc==1)
            {
                setcolor(WHITE);
                outtextxy(xVector,yVector+300,"Va rugam asteptati, se interschimba elementele...");
                delay(2000);

                bar(xVector,yVector+300,xVector+textwidth("Va rugam asteptati, se interschimba elementele..."),yVector+300+textheight("Va rugam"));
            }
            schimbare_are_loc=0;
            bar(xVector+(i-1)*80,yVector,xVector+i*80,yVector+80);///sterg orice era in patratul i, acolo unde are loc interschimbarea cu minimul gasit
            bar(xVector+(index_minim-1)*80,yVector,xVector+index_minim*80,yVector+80);///sterg orice era in patratul j,acolo unde are loc interschimbarea
            deseneaza_vector(a,xVector,yVector);


            setcolor(WHITE);
            rectangle(xVector+(i-1)*80,yVector,xVector+i*80,yVector+80);///refac culoarea alb patratului alb
            delay(1000);

            setcolor(BLACK);
            setlinestyle(DASHED_LINE,0,3);
            line(xVector+(i-1)*80,yVector-15,xVector+(i-1)*80,yVector+80+15);///fac linia punctata sa nu se vada

            bar(0,0,screenWidth-100,yVector-1);///sterg textele


            setlinestyle(0,0,0); ///refac linestyle pentru desenarile viitoare
            setcolor(WHITE);///refac  linia din stanga a patratului i pentru ca linia magenta fiind fix pe deasupra ei, se sterge (cine? linia dinstanga patratului i) cand o fac neagra si raman doar niste punctulete albe in loc de linie(operatie facuta mai sus)
            line(xVector+(i-1)*80,yVector,xVector+(i-1)*80,yVector+80);

            rectangle(xVector,yVector,xVector+a.nrElemente*80,yVector+80);///cand se sterge linia punctata raman niste spatii intre casute, asa ca desenez inca o data linia de sus si de jos a vectorului
        }
    }
    else if(n>16)
    {
        for(int i=1;i<=n-1;i++)
            for(int j=i+1;j<=n;j++)
                if(a.v[i]<a.v[j])
                    swap(a.v[i],a.v[j]);
        delay(2000);
        bar(xVector,yVector,screenWidth-100,screenHeight);

        outtextxy(xVector,yVector+300,"Va rugam asteptati, se interschimba elementele...");
        delay(2000);
         bar(xVector,yVector+300,xVector+textwidth("Va rugam asteptati, se interschimba elementele..."),yVector+300+textheight("Va rugam"));

        deseneaza_vector(a,xVector,yVector);
    }

    outtextxy(xVector,yVector+300,"Vectorul a fost sortat descrescator!");

}





void adunare_elemente_vector()
{
    settextstyle(1,0,3);
    outtextxy(100,100,"Introduceti in consola elementele vectorului");

    setcolor(WHITE);
    settextstyle(1,0,2);
    citire_vector(W);
    delay(1500);

    bar(0,50,900,200); ///sterge mesajul de mai sus
    settextstyle(1,0,3);
    outtextxy(70,177,"V : ");
    settextstyle(1,0,2);
    deseneaza_vector(W,150,150);
    delay(1000);

    settextstyle(1,0,3);
    outtextxy(150,350,"Adunarea elementelor unui vector se realizeaza astfel:");
    outtextxy(50,447,"Suma");
    delay(1000);
    outtextxy(160,450,"=");
    delay(1000);

    int p=200;
    int suma=0;

    settextstyle(1,0,2);
    if(W.nrElemente<=16)
    {
        int xdes=150;
        int ydes=150;
        for(int i=1; i<=W.nrElemente; i++)
        {
            suma+=W.v[i];
            setcolor(YELLOW);
            rectangle(xdes,ydes,xdes+80,ydes+80);
///setcolor(white)
            outintxy(p,450,W.v[i]);
            modificare_p(p,W.v[i]);
            delay(1500);

            setcolor(WHITE);
            rectangle(xdes,ydes,xdes+80,ydes+80);
            if(i<W.nrElemente)
            {
                outtextxy(p,450,"+");
                p+=30;
                delay(1000);
            }
            xdes+=80;
        }
        outtextxy(p,450,"=");
        p+=30;
        delay(1000);
        setcolor(YELLOW);
        outintxy(p,450,suma);
    }
    ///daca sunt mai mult de 16 elemente in vector
    else
    {
        for(int i=1; i<=W.nrElemente; i++)
        {
            suma+=W.v[i];
        }
        int xdes=150;
        int ydes=150;
        for(int i=1; i<=7; i++)
        {
            setcolor(YELLOW);
            rectangle(xdes,ydes,xdes+80,ydes+80);
///setcolor(white)
            outintxy(p,450,W.v[i]);
            modificare_p(p,W.v[i]);
            delay(1500);
            setcolor(WHITE);
            rectangle(xdes,ydes,xdes+80,ydes+80);
            if(i<W.nrElemente)
            {
                outtextxy(p,450,"+");
                p+=30;
                delay(1000);
            }
            xdes+=80;
        }

        outtextxy(p,450,"......");
        delay(1000);
        p+=70;
        outtextxy(p,450,"+");
        p+=30;
        delay(1000);

        xdes=160+80*7+160;
        int cont=W.nrElemente-5;///luam ultimele 5 elemente
        for(int i=cont; i<=W.nrElemente; i++)
        {
            setcolor(YELLOW);
            rectangle(xdes,ydes,xdes+80,ydes+80);
///setcolor(white)
            outintxy(p,450,W.v[i]);
            modificare_p(p,W.v[i]);
            delay(1500);

            setcolor(WHITE);
            rectangle(xdes,ydes,xdes+80,ydes+80);
            if(i<W.nrElemente)///fara if se mai pune un plus inainte de egal
            {
                outtextxy(p,450,"+");
                p+=30;
                delay(1000);
            }
            xdes+=80;
        }
        outtextxy(p,450,"=");
        delay(1000);
        p+=30;
        setcolor(YELLOW);
        outintxy(p,450,suma);
    }

}

void deseneaza_matrice(matrice a, int x, int y)///deseneaza o matrice incepand cu punctul de coord. x y
{

    settextstyle(1,0,2);
    int xCont=x;
    int yCont=y;
    for(int i=0; i<a.nrLinii; i++,yCont+=80)
    {
        for(int j=0; j<a.nrColoane; j++,xCont+=80)
        {
            rectangle(xCont,yCont,xCont+80,yCont+80);
            //delay(500);
            incadrare_int_in_casuta(a.mat[i][j],xCont,yCont);
        }
        xCont=x;
    }
    ///getch() daca il pun: la operatii uneori trebuie sa apas o tasta ca sa apara operatorul, uneori nu... nu stiu de ce face figuri...
}


void outintxy(int x, int y, int value)
{

    char digit_string[20];
    sprintf(digit_string, "%d", value);
    outtextxy(x, y, digit_string);
}

void deseneaza_plus(int x, int y)
{
    line(x,y,x+40,y); ///bara orizontala
    line(x+20,y-20,x+20,y+20);
}
void deseneaza_egal(int x,int y)
{
    line(x,y-5,x+40,y-5);///deseneaza bara de sus
    line(x,y+5,x+40,y+5);
}
void deseneaza_minus(int x, int y)
{
    line(x,y,x+40,y);
}
void deseneaza_cerc(int x, int y)
{
    line(x-10,y,x+10,y);
    line(x,y-10,x,y+10);
    line(x-8,y-8,x+8,y+8);
    line(x+8,y-8,x-8,y+8);
}

void adunare_matrice()
{
        readimagefile("e:\\facultate\\Anul 1 Sem 1\\IP\\BibMat\\stelute.jpg",0,0,screenWidth,screenHeight);


    settextstyle(1,0,3);
    outtextxy(100,100,"Introduceti elementele matricelor in consola");
    citire_matrice(A);
    setcolor(BLACK);
    bar(50,50,900,200);
    setcolor(WHITE);

    int xDes, yDes;
    xDes=50;
    yDes=100;

    deseneaza_matrice(A,xDes,yDes);

    int XindicePlus=xDes+A.nrColoane*80+50; //x-ul de unde incepe plusul
    int YindicePlus=yDes+A.nrLinii*80/2;

    deseneaza_plus(XindicePlus,YindicePlus);
    citire_matrice(B);

    ///vedem cam cat de mare e matricea B (daca are mai multe linii sau nu) si unde sa o desenam

    if(B.nrLinii>A.nrLinii)
    {
        int dimensiuneLinii;
        dimensiuneLinii=yDes+B.nrLinii*80;

        int mijlocLinii;
        mijlocLinii=yDes+(dimensiuneLinii-yDes)/2;

        int offset;
        offset=mijlocLinii-YindicePlus;

        yDes=yDes-offset;
        deseneaza_matrice(B,XindicePlus+40+50,yDes);
    }

    else if(B.nrLinii<A.nrLinii)
    {
        int dimensiuneLinii;
        dimensiuneLinii=yDes+B.nrLinii*80;

        int mijlocLinii;
        mijlocLinii=yDes+(dimensiuneLinii-yDes)/2;

        int offset;
        offset=YindicePlus-mijlocLinii;

        yDes=yDes+offset;
        deseneaza_matrice(B,XindicePlus+40+50,yDes);
    }
    else deseneaza_matrice(B,XindicePlus+40+50,yDes);


    if(A.nrLinii!=B.nrLinii||A.nrColoane!=B.nrColoane)
    {
        settextstyle(1,0,3);
        outtextxy(XindicePlus+90+B.nrColoane*80+50,YindicePlus,"Adunare imposibila!");
        outtextxy(130,A.nrLinii*80+250,"Doua matrice pot fi adunate doar daca au acelasi numar de linii si coloane" );
        outtextxy(500,A.nrLinii*80+300,"Incearca din nou!");
    }
    else
    {

        C.nrLinii=A.nrLinii;
        C.nrColoane=A.nrColoane;
        for(int i=0; i<A.nrLinii; i++)
            for(int j=0; j<A.nrColoane; j++)
            {
                C.mat[i][j]=A.mat[i][j]+B.mat[i][j];
            }

        int XindiceEgal;
        int YindiceEgal;

        XindiceEgal=XindicePlus+90+B.nrColoane*80+50;
        YindiceEgal=YindicePlus;

        deseneaza_egal(XindiceEgal,YindiceEgal);

        deseneaza_matrice(C,XindiceEgal+40+50,yDes);

        delay(1000);
        outtextxy(50,A.nrLinii*80+200,"Adunarea a doua matrice se realizeaza astfel:");
        int yText=A.nrLinii*80+200;///y ul unde afisam adunarile


        int ya=yDes;
        int yb=yDes;
        int yc=yDes;

        int p=700;///x ul pt afisare adunari
        for(int i=0; i<A.nrLinii; i++)
        {
            p=700;
            int xa=xDes;
            int xb=XindicePlus+40+50;
            int xc=XindiceEgal+40+50;
            for(int j=0; j<A.nrColoane; j++)
            {
                p=700;
                char char_a[20];
                sprintf(char_a, "%d", A.mat[i][j]);
                char char_b[20];
                sprintf(char_b, "%d", B.mat[i][j]);
                char char_c[20];
                sprintf(char_c, "%d", C.mat[i][j]);

                setcolor(YELLOW);
                rectangle(xa,ya,xa+80,ya+80);
                setcolor(WHITE);
                outtextxy(p,yText,char_a);
                modificare_p(p,A.mat[i][j]);

                delay(800);

                setcolor(YELLOW);
                deseneaza_plus(XindicePlus,YindicePlus);
                setcolor(WHITE);
                outtextxy(p,yText,"+");
                p+=30;

                delay(800);

                setcolor(YELLOW);
                rectangle(xb,yb,xb+80,yb+80);
                setcolor(WHITE);
                outtextxy(p,yText,char_b);
                modificare_p(p,B.mat[i][j]);

                delay(800);

                setcolor(YELLOW);
                deseneaza_egal(XindiceEgal,YindiceEgal);
                setcolor(WHITE);
                outtextxy(p,yText,"=");
                p+=30;
                delay(800);

                setcolor(YELLOW);
                rectangle(xc,yc,xc+80,yc+80);
                setcolor(WHITE);
                outtextxy(p,yText,char_c);
                modificare_p(p,C.mat[i][j]);

                delay(1000);
                setcolor(WHITE);///refacem patratele si semnele
                rectangle(xa,ya,xa+80,ya+80);
                rectangle(xb,yb,xb+80,yb+80);
                rectangle(xc,yc,xc+80,yc+80);

                deseneaza_egal(XindiceEgal,YindiceEgal);
                deseneaza_plus(XindicePlus,YindicePlus);

                setcolor(BLACK);  ///acoperim calculele
                bar(700,yText-20,1000,yText+20);
                xa+=80;
                xb+=80;
                xc+=80;
            }
            ya+=80;
            yb+=80;
            yc+=80;
        }
        setcolor(BLACK);
        bar(10,yText-50,1000,yText+20);///ca sa stergem mesajul cu ,,Adunare a doua..."
        setcolor(WHITE);
    }
}

void scadere_matrice()
{

    settextstyle(1,0,3);
    outtextxy(100,100,"Introduceti elementele matricelor in consola");
    citire_matrice(A);
    setcolor(BLACK);
    bar(50,50,900,200);
    setcolor(WHITE);


    int xDes, yDes;
    xDes=50;
    yDes=100;

    deseneaza_matrice(A,xDes,yDes);

    int XindiceMinus=xDes+A.nrColoane*80+50; //x-ul de unde incepe minusul
    int YindiceMinus=yDes+A.nrLinii*80/2;

    deseneaza_minus(XindiceMinus,YindiceMinus);

    citire_matrice(B);

    ///vedem cam cat de mare e matricea B (daca are mai multe linii sau nu) si unde sa o desenam

    if(B.nrLinii>A.nrLinii)
    {
        int dimensiuneLinii;
        dimensiuneLinii=yDes+B.nrLinii*80;

        int mijlocLinii;
        mijlocLinii=yDes+(dimensiuneLinii-yDes)/2;

        int offset;
        offset=mijlocLinii-YindiceMinus;

        yDes=yDes-offset;
        deseneaza_matrice(B,XindiceMinus+40+50,yDes);
    }

    else if(B.nrLinii<A.nrLinii)
    {
        int dimensiuneLinii;
        dimensiuneLinii=yDes+B.nrLinii*80;

        int mijlocLinii;
        mijlocLinii=yDes+(dimensiuneLinii-yDes)/2;

        int offset;
        offset=YindiceMinus-mijlocLinii;

        yDes=yDes+offset;
        deseneaza_matrice(B,XindiceMinus+40+50,yDes);
    }
    else deseneaza_matrice(B,XindiceMinus+40+50,yDes);

    settextstyle(1,0,3);
    if(A.nrLinii!=B.nrLinii||A.nrColoane!=B.nrColoane)
    {

        // outtextxy(XindicePlus+90+B.nrColoane*80+50+40+50,YindicePlus,"Matricele nu se pot aduna");///trebuie sa stabilim unde punem textul
        outtextxy(XindiceMinus+90+B.nrColoane*80+50,YindiceMinus,"Scadere imposibila!");
        outtextxy(130,A.nrLinii*80+250,"Doua matrice se pot scadea doar daca au acelasi numar de linii si coloane" );
        outtextxy(500,A.nrLinii*80+300,"Incearca din nou!");
    }
    else
    {
        C.nrLinii=A.nrLinii;
        C.nrColoane=A.nrColoane;
        for(int i=0; i<A.nrLinii; i++)
            for(int j=0; j<A.nrColoane; j++)
            {
                C.mat[i][j]=A.mat[i][j]-B.mat[i][j];
            }

        int XindiceEgal;
        int YindiceEgal;

        XindiceEgal=XindiceMinus+90+B.nrColoane*80+50;
        YindiceEgal=YindiceMinus;

        deseneaza_egal(XindiceEgal,YindiceEgal);

        deseneaza_matrice(C,XindiceEgal+40+50,yDes);


        delay(1000);
        outtextxy(50,A.nrLinii*80+200,"Scaderea a doua matrice se realizeaza astfel:");
        int yText=A.nrLinii*80+200;///y ul unde afisam adunarile


        int ya=yDes;
        int yb=yDes;
        int yc=yDes;

        int p=700;///x ul pt afisare adunari
        for(int i=0; i<A.nrLinii; i++)
        {
            p=700;
            int xa=xDes;
            int xb=XindiceMinus+40+50;
            int xc=XindiceEgal+40+50;
            for(int j=0; j<A.nrColoane; j++)
            {
                p=700;
                char char_a[20];
                sprintf(char_a, "%d", A.mat[i][j]);
                char char_b[20];
                sprintf(char_b, "%d", B.mat[i][j]);
                char char_c[20];
                sprintf(char_c, "%d", C.mat[i][j]);

                setcolor(RED);
                rectangle(xa,ya,xa+80,ya+80);
                setcolor(WHITE);
                outtextxy(p,yText,char_a);
                modificare_p(p,A.mat[i][j]);

                delay(800);

                setcolor(YELLOW);
                deseneaza_minus(XindiceMinus,YindiceMinus);
                setcolor(WHITE);
                outtextxy(p,yText,"-");
                p+=30;

                delay(800);

                setcolor(RED);
                rectangle(xb,yb,xb+80,yb+80);
                setcolor(WHITE);
                outtextxy(p,yText,char_b);
                modificare_p(p,B.mat[i][j]);

                delay(800);

                setcolor(RED);
                deseneaza_egal(XindiceEgal,YindiceEgal);
                setcolor(WHITE);
                outtextxy(p,yText,"=");
                p+=30;
                delay(800);

                setcolor(RED);
                rectangle(xc,yc,xc+80,yc+80);
                setcolor(WHITE);
                outtextxy(p,yText,char_c);
                modificare_p(p,C.mat[i][j]);

                delay(800);
                setcolor(WHITE);///refacem patratele si semnele
                rectangle(xa,ya,xa+80,ya+80);
                rectangle(xb,yb,xb+80,yb+80);
                rectangle(xc,yc,xc+80,yc+80);

                deseneaza_egal(XindiceEgal,YindiceEgal);
                deseneaza_minus(XindiceMinus,YindiceMinus);

                setcolor(BLACK);  ///acoperim calculele
                bar(700,yText-20,1000,yText+20);
                xa+=80;
                xb+=80;
                xc+=80;
            }
            ya+=80;
            yb+=80;
            yc+=80;
        }
        setcolor(BLACK);
        bar(10,yText-50,1000,yText+20);///ca sa stergem mesajul cu ,,Adunare a doua..."
        setcolor(WHITE);

    }
}


void initializareFereastra()
{
    DWORD screenWidth=GetSystemMetrics(SM_CXSCREEN);
    DWORD screenHeight=GetSystemMetrics(SM_CYSCREEN);
    initwindow(screenWidth,screenHeight,"BibMat",-3,-3);
}


void afisareCoordonate()
{
    POINT cursorPosition;
    int mx,my;
    while(1)
    {
        GetCursorPos(&cursorPosition);
        while(1)
        {
            mx=cursorPosition.x;
            my=cursorPosition.y;
            std::cout<<"Cursorul se afla la x-ul: "<<mx<<'\n';
            std::cout<<"Cursorul se afla la y-ul: "<<my<<'\n';
            delay(2000);
            break;
        }
    }

}

void centreazaText(char *a, int margineSt, int margineDr, int sus, int jos)
{

    int midx=(margineSt+margineDr)/2;
    int width = textwidth (a);
    int height = textheight(a);
    int yText=(sus+jos)/2;
    settextstyle(3, HORIZ_DIR, 1);
    outtextxy(midx-width/2, yText-height/2, a);
}

void initializarePag1()
{

    ///titlu
    int midx=getmaxx()/2;
    int midy=getmaxy()/2;

    settextstyle(3, HORIZ_DIR, 7);
    //char a[100];
    int width = textwidth ("Proiectul BibMat");
    int height = textheight("Proiectul BibMat");
    //sprintf(a,"Width is %d and height is %d ", width,height);
    setcolor(WHITE);


    outtextxy(midx/**-width*4.5**/-width/2, 20, "Proiectul BibMat");

    int yDreapta=getmaxx(); ///sau puteam folosi screenWidth


    setcolor(WHITE);
    ///casuta vectori
    char* a="vectori";
    // centreazaText(*a,75,350);
    setlinestyle(DASHED_LINE,1,1);
    rectangle(105,200,630,375);
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,5);
    outtextxy(260,270,"VECTORI");

    ///casuta matrici
    setlinestyle(DASHED_LINE,1,1);
    rectangle(105,200+300,630,375+300);
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,5);
    outtextxy(275,270+300,"MATRICI");

    ///casuta Despre proiect
    setlinestyle(DASHED_LINE,1,1);
    rectangle(900,200,1425,375);
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,5);
    outtextxy(950,270,"DESPRE PROIECT");

    ///casuta Exit
    setlinestyle(DASHED_LINE,1,1);
    rectangle(900,200+300,1425,375+300);
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,5);
    outtextxy(1100,270+300,"EXIT");

    readimagefile("royal.jpg",0,0,screenWidth,screenHeight);


    setcolor(WHITE);

    setlinestyle(SOLID_LINE,0,1);///important pentru cand se revine din butonul back din paginaDespreProiect() pentru ca acolo se schimba linesrtyle-ul, mai exact se schimba grosimea liniei
    for(int i=115; i<=120; i++)
        line(0,i,yDreapta,i);
    // bar(0,115,getmaxx(),120);

    deciziePagina1();




}

void buton (char *a, int &yButonPrecedent, int &yButon)
{
    DWORD screenWidth=GetSystemMetrics(SM_CXSCREEN);
    DWORD screenHeight=GetSystemMetrics(SM_CYSCREEN);

    setlinestyle(SOLID_LINE,1,1);
    rectangle(screenWidth-100,yButonPrecedent,screenWidth-5,yButon);
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,1);

    centreazaText(a,screenWidth-100,screenWidth,yButonPrecedent,yButon);

    int dimensiunePatrat=yButon-yButonPrecedent;

    yButonPrecedent=yButon;
    yButon=yButon+dimensiunePatrat;
}
void buton_fara_referinta (char *a, int yButon, int yButonPrecedent)
{
    DWORD screenWidth=GetSystemMetrics(SM_CXSCREEN);
    DWORD screenHeight=GetSystemMetrics(SM_CYSCREEN);

    setlinestyle(SOLID_LINE,1,1);
    rectangle(screenWidth-100,1,screenWidth-5,yButon);
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,1);

    centreazaText(a,screenWidth-100,screenWidth,yButonPrecedent,yButon);
}

void restore(char *a,int x,int y)
{
    setfillstyle(SLASH_FILL,BLACK);
    bar(screenWidth-98, x+3, screenWidth-6, y-2);

    setcolor(WHITE);
    buton_fara_referinta(a,x+1,y);
}

void restore2nivele(char *a,char *b,int x,int y)
{
    setfillstyle(SLASH_FILL,BLACK);
    bar(screenWidth-98, x+3, screenWidth-6, y-2);

    setcolor(WHITE);
    buton2nivele_fara_referinta(a,b,x+1,y);
}

void restore2niveleOptiuni(char* a, char* b, int stanga, int dreapta, int sus, int jos,int color)
{
    setfillstyle(SLASH_FILL,BLACK);
    bar(stanga,sus,dreapta,jos);

    setcolor(color);
    centreazaText2nivele(a,b,stanga,dreapta,sus,jos);
}

void inmultire_matrice()
{
    settextstyle(1,0,3);
    outtextxy(100,100,"Introduceti elementele matricelor in consola");
    citire_matrice(A);
    setcolor(BLACK);
    bar(50,50,900,200);
    setcolor(WHITE);

    int xDes, yDes;
    xDes=50;
    yDes=100;

    deseneaza_matrice(A,xDes,yDes);

    int XindiceInmultire=xDes+A.nrColoane*80+75; //x-ul de unde incepe minusul
    int YindiceInmultire=yDes+A.nrLinii*80/2;

    deseneaza_cerc(XindiceInmultire,YindiceInmultire);

    citire_matrice(B);

    ///vedem cam cat de mare e matricea B (daca are mai multe linii sau nu) si unde sa o desenam

    if(B.nrLinii>A.nrLinii)
    {
        int dimensiuneLinii;
        dimensiuneLinii=yDes+B.nrLinii*80;

        int mijlocLinii;
        mijlocLinii=yDes+(dimensiuneLinii-yDes)/2;

        int offset;
        offset=mijlocLinii-YindiceInmultire;

        yDes=yDes-offset;
        deseneaza_matrice(B,XindiceInmultire+40+50,yDes);
    }

    else if(B.nrLinii<A.nrLinii)
    {
        int dimensiuneLinii;
        dimensiuneLinii=yDes+B.nrLinii*80;

        int mijlocLinii;
        mijlocLinii=yDes+(dimensiuneLinii-yDes)/2;

        int offset;
        offset=YindiceInmultire-mijlocLinii;

        yDes=yDes+offset;
        deseneaza_matrice(B,XindiceInmultire+40+50,yDes);
    }
    else
        deseneaza_matrice(B,XindiceInmultire+40+50,yDes);

    if(A.nrColoane!=B.nrLinii)
    {
        settextstyle(1,0,3);
        outtextxy(XindiceInmultire+90+B.nrColoane*80+50+40+50,YindiceInmultire,"Inmultire imposibila!");
        outtextxy(50,A.nrLinii*80+200,"Pentru a inmulti doua matrice numarul coloanelor primei matrice trebuie sa fie egal");
        outtextxy(400,A.nrLinii*80+250,"cu numarul liniilor celei de a doua matrice.");
        outtextxy(600,A.nrLinii*80+400,"Incearca din nou!");
    }
    else
    {
        for(int i=0; i<A.nrLinii; i++)
        {
            for(int j=0; j<B.nrColoane; j++)
            {
                C.mat[i][j]=0;
                for(int k=0; k<A.nrColoane; k++)
                    C.mat[i][j]=C.mat[i][j]+A.mat[i][k]*B.mat[k][j];
            }
        }
        C.nrLinii=A.nrLinii;
        C.nrColoane=B.nrColoane;

        int XindiceEgal;
        int YindiceEgal;

        XindiceEgal=XindiceInmultire+90+B.nrColoane*80+50;
        YindiceEgal=YindiceInmultire;

        deseneaza_egal(XindiceEgal,YindiceEgal);

        int xa=50;///putem pune xDes pt ca nu se modifica
        int ya=100;///!!! NU putem pune yDes pentru ca se modifica in functie de dimensiunile matricii B

        int xb=XindiceInmultire+40+50;
        int yb=yDes;

        int xc,yc;
        ///stabilim unde desenam matricea C, avem 3 cazuri
        if(A.nrLinii==B.nrLinii)
        {
            deseneaza_matrice(C,XindiceEgal+40+50,yDes); ///yDes sau 100, nu conteaza pt ca A.nrLinii=B.nrLinii
            xc=XindiceEgal+40+50;
            yc=yDes;
        }

        if(A.nrLinii<B.nrLinii)
        {
            deseneaza_matrice(C,XindiceEgal+40+50,100);
            xc=XindiceEgal+40+50;
            yc=100;
        }

        if(A.nrLinii>B.nrLinii)
        {
            deseneaza_matrice(C,XindiceEgal+40+50,100);
            xc=XindiceEgal+40+50;
            yc=100;
        }

        setcolor(WHITE);
        outtextxy(50,A.nrLinii*80+200,"Inmultirea a doua matrice se realizeaza astfel:");
        int yText=A.nrLinii*80+250;///y ul unde afisam inmultirile

        for(int i=0; i<A.nrLinii; i++)
        {
            for(int j=0; j<B.nrColoane; j++)
            {
                int p=50;
                for(int k=0; k<A.nrColoane; k++)
                {
                    char char_a[20];
                    sprintf(char_a, "%d", A.mat[i][k]);
                    setcolor(GREEN);
                    rectangle(xa,ya,xa+80,ya+80);
                    setcolor(WHITE);
                    outtextxy(p,yText,char_a);
                    modificare_p(p,A.mat[i][k]);
                    delay(600);

                    setcolor(GREEN);
                    deseneaza_cerc(XindiceInmultire,YindiceInmultire);
                    setcolor(WHITE);
                    outtextxy(p,yText,"*");
                    p+=30;
                    delay(600);


                    char char_b[20];
                    sprintf(char_b, "%d", B.mat[k][j]);
                    setcolor(GREEN);
                    rectangle(xb,yb,xb+80,yb+80);
                    setcolor(WHITE);
                    outtextxy(p,yText,char_b);
                    modificare_p(p, B.mat[k][j]);
                    delay(600);
                    rectangle(xa,ya,xa+80,ya+80);
                    rectangle(xb,yb,xb+80,yb+80);
                    deseneaza_cerc(XindiceInmultire,YindiceInmultire);


                    if(k<B.nrLinii-1)
                    {
                        outtextxy(p,yText,"+");
                        p=p+30;
                        delay(400);
                    }
                    xa+=80;
                    yb+=80;
                }

                setcolor(GREEN);
                deseneaza_egal(XindiceEgal,YindiceEgal);
                setcolor(WHITE);
                outtextxy(p,yText,"=");
                p+=30;
                delay(600);

                char char_c[20];
                sprintf(char_c, "%d", C.mat[i][j]);
                setcolor(GREEN);
                rectangle(xc,yc,xc+80,yc+80);
                setcolor(WHITE);
                outtextxy(p,yText,char_c);
                modificare_p(p,C.mat[i][j]);
                delay(600);
                rectangle(xc,yc,xc+80,yc+80);

                setcolor(WHITE);
                deseneaza_egal(XindiceEgal,YindiceEgal);

                setcolor(BLACK);
                bar(5,yText-20,1400,yText+20);

                xc+=80;
                xa=xDes;
                xb+=80;
                yb=yDes;
            }
            xc=XindiceEgal+40+50;
            yc+=80;
            xb=XindiceInmultire+40+50;
            ya+=80;
        }
        setcolor(BLACK);
        bar(5,yText-100,1400,yText+20);
        setcolor(WHITE);

    }
}

void suma_diag_principala()
{
    settextstyle(1,0,3);
    outtextxy(100,100,"Introduceti elementele matricei in consola");
    citire_matrice(A);
    setcolor(BLACK);
    bar(50,50,900,200);
    setcolor(WHITE);

    deseneaza_matrice(A,50,100);
    delay(2000);
    int i,j,s;
    s=0;
    for(i=0; i<A.nrLinii; i++)
        for(j=0; j<A.nrColoane; j++)
        {
            if(i==j)
                s=s+A.mat[i][j];
            if(i==A.nrColoane) ///mai eficient
                break;
        }

    int xIndiceText=50+A.nrColoane*80+50;
    int yIndiceText=100+A.nrLinii*80/2;

    if(A.nrLinii!=A.nrColoane)
    {
        outtextxy(xIndiceText,yIndiceText-textheight("Nu exista diagonala principala")/2,"Nu exista diagonala principala");
    }
    else
    {
        outtextxy(50,A.nrLinii*80+150,"Suma elementelor de pe diagonala principala se calculeaza astfel:");
        delay(2000);
        int xa=50;
        int ya=100;
        int p=50;
        for(i=0; i<A.nrLinii; i++)
            for(j=0; j<A.nrColoane; j++)
            {
                if(i==j)
                {
                    setcolor(YELLOW);
                    rectangle(xa,ya,xa+80,ya+80);
                    setcolor(WHITE);
                    char char_a[20];
                    sprintf(char_a, "%d", A.mat[i][j]);
                    outtextxy(p,A.nrLinii*80+200,char_a);
                    modificare_p(p,A.mat[i][j]);
                    delay(1000);
                    if(i<A.nrLinii-1)
                    {
                        setcolor(WHITE);
                        outtextxy(p,A.nrLinii*80+200,"+");
                        p+=30;
                        delay(1000);
                    }
                    xa+=80;
                    ya+=80;
                }
            }
        outtextxy(p,A.nrLinii*80+200,"=");
        p+=30;
        delay(1000);
        char char_b[20];
        sprintf(char_b, "%d", s);
        outtextxy(p,A.nrLinii*80+200,char_b);
    }

}

void suma_deasupra_diag_principala()
{
    settextstyle(1,0,3);
    outtextxy(100,100,"Introduceti elementele matricei in consola");
    citire_matrice(A);
    setcolor(BLACK);
    bar(50,50,900,200);
    setcolor(WHITE);

    deseneaza_matrice(A,50,100);
    delay(1000);

    int i,j,s;
    s=0;
    for(i=0; i<A.nrLinii; i++)
        for(j=0; j<A.nrColoane; j++)
        {
            if(i<j) ///i!=A.nrLinii in cazul in care nu avem matrice patratica
                s=s+A.mat[i][j];
        }
    int xIndiceText=50+A.nrColoane*80+50;
    int yIndiceText=100+A.nrLinii*80/2-textheight("suma este")/2;


    settextstyle(1,0,3);
    if(A.nrLinii!=A.nrColoane)
    {
        outtextxy(xIndiceText,yIndiceText-textheight("Nu exista diagonala principala")/2,"Nu exista diagonala principala");
    }
    else
    {
        outtextxy(50,A.nrLinii*80+150,"Suma elementelor de deasupra diagonalei principale se calculeaza astfel:");
        delay(2000);
        int xprim=130;
        int yprim=100;
        int ya=yprim;
        int p=50;
        for(i=0; i<A.nrLinii; i++)
        {
            int xa=xprim;
            for(j=0; j<A.nrColoane; j++)
            {
                if( i<j)
                {
                    setcolor(RED);
                    rectangle(xa,ya,xa+80,ya+80);
                    setcolor(WHITE);
                    outintxy(p,A.nrLinii*80+200,A.mat[i][j]);
                    modificare_p(p,A.mat[i][j]);
                    delay(1000);
                    if(i<A.nrLinii-2)
                    {
                        setcolor(WHITE);
                        outtextxy(p,A.nrLinii*80+200,"+");
                        p+=30;
                        delay(1000);
                    }
                    xa+=80;
                }
            }
            xprim+=80;
            ya+=80;
        }

        outtextxy(p,A.nrLinii*80+200,"=");
        p+=30;
        delay(1000);
        outintxy(p,A.nrLinii*80+200,s);
    }

}

void suma_sub_diag_principala()
{
    settextstyle(1,0,3);
    outtextxy(100,100,"Introduceti elementele matricei in consola");
    citire_matrice(A);
    setcolor(BLACK);
    bar(50,50,900,200);
    setcolor(WHITE);
    deseneaza_matrice(A,50,100);
    delay(1000);
    int i,j,s;

    s=0;
    for(i=0; i<A.nrLinii; i++)
        for(j=0; j<A.nrColoane; j++)
        {
            if(i>j)
                s=s+A.mat[i][j];
        }

    int xIndiceText=50+A.nrColoane*80+50;
    int yIndiceText=100+A.nrLinii*80/2-textheight("suma este")/2;

    settextstyle(1,0,3);
    if(A.nrLinii!=A.nrColoane)
    {
        outtextxy(xIndiceText,yIndiceText-textheight("Nu exista diagonala principala")/2,"Nu exista diagonala principala");
    }
    else
    {
        outtextxy(50,A.nrLinii*80+150,"Suma elementelor de sub diagonala principala se calculeaza astfel:");
        delay(2000);
        int xa;
        int xprim=50;
        int yprim=100;
        int ya=yprim;
        int p=50;
        for(i=0; i<A.nrLinii; i++)
        {
            xa=xprim;
            for(j=0; j<A.nrColoane; j++)
            {
                if( i>j)
                {
                    setcolor(GREEN);
                    rectangle(xa,ya,xa+80,ya+80);
                    setcolor(WHITE);
                    outintxy(p,A.nrLinii*80+200,A.mat[i][j]);
                    modificare_p(p,A.mat[i][j]);
                    delay(1000);
                    if(i<A.nrLinii&&j!=A.nrColoane-2)
                    {
                        setcolor(WHITE);
                        outtextxy(p,A.nrLinii*80+200,"+");
                        p+=30;
                        delay(1000);
                    }
                    xa+=80;
                }
            }
            ya+=80;
        }

        outtextxy(p,A.nrLinii*80+200,"=");
        p+=30;
        delay(1000);
        outintxy(p,A.nrLinii*80+200,s);
    }

}


void suma_diag_secundara()
{

    settextstyle(1,0,3);
    outtextxy(100,100,"Introduceti elementele matricei in consola");
    citire_matrice(A);
    setcolor(BLACK);
    bar(50,50,900,200);
    setcolor(WHITE);

    deseneaza_matrice(A,50,100);
    delay(1000);

    int xIndiceText=50+A.nrColoane*80+50;
    int yIndiceText=100+A.nrLinii*80/2;

    settextstyle(1,0,3);

    if(A.nrLinii!=A.nrColoane)
        outtextxy(xIndiceText,yIndiceText-textheight("Nu exista diagonala secundara")/2,"Nu exista diagonala secundara");
    else
    {
        outtextxy(50,A.nrLinii*80+150,"Suma elementelor de pe diagonala secundara se calculeaza astfel:");
        delay(1000);
        int i,j,s;
        s=0;
        for(i=0; i<A.nrLinii; i++)
            for(j=0; j<A.nrColoane; j++)
                if(i+j==A.nrLinii-1) ///sau ==A.nrColoane-1 pentru ca e matr patratica
                    s=s+A.mat[i][j];


        int xa=50+80*(A.nrColoane-1);
        int ya=100;
        int p=50;
        for(i=0; i<A.nrLinii; i++)
            for(j=0; j<A.nrColoane; j++)
            {
                if(i+j==A.nrLinii-1)
                {
                    setcolor(MAGENTA);
                    rectangle(xa,ya,xa+80,ya+80);
                    setcolor(WHITE);
                    char char_a[20];
                    sprintf(char_a, "%d", A.mat[i][j]);
                    outtextxy(p,A.nrLinii*80+200,char_a);
                    modificare_p(p,A.mat[i][j]);
                    delay(1000);
                    if(i<A.nrLinii-1)
                    {
                        setcolor(WHITE);
                        outtextxy(p,A.nrLinii*80+200,"+");
                        p+=30;
                        delay(1000);
                    }
                    xa-=80;
                    ya+=80;
                }
            }
        outtextxy(p,A.nrLinii*80+200,"=");
        p+=30;
        delay(1000);
        char char_b[20];
        sprintf(char_b, "%d", s);
        outtextxy(p,A.nrLinii*80+200,char_b);
    }
}

void suma_deasupra_diag_secundara()
{
    settextstyle(1,0,3);
    outtextxy(100,100,"Introduceti elementele matricei in consola");
    citire_matrice(A);
    setcolor(BLACK);
    bar(50,50,900,200);
    setcolor(WHITE);
    deseneaza_matrice(A,50,100);
    delay(1000);
    int xIndiceText=50+A.nrColoane*80+50;
    int yIndiceText=100+A.nrLinii*80/2;

    settextstyle(1,0,3);
    if(A.nrLinii!=A.nrColoane)
        outtextxy(xIndiceText,yIndiceText-textheight("Nu exista diagonala secundara")/2,"Nu exista diagonala secundara");
    else
    {
        outtextxy(50,A.nrLinii*80+150,"Suma elementelor de deasupra diagonalei secundare se calculeaza astfel:");
        delay(1000);
        int i,j,s;
        s=0;
        for(i=0; i<A.nrLinii; i++)
            for(j=0; j<A.nrColoane; j++)
                if(i+j<A.nrLinii-1) ///sau ==A.nrColoane-1 pentru ca e matr patratica
                    s=s+A.mat[i][j];

        int xa, ya;
        int p=50;
        ya=100;
        for(i=0; i<A.nrLinii; i++)
        {
            xa=50;
            for(j=0; j<A.nrColoane; j++)
            {
                if(i+j<A.nrLinii-1)
                {
                    setcolor(BLUE);
                    rectangle(xa,ya,xa+80,ya+80);
                    setcolor(WHITE);
                    char char_a[20];
                    sprintf(char_a, "%d", A.mat[i][j]);
                    outtextxy(p,A.nrLinii*80+200,char_a);
                    modificare_p(p,A.mat[i][j]);
                    delay(1000);
                    if(i<A.nrLinii-2)
                    {
                        setcolor(WHITE);
                        outtextxy(p,A.nrLinii*80+200,"+");
                        p+=30;
                        delay(1000);
                    }
                    xa+=80;
                }
            }
            ya+=80;
        }
        outtextxy(p,A.nrLinii*80+200,"=");
        p+=30;
        delay(1000);
        char char_b[20];
        sprintf(char_b, "%d", s);
        outtextxy(p,A.nrLinii*80+200,char_b);
    }


}

void suma_sub_diag_secundara()
{

    settextstyle(1,0,3);
    outtextxy(100,100,"Introduceti elementele matricei in consola");
    citire_matrice(A);
    setcolor(BLACK);
    bar(50,50,900,200);
    setcolor(WHITE);
    deseneaza_matrice(A,50,100);
    delay(1000);

    int xIndiceText=50+A.nrColoane*80+50;
    int yIndiceText=100+A.nrLinii*80/2;

    settextstyle(1,0,3);
    if(A.nrLinii!=A.nrColoane)
        outtextxy(xIndiceText,yIndiceText-textheight("Nu exista diagonala secundara")/2,"Nu exista diagonala secundara");
    else
    {
        outtextxy(50,A.nrLinii*80+150,"Suma elementelor de sub diagonala secundara se calculeaza astfel:");
        delay(1000);
        int i,j,s;
        s=0;
        for(i=0; i<A.nrLinii; i++)
            for(j=0; j<A.nrColoane; j++)
                if(i+j>A.nrLinii-1) ///sau ==A.nrColoane-1 pentru ca e matr patratica
                    s=s+A.mat[i][j];

        int xa, ya,xprim;
        xprim=50+(A.nrColoane)*80;
        int p=50;
        ya=100;
        for(i=0; i<A.nrLinii; i++)
        {
            xa=xprim;
            for(j=0; j<A.nrColoane; j++)
            {
                if(i+j>A.nrLinii-1)
                {
                    setcolor(YELLOW);
                    rectangle(xa,ya,xa+80,ya+80);
                    setcolor(WHITE);
                    char char_a[20];
                    sprintf(char_a, "%d", A.mat[i][j]);
                    outtextxy(p,A.nrLinii*80+200,char_a);
                    modificare_p(p,A.mat[i][j]);
                    delay(1000);
                    if(i==A.nrLinii-1&&j==A.nrColoane-1)
                    {
                        outtextxy(p,A.nrLinii*80+200,"=");
                        p+=30;
                        delay(1000);
                    }
                    else
                    {
                        setcolor(WHITE);
                        outtextxy(p,A.nrLinii*80+200,"+");
                        p+=30;
                        delay(1000);
                    }
                    xa+=80;
                }
            }
            xprim-=80;
            ya+=80;
        }

        char char_b[20];
        sprintf(char_b, "%d", s);
        outtextxy(p,A.nrLinii*80+200,char_b);
    }

}



void arata_optiuni(int sus, int jos, int entries)
{
    int mid=(sus+jos)/2;
    line(screenWidth-100,mid,screenWidth-140,mid);

    int lungime=entries*75;
    int latime=150;
    int yStangaSus=mid-entries/2*75-20;
    ///cout<<yStangaSus; ca sa vedem coordonata
    int xStangaSus=screenWidth-140-latime;
    int xDreaptaJos=screenWidth-140;
    int yDreaptaJos=yStangaSus+lungime;
    ///cout<<yDreaptaJos;
    rectangle(xStangaSus,yStangaSus,xDreaptaJos,yDreaptaJos);

    int y;
    for(y=yStangaSus; y<=yDreaptaJos; y=y+75)
        line(xStangaSus,y,xDreaptaJos,y);
    int yButonPrecedent=yStangaSus;
    int yButon=yStangaSus+75;

    centreazaText2nivele("suma de pe","diag.principala",xStangaSus,xDreaptaJos,yButonPrecedent,yButon);
    yButonPrecedent=yButon;
    yButon=yButon+75;

    centreazaText2nivele("suma de deasupra","diag.principala",xStangaSus,xDreaptaJos,yButonPrecedent,yButon);
    yButonPrecedent=yButon;
    yButon=yButon+75;

    centreazaText2nivele("suma de sub","diag.principala",xStangaSus,xDreaptaJos,yButonPrecedent,yButon);
    yButonPrecedent=yButon;
    yButon=yButon+75;

    centreazaText2nivele("suma de pe","diag.secundara",xStangaSus,xDreaptaJos,yButonPrecedent,yButon);
    yButonPrecedent=yButon;
    yButon=yButon+75;

    centreazaText2nivele("suma de deasupra","diag.secundara",xStangaSus,xDreaptaJos,yButonPrecedent,yButon);
    yButonPrecedent=yButon;
    yButon=yButon+75;

    centreazaText2nivele("suma de sub","diag.secundara",xStangaSus,xDreaptaJos,yButonPrecedent,yButon);
    yButonPrecedent=yButon;
    yButon=yButon+75;

    ///facem butonul de back
    int xStangaSusBack=xDreaptaJos;
    int yStangaSusBack=yDreaptaJos-50;
    rectangle(xStangaSusBack,yStangaSusBack,xStangaSusBack+50,yDreaptaJos);
    centreazaText("BACK",xStangaSusBack,xStangaSusBack+50,yStangaSusBack,yDreaptaJos);
    ///DONE:de facut functional back, de pus patrate negre pe tot ecranul ca sa curat ce era inainte cand apas un buton de la optiuni
    ///done:de facut functii pentru toate butoanele
    ///DONE:de facut functie pentru restore la butoanele din optiuni

    decizieOptiuni();
}

void decizieOptiuni()
{
    POINT cursorPosition;

    int xStangaSus=screenWidth-140-150; ///150=latime
    int xDreaptaJos=screenWidth-140;
    int nr=0;

    while(1)
    {
        GetCursorPos(&cursorPosition);
        if(GetAsyncKeyState(VK_LBUTTON))
        {
            int mx=cursorPosition.x;
            int my=cursorPosition.y;
            //afisareCoordonate();
            if(mx>=1440-40-150 && mx<=1535-100-40 && my>=342 && my<=408) ///suma de pe dp
            {
                setfillstyle(BKSLASH_FILL,YELLOW);
                bar(screenWidth-98-40-150,320,screenWidth-2-100-40,390);

                setcolor(LIGHTCYAN);
                centreazaText2nivele("suma de pe","diag.principala",xStangaSus,xDreaptaJos,317,392);

                setfillstyle(SOLID_FILL,BLACK);
                bar(0,0,xStangaSus,screenHeight); ///sau xStangaSus, 767; 767=yDreaptaJos
                if(nr>=1)
                {
                    restore2niveleOptiuni("suma de deasupra","diag.principala",xStangaSus+1,xDreaptaJos,392+1,467,LIGHTRED);
                    restore2niveleOptiuni("suma de sub","diag.principala",xStangaSus+1,xDreaptaJos,467+1,542,LIGHTGREEN);
                    restore2niveleOptiuni("suma de pe","diag.secundara",xStangaSus+1,xDreaptaJos,542+1,617,LIGHTMAGENTA);
                    restore2niveleOptiuni("suma de deasupra","diag.secundara",xStangaSus+1,xDreaptaJos,617+1,692,LIGHTBLUE);
                    restore2niveleOptiuni("suma de sub","diag.secundara",xStangaSus+1,xDreaptaJos,692+1,767,LIGHTGRAY);
                }
                nr++;
                setcolor(WHITE);
                Beep(500,100);
                suma_diag_principala();
            }
            if(mx>=1250 && mx<=xDreaptaJos && my>=418 && my<=484) ///suma de deasupra dp.
            {
                setfillstyle(BKSLASH_FILL,RED);
                bar(screenWidth-98-40-150,395,screenWidth-2-100-40,465);

                setcolor(LIGHTCYAN);
                centreazaText2nivele("suma de deasupra","diag.principala",xStangaSus,xDreaptaJos,392,467);

                setfillstyle(SOLID_FILL,BLACK);
                bar(0,0,xStangaSus,screenHeight);

                if(nr>=1)
                {
                    restore2niveleOptiuni("suma de pe","diag.principala",xStangaSus+1,xDreaptaJos,317+1,392,YELLOW);
                    restore2niveleOptiuni("suma de sub","diag.principala",xStangaSus+1,xDreaptaJos,467+1,542,LIGHTGREEN);
                    restore2niveleOptiuni("suma de pe","diag.secundara",xStangaSus+1,xDreaptaJos,542+1,617,LIGHTMAGENTA);
                    restore2niveleOptiuni("suma de deasupra","diag.secundara",xStangaSus+1,xDreaptaJos,617+1,692,LIGHTBLUE);
                    restore2niveleOptiuni("suma de sub","diag.secundara",xStangaSus+1,xDreaptaJos,692+1,767,LIGHTGRAY);

                }
                nr++;
                setcolor(WHITE);
                Beep(500,100);
                suma_deasupra_diag_principala();
            }
            if(mx>=1250 && mx<=xDreaptaJos && my>=494 && my<=559) ///suma de sub dp.
            {
                setfillstyle(BKSLASH_FILL,GREEN);
                bar(screenWidth-98-40-150,470,screenWidth-2-100-40,540);

                setcolor(LIGHTCYAN);
                centreazaText2nivele("suma de sub","diag.principala",xStangaSus,xDreaptaJos,467,542);

                setfillstyle(SOLID_FILL,BLACK);
                bar(0,0,xStangaSus,screenHeight);

                if(nr>=1)
                {
                    restore2niveleOptiuni("suma de pe","diag.principala",xStangaSus+1,xDreaptaJos,317+1,392,YELLOW);
                    restore2niveleOptiuni("suma de deasupra","diag.principala",xStangaSus+1,xDreaptaJos,392+1,467,LIGHTRED);
                    restore2niveleOptiuni("suma de pe","diag.secundara",xStangaSus+1,xDreaptaJos,542+1,617,LIGHTMAGENTA);
                    restore2niveleOptiuni("suma de deasupra","diag.secundara",xStangaSus+1,xDreaptaJos,617+1,692,LIGHTBLUE);
                    restore2niveleOptiuni("suma de sub","diag.secundara",xStangaSus+1,xDreaptaJos,692+1,767,LIGHTGRAY);

                }
                nr++;
                setcolor(WHITE);
                Beep(500,100);
                suma_sub_diag_principala();
            }
            if(mx>=1250 && mx<=xDreaptaJos && my>=568 && my<=636) ///suma de pe ds.
            {
                setfillstyle(BKSLASH_FILL,MAGENTA);
                bar(screenWidth-98-40-150,545,screenWidth-2-100-40,615);

                setcolor(LIGHTCYAN);
                centreazaText2nivele("suma de pe","diag.secundara",xStangaSus,xDreaptaJos,542,617);

                setfillstyle(SOLID_FILL,BLACK);
                bar(0,0,xStangaSus,screenHeight);

                if(nr>=1)
                {
                    restore2niveleOptiuni("suma de pe","diag.principala",xStangaSus+1,xDreaptaJos,317+1,392,YELLOW);
                    restore2niveleOptiuni("suma de deasupra","diag.principala",xStangaSus+1,xDreaptaJos,392+1,467,LIGHTRED);
                    restore2niveleOptiuni("suma de sub","diag.principala",xStangaSus+1,xDreaptaJos,467+1,542,LIGHTGREEN);
                    restore2niveleOptiuni("suma de deasupra","diag.secundara",xStangaSus+1,xDreaptaJos,617+1,692,LIGHTBLUE);
                    restore2niveleOptiuni("suma de sub","diag.secundara",xStangaSus+1,xDreaptaJos,692+1,767,LIGHTGRAY);
                }
                nr++;
                setcolor(WHITE);
                Beep(500,100);
                suma_diag_secundara();
            }
            if(mx>=1250 && mx<=xDreaptaJos && my>=643 && my<=709) ///suma de deasupra ds.
            {
                setfillstyle(BKSLASH_FILL,BLUE);
                bar(screenWidth-98-40-150,620,screenWidth-2-100-40,690);

                setcolor(LIGHTCYAN);
                centreazaText2nivele("suma de deasupra","diag.secundara",xStangaSus,xDreaptaJos,617,692);

                setfillstyle(SOLID_FILL,BLACK);
                bar(0,0,xStangaSus,screenHeight);

                if(nr>=1)
                {
                    restore2niveleOptiuni("suma de pe","diag.principala",xStangaSus+1,xDreaptaJos,317+1,392,YELLOW);
                    restore2niveleOptiuni("suma de deasupra","diag.principala",xStangaSus+1,xDreaptaJos,392+1,467,LIGHTRED);
                    restore2niveleOptiuni("suma de sub","diag.principala",xStangaSus+1,xDreaptaJos,467+1,542,LIGHTGREEN);
                    restore2niveleOptiuni("suma de pe","diag.secundara",xStangaSus+1,xDreaptaJos,542+1,617,LIGHTMAGENTA);
                    restore2niveleOptiuni("suma de sub","diag.secundara",xStangaSus+1,xDreaptaJos,692+1,767,LIGHTGRAY);

                }
                nr++;
                setcolor(WHITE);
                Beep(500,100);
                suma_deasupra_diag_secundara();
            }
            if(mx>=1250 && mx<=xDreaptaJos && my>=720 && my<=785) ///suma de sub ds.
            {
                setfillstyle(BKSLASH_FILL,BROWN);
                bar(screenWidth-98-40-150,695,screenWidth-2-100-40,765);

                setcolor(LIGHTCYAN);
                centreazaText2nivele("suma de sub","diag.secundara",xStangaSus,xDreaptaJos,692,767);

                setfillstyle(SOLID_FILL,BLACK);
                bar(0,0,xStangaSus,screenHeight);

                if(nr>=1)
                {
                    restore2niveleOptiuni("suma de pe","diag.principala",xStangaSus+1,xDreaptaJos,317+1,392,YELLOW);
                    restore2niveleOptiuni("suma de deasupra","diag.principala",xStangaSus+1,xDreaptaJos,392+1,467,LIGHTRED);
                    restore2niveleOptiuni("suma de sub","diag.principala",xStangaSus+1,xDreaptaJos,467+1,542,LIGHTGREEN);
                    restore2niveleOptiuni("suma de pe","diag.secundara",xStangaSus+1,xDreaptaJos,542+1,617,LIGHTMAGENTA);
                    restore2niveleOptiuni("suma de deasupra","diag.secundara",xStangaSus+1,xDreaptaJos,617+1,692,LIGHTBLUE);
                }
                nr++;
                setcolor(WHITE);
                Beep(500,100);
                suma_sub_diag_secundara();
            }
            if(mx>=1397 && mx<=1444 && my>=743 && my<=786) ///back
            {
                setfillstyle(SOLID_FILL, BLACK);
                bar(0,0,screenWidth-100,screenHeight); ///bara din stanga
                bar(1400,705,1524,805);///acopera de tot back
                Beep(500,100);
                restore2nivele("sume de","elemente",525,600);
                deciziePaginaMatrice();/// nu trebuie pusa ca oricum nu se executa;; dupa break se intoare in deciziePaginaMatrici
                break;

            }
        }
    }
}


void deciziePaginaMatrice()
{

    POINT cursorPosition;

    int nr=0;

    while(1)
    {
        GetCursorPos(&cursorPosition);
        int mx=cursorPosition.x;
        int my=cursorPosition.y;


        if(GetAsyncKeyState(VK_LBUTTON))
        {
            ///afisareCoordonate();
            if(mx>=1440 && mx<=1530 && my>=27 && my<=92) ///adunare
            {
                setcolor(YELLOW);
                setfillstyle(SLASH_FILL,YELLOW);
                bar(screenWidth-98, 3, screenWidth-6, 73);
                setcolor(WHITE);
                buton_fara_referinta("adunare",75,0);

                setfillstyle(SOLID_FILL, BLACK);
                bar(0, 0, screenWidth-100, screenHeight);
                if(nr>=1)
                {
                    restore("scadere",75,150);
                    restore("inmultire",150,225);
                    restore2nivele("inmultire cu"," scalar",225,300);
                    restore("determinant",300,375);
                    restore("transpusa",375,450);
                    restore("inversa",450,525);
                    restore2nivele("sume de","elemente",525,600);
                    restore("meniu",600,675);///nu e necesar ca mergem direct in meniu fara vreun delay
                }
                nr++;
                Beep(500,100);
                adunare_matrice();
            }


            if(mx>=1440 && mx<=1530 && my>=104 && my<=165)  ///scadere
            {
                setfillstyle(SLASH_FILL,RED);
                bar(screenWidth-98, 78, screenWidth-6, 148);

                setcolor(WHITE);
                buton_fara_referinta("scadere",75,150);

                setfillstyle(SOLID_FILL, BLACK);
                bar(0, 0, screenWidth-100, screenHeight);

                if(nr>=1)
                {
                    restore("adunare",0,75);
                    restore("inmultire",150,225);
                    restore2nivele("inmultire cu"," scalar",225,300);
                    restore("determinant",300,375);
                    restore("transpusa",375,450);
                    restore("inversa",450,525);
                    restore2nivele("sume de","elemente",525,600);
                    restore("meniu",600,675);
                }

                nr++;
                Beep(500,100);
                scadere_matrice();
            }


            if(mx>=1440 && mx<=1530 && my>=179 && my<=242)  ///inmultire
            {

                setfillstyle(SLASH_FILL,GREEN);
                bar(screenWidth-98, 153, screenWidth-6, 223);

                setcolor(WHITE);
                buton_fara_referinta("inmultire",150,225);

                setfillstyle(SOLID_FILL, BLACK);
                bar(0, 0, screenWidth-100, screenHeight);

                if(nr>=1)
                {
                    restore("adunare",0,75);
                    restore("scadere",75,150);
                    restore2nivele("inmultire cu"," scalar",225,300);
                    restore("determinant",300,375);
                    restore("transpusa",375,450);
                    restore("inversa",450,525);
                    restore2nivele("sume de","elemente",525,600);
                    restore("meniu",600,675);
                }
                nr++;
                Beep(500,100);
                inmultire_matrice();
            }


            if(mx>=1440 && mx<=1530 && my>=254 && my<=317)  ///putere
            {

                setfillstyle(SLASH_FILL,MAGENTA);
                bar(screenWidth-98, 228, screenWidth-6, 298);

                setcolor(WHITE);
                buton2nivele_fara_referinta("inmultire cu"," scalar",225,300);

                setfillstyle(SOLID_FILL, BLACK);
                bar(0, 0, screenWidth-100, screenHeight);

                if(nr>=1)
                {
                    restore("adunare",0,75);
                    restore("scadere",75,150);
                    restore("inmultire",150,225);
                    restore("determinant",300,375);
                    restore("transpusa",375,450);
                    restore("inversa",450,525);
                    restore2nivele("sume de","elemente",525,600);
                    restore("meniu",600,675);
                }
                nr++;
                Beep(500,100);
                inmultire_matrice_cu_sclar();
            }

            if(mx>=1440 && mx<=1530 && my>=331 && my<=393)  ///determinant
            {
                setfillstyle(SLASH_FILL,BLUE);
                bar(screenWidth-98, 303, screenWidth-6, 373);

                setcolor(WHITE);
                buton_fara_referinta("determinant",300,375);

                setfillstyle(SOLID_FILL, BLACK);
                bar(0, 0, screenWidth-100, screenHeight);

                if(nr>=1)
                {
                    restore("adunare",0,75);
                    restore("scadere",75,150);
                    restore("inmultire",150,225);
                    restore2nivele("inmultire cu"," scalar",225,300);
                    restore("transpusa",375,450);
                    restore("inversa",450,525);
                    restore2nivele("sume de","elemente",525,600);
                    restore("meniu",600,675);
                }
                nr++;
                Beep(500,100);
                determinant_matrice();
            }

            if(mx>=1440 && mx<=1530 && my>=406 && my<=465) ///transpusa
            {

                setfillstyle(SLASH_FILL,CYAN);
                bar(screenWidth-98, 378, screenWidth-6, 448);

                setcolor(WHITE);
                buton_fara_referinta("transpusa",375,450);

                setfillstyle(SOLID_FILL, BLACK);
                bar(0, 0, screenWidth-100, screenHeight);

                if(nr>=1)
                {
                    restore("adunare",0,75);
                    restore("scadere",75,150);
                    restore("inmultire",150,225);
                    restore2nivele("inmultire cu"," scalar",225,300);
                    restore("determinant",300,375);
                    restore("inversa",450,525);
                    restore2nivele("sume de","elemente",525,600);
                    restore("meniu",600,675);
                }
                nr++;
                Beep(500,100);
                transpusa();
            }


            if(mx>=1440 && mx<=1530 && my>=477 && my<=541) ///inversa
            {

                setfillstyle(SLASH_FILL,BROWN);
                bar(screenWidth-98, 453, screenWidth-6, 523);

                setcolor(WHITE);
                buton_fara_referinta("inversa",450,525);

                setfillstyle(SOLID_FILL, BLACK);
                bar(0, 0, screenWidth-100, screenHeight);

                if(nr>=1)
                {
                    restore("adunare",0,75);
                    restore("scadere",75,150);
                    restore("inmultire",150,225);
                    restore2nivele("inmultire cu"," scalar",225,300);
                    restore("determinant",300,375);
                    restore("transpusa",375,450);
                    restore2nivele("sume de","elemente",525,600);
                    restore("meniu",600,675);
                }
                nr++;
                Beep(500,100);
                inversa();
            }


            if(mx>=1440 && mx<=1530 && my>=554 && my<=617) ///sume de elemente
            {
                setfillstyle(SLASH_FILL,LIGHTCYAN);
                bar(screenWidth-98, 528, screenWidth-6, 598);

                setcolor(WHITE);
                buton2nivele_fara_referinta("sume de","elemente",525,600);

                setfillstyle(SOLID_FILL, BLACK);
                bar(0, 0, screenWidth-100, screenHeight);

                if(nr>=1)
                {
                    restore("adunare",0,75);
                    restore("scadere",75,150);
                    restore("inmultire",150,225);
                    restore2nivele("inmultire cu"," scalar",225,300);
                    restore("determinant",300,375);
                    restore("transpusa",375,450);
                    restore("inversa",450,525);
                    restore("meniu",600,675);
                }
                nr++;
                Beep(500,100);
                arata_optiuni(525,600,6);
                decizieOptiuni();
            }

            if(mx>=1440 && mx<=1530 && my>=626 && my<=692)  ///meniu
            {
                bar(screenWidth-98, 603, screenWidth-6, 673);

                buton_fara_referinta("meniu",600,675);

                setfillstyle(SOLID_FILL, BLACK);
                bar(0, 0, screenWidth-100, screenHeight);

                if(nr>=1)
                {
                    restore("adunare",0,75);
                    restore("scadere",75,150);
                    restore("inmultire",150,225);
                    restore2nivele("inmultire cu"," scalar",225,300);
                    restore("determinant",300,375);
                    restore("transpusa",375,450);
                    restore("inversa",450,525);
                    restore2nivele("sume de","elemente",525,600);
                }
                nr++;
                Beep(500,100);
                clearviewport();
                loading();
                initializarePag1();
                deciziePagina1();
            }

        }
    }
}


void deciziePaginaVectori()
{


    POINT cursorPosition;

    int nr=0;

    while(1)
    {
        GetCursorPos(&cursorPosition);
        if(GetAsyncKeyState(VK_LBUTTON))
        {
            int mx=cursorPosition.x;
            int my=cursorPosition.y;
            if(mx>=1440 && mx<=1530 && my>=29 && my<=120) ///adunare elemente
            {
                setcolor(YELLOW);
                setfillstyle(SLASH_FILL,YELLOW);
                bar(screenWidth-98, 3, screenWidth-6, 98);

                setcolor(WHITE);
                buton2nivele_fara_referinta("adunare","elemente",1,100);

                setfillstyle(SOLID_FILL, BLACK);
                bar(0, 0, screenWidth-100, screenHeight);///sterge tot din partea dreapta
                if(nr>=1)
                {
                    restore2nivele("adunare","doi vectori",100,200); ///vezi part3
                    restore2nivele("inmultire"," cu scalar",200,300);
                    restore2nivele("shiftare","la stanga",200,300);
                    restore2nivele("shiftare","la dreapta",400,500);
                    restore2nivele("sortare","crescatoare",500,600);
                    restore2nivele("sortare","desc",600,700);
                    restore("meniu",700,800);
                }
                nr++;
                Beep(500,100);
                adunare_elemente_vector();
            }


            if(mx>=1440 && mx<=1530 && my>=127 && my<=220) ///adunare 2 vectori
            {
                setfillstyle(SLASH_FILL,RED);
                bar(screenWidth-98, 103, screenWidth-6, 198);

                setcolor(WHITE);
                buton2nivele_fara_referinta("adunare","doi vectori",101,200);

                setfillstyle(SOLID_FILL, BLACK);
                bar(0, 0, screenWidth-100, screenHeight);

                if(nr>=1)
                {
                    restore2nivele("adunare", "elemente",0,100);
                    restore2nivele("inmultire","cu scalar",200,300);
                    restore2nivele("shiftare","la stanga",300,400);
                    restore2nivele("shiftare","la dreapta",400,500);
                    restore2nivele("sortare","crescatoare",500,600);
                    restore2nivele("sortare","desc",600,700);
                    restore("meniu",700,800);
                }

                nr++;
                Beep(500,100);
                adunare_2_vectori();

            }


            if(mx>=1440 && mx<=1530 && my>=224 && my<=320)  ///inmultire cu scalar
            {

                setfillstyle(SLASH_FILL,GREEN);
                bar(screenWidth-98, 203, screenWidth-6, 298);

                setcolor(WHITE);
                buton2nivele_fara_referinta("inmultire","cu scalar",201,300);

                setfillstyle(SOLID_FILL, BLACK);
                bar(0, 0, screenWidth-100, screenHeight);

                if(nr>=1)
                {
                    restore2nivele("adunare", "elemente",0,100);
                    restore2nivele("adunare","doi vectori",100,200);
                    restore2nivele("shiftare","la stanga",300,400);
                    restore2nivele("shiftare","la dreapta",400,500);
                    restore2nivele("sortare","crescatoare",500,600);
                    restore2nivele("sortare","desc",600,700);
                    restore("meniu",700,800);
                }
                nr++;
                Beep(500,100);
                inmultire_vector_cu_scalar();

            }


            if(mx>=1440 && mx<=1530 && my>=324 && my<=419)  ///shiftare la stanga
            {

                setfillstyle(SLASH_FILL,GREEN);
                bar(screenWidth-98, 303, screenWidth-6, 398);

                setcolor(WHITE);
                buton2nivele_fara_referinta("shiftare ","la stanga",301,400);

                setfillstyle(SOLID_FILL, BLACK);
                bar(0, 0, screenWidth-100, screenHeight);

                if(nr>=1)
                {
                    restore2nivele("adunare", "elemente",0,100);
                    restore2nivele("adunare","doi vectori",100,200);
                    restore2nivele("inmultire"," cu scalar",200,300);
                    restore2nivele("shiftare","la dreapta",400,500);
                    restore2nivele("sortare","crescatoare",500,600);
                    restore2nivele("sortare","desc",600,700);
                    restore("meniu",700,800);

                }
                nr++;
                Beep(500,100);
                shiftStangaKpozitii();

            }


            if(mx>=1440 && mx<=1530 && my>=424 && my<=518)  ///shiftare la dreapta
            {

                setfillstyle(SLASH_FILL,GREEN);
                bar(screenWidth-98, 403, screenWidth-6, 498);

                setcolor(WHITE);
                buton2nivele_fara_referinta("shiftare","la dreapta",401,500);

                setfillstyle(SOLID_FILL, BLACK);
                bar(0, 0, screenWidth-100, screenHeight);

                if(nr>=1)
                {
                    restore2nivele("adunare", "elemente",0,100);
                    restore2nivele("adunare","doi vectori",100,200);
                    restore2nivele("inmultire","cu scalar",200,300);
                    restore2nivele("shiftare","la stanga",300,400);
                    restore2nivele("sortare","crescatoare",500,600);
                    restore2nivele("sortare","desc",600,700);
                    restore("meniu",700,800);


                }
                nr++;
                Beep(500,100);
                shiftDreaptaKpozitii();

            }


            if(mx>=1440 && mx<=1530 && my>=527 && my<=619) ///sortare cresc
            {

                setfillstyle(SLASH_FILL,BLUE);
                bar(screenWidth-98, 503, screenWidth-6, 598);

                setcolor(WHITE);
                buton2nivele_fara_referinta("sortare","crescatoare",501,600);

                setfillstyle(SOLID_FILL, BLACK);
                bar(0, 0, screenWidth-100, screenHeight);

                if(nr>=1)
                {
                    restore2nivele("adunare","elemente",0,100);
                    restore2nivele("adunare","doi vectori",100,200);
                    restore2nivele("inmultire","cu scalar",200,300);
                    restore2nivele("shiftare","la stanga",300,400);
                    restore2nivele("shiftare","la dreapta",400,500);
                    restore2nivele("sortare","desc",600,700);
                    restore("meniu",700,800);


                }
                nr++;
                Beep(500,100);
                sortareCrescatoare();

            }

            if(mx>=1440 && mx<=1530 && my>=630 && my<=720) ///sortare desc
            {

                setfillstyle(SLASH_FILL,BLUE);
                bar(screenWidth-98, 603, screenWidth-6,698 );

                setcolor(WHITE);
                buton2nivele_fara_referinta("sortare","desc",601,700);

                setfillstyle(SOLID_FILL, BLACK);
                bar(0, 0, screenWidth-100, screenHeight);

                if(nr>=1)
                {
                    restore2nivele("adunare","elemente",0,100);
                    restore2nivele("adunare","doi vectori",100,200);
                    restore2nivele("inmultire","cu scalar",200,300);
                    restore2nivele("shiftare","la stanga",300,400);
                    restore2nivele("shiftare","la dreapta",400,500);
                    restore2nivele("sortare","crescatoare",500,600);
                    restore("meniu",700,800);

                }
                nr++;
                Beep(500,100);
                sortareDescrescatoare();
            }
             if(mx>=1440 && mx<=1530 && my>=733 && my<=821) ///meniu
            {

                setfillstyle(SLASH_FILL,BLUE);
                bar(screenWidth-98, 703, screenWidth-6,798 );

                setcolor(WHITE);
                buton_fara_referinta("meniu",701,800);

                setfillstyle(SOLID_FILL, BLACK);
                bar(0, 0, screenWidth-100, screenHeight);

                if(nr>=1)
                {
                    restore2nivele("adunare","elemente",0,100);
                    restore2nivele("adunare","doi vectori",100,200);
                    restore2nivele("inmultire","cu scalar",200,300);
                    restore2nivele("shiftare","la stanga",300,400);
                    restore2nivele("shiftare","la dreapta",400,500);
                    restore2nivele("sortare","crescatoare",500,600);
                    restore2nivele("sortare","desc",600,700);

                }
                nr++;
                Beep(500,100);
                clearviewport();
                loading();
                initializarePag1();
                deciziePagina1();
            }

        }

    }

}
void paginaMatrici()
{
    clearviewport();


    int yButon=75;
    int yButonPrecedent=0;
    buton("adunare",yButonPrecedent,yButon);
    buton("scadere",yButonPrecedent,yButon);
    buton("inmultire",yButonPrecedent,yButon);
    buton2nivele("inmultire cu"," scalar",yButonPrecedent,yButon);
    buton("determinant",yButonPrecedent,yButon);
    buton("transpusa",yButonPrecedent,yButon);
    buton("inversa",yButonPrecedent,yButon);
    buton2nivele("sume de","elemente",yButonPrecedent,yButon);
    buton("meniu",yButonPrecedent,yButon);

    deciziePaginaMatrice();

}
void buton2nivele_fara_referinta(char* a, char* b, int yButonPrecedent, int yButon)
{
    setlinestyle(SOLID_LINE,1,1);
    rectangle(screenWidth-100,yButonPrecedent,screenWidth-5,yButon);

    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,1);
    centreazaText2nivele(a,b,screenWidth-100,screenWidth,yButonPrecedent,yButon);
}

void buton2nivele(char* a, char* b, int& yButonPrecedent, int& yButon) ///xButon - stanga sus; yButon - dreapta jos ///vezi explicatii coordonare part2
{
    setlinestyle(SOLID_LINE,1,1);
    rectangle(screenWidth-100,yButonPrecedent,screenWidth-5,yButon);

    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,1);
    centreazaText2nivele(a,b,screenWidth-100,screenWidth,yButonPrecedent,yButon);

    int dimensiunePatrat=yButon-yButonPrecedent;

    yButonPrecedent=yButon;
    yButon=yButon+dimensiunePatrat;
}

void centreazaText2nivele(char* a, char* b, int margineSt, int margineDr, int sus, int jos)
{
    settextstyle(3, HORIZ_DIR, 1);

    int midx=(margineSt+margineDr)/2;

    int width_a = textwidth (a);
    int height_a = textheight(a);
    int width_b = textwidth(b);
    int height_b = textheight(b);

    int distantaTextFataDeMargini = ( (jos-sus) - (height_a + height_b) ) / 2 ;

    outtextxy( midx-width_a/2, sus + distantaTextFataDeMargini, a);

    outtextxy( midx-width_b/2, jos - distantaTextFataDeMargini - height_b, b);

}

void paginaVectori()
{
    clearviewport();

    int yButon=100;
    int yButonPrecedent=0;
    buton2nivele("adunare","elemente",yButonPrecedent,yButon);
    buton2nivele("adunare","doi vectori",yButonPrecedent,yButon);
    buton2nivele("inmultire","cu scalar",yButonPrecedent,yButon);
    buton2nivele("shiftare","la stanga",yButonPrecedent,yButon);
    buton2nivele("shiftare","la dreapta",yButonPrecedent,yButon);
    buton2nivele("sortare","cresc",yButonPrecedent,yButon);
    buton2nivele("sortare","descresc",yButonPrecedent,yButon);
    buton("meniu",yButonPrecedent,yButon);

    deciziePaginaVectori();


}

void deciziePagina1()
{
    POINT cursorPosition;

    while(1)
    {
        GetCursorPos(&cursorPosition);
        int mx=cursorPosition.x;
        int my=cursorPosition.y;
        //afisareCoordonate();
        if(ismouseclick(WM_MOUSEMOVE))
        {
            if(mx>=530 && mx<=1010 && my>=54 && my<=94)
            {
                setcolor(YELLOW);
                int midx=getmaxx()/2;
                int midy=getmaxy()/2;

                settextstyle(3, HORIZ_DIR, 7);

                int width = textwidth ("Proiectul BibMat");
                int height = textheight("Proiectul BibMat");

                outtextxy(midx/**-width*4.5**/-width/2, 20, "Proiectul BibMat");
            }
            else
            {
                setcolor(WHITE);
                int midx=getmaxx()/2;
                int midy=getmaxy()/2;

                settextstyle(3, HORIZ_DIR, 7);

                int width = textwidth ("Proiectul BibMat");
                int height = textheight("Proiectul BibMat");

                outtextxy(midx/**-width*4.5**/-width/2, 20, "Proiectul BibMat");
            }


            if(mx>=110 && mx<=620 && my>=529 && my<=690)///buton matrici
            {
                setcolor(GREEN);
                setlinestyle(DASHED_LINE,1,1);
                rectangle(105,200+300,630,375+300);
                settextstyle(SANS_SERIF_FONT,HORIZ_DIR,5);
                outtextxy(275,270+300,"MATRICI");
                setcolor(WHITE);
            }
            else
            {
                setcolor(WHITE);
                setlinestyle(DASHED_LINE,1,1);
                rectangle(105,200+300,630,375+300);
                settextstyle(SANS_SERIF_FONT,HORIZ_DIR,5);
                outtextxy(275,270+300,"MATRICI");
            }

            if(mx>=110 && mx<=620 && my>=227 && my<=389)///buton vectori
            {
                setcolor(GREEN);
                setlinestyle(DASHED_LINE,1,1);
                rectangle(105,200,630,375);
                settextstyle(SANS_SERIF_FONT,HORIZ_DIR,5);
                outtextxy(260,270,"VECTORI");
                setcolor(WHITE);
            }
            else
            {
                setcolor(WHITE);
                setlinestyle(DASHED_LINE,1,1);
                rectangle(105,200,630,375);
                settextstyle(SANS_SERIF_FONT,HORIZ_DIR,5);
                outtextxy(260,270,"VECTORI");
            }

            if(mx>=905&&mx<=1415&&my>=227 && my<=389)///buton despre proiect
            {
                setcolor(GREEN);;
                setlinestyle(DASHED_LINE,1,1);
                rectangle(900,200,1425,375);
                settextstyle(SANS_SERIF_FONT,HORIZ_DIR,5);
                outtextxy(950,270,"DESPRE PROIECT");
                setcolor(WHITE);
            }
            else
            {
                setcolor(WHITE);
                setlinestyle(DASHED_LINE,1,1);
                rectangle(900,200,1425,375);
                settextstyle(SANS_SERIF_FONT,HORIZ_DIR,5);
                outtextxy(950,270,"DESPRE PROIECT");
            }

            if(mx>=905&&mx<=1415&&my>=529 && my<=690)///buton exit
            {
                setcolor(GREEN);
                setlinestyle(DASHED_LINE,1,1);
                rectangle(900,200+300,1425,375+300);
                settextstyle(SANS_SERIF_FONT,HORIZ_DIR,5);
                outtextxy(1100,270+300,"EXIT");
                setcolor(WHITE);
            }
            else
            {
                setcolor(WHITE);
                setlinestyle(DASHED_LINE,1,1);
                rectangle(900,200+300,1425,375+300);
                settextstyle(SANS_SERIF_FONT,HORIZ_DIR,5);
                outtextxy(1100,270+300,"EXIT");
            }

        }

        if(GetAsyncKeyState(VK_LBUTTON))
        {

            if(mx>=110 && mx<=620 && my>=227 && my<=389)
            {
                Beep(500,100);
                paginaVectori();
                getch();
                closegraph();
            }
            if(mx>=110 && mx<=620 && my>=529 && my<=690)
            {
                Beep(500,100);
                paginaMatrici();
                getch();
                closegraph();
            }
            if(mx>=905&&mx<=1415&&my>=227 && my<=389)
            {
                Beep(500,100);
                paginaDespreProiect();
                getch();
                closegraph();
            }
            if(mx>=905&&mx<=1415&&my>=529 && my<=690)
            {
                Beep(500,100);
                exit(0); ///in loc de closegraph(); -> da eroarea Drawing operation was attempted when there was no current window
            }
        }


        int oldwindow=getcurrentwindow();

        if(GetAsyncKeyState(VK_RBUTTON))
        {
            if(mx>=530 && mx<=1010 && my>=54 && my<=94)
            {
                initwindow(600,600,"Easter Egg");
                readimagefile("barney2.jpg",100,100,500,500);
                settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);

                outtextxy(600/2-textwidth("Easter Egg Found! Congrats!")/2,50,"Easter Egg Found! Congrats!");

                outtextxy(600/2-textwidth("Barney te saluta din epoca de piatra!")/2,80,"Barney te saluta din epoca de piatra!");

                outtextxy(600/2-textwidth("Press any key to return to the main page")/2,500,"Press any key to return to the main page");


                {
                    setcolor(BROWN);
                    settextstyle(SMALL_FONT,HORIZ_DIR,55);
                    outtextxy(600/2-textwidth("P.S. Si Barney foloseste WinBGIm")/2,550,"P.S. Si Barney foloseste WinBGIm");

                    POINT cursorPositionEaster;
                    GetCursorPos(&cursorPositionEaster);

                    getch();
                    closegraph(CURRENT_WINDOW);
                    setcurrentwindow(oldwindow);

                }
            }
        }
    }


}
void paginaDespreProiect()
{
    clearviewport();
    setcolor(WHITE);
    setlinestyle(SOLID_LINE,1,2);
    int xDes=50;int yDes=50;
    circle(xDes,yDes,30);
    setlinestyle(SOLID_LINE,1,2);
    line(xDes+5,yDes-15,xDes-13,yDes);
    line(xDes+5,yDes+15,xDes-13,yDes);

    POINT cursorPosition;

    settextstyle(1,0,4);
    outtextxy(600,50,"Despre proiect");
    settextstyle(1,0,2);
    outtextxy(75,150," BibMat este un proiect realizat de studentii in anul 1 la FII Curcudel Teodor si Muraru Cosmin  care are ");
    outtextxy(15,200,"ca scop vizualizarea operatiilor pe matrice (adunarea, scaderea, inmultirea a doua matrice, determinant si");
    outtextxy(15,250,"inversa pentru matrici patratice de ordin n ...), dar si pe vectori (adunarea elementelor unui vector, shiftarea");
    outtextxy(15,300,"si sortarea crescatoare/descrescatoare a unui vector).");
    settextstyle(1,0,3);
    outtextxy(75,400,"Sfaturi pentru utilizatori:");
    settextstyle(1,0,2);
    outtextxy(150,450,"-ganditi-va de doua ori inainte de a apasa un buton deoarece operatiile nu pot fi intrerupte.");
    outtextxy(150,500,"-la fiecare operatie veti fi rugati sa adaugati elementele din consola.");
    settextstyle(1,0,3);
    outtextxy(450,600,"De asemenea am adaugat si un mic Easter Egg!");
    outtextxy(370,650,"Distrati-va incercand sa il gasiti in cel mai neasteptat loc.");


    while(1)
    {
        GetCursorPos(&cursorPosition);
        int mx=cursorPosition.x;
        int my=cursorPosition.y;
        ///afisareCoordonate();
        if(ismouseclick(WM_MOUSEMOVE))
        {
            //if( (mx>=19 && mx<=25 && my>=61 && my<=87) || (mx>=25 && mx<=34 && my>=57 && my <=110) ||   (mx>=34 && mx<=69 && my>=44 && my <=97))
            if(mx>=xDes-30 && mx<=xDes+30 && my>=yDes-8 && my<=yDes+53)
            {
                setcolor(GREEN);
                circle(xDes,yDes,30);
                setlinestyle(SOLID_LINE,1,4);
                line(xDes+5,yDes-15,xDes-13,yDes);
                line(xDes+5,yDes+15,xDes-13,yDes);
            }
            else
            {
                setcolor(WHITE);
                circle(xDes,yDes,30);
                setlinestyle(SOLID_LINE,1,4);
                line(xDes+5,yDes-15,xDes-13,yDes);
                line(xDes+5,yDes+15,xDes-13,yDes);
            }
        }

        if(GetAsyncKeyState(VK_LBUTTON))
        {
            if(mx>=xDes-30 && mx<=xDes+30 && my>=yDes-8 && my<=yDes+53)
            {
                setcolor(WHITE);
                clearviewport();
                initializarePag1();
            }
        }

    }

}



void citire_matrice(matrice &a)
{
    int i,j;
    cout<<"Introduceti numarul de linii:";
    cin>>a.nrLinii;
    cout<<"Introduceti numarul de coloane:";
    cin>>a.nrColoane;
    cout<<"Introduceti elemente:"<<endl;
    for(i=0; i<a.nrLinii; i++)
        for(j=0; j<a.nrColoane; j++)
        {
            cout<<"Matrice["<<i<<"]["<<j<<"]=";
            cin>>a.mat[i][j];
        }
}


void initializeaza_vector(matrice &A,int linii, int coloane, int* p)
{
    int i,j,k;
    A.nrLinii=linii;
    A.nrColoane=linii; ///!!!!!!
    for(i=0; i<A.nrLinii; i++)
    {
        for(j=0; j<A.nrLinii; j++)
        {
            cout<<"Matrice["<<i<<"]["<<j<<"]=";
            cin>>A.mat[i][j];
            k=A.mat[i][j];
            *(p+i*A.nrLinii+j)=k;
        }
    }
}

void determinant_matrice()
{
    settextstyle(1,0,3);
    outtextxy(100,100,"Introduceti elementele matricei in consola");
    int linii,*p;
    cout<<"Cate linii? ";
    cin>>linii;

    p=new int[linii*linii];
    initializeaza_vector(A,linii,linii,p);
    setcolor(BLACK);
    bar(50,50,900,200);
    setcolor(WHITE);


    int xDes, yDes;
    xDes=75;
    yDes=100;

    int width=textwidth("det");
    int height=textheight("det");

    outtextxy(xDes-width-15,yDes + A.nrLinii*80/2 - height/2,"det"); ///height/2 pentru ca incepe sa deseneze de la y in jos si vreau sa il dau inapoi doar height/2 ca sa fie centrat
    deseneaza_matrice(A,xDes,yDes);
    delay(2000);
    double rez = determinant(linii,p);

    int XindiceEgal;
    int YindiceEgal;

    XindiceEgal=xDes+A.nrColoane*80+50;
    YindiceEgal=yDes+A.nrLinii*80/2;

    settextstyle(1,0,3);
    deseneaza_egal(XindiceEgal,YindiceEgal);
    delay(1000);


    outintxy(XindiceEgal+50+20,YindiceEgal-textheight("123456789")/2,rez);  ///nu pun +50+40 ca sa fie mai aproape de egal
    delay(1000);
    int c=250;
    if(linii==2)
    {
        outtextxy(20,A.nrLinii*80+150,"Determinantul unei matrice de ordin 2 se calculeaza astfel:");
        delay(2000);
        setcolor(BLUE);
        rectangle(xDes,yDes,xDes+80,yDes+80);
        setcolor(WHITE);
        outtextxy(c,A.nrLinii*80+250,"(");
        c+=30;
        outintxy(c,A.nrLinii*80+250,A.mat[0][0]);
        modificare_p(c,A.mat[0][0]);

        delay(800);
        rectangle(xDes,yDes,xDes+80,yDes+80);
        outtextxy(c,A.nrLinii*80+250,"*");
        c+=30;
        delay(800);
        setcolor(BLUE);
        rectangle(xDes+80,yDes+80,xDes+160,yDes+160);
        setcolor(WHITE);
        outintxy(c,A.nrLinii*80+250,A.mat[1][1]);
        modificare_p(c,A.mat[1][1]);
        outtextxy(c,A.nrLinii*80+250,")");
        c+=30;
        delay(800);

        setcolor(WHITE);
        rectangle(xDes+80,yDes+80,xDes+160,yDes+160);
        outtextxy(c,A.nrLinii*80+250,"-");
        c+=30;
        delay(800);

        setcolor(BLUE);
        rectangle(xDes+80,yDes,xDes+160,yDes+80);
        setcolor(WHITE);
        outtextxy(c,A.nrLinii*80+250,"(");
        c+=30;
        outintxy(c,A.nrLinii*80+250,A.mat[0][1]);
        modificare_p(c,A.mat[0][1]);
        delay(800);
        rectangle(xDes+80,yDes,xDes+160,yDes+80);
        outtextxy(c,A.nrLinii*80+250,"*");
        delay(800);
        c+=30;
        setcolor(BLUE);
        rectangle(xDes,yDes+80,xDes+80,yDes+160);
        setcolor(WHITE);
        outintxy(c,A.nrLinii*80+250,A.mat[1][0]);
        modificare_p(c,A.mat[1][0]);
        outtextxy(c,A.nrLinii*80+250,")");
        c+=30;
        delay(1000);
        setcolor(WHITE);
        rectangle(xDes,yDes+80,xDes+80,yDes+160);
        setcolor(BLUE);
        deseneaza_egal(XindiceEgal,YindiceEgal);
        setcolor(WHITE);
        outtextxy(c,A.nrLinii*80+250,"=");
        c+=30;
        delay(800);

        setcolor(WHITE);
        deseneaza_egal(XindiceEgal,YindiceEgal);
        outintxy(c,A.nrLinii*80+250,rez);
    }
    if(linii==3)
    {
        c=250;
        outtextxy(20,A.nrLinii*80+200,"Determinantul unei matrice de ordin 3 se calculeaza astfel:");
        delay(1000);
        setcolor(WHITE);
        outtextxy(c,A.nrLinii*80+250,"(");
        c+=30;
        delay(800);
        setcolor(BLUE);
        rectangle(xDes,yDes,xDes+80,yDes+80);
        setcolor(WHITE);
        outintxy(c,A.nrLinii*80+250,A.mat[0][0]);
        modificare_p(c,A.mat[0][0]);
        delay(800);
        rectangle(xDes,yDes,xDes+80,yDes+80);
        outtextxy(c,A.nrLinii*80+250,"*");
        c+=30;
        delay(800);

        setcolor(BLUE);
        rectangle(xDes+80,yDes+80,xDes+160,yDes+160);
        setcolor(WHITE);
        outintxy(c,A.nrLinii*80+250,A.mat[1][1]);
        modificare_p(c,A.mat[1][1]);
        delay(800);
        rectangle(xDes+80,yDes+80,xDes+160,yDes+160);
        outtextxy(c,A.nrLinii*80+250,"*");
        c+=30;
        delay(800);
        setcolor(WHITE);


        setcolor(BLUE);
        rectangle(xDes+160,yDes+160,xDes+240,yDes+240);
        setcolor(WHITE);
        outintxy(c,A.nrLinii*80+250,A.mat[2][2]);
        modificare_p(c,A.mat[2][2]);
        delay(800);
        setcolor(WHITE);
        rectangle(xDes+160,yDes+160,xDes+240,yDes+240);

        outtextxy(c,A.nrLinii*80+250,"+");
        c+=30;
        delay(800);

        setcolor(BLUE);
        rectangle(xDes,yDes+160,xDes+80,yDes+240);
        setcolor(WHITE);
        outintxy(c,A.nrLinii*80+250,A.mat[2][0]);
        modificare_p(c,A.mat[2][0]);
        delay(800);

        setcolor(WHITE);
        rectangle(xDes,yDes+160,xDes+80,yDes+240);
        outtextxy(c,A.nrLinii*80+250,"*");
        c+=30;
        delay(800);

        setcolor(BLUE);
        rectangle(xDes+80,yDes,xDes+160, yDes+80);
        setcolor(WHITE);
        outintxy(c,A.nrLinii*80+250,A.mat[0][1]);
        modificare_p(c,A.mat[0][1]);
        delay(800);

        setcolor(WHITE);
        rectangle(xDes+80,yDes,xDes+160, yDes+80);
        outtextxy(c,A.nrLinii*80+250,"*");
        c+=30;
        delay(800);

        setcolor(BLUE);
        rectangle(xDes+160,yDes+80,xDes+240, yDes+160);
        setcolor(WHITE);
        outintxy(c,A.nrLinii*80+250,A.mat[1][2]);
        modificare_p(c,A.mat[1][2]);
        delay(800);

        setcolor(WHITE);
        rectangle(xDes+160,yDes+80,xDes+240, yDes+160);
        delay(1000);

        outtextxy(c,A.nrLinii*80+250,"+");
        c+=30;
        delay(1000);

        setcolor(BLUE);
        rectangle(xDes,yDes+80,xDes+80,yDes+160);
        setcolor(WHITE);
        outintxy(c,A.nrLinii*80+250,A.mat[1][0]);
        modificare_p(c,A.mat[1][0]);
        delay(1000);

        setcolor(WHITE);
        rectangle(xDes,yDes+80,xDes+80,yDes+160);
        outtextxy(c,A.nrLinii*80+250,"*");
        c+=30;
        delay(1000);

        setcolor(BLUE);
        rectangle(xDes+80,yDes+160,xDes+160,yDes+240);
        setcolor(WHITE);
        outintxy(c,A.nrLinii*80+250,A.mat[2][1]);
        modificare_p(c,A.mat[2][1]);
        delay(1000);

        setcolor(WHITE);
        rectangle(xDes+80,yDes+160,xDes+160,yDes+240);
        outtextxy(c,A.nrLinii*80+250,"*");
        c+=30;
        delay(1000);

        setcolor(BLUE);
        rectangle(xDes+160,yDes,xDes+240,yDes+80);
        setcolor(WHITE);
        outintxy(c,A.nrLinii*80+250,A.mat[0][2]);
        modificare_p(c,A.mat[0][2]);
        delay(1000);

        setcolor(WHITE);
        rectangle(xDes+160,yDes,xDes+240,yDes+80);
        outtextxy(c,A.nrLinii*80+250,")");
        c+=30;
        delay(800);



        settextstyle(1,0,4);
        outtextxy((c/2)+150,A.nrLinii*80+300,"-");
        delay(800);
        c=250;
        settextstyle(1,0,3);



        outtextxy(c,A.nrLinii*80+350,"(");
        c+=30;
        delay(800);

        setcolor(BLUE);
        rectangle(xDes+160,yDes,xDes+240,yDes+80);
        setcolor(WHITE);
        outintxy(c,A.nrLinii*80+350,A.mat[0][2]);
        modificare_p(c,A.mat[0][2]);
        delay(800);
        rectangle(xDes+160,yDes,xDes+240,yDes+80);
        outtextxy(c,A.nrLinii*80+350,"*");
        c+=30;
        delay(800);

        setcolor(BLUE);
        rectangle(xDes+80,yDes+80,xDes+160,yDes+160);
        setcolor(WHITE);
        outintxy(c,A.nrLinii*80+350,A.mat[1][1]);
        modificare_p(c,A.mat[1][1]);
        delay(800);
        rectangle(xDes+80,yDes+80,xDes+160,yDes+160);
        outtextxy(c,A.nrLinii*80+350,"*");
        c+=30;
        delay(800);

        setcolor(BLUE);
        rectangle(xDes,yDes+160,xDes+80,yDes+240);
        setcolor(WHITE);
        outintxy(c,A.nrLinii*80+350,A.mat[2][0]);
        modificare_p(c,A.mat[2][0]);
        delay(800);
        setcolor(WHITE);
        rectangle(xDes,yDes+160,xDes+80,yDes+240);


        outtextxy(c,A.nrLinii*80+350,"+");
        c+=30;
        delay(800);

        setcolor(BLUE);
        rectangle(xDes,yDes+80,xDes+80,yDes+160);
        setcolor(WHITE);
        outintxy(c,A.nrLinii*80+350,A.mat[1][0]);
        modificare_p(c,A.mat[1][0]);
        delay(800);

        setcolor(WHITE);
        rectangle(xDes,yDes+80,xDes+80,yDes+160);
        outtextxy(c,A.nrLinii*80+350,"*");
        c+=30;
        delay(800);

        setcolor(BLUE);
        rectangle(xDes+80,yDes,xDes+160, yDes+80);
        setcolor(WHITE);
        outintxy(c,A.nrLinii*80+350,A.mat[0][1]);
        modificare_p(c,A.mat[0][1]);
        delay(800);

        setcolor(WHITE);
        rectangle(xDes+80,yDes,xDes+160, yDes+80);
        outtextxy(c,A.nrLinii*80+350,"*");
        c+=30;
        delay(800);

        setcolor(BLUE);
        rectangle(xDes+160,yDes+160,xDes+240, yDes+240);
        setcolor(WHITE);
        outintxy(c,A.nrLinii*80+350,A.mat[2][2]);
        modificare_p(c,A.mat[2][2]);
        delay(800);

        setcolor(WHITE);
        rectangle(xDes+160,yDes+160,xDes+240, yDes+240);


        outtextxy(c,A.nrLinii*80+350,"+");
        c+=30;
        delay(800);

        setcolor(BLUE);
        rectangle(xDes,yDes,xDes+80,yDes+80);
        setcolor(WHITE);
        outintxy(c,A.nrLinii*80+350,A.mat[0][0]);
        modificare_p(c,A.mat[0][0]);
        delay(800);

        setcolor(WHITE);
        rectangle(xDes,yDes,xDes+80,yDes+80);
        outtextxy(c,A.nrLinii*80+350,"*");
        c+=30;
        delay(800);

        setcolor(BLUE);
        rectangle(xDes+80,yDes+160,xDes+160,yDes+240);
        setcolor(WHITE);
        outintxy(c,A.nrLinii*80+350,A.mat[2][1]);
        modificare_p(c,A.mat[2][1]);
        delay(800);

        setcolor(WHITE);
        rectangle(xDes+80,yDes+160,xDes+160,yDes+240);
        outtextxy(c,A.nrLinii*80+350,"*");
        c+=30;
        delay(800);

        setcolor(BLUE);
        rectangle(xDes+160,yDes+80,xDes+240,yDes+160);
        setcolor(WHITE);
        outintxy(c,A.nrLinii*80+350,A.mat[1][2]);
        modificare_p(c,A.mat[1][2]);
        delay(800);

        setcolor(WHITE);
        rectangle(xDes+160,yDes+80,xDes+240,yDes+160);
        outtextxy(c,A.nrLinii*80+350,")");
        delay(800);
        outtextxy(c/2+120,A.nrLinii*80+400,"=");
        outintxy(c/2+150,A.nrLinii*80+400,rez);
    }
    delete[]p;

}




void afiseaza_vector_folosind_pointeri(int r, int c, int *ptr)
{
    int i,j;
    for(i=0; i<r; i++)
    {
        cout<<"[";
        for(j=0; j<c; j++)
        {
            cout<<" "<<*ptr;
            ptr=ptr+1;
        }
        cout<<"]"<<endl;
    }
    return;
}

int determinant(int n, int* p)
{
    double rez;
    rez=0;
    if(n ==1 || n==2)
    {
        if(n==1)
            rez=*p;
        else
        {
            int a,b,c,d;
            a=*p;
            b=*(p+1);
            c=*(p+2);
            d=*(p+3);
            rez=a*d-b*c;
        }
    }
    else
    {
        int semn=1,i,j,k,complement,solutie_interioara;
        int *q;
        q=new int[(n-1)*(n-1)];
        for(i=0; i<n; i++)
        {
            complement=*(p+i); ///complement algebric era cu semn
            int index_pentru_element = 0;
            int index_pentru_element_din_matricea_q = 0; ///matricea q = matricea mica
            for(j=0; j<n; j++)
            {
                for(k=0; k<n; k++)
                {
                    int element_din_matrice_mare = *(p+index_pentru_element);
                    if(j!=0 && k!=i)
                    {
                        *(q+index_pentru_element_din_matricea_q)=element_din_matrice_mare;
                        index_pentru_element_din_matricea_q++;
                    }
                    index_pentru_element++;
                }
            }
            solutie_interioara = semn*complement*determinant(n-1,q);
            rez=rez+solutie_interioara;
            semn=semn*(-1);
        }
        delete [] q;
    }
    return rez;
}

void loading()
{
    int mijlocX=getmaxx()/2;
    int mijlocY=getmaxy()/2;

    settextstyle(COMPLEX_FONT,HORIZ_DIR,6);

    int mijlocTextX=mijlocX-textwidth("LOADING...PLEASE WAIT")/2;
    int mijlocTextY=mijlocY-textheight("LOADING...PLEASE WAIT")/2;

    outtextxy(mijlocTextX,mijlocTextY-100,"LOADING...PLEASE WAIT");

    setlinestyle(SOLID_LINE,0,THICK_WIDTH);
    rectangle(mijlocX-500,mijlocY-50,mijlocX+505,mijlocY+50);

    int h=1;
    int ok=0;
    for(int i=mijlocX-495; i<= mijlocX+495; i+=20)  ///i de la 272 la 1262
    {
        delay(1);
        setcolor(GREEN);
        ///bar(i,mijlocY-45,i+20,mijlocY+45);
        for(int j=1; j<=20; j++)
            line(i+j,mijlocY-45,i+j,mijlocY+45);
        delay(1);
        i+=5;
    }
    clearviewport();
}
void inmultire_matrice_cu_sclar()
{
    settextstyle(1,0,3);
    outtextxy(100,100,"Introduceti elementele matricei in consola");
    citire_matrice(A);
    setcolor(BLACK);
    bar(50,50,900,200);
    setcolor(WHITE);

    int xDes, yDes;
    xDes=50;
    yDes=100;

    deseneaza_matrice(A,xDes,yDes);
    delay(700);

    int XindiceInmultire=xDes+A.nrColoane*80+75; //x-ul de unde incepe minusul
    int YindiceInmultire=yDes+A.nrLinii*80/2;

    deseneaza_cerc(XindiceInmultire,YindiceInmultire);


    cout<<"Introduceti scalar:";
    settextstyle(1,0,3);
    outtextxy(XindiceInmultire+75,YindiceInmultire-40,"Introduceti scalarul in consola");
    int elem;
    cin>>elem;
    setcolor(BLACK);
    bar(XindiceInmultire+65,YindiceInmultire-40-20,XindiceInmultire+75+500,YindiceInmultire-40+20);
    setcolor(WHITE);

    rectangle(XindiceInmultire+75,YindiceInmultire-40,XindiceInmultire+75+80,YindiceInmultire-40+80);
    incadrare_int_in_casuta(elem,XindiceInmultire+75,YindiceInmultire-40);
    delay(700);

    int XindiceEgal;
    int YindiceEgal;

    XindiceEgal=XindiceInmultire+150+80;
    YindiceEgal=YindiceInmultire;

    deseneaza_egal(XindiceEgal,YindiceEgal);
    delay(700);

    for(int i=0; i<A.nrLinii; i++)
    {
        for(int j=0; j<A.nrColoane; j++)
        {
            C.mat[i][j]=A.mat[i][j]*elem;
        }
    }
    C.nrLinii=A.nrLinii;
    C.nrColoane=A.nrColoane;
    deseneaza_matrice(C,XindiceEgal+120,yDes);
    delay(700);

    settextstyle(1,0,3);
    outtextxy(50,100+80*A.nrLinii+100,"Inmultirea unei matrici cu un scalar se realizeaza astfel:");
    int yText=100+80*A.nrLinii+100+50;

    int xa=50;
    int ya=100;
    int xe=XindiceInmultire+75;
    int ye=YindiceInmultire-40;
    int xc=XindiceEgal+120;
    int yc=yDes;
    for(int i=0; i<A.nrLinii; i++)
    {
        for(int j=0; j<A.nrColoane; j++)
        {
            int p=200;
            setcolor(MAGENTA);
            rectangle(xa,ya,xa+80,ya+80);
            setcolor(WHITE);
            outintxy(p,yText,A.mat[i][j]);
            modificare_p(p,A.mat[i][j]);
            delay(800);

            setcolor(MAGENTA);
            deseneaza_cerc(XindiceInmultire,YindiceInmultire);
            setcolor(WHITE);
            outtextxy(p,yText,"*");
            p+=30;
            delay(800);

            setcolor(MAGENTA);
            rectangle(XindiceInmultire+75,YindiceInmultire-40,XindiceInmultire+75+80,YindiceInmultire-40+80);
            setcolor(WHITE);
            outintxy(p,yText,elem);
            modificare_p(p,elem);
            delay(800);

            setcolor(MAGENTA);
            deseneaza_egal(XindiceEgal,YindiceEgal);
            setcolor(WHITE);
            outtextxy(p,yText,"=");
            p+=30;
            delay(800);

            setcolor(MAGENTA);
            rectangle(xc,yc,xc+80,yc+80);
            setcolor(WHITE);
            outintxy(p,yText,C.mat[i][j]);
            modificare_p(p,C.mat[i][j]);
            delay(800);

            setcolor(WHITE);
            rectangle(xc,yc,xc+80,yc+80);
            deseneaza_egal(XindiceEgal,YindiceEgal);
            rectangle(XindiceInmultire+75,YindiceInmultire-40,XindiceInmultire+75+80,YindiceInmultire-40+80);
            deseneaza_cerc(XindiceInmultire,YindiceInmultire);
            rectangle(xa,ya,xa+80,ya+80);

            setcolor(BLACK);  ///acoperim calculele
            bar(10,yText-30,700,yText+30);
            xa+=80;
            xc+=80;
            setcolor(WHITE);
        }
        ya+=80;
        yc+=80;
        xa=50;
        xc=XindiceEgal+120;
    }
    setcolor(BLACK);
    bar(10,yText-100,1000,yText+30);
    setcolor(WHITE);
}
void transpusa()
{
    citire_matrice(A);
    int xDes=50;
    int yDes=100;
    settextstyle(1,0,3);
    outtextxy(50,70,"Matricea A");
    delay(1000);
    settextstyle(0,0,2);
    deseneaza_matrice(A,xDes,yDes);
    delay(1000);

    At.nrColoane=A.nrLinii;
    At.nrLinii=A.nrColoane;

    for(int i=0; i<A.nrColoane; i++)
        for(int j=0; j<A.nrLinii; j++)
        {
            At.mat[i][j]=A.mat[j][i];
        }
    settextstyle(1,0,3);
    outtextxy(80*(A.nrColoane+4),70,"Transpusa matricei A");
    delay(800);
    settextstyle(0,0,2);
    deseneaza_matrice(At,80*(A.nrColoane+4),yDes);
    setlinestyle(0,0,5);


    int xa=xDes;
    int ya=yDes;

    int xb=80*(A.nrColoane+4);
    int yb=yDes;
    for(int i=0; i<A.nrLinii; i++)
    {
        for(int j=0; j<A.nrColoane; j++)
        {
            setcolor(GREEN);
            rectangle(xa,ya,xa+80,ya+80);
            rectangle(xb,yb,xb+80,yb+80);
            delay(800);
            xa=xa+80;
            yb=yb+80;
        }
        xa=xDes;
        ya=ya+80;
        xb=xb+80;
        yb=yDes;
    }

}

void inversa()
{
    matrice Adj;

    int dimensiune;
    cout<<"Dati numarul de linii: ";
    cin>>dimensiune;

    int *p;
    p=new int[dimensiune*dimensiune];

    int det=0;
    initializeaza_vector_transpusa( A,dimensiune,dimensiune,p,At,det);

    ///acum p-ul pointeaza la inceputul transpusei, nu la matricea initiala ca in functia determinant

    int xDes=50;
    int yDes=100;

    deseneaza_matrice(A,xDes,yDes);
    outtextxy(xDes,yDes-25,"MATRICEA A");

    int h=textheight("Determinantul=0 => Matricea nu e inversabila!!");
    int w=textwidth("Determinantul=0 => Matricea nu e inversabila!!");

    if(det==0)
    {
        outtextxy(50+A.nrColoane*80+10,100+A.nrLinii*80/2-h/2,"Determinantul=0 => Matricea nu e inversabila!!");
        return;
    }
    ///int dimensiune=A.nrLinii;

    deseneaza_matrice(At,xDes+A.nrColoane*80+100,yDes);
    outtextxy(xDes+A.nrColoane*80+100,yDes-25,"TRANSPUSA");

    Adj.nrLinii=dimensiune;
    Adj.nrColoane=dimensiune;
    int semn=1;
    int lin=0;
    int col=0;

    int *q;
    q=new int[(dimensiune-1)*(dimensiune-1)];
    for(int f=0; f<dimensiune; f++)
        for(int i=0; i<dimensiune; i++)
        {
            int complement=*(p+f*dimensiune+i);
            int index_pentru_element=0;
            int index_pentru_element_din_matricea_q=0;
            for(int j=0; j<dimensiune; j++)
            {
                for(int k=0; k<dimensiune; k++)
                {
                    int element_din_matricea_mare=*(p+index_pentru_element);
                    if(j!=f && k!=i)
                    {
                        *(q+index_pentru_element_din_matricea_q)=element_din_matricea_mare;
                        index_pentru_element_din_matricea_q++;
                    }
                    index_pentru_element++;
                }
            }
            int complement_algebric = semn*determinant(dimensiune-1,q); ///determinantul reprezinta minorul
            /**if(col==dimensiune)
            {
                lin++;
                col=0;
            }**/
            Adj.mat[lin][col]=complement_algebric;
            ///cout<<Adj.mat[lin][col]<<endl;
            col++;
            if(col==dimensiune)
            {
                lin++;
                col=0;
            }

            semn=semn*(-1);
        }

    deseneaza_matrice(Adj,xDes+A.nrColoane*80+100+At.nrColoane*80+100,yDes);
    outtextxy(xDes+A.nrColoane*80+100+At.nrColoane*80+100,yDes-25,"ADJUNCTA");

    cout<<det<<endl<<endl<<endl;
    /**for(int i=0;i<dimensiune;i++)
    {
        for(int j=0;j<dimensiune;j++)
        {
            Adj.mat[i][j]=Adj.mat[i][j]*1/det;
            cout<<fixed<<setprecision(4)<<Adj.mat[i][j]<<" ";

        }
        cout<<endl;
    }**/
    matriceFloat Inversa;
    for(int i=0; i<dimensiune; i++)
        for(int j=0; j<dimensiune; j++)
        {
            Inversa.mat[i][j]=(float)Adj.mat[i][j]/det;
            cout<<Inversa.mat[i][j]<<endl;
        }

    Inversa.nrLinii=dimensiune;
    Inversa.nrColoane=dimensiune;

    char digit_string[20];
    sprintf(digit_string, "%d", det);

    int xInv=xDes+75;
    int yInv=yDes+A.nrLinii*80+100;
    int lungimeDeterminant=textwidth(digit_string);
    int inaltimeDeterminant=textheight(digit_string); ///=20


    int yLinie=yInv+Inversa.nrLinii*80/2;
    line(xInv-10,yLinie,xInv-10-lungimeDeterminant, yLinie);
    int lungimeLinie=(xInv-10)-(xInv-10-lungimeDeterminant);

    cout<<"ylinie este "<<yLinie<<endl;
    outintxy(xInv-10-lungimeLinie/2-textwidth("1")/2,yLinie-inaltimeDeterminant-1,1);
    outintxy(xInv-10-lungimeDeterminant,yLinie+2,det);

    setlinestyle(0,0,4);
    ellipse(xInv,yLinie,0,360,1,1);

    deseneaza_matrice(Adj,xInv+10,yInv);
    outtextxy(xInv+10,yInv-25, "ADJUNCTA");

    int XindiceEgal=xInv+10+dimensiune*80+40;
    deseneaza_egal(XindiceEgal,yLinie);

    deseneaza_matrice_float(Inversa,XindiceEgal+40+40,yInv);
    outtextxy(XindiceEgal+40+40,yInv-25,"INVERSA");

    /** setcolor(BROWN);

     line(xDes-15,yInv+Inversa.nrLinii*80/2,xDes+15,yInv+Inversa.nrLinii*80/2);
     outintxy(xDes-15,yInv+Inversa.nrLinii*80/2,det);

     setcolor(WHITE);
     ///outtextxy(xDes,yDes+A.nrLinii*80+100,"1")**/

    delete[] p;
}

void initializeaza_vector_transpusa(matrice &A,int linii, int coloane, int* p, matrice &At, int &det)  ///p-ul e pentru transpusa
{
    int i,j,g,k;
    A.nrLinii=linii;
    A.nrColoane=linii; ///!!!!!!
    int*z;
    z=new int[A.nrLinii*A.nrLinii];
    for(i=0; i<A.nrLinii; i++)
    {
        for(j=0; j<A.nrLinii; j++)
        {
            cout<<"Matrice["<<i<<"]["<<j<<"]=";
            cin>>A.mat[i][j];
            g=A.mat[i][j];
            *(z+i*A.nrLinii+j)=g;
        }
    }
    det=determinant(A.nrLinii,z);

    At.nrLinii=linii;
    At.nrColoane=linii;
    for(i=0; i<A.nrLinii; i++)
        for(j=0; j<A.nrLinii; j++)
            At.mat[i][j]=A.mat[j][i];

    for(i=0; i<At.nrLinii; i++)
    {
        for(j=0; j<At.nrLinii; j++)
        {
            k=At.mat[i][j];
            *(p+i*A.nrLinii+j)=k;
        }
    }

}
void deseneaza_matrice_float(matriceFloat a,int x, int y)
{
    setlinestyle(0,0,3);
    int xCont=x;
    int yCont=y;
    for(int i=0; i<a.nrLinii; i++,yCont+=80)
    {
        for(int j=0; j<a.nrColoane; j++,xCont+=80)
        {
            rectangle(xCont,yCont,xCont+80,yCont+80);
            delay(500);

            char digit_string[20];
            sprintf(digit_string, "%.3f", a.mat[i][j]);

            if(a.mat[i][j]>=0) ///4 caractere + punct
            {
                centreazaText(digit_string,xCont,xCont+80,yCont,yCont+80);
            }
            if(a.mat[i][j]<0) ///5 caractere (4+minus) + punct
            {
                centreazaText(digit_string,xCont,xCont+80,yCont,yCont+80);
            }
        }
        xCont=x;
    }
}


