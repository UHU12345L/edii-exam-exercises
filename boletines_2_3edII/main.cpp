#include <iostream>
#include <string>
using namespace std;

// ============================================================
// CLASE Arbin
// ============================================================
template <typename T>
class NodoB {
public:
    T obj; NodoB<T>* izq; NodoB<T>* der;
    NodoB(const T& o, NodoB<T>* i=nullptr, NodoB<T>* d=nullptr):obj(o),izq(i),der(d){}
};

template <typename T>
class Arbin {
public:
    class Iterador {
        friend class Arbin<T>; NodoB<T>* pnodo; Iterador(NodoB<T>* p):pnodo(p){}
    public:
        Iterador():pnodo(nullptr){}
        const T& observar() const { return pnodo->obj; }
        bool arbolVacio() const { return pnodo==nullptr; }
        bool operator==(const Iterador& i) const { return pnodo==i.pnodo; }
        bool operator!=(const Iterador& i) const { return pnodo!=i.pnodo; }
    };
    Arbin():raiz(nullptr){}
    Arbin(const T& obj, const Arbin& ai, const Arbin& ad){
        raiz=new NodoB<T>(obj,copia(ai.raiz),copia(ad.raiz));
    }
    Arbin(const Arbin& a):raiz(copia(a.raiz)){}
    Arbin& operator=(const Arbin& a){
        if(this!=&a){elimina(raiz);raiz=copia(a.raiz);}return *this;
    }
    ~Arbin(){ elimina(raiz); }
    Iterador getRaiz() const { return Iterador(raiz); }
    bool esVacio() const { return raiz==nullptr; }
    Iterador subIzq(const Iterador& r) const { return Iterador(r.pnodo?r.pnodo->izq:nullptr); }
    Iterador subDer(const Iterador& r) const { return Iterador(r.pnodo?r.pnodo->der:nullptr); }
private:
    NodoB<T>* raiz;
    NodoB<T>* copia(NodoB<T>* p){
        if(!p)return nullptr;
        return new NodoB<T>(p->obj,copia(p->izq),copia(p->der));
    }
    void elimina(NodoB<T>* p){ if(!p)return; elimina(p->izq);elimina(p->der);delete p; }
};

template <typename T> using ABB = Arbin<T>;

// ============================================================
// EXCEPCIONES Y CONSTANTES
// ============================================================
struct NoHayAnterior{};
const int MI_MIN = -2147483647;
const int MI_MAX =  2147483647;

// ============================================================
// AUXILIAR — altura (necesaria para equilibrado)
// ============================================================
int alturaRec(const Arbin<int>& a, const Arbin<int>::Iterador& r){
    if(r.arbolVacio()) return 0;
    int altIzq=alturaRec(a,a.subIzq(r));
    int altDer=alturaRec(a,a.subDer(r));
    if(altIzq>altDer) return 1+altIzq;
    return 1+altDer;
}

// ============================================================
// T2.1 — Árboles idénticos
// ============================================================
bool iguales(const Arbin<int>&a, const Arbin<int>::Iterador &ra, const Arbin<int>&b, const Arbin<int>::Iterador &rb){
    if(ra.arbolVacio() && rb.arbolVacio()) return true;
    if(ra.arbolVacio() || rb.arbolVacio()) return false;
    bool son_iguales=false;
    if(ra.observar()==rb.observar()) {
            son_iguales= true;
    }
    return son_iguales && iguales(a,a.subIzq(ra),b,b.subIzq(rb)) && iguales(a,a.subDer(ra), b,b.subDer(rb));
}
bool iguales(const Arbin<int>&a, const Arbin<int>&b){
    return iguales(a,a.getRaiz(),b,b.getRaiz());
}


// ============================================================
// T2.2 — Suma de nodos
// ============================================================
int sumaRec(const Arbin<int>&a, const Arbin<int>::Iterador&r){
    if(r.arbolVacio()) return 0;

    return r.observar()+sumaRec(a,a.subIzq(r))+sumaRec(a,a.subDer(r));
}

int sumaRec(const Arbin<int>&a){
    return sumaRec(a,a.getRaiz());
}


// ============================================================
// T2.3 — Copia simétrica
// ============================================================
template <typename T>
Arbin<T> simetrico(const Arbin<T> &a, const typename Arbin<T>::Iterador &r){
    if(r.arbolVacio()) return Arbin<T>();
    return Arbin<T>(r.observar(), simetrico(a,a.subDer(r)), simetrico(a,a.subIzq(r)));
}

