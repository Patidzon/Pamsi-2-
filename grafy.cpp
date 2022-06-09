#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>
#include <cstring>
using namespace std;
class grafmatrix
{
private:
    int v;
    double ** adj;
    double *parent;
public:
    grafmatrix(int v)
    {
        this->v=v;
        adj=new double*[v];
        for (int r = 0; r < v; r++)
        {
            adj[r]=new double[v];
            for (int c = 0; c < v; c++)
            {
                adj[r][c]=999;
            }
        }      
    }
    void dodajkrawedz(int a, int b,int c)
    {
        adj[a][b]=c;
        adj[b][a]=c;
    }  
    void wypisz()
    {
        for (int i = 0; i < v; i++)
        {
            for (int j = 0; j < v; j++)
            {   if (adj[i][j]==999)
            {
                cout<<0<<" ";
            }
            else
            {
                cout<<adj[i][j]<<" ";
            }
            
                
            }
            cout<<endl;
        }
    }
    int find (int i)
    {
        while (parent[i]!=i)
        {
            i=parent[i];
        }
        return i;
    }
    void unia(int i, int j)
    {
        int a = find(i);
        int b = find(j);
        parent[a] = b;
    }
    void kruskalMST()
     {
         int mincost=0;
         for (int i = 0; i < v; i++)
            {
                parent[i] = i;
                //cout<<parent[i]<<endl;
            }    
        int edge_count=0;
        while (edge_count<v-1)
        {
            int min=999,a=0,b=0;
            for (int i = 0; i < v; i++)
            {
                for (int j = 0; j < v; j++)
                {
                   if (find(i)!=find(j)&& adj[i][j]<min)
                   {//cout<<"test1"<<endl;
                       min=adj[i][j];
                       //cout<<adj[i][j]<<endl;
                    //cout<<"test2"<<endl;
                       a=i;
                       b=j;
                   }
                   
                }
                
            }

           unia(a,b);
           //cout<<"Edge"<<edge_count<<":"<<a<<","<<b<<"cost"<<min<<endl;
           mincost+=min; 
           edge_count++;
        }
        cout<<endl<<"Minimum cost="<<mincost<<endl;
     }  
     void PrimMst()
     {
        int edge_count=0;
        int mincost=0;
        int selected[v];
        memset (selected,false,sizeof(selected));
        selected[0]=true;
        while (edge_count<v-1)
        {
            int min=999,a=0,b=0;
            for (int i = 0; i < v; i++)
            {
                if(selected[i])
                {
                    for (int j = 0; j < v; j++)
                    {
                       if (!selected[j] &&adj[i][j])
                       {
                          if (min>adj[i][j])
                          {
                             min=adj[i][j];
                             a=i;
                             b=j;
                          }                         
                       }                     
                    }    
                }
            }
           // cout<<"Edge"<<edge_count<<":"<<a<<","<<b<<"cost"<<min<<endl;
            edge_count++;
            selected[b]=true;
            mincost+=min; 
        }
       cout<<endl<<"Minimum cost="<<mincost<<endl;
     }

};
struct Node 
{
    int waga;
    int nrwierzcholka;
    struct Node* next;
    public:

};
class graflist
{
private:
    int v;
    struct Node **l,*p;
public:
    graflist(int v)
    {
         this->v=v;
        l=new Node*[v];   
    }
    void dodajkrawedz(int a, int b,int c)
    {
       p=new Node;
       p->next=l[a-1];p->nrwierzcholka=b;p->waga=c;l[a-1]=p;
    }  
    void wypisz()
    {
        for (int i = 0; i < v-1; i++)
        {
            cout<<i+1<<":";
            p=l[i];
            while (p)
            {
                cout<<p->nrwierzcholka<<"#"<<p->waga<<" ";
                p=p->next;
            }
           cout<<endl; 
        }
        
    }
};
/*void tworzgraf(int v)
{int k;
int e=0;
cout<<"graf matrix -1"<<endl
<<"graf list -2"<<endl;
cin>>k;

for (int i = v-1; i > 0; i--)
{
    e=+i;
}
cout<<"maksymalna liczba krawedzi: "<<e<<endl;
}*/
bool check(double macA[],double macB[],int i, int a,int b)
{   if (i==0)
{
    macA[i]=a;
    macB[i]=b;
    return true;
   
}

    for (int j = 0; j < i; j++)
    {  //cout<<"test check a="<<a<<" b="<<b<<" a'="<<macA[j]<<" b'="<<macB[j]<<endl;
       if ((a==macA[j]&&b==macB[j])||a==b)
       {
          return false;
       }
        if ((b==macA[j]&&a==macB[j])||a==b)
       {
          return false;
       }
    }
    macA[i]=a;
    macB[i]=b;
    return true;
    
}
int main(){
double *macA, *macB;
int v,procent;
int e=0;
int a,b,c;
int srKruskal=0,srPrim=0;
 macA=new double[1000000];
 macB=new double[1000000];
 //int srK[100];
 //int srP[100];
 graflist gl(5);
gl.dodajkrawedz(1,2,4);
gl.dodajkrawedz(1,3,3);
gl.dodajkrawedz(3,2,1);
gl.dodajkrawedz(3,4,5);
gl.dodajkrawedz(4,1,7);
gl.wypisz();
 cout<<"podaj ilość wezlow"<<endl;
 cin>>v;
 grafmatrix g(v);
// graflist g1(v);
cout<<"podaj procent wypelnienia grafu(1-100)"<<endl;
cin>>procent;
for (int i = v-1; i > 0; i--)
{
    e=e+i;
}
e=e*procent/100;
cout<<"maksymalna liczba krawedzi: "<<e<<endl;
for (int z = 0; z < 1; z++)
{
   

    if (procent==100)
{
   for ( int i= 0; i < v; i++)
   {
      for (int j = i+1; j < v; j++)
      {
          c=rand() % 20+1;
          g.dodajkrawedz(i,j,c);  
         // g1.dodajkrawedz(i,j,c);
      }
      
   }
   
}
else{
for (double u = 0; u < e;u++)
{  


    /* code */


    a=rand() % v;
    b=rand() % v;
    c=rand() % 20+1;
    while (!check(macA,macB,u,a,b))
    {
    a=rand() % v;
    b=rand() % v;
    c=rand() % 20+1;
    }
    g.dodajkrawedz(a,b,c);  
   // g1.dodajkrawedz(a,b,c);  


}
}
cout<<"graf na liscie"<<endl;
//g1.wypisz();
cout<<endl<<"tworzenie drzewa"<<endl;
cout<<"Kruskal"<<endl;
auto poczatek = std::chrono::high_resolution_clock::now();
g.kruskalMST();
auto koniec = std::chrono::high_resolution_clock::now();
std::chrono::duration<double> elapsed=koniec-poczatek;
cout<<"czas dzialania kruskal: ";
cout<<elapsed.count()<<endl;
cout<<endl<<endl;
cout<<"Prim"<<endl;
poczatek = std::chrono::high_resolution_clock::now();
g.PrimMst();
koniec = std::chrono::high_resolution_clock::now();
elapsed=koniec-poczatek;
cout<<"czas dzialania prim: ";
cout<<elapsed.count()<<endl;
//srP[z]=elapsed.count();
}
/*for (int i = 0; i < 100; i++)
{
    srKruskal=srKruskal+srK[i];
}
for (int i = 0; i < 100; i++)
{
    srPrim=srPrim+srP[i];
}*/
//cout<<"sredni czas dzialania algorytmu kruskala to:"<<srKruskal/100<<"sekund"<<endl;
//cout<<"sredni czas dzialania algorytmu Prima to:"<<srPrim/100<<"sekund"<<endl;
    return 0;
}