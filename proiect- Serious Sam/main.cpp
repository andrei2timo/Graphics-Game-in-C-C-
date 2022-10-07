#include <iostream>
#include <fstream>
#include <cstdlib>
#include <graphics.h>

using namespace std;
struct pozitie
{
    int X, Y;
} d[2500], dopt[2500];
struct coordonate
{
    int Cf,Lf;
} v[100];
int lopt=2500;
int a[50][50];
int n,m,Li,Ci,k,latura=80;
int ns;
void citire()
{
    ifstream f("labirint.in");
    f>>n>>m;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            f>>a[i][j];
    f>>Li>>Ci;
    for(int i=1; i<=m; i++)
        f>>v[i].Lf>>v[i].Cf;
}
void afisare()
{
    int i, j;
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=n; j++)
            cout<<a[i][j];
        cout<<endl;
    }
    cout<<endl;
}
void afisare1()
{
    int i, j;
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=n; j++)
            cout<<(char)(a[i][j]+177);
        cout<<endl;
    }
    cout<<endl;
}
void incarca_imagine(int i, int j, int val);
void afisare2()
{
    int i, x, y;
    for(i=1; i<=k; i++)
    {
        cout<<"("<<d[i].X<<","<<d[i].Y<<") ";
        x=d[i].X;
        y=d[i].Y;
        incarca_imagine(x,y,11);
        delay(300);
        incarca_imagine(x,y,0);
    }
    for(i=1; i<=m; i++)
        incarca_imagine(v[i].Lf,v[i].Cf,3);
    cout<<endl;
}
void afiseaza_drumul_optim()
{
    int i,x,y;
    for(i=1; i<=lopt; i++)
    {
        cout<<"("<<dopt[i].X<<","<<dopt[i].Y<<") ";
        x=dopt[i].X;
        y=dopt[i].Y;
        incarca_imagine(x,y,11);
        delay(300);
        incarca_imagine(x,y,0);
    }
    incarca_imagine(x,y,0);
}
void incarca_imagine(int i, int j, int val)
{
    int x, y;
    x=(j-1)*latura;
    y=(i-1)*latura;
    char nf[20];
    itoa(val, nf,10);
    strcat(nf,".jpg");
    readimagefile(nf,x,y,x+latura,y+latura);
}
void  actualizeaza_drum_optim()
{
    lopt=k;
    for(int i=1; i<=k; i++)
        dopt[i]=d[i];
}
void sol(int x, int y,int Lf,int Cf)
{
    if(a[x][y]==0)
    {
        a[x][y]=2;
        k++;
        d[k].X=x;
        d[k].Y=y;
        if(x==Lf && y==Cf)
        {
            afisare();
            //afisare1();
            //afisare2();
            ns++;
            if(k<lopt)
                actualizeaza_drum_optim();
        }
        else
        {
            sol(x-1,y,Lf,Cf);
            sol(x,y+1,Lf,Cf);
            sol(x+1,y,Lf,Cf);
            sol(x,y-1,Lf,Cf);
        }
        a[x][y]=0;
        k--;
    }
}
void bordare()
{
    for(int i=0; i<=n+1; i++)
        a[0][i]=a[n+1][i]=a[i][0]=a[i][n+1]=1;
}
void generare_fereastra_grafica()
{
    int H, W;
    H=n*latura;
    W=n*latura;
    initwindow(H,W," L A B I R I N T");
}
void generez_labirint()
{
    int i, j;
    for(i=1; i<=n; i++)
        for(j=1; j<=n; j++)
            incarca_imagine(i,j,a[i][j]);
    incarca_imagine(Li,Ci,11);///11 este un soricel
    for(i=1; i<=m; i++)
        incarca_imagine(v[i].Lf,v[i].Cf,3);
}
int main()
{
    citire();
    generare_fereastra_grafica();
    generez_labirint();
    //afisare();
    //afisare1();
    //bordare();
    for(int i=1; i<=m; i++)
    {
        k=0;
        lopt=2500;
        sol(Li,Ci,v[i].Lf,v[i].Cf);
        afiseaza_drumul_optim();
    }

    cout<<endl;
    cout<<"Sunt "<<ns<<" solutii.";
    system("pause");
    return 0;
}