template <typename T>
Arbin<T> simetrico(const Arbin<T> &a){
    return simetrico(a,a.getRaiz());
}


// ============================================================
// T2.4 — Nodos del nivel n
// ============================================================
void nivelK(const Arbin<int>&a, const Arbin<int>::Iterador &r, int n, int voy){
    if(r.arbolVacio()) return;
    if(n==voy){
        cout<<r.observar()<<" ";
        return;

    }
    nivelK(a,a.subIzq(r),n,voy+1);
    nivelK(a,a.subDer(r),n,voy+1);
}


void nivelK(const Arbin<int>&a, int n){
    nivelK(a,a.getRaiz(),n,0);
}


// ============================================================
// T2.5 — ¿Es completo?
// ============================================================
bool esCompleto(const Arbin<int>&a, const Arbin<int>::Iterador&r){
    if(r.arbolVacio()) return true;
    bool esHoja=a.subIzq(r).arbolVacio()&&a.subDer(r).arbolVacio();
    if(esHoja) return true;
    bool completito=!a.subIzq(r).arbolVacio() && !a.subDer(r).arbolVacio();
    return completito&&esCompleto(a,a.subIzq(r))&&esCompleto(a,a.subDer(r));
}
bool esCompleto(const Arbin<int>&a){
    return esCompleto(a,a.getRaiz());
}


// ============================================================
// T2.8 — ¿Misma forma?
// ============================================================
bool mismaForma(const Arbin<int>&a, const Arbin<int>::Iterador &ra, const Arbin<int>&b, const Arbin<int>::Iterador &rb){
    if(ra.arbolVacio() &&rb.arbolVacio()) return true;
    if(ra.arbolVacio() || rb.arbolVacio()) return false;
    return mismaForma(a,a.subIzq(ra),b,b.subIzq(rb)) && mismaForma(a,a.subDer(ra),b,b.subDer(rb));
}
bool mismaForma(const Arbin<int>& a, const Arbin<int>& b){
    return mismaForma(a,a.getRaiz(),b,b.getRaiz());
}

// ============================================================
// T3.1 — ¿Es ABB válido?
// ============================================================
bool esABB(const Arbin<int>&a, const Arbin<int>::Iterador&r, int mn, int mx){
    if(r.arbolVacio()) return true;

    if(r.observar()<=mn || r.observar()>=mx) return false;
    return esABB(a,a.subIzq(r), mn, r.observar()) && esABB(a,a.subDer(r),r.observar(),mx);
}
bool esABB(const Arbin<int>&a){
    return esABB(a,a.getRaiz(), MI_MIN, MI_MAX);
}

// ============================================================
// T3.2 — Inorden descendente
// ============================================================
void inordenDesc(const ABB<int>&a, const ABB<int>::Iterador&r){
    if(r.arbolVacio()) return;
    inordenDesc(a,a.subDer(r));
    cout<<r.observar()<<" ";
    inordenDesc(a,a.subIzq(r));
}
void inordenDesc(const ABB<int>&a){
    return inordenDesc(a,a.getRaiz());
}


// ============================================================
// T3.3 — Antecesores de un elemento en ABB
// ============================================================

void antecesores(const ABB<int>&a, const ABB<int>::Iterador&r, int x){
    if(r.arbolVacio())return;

    if(r.observar()==x){
       return;
    }
    cout<<r.observar()<<" ";
    if(r.observar()>x){
        antecesores(a,a.subIzq(r),x);
    }else{
        antecesores(a,a.subDer(r),x);
    }
}
void antecesores(const ABB<int>&a, int x){
    antecesores(a,a.getRaiz(),x);
}
    // ABB de prueba:
    //            8
    //           / \
    //          3   14
    //         / \    \
    //        1   6   20
    //           / \  /
    //          4   7 16
    // Inorden: 1 3 4 6 7 8 14 16 20

