#include <iostream>
#include <cstdlib>
#include <queue>
#include "arbin.h"
#include "abb.h"
#include "Excep_Ej6.h"

// Recorridos

template <typename T>
void inorden(const Arbin<T>& a, const typename Arbin<T>::Iterador& r) {
    if (!r.arbolVacio()) {
        inorden(a, a.subIzq(r));
        cout << r.observar() << " ";
        inorden(a, a.subDer(r));
    }
}

template <typename T>
void preorden(const Arbin<T>& a, const typename Arbin<T>::Iterador& r) {
    if (!r.arbolVacio()) {
        cout << r.observar() << " ";
        preorden(a, a.subIzq(r));
        preorden(a, a.subDer(r));
    }
}

template <typename T>
void postorden(const Arbin<T>& a, const typename Arbin<T>::Iterador& r) {
    if (!r.arbolVacio()) {
        postorden(a, a.subIzq(r));
        postorden(a, a.subDer(r));
        cout << r.observar() << " ";
    }
}

template <typename T>
void anchura(const Arbin<T>& a) {
    if (!a.esVacio()) {
        queue<typename Arbin<T>::Iterador> c;
        typename Arbin<T>::Iterador ic = a.getRaiz();
        c.push(ic);
        while (!c.empty()) {
             ic = c.front();
             c.pop();
             cout << ic.observar() << " ";
             if (!a.subIzq(ic).arbolVacio())
                c.push(a.subIzq(ic));
             if (!a.subDer(ic).arbolVacio())
                c.push(a.subDer(ic));
        }
    }
}

void sep(const string& t){cout<<"\n=== "<<t<<" ===\n";}
void ok(const string& m){cout<<"  [OK] "<<m<<"\n";}
void check(const string& m,bool c){cout<<(c?"  [OK] ":"  [!!] ")<<m<<"\n";}

bool todosMayores(const Arbin<int>&a, const Arbin<int>::Iterador&r, int x){
    if(r.arbolVacio()) return true;
    bool sonMayores=false;
    if(r.observar()>x) sonMayores=true;
    return sonMayores && todosMayores(a,a.subIzq(r),x) && todosMayores(a,a.subDer(r),x);
}
bool todosMayores(const Arbin<int>&a, int x){
    return todosMayores(a,a.getRaiz(),x);
}

bool haySuma(const Arbin<int>&a, const Arbin<int>::Iterador &r, int suma){
    if(r.arbolVacio()) return suma==0;
    int resto=suma-r.observar();
    bool esHoja=a.subIzq(r).arbolVacio() && a.subDer(r).arbolVacio();
    if(esHoja){
        if(resto==0){
           return true;
        } else{
            return false;
        }
    }
    return haySuma(a,a.subIzq(r),resto) || haySuma(a,a.subDer(r),resto);
}
bool haySuma(const Arbin<int>&a, int objetivo){
    return haySuma(a,a.getRaiz(),objetivo);
}

int contarTodos(const Arbin<int>&a, const Arbin<int>::Iterador&r){
    if(r.arbolVacio()) return 0;
    return 1+contarTodos(a,a.subIzq(r))+contarTodos(a,a.subDer(r));
}
bool compensado(const Arbin<int>&a, const Arbin<int>::Iterador&r){
    if(r.arbolVacio()) return true;
    int nIzq=contarTodos(a,a.subIzq(r));
    int nDer=contarTodos(a,a.subDer(r));
    int dif=nIzq-nDer;
    if(dif<0) dif=-dif;
    return dif<=1 &&compensado(a,a.subIzq(r)) &&compensado(a,a.subDer(r));
}
bool compensado(const Arbin<int>&a){
    return compensado(a,a.getRaiz());
}
void imprimirSumasCaminos(const Arbin<int>&a, const Arbin<int>::Iterador &r, int acum){
    if(r.arbolVacio()) return;
    acum+=r.observar();
    bool esHoja=a.subIzq(r).arbolVacio() && a.subDer(r).arbolVacio();
    if(esHoja){
        cout<<acum<<endl;
        return;
    }
    imprimirSumasCaminos(a,a.subIzq(r), acum);
    imprimirSumasCaminos(a,a.subDer(r), acum);
}
void imprimirSumasCaminos(const Arbin<int>&a){
     imprimirSumasCaminos(a,a.getRaiz(),0);
}

int siguienteMayor(const ABB<int>&a, const Arbin<int>::Iterador &r, int x){
    if(r.arbolVacio()) throw NoHaySiguienteMayor();
    if(r.observar()<=x){
        return siguienteMayor(a,a.subDer(r),x);
    }else{
        try{
            return siguienteMayor(a,a.subIzq(r),x);
        }catch(NoHaySiguienteMayor){
            return r.observar();
        }
    }
}
int siguienteMayor(const ABB<int>&a, int x){
    return siguienteMayor(a,a.getRaiz(),x);
}

