#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

struct Grade
{
    int grad_ext;
    int grad_int;
};
class Nod
{
    int *grad_extern,*grad_intern;
    int *indice;
    int *arce;
    friend class GrafOrientat;
public:
    Nod();
    Nod(const Nod&);
    ~Nod();
    Nod& operator =(const Nod&);
    void setgrad_intern0()
    {
        (*grad_intern)=0;
    }
    void setgrad_intern()
    {
        (*grad_intern)++;
    }
    void setgrad_extern(int &x)
    {
        *grad_extern=x;
    }
    void setindice(int &i)
    {
        *indice=i;
    }
    void setarce(int *);
    int getgrad_intern()
    {
        return *grad_intern;
    }
    int getgrad_extern()
    {
        return *grad_extern;
    }
    int getindice()
    {
        return *indice;
    }
    int* getarce();
};
Nod::Nod()
{
    grad_extern=new int;
    grad_intern=new int;
    *grad_intern=0;
    *grad_extern=0;
    indice=new int;
}
Nod::Nod(const Nod &nod)
{
    grad_extern=new int;
    grad_intern=new int;
    indice=new int;
    *grad_intern=*nod.grad_intern;
    *grad_extern=*nod.grad_extern;
    *indice=*nod.indice;
    arce=new int[*grad_extern];
    for(int i=0;i<*grad_extern;i++)
    {
        arce[i]=nod.arce[i];
    }
}
Nod::~Nod()
{
    delete grad_extern;
    delete grad_intern;
    delete indice;
    delete[] arce;
}
Nod& Nod::operator=(const Nod &n1)
{
    if(this==&n1)
        return *this;
    *grad_extern=*n1.grad_extern;
    *grad_intern=*n1.grad_intern;
    *indice=*n1.indice;
    delete[] arce;
    arce=new int[*grad_extern];
    for(int i=0;i<*grad_extern;i++)
    {
        arce[i]=n1.arce[i];
    }
    return *this;
}
int* Nod::getarce()
{
    int *p=new int[*grad_extern];
    for(int i=0;i<*grad_extern;i++)
    {
        p[i]=arce[i];
    }
    return p;
}
void Nod::setarce(int *arc)
{
    arce=new int[*grad_extern];
    for(int i=0;i<*grad_extern;i++)
    {
        arce[i]=arc[i];
    }
}
class GrafOrientat
{
    int *numar_noduri;
    Nod *graf;
public:
    GrafOrientat();
    GrafOrientat(const GrafOrientat&);
    ~GrafOrientat();
    friend istream& operator >>(istream &,GrafOrientat &);
    friend ostream& operator <<(ostream &,const GrafOrientat &);
    friend bool operator ==(const GrafOrientat&,const GrafOrientat&);
    friend bool operator !=(const GrafOrientat&,const GrafOrientat&);
    friend bool operator >(const GrafOrientat&,const GrafOrientat&);
    friend bool operator <(const GrafOrientat&,const GrafOrientat&);
    friend GrafOrientat& operator +(const GrafOrientat&,const GrafOrientat&);
    GrafOrientat& operator =(const GrafOrientat&);
    int** det_matrice_drumuri();
    bool graf_aciclic();
    bool graf_tare_conex();
    int* componente_tare_conexe();
    void sortare_topologica();
    void BFS(int);
    void DFS(int);
};
GrafOrientat::GrafOrientat()
{
    numar_noduri=new int;
}
GrafOrientat::GrafOrientat(const GrafOrientat &graff)
{
    numar_noduri=new int;
    *numar_noduri=*graff.numar_noduri;
    graf=new Nod[*graff.numar_noduri];
    for(int i=0;i<*graff.numar_noduri;i++)
    {
        graf[i]=graff.graf[i];
    }
}
GrafOrientat::~GrafOrientat()
{
    delete numar_noduri;
    delete[] graf;
}
int cmp(const void *a,const void *b)
{
    Grade *x=(Grade*)a,*y=(Grade*)b;
    if(x->grad_ext<y->grad_ext)
        return -1;
    else if(x->grad_ext>y->grad_ext)
        return 1;
    return 0;
}
GrafOrientat& GrafOrientat:: operator =(const GrafOrientat &g)
{
    if(this==&g)
        return *this;
    *numar_noduri=*g.numar_noduri;
    delete[] graf;
    graf=new Nod[*numar_noduri];
    for(int i=0;i<*numar_noduri;i++)
    {
        graf[i]=g.graf[i];
    }
    return *this;
}
bool operator ==(const GrafOrientat &g1,const GrafOrientat &g2)
{
    if(*g1.numar_noduri!=*g2.numar_noduri)
        return false;
    Grade *grade1=new Grade[*g1.numar_noduri];
    Grade *grade2=new Grade[*g1.numar_noduri];
    for(int i=0;i<*g1.numar_noduri;i++)
    {
        grade1[i].grad_ext=g1.graf[i].getgrad_extern();
        grade1[i].grad_int=g1.graf[i].getgrad_intern();
        grade2[i].grad_ext=g2.graf[i].getgrad_extern();
        grade2[i].grad_int=g2.graf[i].getgrad_intern();
    }
    qsort(grade1,*g1.numar_noduri,sizeof(Grade),cmp);
    qsort(grade2,*g1.numar_noduri,sizeof(Grade),cmp);
    for(int i=0;i<*g1.numar_noduri;i++)
    {
        if(grade1[i].grad_ext!=grade2[i].grad_ext || grade1[i].grad_int!=grade2[i].grad_int)
            return false;
    }
    return true;
}
bool operator !=(const GrafOrientat &g1,const GrafOrientat &g2)
{
    if(*g1.numar_noduri!=*g2.numar_noduri)
        return true;
    Grade *grade1=new Grade[*g1.numar_noduri];
    Grade *grade2=new Grade[*g1.numar_noduri];
    for(int i=0;i<*g1.numar_noduri;i++)
    {
        grade1[i].grad_ext=g1.graf[i].getgrad_extern();
        grade1[i].grad_int=g1.graf[i].getgrad_intern();
        grade2[i].grad_ext=g2.graf[i].getgrad_extern();
        grade2[i].grad_int=g2.graf[i].getgrad_intern();
    }
    qsort(grade1,*g1.numar_noduri,sizeof(Grade),cmp);
    qsort(grade2,*g1.numar_noduri,sizeof(Grade),cmp);
    for(int i=0;i<*g1.numar_noduri;i++)
    {
        if(grade1[i].grad_ext!=grade2[i].grad_ext || grade1[i].grad_int!=grade2[i].grad_int)
            return true;
    }
    return false;
}
bool operator <(const GrafOrientat &g1,const GrafOrientat &g2)
{
    return *g1.numar_noduri<*g2.numar_noduri;
}
bool operator >(const GrafOrientat &g1,const GrafOrientat &g2)
{
    return *g1.numar_noduri>*g2.numar_noduri;
}
istream& operator >>(istream &in,GrafOrientat &g)
{
    int x;
    in>>x;
    *g.numar_noduri=x;
    g.graf=new Nod[x];
    for(int i=0;i<x;i++)
    {
        int a,m;
        in>>a>>m;
        g.graf[i].setindice(a);
        g.graf[i].setgrad_extern(m);
        int *arc=new int[m];
        for(int j=0;j<m;j++)
        {
            in>>arc[j];
        }
        g.graf[i].setarce(arc);
    }
    for(int i=0;i<x;i++)
    {
        int *arc=g.graf[i].getarce();
        int gr_ext=g.graf[i].getgrad_extern();
        for(int j=0;j<gr_ext;j++)
        {
            int u;
            for(u=0;u<*g.numar_noduri;u++)
            {
                if(arc[j]==g.graf[u].getindice())
                {
                    g.graf[u].setgrad_intern();
                    break;
                }
            }
        }
    }
    return in;
}
ostream& operator <<(ostream &out,const GrafOrientat &g)
{
    out<<"Numarul de noduri:"<<*g.numar_noduri<<endl;
    for(int i=0;i<*g.numar_noduri;i++)
    {
        out<<"Nodul cu indicele "<<g.graf[i].getindice()<<", grad extern "<<g.graf[i].getgrad_extern()<<", grad intern "<<g.graf[i].getgrad_intern()<<", arce catre:";
        int *p;
        p=g.graf[i].getarce();
        for(int j=0;j<g.graf[i].getgrad_extern();j++)
        {
            out<<" "<<p[j];
        }
        out<<endl;
    }
    return out;
}
GrafOrientat& operator +(const GrafOrientat &g1,const GrafOrientat &g2)
{
    GrafOrientat *g3=new GrafOrientat;
    *g3=g1;
    for(int i=0;i<*g2.numar_noduri;i++)
    {
        int j;
        for(j=0;j<*(g3->numar_noduri);j++)
        {
            if(g2.graf[i].getindice()==g3->graf[j].getindice())
                break;
        }
        int *arc2=g2.graf[i].getarce();
        int *arc3=g3->graf[j].getarce();
        int *arc=new int[*g1.numar_noduri];
        int k3=-1;
        for(int k=0;k<g2.graf[i].getgrad_extern();k++)
        {
            int o=0;
            for(int k1=0;k1<g3->graf[j].getgrad_extern();k1++)
                if(arc2[k]==arc3[k1])
            {
                o=1;
                break;
            }
            if(o==0)
            {
                k3++;
                arc[k3]=arc2[k];
            }
        }
        int *arct=new int[g3->graf[j].getgrad_extern()+k3+1];
        for(int k=0;k<g3->graf[j].getgrad_extern();k++)
        {
            arct[k]=arc3[k];
        }
        int k=g3->graf[j].getgrad_extern();
        for(int k1=0;k1<=k3;k1++)
        {
            arct[k]=arc[k1];
            k++;
        }
        int x=g3->graf[j].getgrad_extern()+k3+1;
        g3->graf[j].setgrad_extern(x);
        g3->graf[j].setarce(arct);
    }
    for(int i=0;i<*(g3->numar_noduri);i++)
        g3->graf[i].setgrad_intern0();
    for(int i=0;i<*(g3->numar_noduri);i++)
    {
        int *arc=g3->graf[i].getarce();
        int gr_ext=g3->graf[i].getgrad_extern();
        for(int j=0;j<gr_ext;j++)
        {
            int u;
            for(u=0;u<*(g3->numar_noduri);u++)
            {
                if(arc[j]==g3->graf[u].getindice())
                {
                    g3->graf[u].setgrad_intern();
                    break;
                }
            }
        }
    }
    return *g3;
}
void GrafOrientat::BFS(int nod_start)
{
    int *coada=new int[*numar_noduri];
    int *viz=new int[*numar_noduri];
    for(int i=0;i<*numar_noduri;i++)
    {
        viz[i]=0;
    }
    int k=0,o=0;
    coada[k]=nod_start;
    while(o<=k)
    {
        int i;
        for(i=0;i<*numar_noduri;i++)
        {
            if(coada[o]==graf[i].getindice())
                break;
        }
        viz[i]=1;
        cout<<coada[o]<<" ";  ///prelucrare info
        int *p=graf[i].getarce();
        for(int t1=0;t1<graf[i].getgrad_extern();t1++)
        {
            int t2;
            for(t2=0;t2<*numar_noduri;t2++)
            {
                if(p[t1]==graf[t2].getindice())
                    break;
            }
            if(viz[t2]==0)
            {
                k++;
                coada[k]=p[t1];
            }
        }
        o++;
    }
}
void GrafOrientat::DFS(int nod_start)
{
    int *stiva=new int[*numar_noduri];
    int *viz=new int[*numar_noduri];
    for(int i=0;i<*numar_noduri;i++)
    {
        viz[i]=0;
    }
    int k=0;
    stiva[k]=nod_start;
    while(k>=0)
    {
        int i;
        for(i=0;i<*numar_noduri;i++)
        {
            if(stiva[k]==graf[i].getindice())
                break;
        }
        stiva[k]=-1;
        k--;
        if(viz[i]==0)
        {
            viz[i]=1;
            ///cout<<graf[i].getindice()<<" ";  ///prelucrare info
            int *p=graf[i].getarce();
            for(int t1=0;t1<graf[i].getgrad_extern();t1++)
            {
                int t2;
                for(t2=0;t2<*numar_noduri;t2++)
                {
                    if(p[t1]==graf[t2].getindice())
                        break;
                }
                if(viz[t2]==0)
                {
                    k++;
                    stiva[k]=p[t1];
                }
            }
        }
    }
}
bool GrafOrientat::graf_aciclic()
{
    int *stiva=new int[*numar_noduri];
    int *coada=new int[*numar_noduri];
    int *viz=new int[*numar_noduri];
    int kn=0;
    for(int i=0;i<*numar_noduri;i++)
    {
        viz[i]=0;
        coada[i]=graf[i].getindice();
    }
    while(kn<*numar_noduri)
    {
    int k=0;
    stiva[k]=coada[kn];
    for(int i=0;i<*numar_noduri;i++)
    {
        viz[i]=0;
    }
    while(k>=0)
    {
        int i;
        for(i=0;i<*numar_noduri;i++)
        {
            if(stiva[k]==graf[i].getindice())
                break;
        }
        stiva[k]=-1;
        k--;
        if(viz[i]==0)
        {
            viz[i]=1;
            int *p=graf[i].getarce();
            for(int t1=0;t1<graf[i].getgrad_extern();t1++)
            {
                if(p[t1]==coada[kn])
                        return false;
                int t2;
                for(t2=0;t2<*numar_noduri;t2++)
                {
                    if(p[t1]==graf[t2].getindice())
                        break;
                }

                if(viz[t2]==0)
                {
                    k++;
                    stiva[k]=p[t1];

                }
            }
        }
    }
    kn++;
    }
    return true;
}
void GrafOrientat::sortare_topologica()
{
    bool t=graf_aciclic();
    if(t==false)
    {
        cout<<"Graf ciclic\n";
        return;
    }
    else
    {
    int *stiva=new int[*numar_noduri];
    int k=-1;
    for(int i=0;i<*numar_noduri;i++)
    {
        if(graf[i].getgrad_intern()==0)
        {
            k++;
            stiva[k]=graf[i].getindice();
        }
    }
    int *viz=new int[*numar_noduri];
    for(int i=0;i<*numar_noduri;i++)
        viz[i]=0;
    cout<<"Sortare topologica:\n";
    while(k>=0)
    {
        int i;
        for(i=0;i<*numar_noduri;i++)
        {
            if(stiva[k]==graf[i].getindice())
                break;
        }
        if(viz[i]==0)
        {
            cout<<stiva[k]<<" ";
            viz[i]=1;
        }
        k--;
        int *p=graf[i].getarce();
        for(int j=0;j<graf[i].getgrad_extern();j++)
        {
            k++;
            stiva[k]=p[j];
        }
    }
    }
}
int** GrafOrientat::det_matrice_drumuri()
{
    int **m=new int*[*numar_noduri];
    for(int i=0;i<*numar_noduri;i++)
        m[i]=new int[*numar_noduri];
    for(int i=0;i<*numar_noduri;i++)
        for(int j=0;j<*numar_noduri;j++)
            if(i==j)
                m[i][j]=1;
            else
                m[i][j]=0;
    for(int i=0;i<*numar_noduri;i++)
    {
        int *p=graf[i].getarce();
        int k=graf[i].getgrad_extern();
        for(int j=0;j<k;j++)
        {
            m[graf[i].getindice()][p[j]]=1;
        }
    }
    for(int k=0;k<*numar_noduri;k++)
        for(int i=0;i<*numar_noduri;i++)
        for(int j=0;j<*numar_noduri;j++)
    {
        if(m[i][j]==0 && i!=k && k!=j)
            m[i][j]=m[i][k]*m[k][j];
    }
    return m;
}
bool GrafOrientat::graf_tare_conex()
{
    int **m=det_matrice_drumuri();
    for(int i=0;i<*numar_noduri;i++)
        for(int j=0;j<*numar_noduri;j++)
        if(m[i][j]==0)
        return false;
    return true;
}
int* GrafOrientat::componente_tare_conexe()
{
    int *p=new int[*numar_noduri];
    int nr=0;
    int **m=det_matrice_drumuri();
    for(int i=0;i<*numar_noduri;i++)
        p[i]=-1;
    for(int i=0;i<*numar_noduri;i++)
        {
            if(p[i]==-1)
            {
                nr++;
                for(int j=0;j<*numar_noduri;j++)
                {
                    if(m[i][j]==1 && m[j][i]==1)
                        p[j]=nr;
                }
            }
        }
    return p;
}
int main()
{
    GrafOrientat graf,graf2,graf3;
    ifstream f("graf.in");
    ofstream g("graf.out");
    f>>graf>>graf2;
    graf3=graf+graf2;
    g<<graf<<graf2;
    g<<graf3;
    graf.sortare_topologica();
    graf2.sortare_topologica();
    return 0;
}