// ============================================================
// T3.4 — Anterior en inorden de ABB
// ============================================================
int anterior(const ABB<int>&a, const ABB<int>::Iterador &r,int e){
    if(r.arbolVacio()) throw NoHayAnterior();
    int devolver=0;
    if(r.observar()>=e){
        anterior(a,a.subIzq(r),e);
    }else{
        try{
            return anterior(a,a.subDer(r),e);
        }catch (NoHayAnterior){
            return r.observar();
        }
    }

}
int anterior(const ABB<int>&a, int e){
    return anterior(a,a.getRaiz(),e);
}


// ============================================================
// T3.5 — ¿Está equilibrado (AVL)?
// ============================================================
bool equilibrado(const Arbin<int>&a, const Arbin<int>::Iterador&r){
    if(r.arbolVacio()) return true;
    int altura_izq=alturaRec(a,a.subIzq(r));
    int altura_der=alturaRec(a,a.subDer(r));
    bool comprobar=false;
    if((altura_izq-altura_der)==1 || (altura_izq-altura_der)==-1 || (altura_izq-altura_der)==0) comprobar=true;
    return comprobar&&equilibrado(a,a.subIzq(r))&&equilibrado(a,a.subDer(r));
}
bool equilibrado(const Arbin<int>&a){
    return equilibrado(a,a.getRaiz());
}

// ============================================================
// UTILIDADES
// ============================================================
void sep(const string& t){ cout<<"\n=== "<<t<<" ===\n"; }
void ok(const string& msg){ cout<<"  [OK] "<<msg<<"\n"; }
void check(const string& msg, bool cond){ cout<<(cond?"  [OK] ":"  [!!] ")<<msg<<"\n"; }