int posicion(const ABB<int>& a, const ABB<int>::Iterador& r, int x) {
    if (r.arbolVacio()) return 0;
    if (r.observar() == x) return contarTodos(a, a.subIzq(r)) + 1;
    if (x < r.observar()) return posicion(a, a.subIzq(r), x);
    else {
        int pos = posicion(a, a.subDer(r), x);
        if (pos == 0) return 0;
        return contarTodos(a, a.subIzq(r)) + 1 + pos;
    }
}
int posicion(const ABB<int>&a, int x){
    return posicion(a,a.getRaiz(),x);
}

void antecesores(const ABB<int>&a, const Arbin<int>::Iterador&r, int x){
    if(r.arbolVacio()) return;
    if(r.observar()!=x){
         cout<<r.observar()<<" ";
    }else{
        return;
    }
   if(x<r.observar()){
        antecesores(a,a.subIzq(r),x);
   }else {antecesores(a,a.subDer(r),x);}
}
void antecesores(const ABB<int>&a, int x){
    antecesores(a,a.getRaiz(),x);
}
const int MI_MIN = -2147483647;
const int MI_MAX =  2147483647;
bool esABB(const Arbin<int>&a, const Arbin<int>::Iterador &r, int mn, int mx){
    if(r.arbolVacio()) return true;
    if(r.observar()<mn || r.observar()>mx) return false;
    return esABB(a,a.subIzq(r),mn,r.observar()) &&esABB(a,a.subDer(r),r.observar(),mx);
}
bool esABB(const Arbin<int>&a){
    return esABB(a,a.getRaiz(),MI_MIN,MI_MAX);
}

bool equilibrado(const Arbin<int>&a, const Arbin<int>::Iterador&ra){
    if(ra.arbolVacio()) return true;
    int altIzq=a.subIzq(ra).altura();
    int altDer=a.subDer(ra).altura();
    int dif=altIzq-altDer;
    if(dif<0) dif=-dif;
    bool aceptamos=false;
    if(dif<=1) aceptamos= true;
    return aceptamos&&equilibrado(a,a.subIzq(ra))&&equilibrado(a,a.subDer(ra));
}
bool equilibrado(const Arbin<int>&a){
    return equilibrado(a,a.getRaiz());
}

template <typename T>
Arbin<T> simetrico(const Arbin<T>&a, const typename Arbin<T>::Iterador&r){
    if(r.arbolVacio()) return Arbin<T>();
    return Arbin<T>(r.observar(), simetrico(a,a.subDer(r)), simetrico(a,a.subIzq(r)));
}

template <typename T>
Arbin<T> simetrico(const Arbin<T>&a){
    return simetrico(a,a.getRaiz());
}

void inordenDesc(const ABB<int>&a, const ABB<int>::Iterador&r){
    if (r.arbolVacio()) return;
    if (!r.arbolVacio()) {
        inordenDesc(a, a.subDer(r));
        cout << r.observar() << " ";
        inordenDesc(a, a.subIzq(r));
    }
}

void inordenDesc(const ABB<int>&a){
    inordenDesc(a,a.getRaiz());
}

int contarIntervalo(const ABB<int>&a, const Arbin<int>::Iterador &r, int mn, int mx){
    if(r.arbolVacio()) return 0;
    int estoy=r.observar();

    if(estoy<mn){
        return contarIntervalo(a,a.subDer(r),mn,mx);
    }

    if(estoy>mx){
        return contarIntervalo(a,a.subIzq(r),mn,mx);
    }


    return 1+contarIntervalo(a,a.subDer(r),mn,mx)+contarIntervalo(a,a.subIzq(r),mn,mx);
}
int contarIntervalo(const ABB<int>&a, int mn, int mx){
    return contarIntervalo(a,a.getRaiz(),mn,mx);
}


int main(){
   /* cout<<"============================================\n";
    cout<<"  REPASO FINAL — con headers del profesor\n";
    cout<<"============================================\n";

    // Árbol general:
    //            10
    //           /  \
    //          5    20
    //         / \     \
    //        3   7    30
    //               /
    //              25
    Arbin<int> arbol(10,
        Arbin<int>(5,
            Arbin<int>(3,Arbin<int>(),Arbin<int>()),
            Arbin<int>(7,Arbin<int>(),Arbin<int>())),
        Arbin<int>(20,
            Arbin<int>(),
            Arbin<int>(30,
                Arbin<int>(25,Arbin<int>(),Arbin<int>()),
                Arbin<int>())));

    Arbin<int> arbComp(5,
        Arbin<int>(3,Arbin<int>(),Arbin<int>()),
        Arbin<int>(7,Arbin<int>(),Arbin<int>()));

    // ABB con insertar:
    //            8
    //           / \
    //          3   14
    //         / \    \
    //        1   6   20
    //           / \  /
    //          4   7 16
    ABB<int> abb;
    abb.insertar(8); abb.insertar(3); abb.insertar(14);
    abb.insertar(1); abb.insertar(6); abb.insertar(20);
    abb.insertar(4); abb.insertar(7); abb.insertar(16);

    ABB<int> abbEq;
    abbEq.insertar(5); abbEq.insertar(3); abbEq.insertar(7);

    ABB<int> abbDeseq;
    abbDeseq.insertar(1); abbDeseq.insertar(2);
    abbDeseq.insertar(3); abbDeseq.insertar(4);


    sep("R1 - Todos mayores que umbral");
    check("arbol todos>0: true",  todosMayores(arbol,0)==true);
    check("arbol todos>10: false",todosMayores(arbol,10)==false);
    check("vacio: true",          todosMayores(Arbin<int>(),0)==true);

    sep("R2 - Hay suma camino");
    check("suma 18: true",  haySuma(arbol,18)==true);
    check("suma 22: true",  haySuma(arbol,22)==true);
    check("suma 85: true",  haySuma(arbol,85)==true);
    check("suma 99: false", haySuma(arbol,99)==false);


    sep("R3 - Compensado");
    check("arbol NO compensado: false", compensado(arbol)==false);
    check("arbComp SI: true",           compensado(arbComp)==true);
    check("vacio: true",                compensado(Arbin<int>())==true);

    sep("R4 - Imprimir sumas caminos");
    cout<<"  arbol (esperado 18, 22, 85):\n";
    imprimirSumasCaminos(arbol);

    sep("R5 - Siguiente mayor con excepcion");
    check("siguienteMayor(5)=6",   siguienteMayor(abb,5)==6);
    check("siguienteMayor(7)=8",   siguienteMayor(abb,7)==8);
    check("siguienteMayor(14)=16", siguienteMayor(abb,14)==16);
    try{siguienteMayor(abb,20);cout<<"  [!!] deberia lanzar\n";}
    catch(NoHaySiguienteMayor&){ok("siguienteMayor(20) lanza correctamente");}

    sep("R6 - Posicion inorden ABB");
    check("posicion(1)=1",  posicion(abb,1)==1);
    check("posicion(8)=6",  posicion(abb,8)==6);
    check("posicion(20)=9", posicion(abb,20)==9);
    check("posicion(5)=0",  posicion(abb,5)==0);

    sep("R7 - Antecesores en ABB");
    cout<<"  antecesores(4) esperado 8 3 6: "; antecesores(abb,4); cout<<"\n";
    cout<<"  antecesores(8 raiz) esperado nada: "; antecesores(abb,8); cout<<"\n";

    sep("R8 - Es ABB valido");
    check("abb es ABB: true",        esABB(abb)==true);
    check("arbol es ABB: true",      esABB(arbol)==true);
    Arbin<int> trampa(5,
        Arbin<int>(3,Arbin<int>(),Arbin<int>()),
        Arbin<int>(7,Arbin<int>(2,Arbin<int>(),Arbin<int>()),Arbin<int>()));
    check("trampa NO es ABB: false", esABB(trampa)==false);


    sep("R9 - Equilibrado");
    check("abbEq: true",        equilibrado(abbEq)==true);
    check("abb NO: false",      equilibrado(abb)==false);
    check("abbDeseq NO: false", equilibrado(abbDeseq)==false);
    check("vacio: true",        equilibrado(Arbin<int>())==true);

    sep("R10 - Simetrico");
    Arbin<int> sim=simetrico(arbol);
    check("mismos nodos",          contarTodos(sim,sim.getRaiz())==contarTodos(arbol,arbol.getRaiz()));
    check("hijo izq sim es 20",    sim.subIzq(sim.getRaiz()).observar()==20);
    check("hijo der sim es 5",     sim.subDer(sim.getRaiz()).observar()==5);

    sep("R11 - Inorden descendente");
    cout<<"  abb (esperado 20 16 14 8 7 6 4 3 1): ";
    inordenDesc(abb); cout<<"\n";

    sep("R12 - Contar intervalo ABB");
    check("[3,8]: 5 nodos",    contarIntervalo(abb,3,8)==5);
    check("[1,20]: 9 nodos",   contarIntervalo(abb,1,20)==9);
    check("[100,200]: 0 nodos",contarIntervalo(abb,100,200)==0);

    cout<<"\n============================================\n";
    cout<<"  Fin del repaso\n";
    cout<<"============================================\n";
    */
    ABB<int>a;
    a.insertar(5); a.insertar(3); a.insertar(8); a.insertar(1);a.insertar(4);

    cout<<contarTodos(a,a.getRaiz())<<endl;
    cout<<(esABB(a)? "SI":"NO")<<endl;
    inordenDesc(a); cout<<endl;

    return 0;
}