// ============================================================
// MAIN
// ============================================================
int main(){
    cout<<"============================================\n";
    cout<<"  TEST Boletin Tema 2 y Tema 3 (sin listas)\n";
    cout<<"============================================\n";

    // Árbol general de prueba:
    //            10
    //           /  \
    //          5    20
    //         / \     \
    //        3   7    30
    //               /
    //              25
    Arbin<int> h3(3,Arbin<int>(),Arbin<int>());
    Arbin<int> h7(7,Arbin<int>(),Arbin<int>());
    Arbin<int> h25(25,Arbin<int>(),Arbin<int>());
    Arbin<int> n30(30,h25,Arbin<int>());
    Arbin<int> n5(5,h3,h7);
    Arbin<int> n20(20,Arbin<int>(),n30);
    Arbin<int> arbol(10,n5,n20);

    // Árbol A (completo):
    //       1
    //      / \
    //     2   3
    //    / \ / \
    //   4  5 6  7
    Arbin<int> A(1,
        Arbin<int>(2,Arbin<int>(4,Arbin<int>(),Arbin<int>()),Arbin<int>(5,Arbin<int>(),Arbin<int>())),
        Arbin<int>(3,Arbin<int>(6,Arbin<int>(),Arbin<int>()),Arbin<int>(7,Arbin<int>(),Arbin<int>())));

    // ABB de prueba:
    //            8
    //           / \
    //          3   14
    //         / \    \
    //        1   6   20
    //           / \  /
    //          4   7 16
    // Inorden: 1 3 4 6 7 8 14 16 20
    Arbin<int> a1(1,Arbin<int>(),Arbin<int>());
    Arbin<int> a4(4,Arbin<int>(),Arbin<int>());
    Arbin<int> a7b(7,Arbin<int>(),Arbin<int>());
    Arbin<int> a16(16,Arbin<int>(),Arbin<int>());
    Arbin<int> a6(6,a4,a7b);
    Arbin<int> a3(3,a1,a6);
    Arbin<int> a20(20,a16,Arbin<int>());
    Arbin<int> a14(14,Arbin<int>(),a20);
    ABB<int> abb(8,a3,a14);

    // ABB equilibrado simple:
    //       5
    //      / \
    //     3   7
    ABB<int> abbEq(5,
        Arbin<int>(3,Arbin<int>(),Arbin<int>()),
        Arbin<int>(7,Arbin<int>(),Arbin<int>()));

    // ABB desequilibrado (cadena): 1->2->3->4
    ABB<int> abbDeseq(1,Arbin<int>(),
        Arbin<int>(2,Arbin<int>(),
            Arbin<int>(3,Arbin<int>(),
                Arbin<int>(4,Arbin<int>(),Arbin<int>()))));

    sep("T2.1 - Arboles identicos");
    Arbin<int> copia=arbol;
    check("arbol == copia: true",  iguales(arbol,copia)==true);
    check("arbol == A: false",     iguales(arbol,A)==false);
    check("vacio == vacio: true",  iguales(Arbin<int>(),Arbin<int>())==true);

    sep("T2.2 - Suma de nodos");
    check("arbol: suma 100", sumaRec(arbol)==100);
    check("A: suma 28",      sumaRec(A)==28);
    check("vacio: suma 0",   sumaRec(Arbin<int>())==0);

    sep("T2.3 - Copia simetrica");
    Arbin<int> sim=simetrico(arbol);
    check("simetrico misma suma",     sumaRec(sim)==sumaRec(arbol));
    check("raiz simetrico es 10",     sim.getRaiz().observar()==10);
    check("hijo izq es 20 (era der)", sim.subIzq(sim.getRaiz()).observar()==20);
    check("hijo der es 5 (era izq)",  sim.subDer(sim.getRaiz()).observar()==5);

    sep("T2.4 - Nodos del nivel n");
    cout<<"  Nivel 0 de arbol (esperado 10): ";   nivelK(arbol,0); cout<<"\n";
    cout<<"  Nivel 1 de arbol (esperado 5 20): "; nivelK(arbol,1); cout<<"\n";
    cout<<"  Nivel 1 de A (esperado 2 3): ";      nivelK(A,1);     cout<<"\n";

    sep("T2.5 - Es completo");
    check("A es completo: true",         esCompleto(A)==true);
    check("arbol NO es completo: false", esCompleto(arbol)==false);
    check("vacio es completo: true",     esCompleto(Arbin<int>())==true);

    sep("T2.8 - Misma forma");
    Arbin<int> B(99,
        Arbin<int>(88,Arbin<int>(77,Arbin<int>(),Arbin<int>()),Arbin<int>(66,Arbin<int>(),Arbin<int>())),
        Arbin<int>(55,Arbin<int>(44,Arbin<int>(),Arbin<int>()),Arbin<int>(33,Arbin<int>(),Arbin<int>())));
    check("A y B misma forma (valores distintos): true", mismaForma(A,B)==true);
    check("arbol y A distinta forma: false",             mismaForma(arbol,A)==false);
    check("arbol misma forma que si mismo: true",        mismaForma(arbol,arbol)==true);

    sep("T3.1 - Es ABB valido");
    check("abb es ABB: true",   esABB(abb)==true);
    check("arbol es ABB: true", esABB(arbol)==true);
    Arbin<int> trampa(5,
        Arbin<int>(3,Arbin<int>(),Arbin<int>()),
        Arbin<int>(7,Arbin<int>(2,Arbin<int>(),Arbin<int>()),Arbin<int>()));
    check("trampa NO es ABB: false", esABB(trampa)==false);


    sep("T3.2 - Inorden descendente");
    cout<<"  abb (esperado 20 16 14 8 7 6 4 3 1): ";
    inordenDesc(abb); cout<<"\n";

    sep("T3.3 - Antecesores en ABB");
    cout<<"  Antecesores de 4 (esperado 8 3 6): ";
    antecesores(abb,4); cout<<"\n";
    cout<<"  Antecesores de 16 (esperado 8 14 20): ";
    antecesores(abb,16); cout<<"\n";
    cout<<"  Antecesores de 8 raiz (esperado nada): ";
    antecesores(abb,8); cout<<"\n";

    sep("T3.4 - Anterior en inorden ABB");
    check("anterior(3)=1",   anterior(abb,3)==1);
    check("anterior(8)=7",   anterior(abb,8)==7);
    check("anterior(20)=16", anterior(abb,20)==16);
    try{ anterior(abb,1); cout<<"  [!!] deberia lanzar excepcion\n"; }
    catch(NoHayAnterior){ ok("anterior(1) lanza excepcion correctamente"); }

    sep("T3.5 - Esta equilibrado (AVL)");
    check("abbEq equilibrado: true",                      equilibrado(abbEq)==true);
    check("abb NO equilibrado (nodo14 diff=2): false",    equilibrado(abb)==false);
    check("abbDeseq (cadena) NO equilibrado: false",      equilibrado(abbDeseq)==false);
    check("vacio equilibrado: true",                      equilibrado(Arbin<int>())==true);

    cout<<"\n============================================\n";
    cout<<"  Fin de los tests\n";
    cout<<"============================================\n";
    return 0;
}
