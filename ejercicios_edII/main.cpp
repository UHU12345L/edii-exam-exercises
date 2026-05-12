#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// CLASE Arbin
template <typename T>
class NodoB {
public:
    T obj;
    NodoB<T>* izq;
    NodoB<T>* der;
    NodoB(const T& o, NodoB<T>* i = nullptr, NodoB<T>* d = nullptr)
        : obj(o), izq(i), der(d) {}
};

template <typename T>
class Arbin {
public:
    class Iterador {
        friend class Arbin<T>;
        NodoB<T>* pnodo;
        Iterador(NodoB<T>* p) : pnodo(p) {}
    public:
        Iterador() : pnodo(nullptr) {}
        const T& observar() const { return pnodo->obj; }
        bool arbolVacio() const { return pnodo == nullptr; }
        bool operator==(const Iterador& i) const { return pnodo == i.pnodo; }
        bool operator!=(const Iterador& i) const { return pnodo != i.pnodo; }
    };
    Arbin() : raiz(nullptr) {}
    Arbin(const T& obj, const Arbin& ai, const Arbin& ad) {
        raiz = new NodoB<T>(obj, copia(ai.raiz), copia(ad.raiz));
    }
    Arbin(const Arbin& a) : raiz(copia(a.raiz)) {}
    Arbin& operator=(const Arbin& a) {
        if (this != &a) { elimina(raiz); raiz = copia(a.raiz); }
        return *this;
    }
    ~Arbin() { elimina(raiz); }
    Iterador getRaiz() const { return Iterador(raiz); }
    bool esVacio() const { return raiz == nullptr; }
    Iterador subIzq(const Iterador& r) const {
        if (r.pnodo == nullptr) return Iterador(nullptr);
        return Iterador(r.pnodo->izq);
    }
    Iterador subDer(const Iterador& r) const {
        if (r.pnodo == nullptr) return Iterador(nullptr);
        return Iterador(r.pnodo->der);
    }
private:
    NodoB<T>* raiz;
    NodoB<T>* copia(NodoB<T>* p) {
        if (!p) return nullptr;
        return new NodoB<T>(p->obj, copia(p->izq), copia(p->der));
    }
    void elimina(NodoB<T>* p) {
        if (!p) return;
        elimina(p->izq); elimina(p->der); delete p;
    }
};

template <typename T>
using ABB = Arbin<T>;

// EXCEPCIONES
struct NoHaySiguienteMayor {};
struct NoHayAnterior {};

// CONSTANTES (sin <climits>)
const int MI_MIN = -2147483647;
const int MI_MAX =  2147483647;

// EJ 01
int contarRec(const Arbin<int>& a, const Arbin<int>::Iterador& r) {
    if (r.arbolVacio()) return 0;
    return 1 + contarRec(a, a.subIzq(r)) + contarRec(a, a.subDer(r));
}
int contar(const Arbin<int>& a) {
    return contarRec(a, a.getRaiz());
}

// EJ 02
int contarHojas(const Arbin<int>& a, const Arbin<int>::Iterador& r) {
    if (r.arbolVacio()) return 0;
    if (a.subIzq(r).arbolVacio() && a.subDer(r).arbolVacio()) return 1;
    return contarHojas(a, a.subIzq(r)) + contarHojas(a, a.subDer(r));
}
int contarHojas(const Arbin<int>& a) {
    return contarHojas(a, a.getRaiz());
}

// EJ 03
int contarNodos(const Arbin<int>& a, const Arbin<int>::Iterador& r) {
    if (r.arbolVacio()) return 0;
    if (a.subIzq(r).arbolVacio() && a.subDer(r).arbolVacio()) return 0;
    return 1 + contarNodos(a, a.subIzq(r)) + contarNodos(a, a.subDer(r));
}
int contarNodos(const Arbin<int>& a) {
    return contarNodos(a, a.getRaiz());
}

// auxiliar para posicion (EJ17) y otros: cuenta TODOS los nodos
int contarTodos(const Arbin<int>& a, const Arbin<int>::Iterador& r) {
    if (r.arbolVacio()) return 0;
    return 1 + contarTodos(a, a.subIzq(r)) + contarTodos(a, a.subDer(r));
}

// EJ 04
int sumaRec(const Arbin<int>& a, const Arbin<int>::Iterador& r) {
    if (r.arbolVacio()) return 0;
    if (a.subIzq(r).arbolVacio() && a.subDer(r).arbolVacio()) return r.observar();
    return r.observar() + sumaRec(a, a.subIzq(r)) + sumaRec(a, a.subDer(r));
}
int sumaRec(const Arbin<int>& a) {
    return sumaRec(a, a.getRaiz());
}

// EJ 05
int altura(const Arbin<int>& a, const Arbin<int>::Iterador& r) {
    if (r.arbolVacio()) return 0;
    int altIzq = altura(a, a.subIzq(r));
    int altDer = altura(a, a.subDer(r));
    if (altIzq > altDer) return 1 + altIzq;
    else                 return 1 + altDer;
}
int altura(const Arbin<int>& a) {
    return altura(a, a.getRaiz());
}

// EJ 06
bool todoPositivos(const Arbin<int>& a, const Arbin<int>::Iterador& r) {
    bool valor = false;
    if (r.arbolVacio()) return true;
    if (r.observar() > 0) valor = true;
    return valor && todoPositivos(a, a.subIzq(r)) && todoPositivos(a, a.subDer(r));
}
bool todoPositivos(const Arbin<int>& a) {
    return todoPositivos(a, a.getRaiz());
}

// EJ 07
bool hayMayor(const Arbin<int>& a, const Arbin<int>::Iterador& r, int n) {
    bool mayor = false;
    if (r.arbolVacio()) return false;
    if (r.observar() > n) mayor = true;
    return mayor || hayMayor(a, a.subIzq(r), n) || hayMayor(a, a.subDer(r), n);
}
bool hayMayor(const Arbin<int>& a, int n) {
    return hayMayor(a, a.getRaiz(), n);
}

// EJ 08
bool haySumaCamino(const Arbin<int>& a, int suma, const Arbin<int>::Iterador& r) {
    if (r.arbolVacio()) return suma == 0;
    int resto = suma - r.observar();
    bool esHoja = a.subIzq(r).arbolVacio() && a.subDer(r).arbolVacio();
    if (esHoja) return resto == 0;
    return haySumaCamino(a, resto, a.subIzq(r)) || haySumaCamino(a, resto, a.subDer(r));
}
bool haySumaCamino(const Arbin<int>& a, int suma) {
    return haySumaCamino(a, suma, a.getRaiz());
}

// EJ 09
bool compensado(const Arbin<int>& a, const Arbin<int>::Iterador& r) {
    if (r.arbolVacio()) return true;
    int nIzq = contarRec(a, a.subIzq(r));
    int nDer = contarRec(a, a.subDer(r));
    return abs(nIzq - nDer) <= 1
        && compensado(a, a.subIzq(r))
        && compensado(a, a.subDer(r));
}
bool compensado(const Arbin<int>& a) {
    return compensado(a, a.getRaiz());
}

// EJ 10
int nivel(const Arbin<int>& a, const Arbin<int>::Iterador& r, int x, int contador) {
    if (r.arbolVacio()) return -1;
    if (r.observar() == x) return contador;
    int resIzq = nivel(a, a.subIzq(r), x, contador + 1);
    if (resIzq != -1) return resIzq;
    return nivel(a, a.subDer(r), x, contador + 1);
}
int nivel(const Arbin<int>& a, int x) {
    return nivel(a, a.getRaiz(), x, 0);
}

// EJ 11
void palabras(const Arbin<char>& a, const Arbin<char>::Iterador& r, string prefijo) {
    if (r.arbolVacio()) return;
    prefijo = prefijo + r.observar();
    bool esHoja = a.subIzq(r).arbolVacio() && a.subDer(r).arbolVacio();
    if (esHoja) { cout << prefijo << endl; return; }
    palabras(a, a.subIzq(r), prefijo);
    palabras(a, a.subDer(r), prefijo);
}
void palabras(const Arbin<char>& a) {
    palabras(a, a.getRaiz(), "");
}

// EJ 12
void nivelK(const Arbin<int>& a, const Arbin<int>::Iterador& r, int k, int nivelActual) {
    if (r.arbolVacio()) return;
    if (k == nivelActual) { cout << r.observar() << " "; return; }
    nivelK(a, a.subIzq(r), k, nivelActual + 1);
    nivelK(a, a.subDer(r), k, nivelActual + 1);
}
void nivelK(const Arbin<int>& a, int k) {
    nivelK(a, a.getRaiz(), k, 0);
}

// EJ 13
template <typename T>
void recorridoZigzag(const Arbin<T>& a, const typename Arbin<T>::Iterador& r, char sentido) {
    if (r.arbolVacio()) return;
    cout << r.observar() << " ";
    if (sentido == 'I') {
        recorridoZigzag(a, a.subIzq(r), 'D');
        recorridoZigzag(a, a.subDer(r), 'D');
    } else {
        recorridoZigzag(a, a.subDer(r), 'I');
        recorridoZigzag(a, a.subIzq(r), 'I');
    }
}
template <typename T>
void recorridoZigzag(const Arbin<T>& a, char sentido) {
    recorridoZigzag(a, a.getRaiz(), sentido);
}

// EJ 14
template <typename T>
Arbin<T> simetrico(const Arbin<T>& a, const typename Arbin<T>::Iterador& r) {
    if (r.arbolVacio()) return Arbin<T>();
    return Arbin<T>(r.observar(), simetrico(a, a.subDer(r)), simetrico(a, a.subIzq(r)));
}
template <typename T>
Arbin<T> simetrico(const Arbin<T>& a) {
    return simetrico(a, a.getRaiz());
}

// EJ 15
bool esEspejo(const Arbin<int>& a, const Arbin<int>& b,
              const Arbin<int>::Iterador& r1, const Arbin<int>::Iterador& r2) {
    if (r1.arbolVacio() && r2.arbolVacio()) return true;
    if (r1.arbolVacio() || r2.arbolVacio()) return false;
    return (r1.observar() == r2.observar())
        && esEspejo(a, b, a.subIzq(r1), b.subDer(r2))
        && esEspejo(a, b, a.subDer(r1), b.subIzq(r2));
}
template <typename T>
bool esEspejo(const Arbin<T>& a, const Arbin<T>& b) {
    return esEspejo(a, b, a.getRaiz(), b.getRaiz());
}

// EJ 16
bool buscar(const ABB<int>& a, const ABB<int>::Iterador& r, int x) {
    if (r.arbolVacio()) return false;
    if (r.observar() == x) return true;
    if (x < r.observar()) return buscar(a, a.subIzq(r), x);
    else                   return buscar(a, a.subDer(r), x);
}
bool buscar(const ABB<int>& a, int x) {
    return buscar(a, a.getRaiz(), x);
}

// EJ 17
int posicion(const ABB<int>& a, const ABB<int>::Iterador& r, int x) {
    if (r.arbolVacio()) return 0;
    if (r.observar() == x)
        return contarTodos(a, a.subIzq(r)) + 1;
    if (x < r.observar())
        return posicion(a, a.subIzq(r), x);
    else {
        int pos = posicion(a, a.subDer(r), x);
        if (pos == 0) return 0;
        return contarTodos(a, a.subIzq(r)) + 1 + pos;
    }
}
int posicion(const ABB<int>& a, int x) {
    return posicion(a, a.getRaiz(), x);
}

// EJ 18
int siguienteMayor(const ABB<int>& a, const ABB<int>::Iterador& r, int x) {
    if (r.arbolVacio()) throw NoHaySiguienteMayor();
    if (r.observar() <= x)
        return siguienteMayor(a, a.subDer(r), x);
    else {
        try { return siguienteMayor(a, a.subIzq(r), x); }
        catch (NoHaySiguienteMayor) { return r.observar(); }
    }
}
int siguienteMayor(const ABB<int>& a, int x) {
    return siguienteMayor(a, a.getRaiz(), x);
}

// EJ 19
int anterior(const ABB<int>& a, const ABB<int>::Iterador& r, int x) {
    if (r.arbolVacio()) throw NoHayAnterior();
    if (r.observar() >= x)
        return anterior(a, a.subIzq(r), x);
    else {
        try { return anterior(a, a.subDer(r), x); }
        catch (NoHayAnterior) { return r.observar(); }
    }
}
int anterior(const ABB<int>& a, int x) {
    return anterior(a, a.getRaiz(), x);
}

//EJ 20
int unHijo(const Arbin<int>& a, const Arbin<int>::Iterador& r) {
    if (r.arbolVacio()) return 0;
    bool tieneIzq = !a.subIzq(r).arbolVacio();
    bool tieneDer = !a.subDer(r).arbolVacio();
    int soloUnHijo = 0;
    if (tieneIzq != tieneDer) soloUnHijo = 1;
    return soloUnHijo + unHijo(a, a.subIzq(r)) + unHijo(a, a.subDer(r));
}
int unHijo(const Arbin<int>& a) { return unHijo(a, a.getRaiz()); }

//EJ 21
int sumaHojas(const Arbin<int>&a, const Arbin<int>::Iterador&r){
    if(r.arbolVacio()) return 0;
    if((a.subIzq(r).arbolVacio())&&(a.subDer(r).arbolVacio())) return r.observar();
    return sumaHojas(a,a.subIzq(r))+sumaHojas(a,a.subDer(r));
}
int sumaHojas(const Arbin<int>&a){
    sumaHojas(a,a.getRaiz());
}

//EJ 22
int contarValor(const Arbin<int>&a, const Arbin<int>::Iterador&r, int x){
    if(r.arbolVacio()) return 0;
    int contador=0;
    if(r.observar()==x){
        contador=1;
    } else{
        contador=0;
    }
    return contador+contarValor(a,a.subIzq(r), x)
        +contarValor(a,a.subDer(r), x);
}
int contarValor(const Arbin<int>&a, int x){
    return contarValor(a,a.getRaiz(),x);
}

//EJ 23
int sumaNivel(const Arbin<int>&a, const Arbin<int>::Iterador&r, int x){
    if(r.arbolVacio()) return 0;

    if(x==0){
        return r.observar();;
    }
    return sumaNivel(a,a.subIzq(r),x-1)+sumaNivel(a,a.subDer(r),x-1);
}
int sumaNivel(const Arbin<int>&a, int x){
    return sumaNivel(a, a.getRaiz(),x);
}

//EJ 24

int maximo(const Arbin<int>&a, const Arbin<int>::Iterador&r){
    if(r.arbolVacio()) return MI_MIN;

    int max_izq=maximo(a,a.subIzq(r));
    int max_der=maximo(a,a.subDer(r));

    if(max_izq<r.observar()&&max_der<r.observar()){
        return r.observar();
    }

    if(max_izq>max_der){
        return max_izq;
    }else{
        return max_der;
    }
}
int maximo(const Arbin<int>&a){
    return maximo(a,a.getRaiz());
}

//EJ 25
bool iguales(const Arbin<int>&a, const Arbin<int>::Iterador&ra, const Arbin<int>&b, const Arbin<int>::Iterador&rb){
    if(ra.arbolVacio()&&!rb.arbolVacio()) return false;
    if(rb.arbolVacio()&&!ra.arbolVacio()) return false;
    if(ra.arbolVacio()&&rb.arbolVacio()) return true;

    if((ra.observar()==rb.observar())) {
            return iguales(a,a.subDer(ra),b,b.subDer(rb)) && iguales(a,a.subIzq(ra),b,b.subIzq(rb));
    }else{
        return false;
    }
}

bool iguales(const Arbin<int>&a, const Arbin<int>&b){
    return iguales(a, a.getRaiz(),b,b.getRaiz());
}

//EJ 26
bool mismoNivel(const Arbin<int>&a, const Arbin<int>::Iterador &r, int x, int y){
    int nx=nivel(a,x);
    int ny=nivel(a,y);
    if(nx==-1||ny==-1)return false;
    return nx==ny;
}
bool mismoNivel(const Arbin<int>&a, int x, int y){
    mismoNivel(a,a.getRaiz(),x,y);
}

//EJ 27
bool caminoCreciente(const Arbin<int>&a, const Arbin<int>::Iterador&r, int anterior){
    if (r.arbolVacio()) return false;
    bool esHoja = a.subIzq(r).arbolVacio() && a.subDer(r).arbolVacio();
    bool camino=true;
    if(r.observar()<=anterior) camino=false;
    if(esHoja) return camino;

    return camino&&(caminoCreciente(a,a.subIzq(r),r.observar())||caminoCreciente(a,a.subDer(r),r.observar()));
}
bool caminoCreciente(const Arbin<int>&a){
    if(a.esVacio()) return false;
    return caminoCreciente(a,a.getRaiz(), -9999999999);
}

//EJ 28
int contarIntervalo(const ABB<int>&a, const ABB<int>::Iterador &r, int mini, int maxi){
    if(r.arbolVacio())return 0;

    if(r.observar()<mini){
        return contarIntervalo(a,a.subDer(r),mini,maxi);
    }
    if(r.observar()>maxi){
        return contarIntervalo(a,a.subIzq(r),mini,maxi);
    }
    return 1+contarIntervalo(a,a.subIzq(r),mini,maxi)+contarIntervalo(a,a.subDer(r),mini,maxi);
}
int contarIntervalo(const ABB<int>&a,int mini, int maxi){
    return contarIntervalo(a,a.getRaiz(),mini,maxi);
}

//EJ 29
bool tieneHijo(const ABB<int>&a, const ABB<int>::Iterador &r, int x){
    if(r.arbolVacio()) return false;
    bool hijo=false;
    if(r.observar()==x){
        if(!a.subIzq(r).arbolVacio() || !a.subDer(r).arbolVacio()) hijo=true;
        return hijo;
    }
    return (tieneHijo(a,a.subIzq(r),x) || tieneHijo(a,a.subDer(r),x));
}
bool tieneHijo(const ABB<int>&a,int x){
    return tieneHijo(a,a.getRaiz(),x);
}

//EJ 30
int kesimo(const ABB<int>&a,const ABB<int>::Iterador &r, int k){
    if(r.arbolVacio()) return -1;
    int nodosIzq=contarTodos(a,a.subIzq(r));
    if(k==nodosIzq+1) return r.observar();
    if(k<=nodosIzq) {
            return kesimo(a,a.subIzq(r),k);
    }else{
        return kesimo(a,a.subDer(r),k-nodosIzq-1);
    }
}

int kesimo(const ABB<int>&a,int k){
    if(k<1) return -1;
    return kesimo(a,a.getRaiz(),k);
}

//EJ 31
int sumaNivelesPares(const ABB<int>&a, const ABB<int>::Iterador&r, int actual){
    if(r.arbolVacio())return 0;
    int suma=0;
    if(actual%2==0){
        suma+=r.observar();
    }
    return suma+sumaNivelesPares(a,a.subIzq(r),actual+1)+
        sumaNivelesPares(a,a.subDer(r),actual+1);
}
int sumaNivelesPares(const ABB<int>&a){
    return sumaNivelesPares(a,a.getRaiz(),0);
}

//EJ 32
bool esABB(const Arbin<int>&a, const Arbin<int>::Iterador&r,int mn, int mx){
    if(r.arbolVacio())return true;
    if(r.observar()<=mn||r.observar()>=mx) return false;
    return esABB(a,a.subIzq(r),mn,r.observar()) && esABB(a,a.subDer(r),r.observar(),mx);
}
bool esABB(const Arbin<int>&a){
    return esABB(a,a.getRaiz(),-999999999,999999999);
}

//EJ 33
bool esSimetrico(const Arbin<int>&a, const Arbin<int>::Iterador&ri, const Arbin<int>::Iterador&rd){
    if(ri.arbolVacio()&&rd.arbolVacio()) return true;
    if((a.subDer(rd).arbolVacio()&&!a.subIzq(ri).arbolVacio()) || (!a.subDer(rd).arbolVacio()&&a.subIzq(ri).arbolVacio())) return false;
    if(ri.observar()!=rd.observar()) return false;
    return esSimetrico(a,a.subDer(rd), a.subIzq(ri));

}
bool esSimetrico(const Arbin<int>&a){
    return esSimetrico(a,a.getRaiz(),a.getRaiz());
}

//EJ 34
int masProfundo(const Arbin<int>& a, const Arbin<int>::Iterador& r, int nivelBuscado, int actual) {
    if (r.arbolVacio()) return -1;
    if (actual == nivelBuscado) return r.observar();
    int resIzq = masProfundo(a, a.subIzq(r), nivelBuscado, actual + 1);
    if (resIzq != -1) return resIzq;  // izquierda tiene prioridad en empate
    return masProfundo(a, a.subDer(r), nivelBuscado, actual + 1);
}

int masProfundo(const Arbin<int>& a) {
    if (a.esVacio()) return -1;
    int prof = altura(a, a.getRaiz()) - 1;  // altura-1 = índice del último nivel
    return masProfundo(a, a.getRaiz(), prof, 0);
}

//EJ 35
int contarPares(const Arbin<int>&a, const Arbin<int>::Iterador&r){
    if(r.arbolVacio()) return 0;
    int esPar=0;
    if(r.observar()%2==0) esPar=1;
    return esPar+contarPares(a,a.subIzq(r))+contarPares(a,a.subDer(r));
}
int contarPares(const Arbin<int>&a){
    return contarPares(a,a.getRaiz());
}

//EJ 36
bool existe(const ABB<int>& a, const ABB<int>::Iterador& r, int x) {
    if (r.arbolVacio()) return false;
    if (r.observar() == x) return true;
    if (x < r.observar()) return existe(a, a.subIzq(r), x);
    else                   return existe(a, a.subDer(r), x);
}
bool existe(const ABB<int>& a, int x) {
    return existe(a, a.getRaiz(), x);
}
struct NoHayPredecesor {};

int predecesor(const ABB<int>&a, const ABB<int>::Iterador &r, int x) {
    if(r.arbolVacio()) throw NoHayPredecesor();
    if(r.observar()>=x){
        return predecesor(a,a.subIzq(r),x);
    }else{
        try{
            return predecesor(a,a.subDer(r),x);
        }catch(NoHayPredecesor){
            return r.observar();
        }
    }

}
int predecesor(const ABB<int>&a, int x) {
    if(!existe(a,x)) throw NoHayPredecesor();
    return predecesor(a,a.getRaiz(),x);
}

//EJ 37
int sumaMinCamino(const Arbin<int>&a, const Arbin<int>::Iterador&r,int acum){
    if(r.arbolVacio()) return 0;
    bool esHoja=(a.subIzq(r).arbolVacio())&&(a.subIzq(r).arbolVacio());
    acum+=r.observar();
    if(esHoja) return acum;
    int minIzq=sumaMinCamino(a,a.subIzq(r),acum);
    int minDer=sumaMinCamino(a,a.subDer(r),acum);
    if(minIzq<minDer) return minIzq;
    return minDer;
}
int sumaMinCamino(const Arbin<int>&a){
    return sumaMinCamino(a,a.getRaiz(),0);
}

//EJ 38
int longitudLargo(const Arbin<int>&a, const Arbin<int>::Iterador&r){
    if(r.arbolVacio()) return 0;
    int maxIzq=longitudLargo(a,a.subIzq(r));
    int maxDer=longitudLargo(a,a.subDer(r));
    if(maxIzq>maxDer) return 1+ maxIzq;
    return 1+maxDer;
}
int longitudLargo(const Arbin<int>&a){
    return longitudLargo(a,a.getRaiz());
}

//EJ 39
int sumaTotal(const Arbin<int>&a, const Arbin<int>::Iterador&r){
    if(r.arbolVacio())return 0;
    int suma=r.observar();
    return suma+sumaTotal(a,a.subIzq(r))+sumaTotal(a,a.subDer(r));
}
int sumaTotal(const Arbin<int>&a){
    return sumaTotal(a,a.getRaiz());
}

//EJ 40
bool esCompleto(const ABB<int>&a, const ABB<int>::Iterador &r){
    if(r.arbolVacio()) return true;

     bool esHoja = a.subIzq(r).arbolVacio() && a.subDer(r).arbolVacio();
    if (esHoja) return true;
    if(a.subIzq(r).arbolVacio() || a.subDer(r).arbolVacio()) {
        return false;
    }
    return esCompleto(a,a.subIzq(r)) && esCompleto(a,a.subDer(r));
}
bool esCompleto(const ABB<int>&a){
    return esCompleto(a,a.getRaiz());
}

//EJ 41
bool unoMax(const Arbin<int>&a, const Arbin<int>::Iterador &r){
    if(r.arbolVacio()) return true;
    bool tener=false;
    if((a.subIzq(r).arbolVacio() && !a.subDer(r).arbolVacio()) || (!a.subIzq(r).arbolVacio() && a.subDer(r).arbolVacio())) tener= true;
    if(a.subIzq(r).arbolVacio() && a.subDer(r).arbolVacio()) tener= true;
    if(!a.subIzq(r).arbolVacio() && !a.subDer(r).arbolVacio()) tener =false;
    return tener&&unoMax(a,a.subIzq(r)) &&unoMax(a,a.subDer(r));
}
bool unoMax(const Arbin<int>&a){
    return unoMax(a,a.getRaiz());
}

//EJ 42
bool hijosOrdenados(const Arbin<int>&a, const Arbin<int>::Iterador&r){
    if(r.arbolVacio()) return true;
    bool esHijo=a.subIzq(r).arbolVacio() && a.subDer(r).arbolVacio();
    if(esHijo) return true;
    bool ordenado=true;
    if (!a.subIzq(r).arbolVacio() && !a.subDer(r).arbolVacio()) {

        if((a.subDer(r).observar())<=(a.subIzq(r).observar())) {
            ordenado= false;
    }
}
return ordenado&&hijosOrdenados(a,a.subIzq(r)) &&hijosOrdenados(a, a.subDer(r));
}
bool hijosOrdenados(const Arbin<int>&a){
    return hijosOrdenados(a,a.getRaiz());
}

//EJ 43
bool soloHijoIzq(const Arbin<int>&a, const Arbin<int>::Iterador&r){
    if(r.arbolVacio()) return true;
    bool esHoja=a.subIzq(r).arbolVacio()&&a.subDer(r).arbolVacio();
    bool solito=false;
    if(esHoja)
    {
        return true;
    }
    if(!a.subIzq(r).arbolVacio() && a.subDer(r).arbolVacio())
    {
        solito= true;
    }
    else
    {
        solito= false;
    }

    return solito &&soloHijoIzq(a,a.subIzq(r))&&soloHijoIzq(a,a.subDer(r));
}
bool soloHijoIzq(const Arbin<int>&a){
    return soloHijoIzq(a,a.getRaiz());
}


//EJ 44
int sumaTotalMenor(const Arbin<int>&a, const Arbin<int>::Iterador&r, int x, int sumador){
    if(r.arbolVacio()) return 0;
    bool esHoja=a.subIzq(r).arbolVacio() && a.subDer(r).arbolVacio();
    sumador+=r.observar();
    if(esHoja){
        if(sumador<x){
            return sumador;
        }else{
            return 0;
        }
    }
    return sumaTotalMenor(a,a.subIzq(r),x,sumador) +sumaTotalMenor(a,a.subDer(r),x,sumador);
}
int sumaTotalMenor(const Arbin<int>&a, int x){
    return sumaTotalMenor(a,a.getRaiz(),x,0);
}

//EJ 45
// ----------------------------------------------------------
    // ABB de prueba
    //            8
    //           / \
    //          3   14
    //         / \    \
    //        1   6   20
    //           / \  /
    //          4   7 16
    // Inorden: 1 3 4 6 7 8 14 16 20
    // ----------------------------------------------------------
//EJ 45
int menorDeLosMayores(const ABB<int>& a, const ABB<int>::Iterador& r) {
    if (r.arbolVacio()) throw NoHaySiguienteMayor();
    if (a.subDer(r).arbolVacio()) throw NoHaySiguienteMayor();
    // el sucesor de la raiz es el minimo del subárbol derecho
    Arbin<int>::Iterador it = a.subDer(r);
    while (!a.subIzq(it).arbolVacio()) {
        it = a.subIzq(it);
    }
    return it.observar();
}
int menorDeLosMayores(const ABB<int>& a) {
    return menorDeLosMayores(a, a.getRaiz());
}


//EJ 46
bool hayCaminoNnodos(const Arbin<int>&a, const Arbin<int>::Iterador&r, int n, int contador){
    if(r.arbolVacio()) return false;
    contador++;
    bool esHoja=a.subIzq(r).arbolVacio() && a.subDer(r).arbolVacio();
    if(esHoja){
        if(n==contador){
            return true;
        }else{
            return false;
        }
    }
    return hayCaminoNnodos(a,a.subIzq(r),n,contador)||
        hayCaminoNnodos(a,a.subDer(r),n,contador);
}
bool hayCaminoNnodos(const Arbin<int>&a, int n){
    return hayCaminoNnodos(a,a.getRaiz(),n,0);
}

//EJ 47
int contarLados(const Arbin<int>&a, const Arbin<int>::Iterador&r){
    if(r.arbolVacio()) return 0;
    if (a.subIzq(r).arbolVacio() && a.subDer(r).arbolVacio()) return 0;

    return 1+contarLados(a,a.subIzq(r))+contarLados(a,a.subDer(r));
}
bool cargaPar(const Arbin<int>&a, const Arbin<int>::Iterador&r){
    if(r.arbolVacio()) return true;
    bool esHoja=a.subIzq(r).arbolVacio() && a.subDer(r).arbolVacio();
    if(esHoja) return true;
    int nodosIzq= contarLados(a,a.subIzq(r));
    int nodosDer=contarLados(a,a.subDer(r));
    if((nodosIzq-nodosDer)==0 ||(nodosIzq-nodosDer)==2 || (nodosIzq-nodosDer)==-2) {
            return true;
    } else{
        return false;
    }
    return cargaPar(a, a.subIzq(r)) && cargaPar(a, a.subDer(r));
}
bool cargaPar(const Arbin<int>&a){
    return cargaPar(a,a.getRaiz());
}
// ============================================================
// UTILIDADES
// ============================================================
void sep(const string& t) { cout << "\n=== " << t << " ===\n"; }
void ok(const string& msg) { cout << "  [OK] " << msg << "\n"; }
void check(const string& msg, bool cond) { cout << (cond ? "  [OK] " : "  [!!] ") << msg << "\n"; }

// ============================================================
// MAIN
// ============================================================
int main() {
    cout << "============================================\n";
    cout << "  TEST COMPLETO — Ejercicios 01 a 34\n";
    cout << "============================================\n";

    // ----------------------------------------------------------
    // Árbol general de prueba
    //            10
    //           /  \
    //          5    20
    //         / \     \
    //        3   7    30
    //               /
    //              25
    // Nodos totales: 7  |  Hojas: 3,7,25  |  Internos: 10,5,20,30
    // Suma: 100  |  Altura: 4
    // ----------------------------------------------------------
    Arbin<int> hoja3(3, Arbin<int>(), Arbin<int>());
    Arbin<int> hoja7(7, Arbin<int>(), Arbin<int>());
    Arbin<int> hoja25(25, Arbin<int>(), Arbin<int>());
    Arbin<int> nodo30(30, hoja25, Arbin<int>());
    Arbin<int> nodo5(5, hoja3, hoja7);
    Arbin<int> nodo20(20, Arbin<int>(), nodo30);
    Arbin<int> arbol(10, nodo5, nodo20);

    sep("EJ 01 - Contar nodos totales");
    check("arbol tiene 7 nodos", contar(arbol) == 7);
    check("arbol vacio tiene 0 nodos", contar(Arbin<int>()) == 0);

    sep("EJ 02 - Numero de hojas");
    check("arbol tiene 3 hojas", contarHojas(arbol) == 3);
    check("arbol vacio tiene 0 hojas", contarHojas(Arbin<int>()) == 0);
    Arbin<int> soloRaiz(42, Arbin<int>(), Arbin<int>());
    check("un solo nodo tiene 1 hoja", contarHojas(soloRaiz) == 1);

    sep("EJ 03 - Nodos internos");
    check("arbol tiene 4 nodos internos", contarNodos(arbol) == 4);
    check("hojas + internos = total", contarHojas(arbol) + contarNodos(arbol) == contar(arbol));

    sep("EJ 04 - Suma de nodos");
    check("suma es 100", sumaRec(arbol) == 100);
    check("suma arbol vacio es 0", sumaRec(Arbin<int>()) == 0);

    sep("EJ 05 - Altura");
    check("altura es 4", altura(arbol) == 4);
    check("altura arbol vacio es 0", altura(Arbin<int>()) == 0);
    check("altura un nodo es 1", altura(soloRaiz) == 1);

    sep("EJ 06 - Todos positivos");
    check("arbol con valores positivos: true", todoPositivos(arbol) == true);
    Arbin<int> conNeg(-1, Arbin<int>(), Arbin<int>());
    Arbin<int> arbNeg(5, conNeg, Arbin<int>());
    check("arbol con -1: false", todoPositivos(arbNeg) == false);

    sep("EJ 07 - Hay nodo mayor que umbral");
    check("hay nodo > 15: true", hayMayor(arbol, 15) == true);
    check("hay nodo > 50: false", hayMayor(arbol, 50) == false);
    check("hay nodo > 29: true", hayMayor(arbol, 29) == true);

    sep("EJ 08 - haySumaCamino");
    // caminos: 10+5+3=18 | 10+5+7=22 | 10+20+30+25=85
    check("suma 18 existe: true", haySumaCamino(arbol, 18) == true);
    check("suma 22 existe: true", haySumaCamino(arbol, 22) == true);
    check("suma 85 existe: true", haySumaCamino(arbol, 85) == true);
    check("suma 99 no existe: false", haySumaCamino(arbol, 99) == false);
    check("suma 0 en arbol vacio: true", haySumaCamino(Arbin<int>(), 0) == true);
    check("suma 5 en arbol vacio: false", haySumaCamino(Arbin<int>(), 5) == false);

    sep("EJ 09 - Arbol compensado");
    // nodo20: izq=0 nodos, der=2 nodos → diff=2 → NO compensado
    check("arbol NO esta compensado", compensado(arbol) == false);
    Arbin<int> compIzq(1, Arbin<int>(), Arbin<int>());
    Arbin<int> compDer(2, Arbin<int>(), Arbin<int>());
    Arbin<int> arbolComp(5, compIzq, compDer);
    check("arbol (5,(1),(2)) SI esta compensado", compensado(arbolComp) == true);
    check("arbol vacio esta compensado", compensado(Arbin<int>()) == true);

    sep("EJ 10 - Nivel de un nodo");
    check("nivel de 10 es 0", nivel(arbol, 10) == 0);
    check("nivel de 5 es 1", nivel(arbol, 5) == 1);
    check("nivel de 20 es 1", nivel(arbol, 20) == 1);
    check("nivel de 25 es 3", nivel(arbol, 25) == 3);
    check("nivel de 99 no existe: -1", nivel(arbol, 99) == -1);

    sep("EJ 11 - Palabras raiz->hoja");
    //         o
    //        / \
    //       r   l
    //        \  / \
    //        o a   e
    // palabras: oro, ola, ole
    Arbin<char> co('o', Arbin<char>(), Arbin<char>());
    Arbin<char> ca('a', Arbin<char>(), Arbin<char>());
    Arbin<char> ce('e', Arbin<char>(), Arbin<char>());
    Arbin<char> cr('r', Arbin<char>(), co);
    Arbin<char> cl('l', ca, ce);
    Arbin<char> arbolLetras('o', cr, cl);
    cout << "  Esperado: oro, ola, ole\n  Obtenido:\n";
    palabras(arbolLetras);

    sep("EJ 12 - Nodos del nivel k");
    cout << "  Nivel 0 (esperado 10): ";       nivelK(arbol, 0); cout << "\n";
    cout << "  Nivel 1 (esperado 5 20): ";     nivelK(arbol, 1); cout << "\n";
    cout << "  Nivel 2 (esperado 3 7 30): ";   nivelK(arbol, 2); cout << "\n";
    cout << "  Nivel 3 (esperado 25): ";       nivelK(arbol, 3); cout << "\n";

    sep("EJ 13 - Recorrido en zigzag");
    cout << "  Sentido I (esperado 10 5 7 3 20 30 25): ";
    recorridoZigzag(arbol, 'I'); cout << "\n";
    cout << "  Sentido D (esperado 10 20 30 25 5 3 7): ";
    recorridoZigzag(arbol, 'D'); cout << "\n";

    sep("EJ 14 - Arbol simetrico");
    Arbin<int> sim = simetrico(arbol);
    check("simetrico tiene mismos nodos", contar(sim) == contar(arbol));
    check("simetrico tiene misma altura", altura(sim) == altura(arbol));
    check("raiz del simetrico sigue siendo 10", sim.getRaiz().observar() == 10);
    check("hijo izq del simetrico es 20", sim.subIzq(sim.getRaiz()).observar() == 20);
    check("hijo der del simetrico es 5", sim.subDer(sim.getRaiz()).observar() == 5);

    sep("EJ 15 - Es espejo");
    check("simetrico es espejo de arbol: true", esEspejo(arbol, sim) == true);
    check("arbol es espejo de si mismo: false", esEspejo(arbol, arbol) == false);
    Arbin<int> simSim = simetrico(sim);
    check("doble simetrico es espejo del simetrico: true", esEspejo(sim, simSim) == true);

    // ----------------------------------------------------------
    // ABB de prueba
    //            8
    //           / \
    //          3   14
    //         / \    \
    //        1   6   20
    //           / \  /
    //          4   7 16
    // Inorden: 1 3 4 6 7 8 14 16 20
    // ----------------------------------------------------------
    Arbin<int> n1(1, Arbin<int>(), Arbin<int>());
    Arbin<int> n4(4, Arbin<int>(), Arbin<int>());
    Arbin<int> n7(7, Arbin<int>(), Arbin<int>());
    Arbin<int> n16(16, Arbin<int>(), Arbin<int>());
    Arbin<int> n6(6, n4, n7);
    Arbin<int> n3(3, n1, n6);
    Arbin<int> n20(20, n16, Arbin<int>());
    Arbin<int> n14(14, Arbin<int>(), n20);
    ABB<int> abb(8, n3, n14);

    sep("EJ 16 - Busqueda en ABB");
    check("buscar 6: true", buscar(abb, 6) == true);
    check("buscar 1: true", buscar(abb, 1) == true);
    check("buscar 20: true", buscar(abb, 20) == true);
    check("buscar 5: false", buscar(abb, 5) == false);
    check("buscar 0: false", buscar(abb, 0) == false);

    sep("EJ 17 - Posicion inorden en ABB");
    // inorden: 1 3 4 6 7 8 14 16 20
    check("posicion de 1 es 1", posicion(abb, 1) == 1);
    check("posicion de 3 es 2", posicion(abb, 3) == 2);
    check("posicion de 8 es 6", posicion(abb, 8) == 6);
    check("posicion de 20 es 9", posicion(abb, 20) == 9);
    check("posicion de 5 no existe: 0", posicion(abb, 5) == 0);

    sep("EJ 18 - Siguiente mayor en ABB");
    check("siguienteMayor(5) = 6", siguienteMayor(abb, 5) == 6);
    check("siguienteMayor(6) = 7", siguienteMayor(abb, 6) == 7);
    check("siguienteMayor(7) = 8", siguienteMayor(abb, 7) == 8);
    check("siguienteMayor(14) = 16", siguienteMayor(abb, 14) == 16);
    check("siguienteMayor(0) = 1", siguienteMayor(abb, 0) == 1);
    try { siguienteMayor(abb, 20); cout << "  [!!] deberia lanzar excepcion\n"; }
    catch (NoHaySiguienteMayor) { ok("siguienteMayor(20) lanza excepcion correctamente"); }
    try { siguienteMayor(abb, 99); cout << "  [!!] deberia lanzar excepcion\n"; }
    catch (NoHaySiguienteMayor) { ok("siguienteMayor(99) lanza excepcion correctamente"); }

    sep("EJ 19 - Anterior en ABB");
    check("anterior(7) = 6", anterior(abb, 7) == 6);
    check("anterior(8) = 7", anterior(abb, 8) == 7);
    check("anterior(20) = 16", anterior(abb, 20) == 16);
    check("anterior(21) = 20", anterior(abb, 21) == 20);
    try { anterior(abb, 1); cout << "  [!!] deberia lanzar excepcion\n"; }
    catch (NoHayAnterior) { ok("anterior(1) lanza excepcion correctamente"); }
    try { anterior(abb, 0); cout << "  [!!] deberia lanzar excepcion\n"; }
    catch (NoHayAnterior) { ok("anterior(0) lanza excepcion correctamente"); }

    // ----------------------------------------------------------
    // Árboles para ejercicios 20-34
    //
    //   A:          B (= A):      C:        D:
    //       1           1           1          10
    //      / \         / \         / \        /  \
    //     2   3       2   3       2   3      5    20
    //    / \ / \     / \ / \                / \     \
    //   4  5 6  7   4  5 6  7              1   8    30
    //
    //   ABB2:           Sim:          NoSim:
    //       10            1              1
    //      /  \          / \            / \
    //     5    15       2   2          2   3
    //    / \  /  \     / \ / \
    //   3   7 12  18  3  4 4  3
    // ----------------------------------------------------------
    Arbin<int> A(1,
        Arbin<int>(2, Arbin<int>(4,Arbin<int>(),Arbin<int>()), Arbin<int>(5,Arbin<int>(),Arbin<int>())),
        Arbin<int>(3, Arbin<int>(6,Arbin<int>(),Arbin<int>()), Arbin<int>(7,Arbin<int>(),Arbin<int>())));

    Arbin<int> B(1,
        Arbin<int>(2, Arbin<int>(4,Arbin<int>(),Arbin<int>()), Arbin<int>(5,Arbin<int>(),Arbin<int>())),
        Arbin<int>(3, Arbin<int>(6,Arbin<int>(),Arbin<int>()), Arbin<int>(7,Arbin<int>(),Arbin<int>())));

    Arbin<int> C(1, Arbin<int>(2,Arbin<int>(),Arbin<int>()), Arbin<int>(3,Arbin<int>(),Arbin<int>()));

    Arbin<int> D(10,
        Arbin<int>(5, Arbin<int>(1,Arbin<int>(),Arbin<int>()), Arbin<int>(8,Arbin<int>(),Arbin<int>())),
        Arbin<int>(20, Arbin<int>(), Arbin<int>(30,Arbin<int>(),Arbin<int>())));

    Arbin<int> a3b(3,Arbin<int>(),Arbin<int>());
    Arbin<int> a7b(7,Arbin<int>(),Arbin<int>());
    Arbin<int> a12(12,Arbin<int>(),Arbin<int>());
    Arbin<int> a18(18,Arbin<int>(),Arbin<int>());
    Arbin<int> a5b(5,a3b,a7b);
    Arbin<int> a15(15,a12,a18);
    ABB<int> abb2(10, a5b, a15);

    Arbin<int> s3a(3,Arbin<int>(),Arbin<int>()); Arbin<int> s4a(4,Arbin<int>(),Arbin<int>());
    Arbin<int> s4b(4,Arbin<int>(),Arbin<int>()); Arbin<int> s3b(3,Arbin<int>(),Arbin<int>());
    Arbin<int> s2a(2,s3a,s4a); Arbin<int> s2b(2,s4b,s3b);
    Arbin<int> Sim(1, s2a, s2b);

    Arbin<int> NoSim(1, Arbin<int>(2,Arbin<int>(),Arbin<int>()), Arbin<int>(3,Arbin<int>(),Arbin<int>()));

    Arbin<int> ABBvalido(10,
        Arbin<int>(5, Arbin<int>(1,Arbin<int>(),Arbin<int>()), Arbin<int>(8,Arbin<int>(),Arbin<int>())),
        Arbin<int>(20, Arbin<int>(15,Arbin<int>(),Arbin<int>()), Arbin<int>(30,Arbin<int>(),Arbin<int>())));
    Arbin<int> ABBinvalido(10,
        Arbin<int>(15,Arbin<int>(),Arbin<int>()),
        Arbin<int>(5,Arbin<int>(),Arbin<int>()));

    sep("EJ 20 - Nodos con un solo hijo");
    // A: todos los nodos internos tienen 2 hijos → 0
    // D: nodo20 solo tiene der=30, nodo5 tiene 2 hijos → 1 nodo con un solo hijo (20)
    check("A tiene 0 nodos con un solo hijo", unHijo(A) == 0);
    check("D tiene 1 nodo con un solo hijo (20)", unHijo(D) == 1);
    check("arbol principal tiene 2 (20 y 30)", unHijo(arbol) == 2);

    sep("EJ 21 - Suma de hojas");
    // A: hojas 4+5+6+7 = 22
    // D: hojas 1+8+30 = 39
    check("suma hojas A es 22", sumaHojas(A) == 22);
    check("suma hojas D es 39", sumaHojas(D) == 39);
    check("suma hojas C es 5 (2+3)", sumaHojas(C) == 5);

    sep("EJ 22 - Contar apariciones de un valor");
    check("valor 2 en A aparece 1 vez", contarValor(A, 2) == 1);
    check("valor 99 en A aparece 0 veces", contarValor(A, 99) == 0);
    Arbin<int> dup1(5,Arbin<int>(),Arbin<int>());
    Arbin<int> dup2(5,Arbin<int>(),Arbin<int>());
    Arbin<int> arbDup(5, dup1, dup2);
    check("valor 5 en arbol con duplicados aparece 3 veces", contarValor(arbDup, 5) == 3);

    sep("EJ 23 - Suma de nodos en nivel k");
    // A nivel 0: 1 | nivel 1: 2+3=5 | nivel 2: 4+5+6+7=22
    check("suma nivel 0 de A es 1", sumaNivel(A, 0) == 1);
    check("suma nivel 1 de A es 5", sumaNivel(A, 1) == 5);
    check("suma nivel 2 de A es 22", sumaNivel(A, 2) == 22);
    check("suma nivel 5 de A es 0 (no existe)", sumaNivel(A, 5) == 0);
    // D nivel 2: 1+8+30 = 39
    check("suma nivel 2 de D es 39", sumaNivel(D, 2) == 39);

    sep("EJ 24 - Valor maximo (arbol general)");
    check("maximo de A es 7", maximo(A) == 7);
    check("maximo de D es 30", maximo(D) == 30);
    check("maximo de C es 3", maximo(C) == 3);

    sep("EJ 25 - Dos arboles iguales");
    check("A == B: true", iguales(A, B) == true);
    check("A == C: false", iguales(A, C) == false);
    check("A == A: true", iguales(A, A) == true);
    check("dos vacios son iguales: true", iguales(Arbin<int>(), Arbin<int>()) == true);

    sep("EJ 26 - Dos valores en el mismo nivel");
    // A: 4,5,6,7 estan en nivel 2; 2,3 en nivel 1
    check("4 y 7 mismo nivel en A: true", mismoNivel(A, 4, 7) == true);
    check("2 y 4 mismo nivel en A: false", mismoNivel(A, 2, 4) == false);
    check("4 y 99 (no existe): false", mismoNivel(A, 4, 99) == false);

    sep("EJ 27 - Camino creciente");
    // A: 1->2->4 (1<2<4 creciente) → true
    check("A tiene camino creciente: true", caminoCreciente(A) == true);
    // D: 10->20->30 (creciente) → true
    check("D tiene camino creciente: true", caminoCreciente(D) == true);
    // arbol principal: 10->5->3 (no), 10->5->7 (no), 10->20->30->25 (no) → false
    check("arbol principal no tiene camino creciente: false", caminoCreciente(arbol) == false);

    sep("EJ 28 - Contar nodos en intervalo [mn,mx] en ABB");
    // abb2 inorden: 3 5 7 10 12 15 18
    check("abb2 [5,15]: 5 nodos (5,7,10,12,15)", contarIntervalo(abb2, 5, 15) == 5);
    check("abb2 [1,6]: 2 nodos (3,5)", contarIntervalo(abb2, 1, 6) == 2);
    check("abb2 [20,30]: 0 nodos", contarIntervalo(abb2, 20, 30) == 0);
    check("abb2 [10,10]: 1 nodo (el propio 10)", contarIntervalo(abb2, 10, 10) == 1);

    sep("EJ 29 - Tiene hijo en ABB");
    // abb2: 10 tiene hijos (5 y 15), 3 es hoja
    check("10 tiene hijos: true", tieneHijo(abb2, 10) == true);
    check("5 tiene hijos (3 y 7): true", tieneHijo(abb2, 5) == true);
    check("3 es hoja: false", tieneHijo(abb2, 3) == false);
    check("99 no existe: false", tieneHijo(abb2, 99) == false);

    sep("EJ 30 - K-esimo en inorden de ABB");
    // abb2 inorden: 3 5 7 10 12 15 18
    //              1 2 3  4  5  6  7
    check("1er elemento de abb2 es 3", kesimo(abb2, 1) == 3);
    check("4o elemento de abb2 es 10", kesimo(abb2, 4) == 10);
    check("7o elemento de abb2 es 18", kesimo(abb2, 7) == 18);
    check("99o no existe: -1", kesimo(abb2, 99) == -1);
    check("0 invalido: -1", kesimo(abb2, 0) == -1);

    sep("EJ 31 - Suma niveles pares de ABB");
    // abb2: nivel 0: 10 (par) | nivel 1: 5+15=20 (impar) | nivel 2: 3+7+12+18=40 (par)
    // total pares: 10+40 = 50
    check("suma niveles pares de abb2 es 50", sumaNivelesPares(abb2) == 50);

    sep("EJ 32 - Es ABB valido");
    check("ABBvalido es ABB: true", esABB(ABBvalido) == true);
    check("ABBinvalido no es ABB: false", esABB(ABBinvalido) == false);
    Arbin<int> trampa2(2,Arbin<int>(),Arbin<int>());
    Arbin<int> trampa7(7,trampa2,Arbin<int>());
    Arbin<int> trampa3(3,Arbin<int>(),Arbin<int>());
    Arbin<int> trampa(5, trampa3, trampa7);
    check("arbol trampa (5,3,(7,2,_)) no es ABB: false", esABB(trampa) == false);

    sep("EJ 33 - Arbol simetrico respecto a su eje");
    check("Sim ES simetrico: true", esSimetrico(Sim) == true);
    check("NoSim NO es simetrico: false", esSimetrico(NoSim) == false);
    check("A NO es simetrico: false", esSimetrico(A) == false);
    check("arbol vacio es simetrico: true", esSimetrico(Arbin<int>()) == true);

    sep("EJ 34 - Nodo mas profundo (izquierda en empate)");
    // arbol: hojas 3(niv2), 7(niv2), 25(niv3) → mas profundo es 25
    check("mas profundo de arbol es 25", masProfundo(arbol) == 25);
    // A: todas las hojas en nivel 2, la mas izquierda es 4
    check("mas profundo de A es 4 (izquierda en empate)", masProfundo(A) == 4);
    // empate sencillo: raiz con dos hojas
    Arbin<int> emp2(2,Arbin<int>(),Arbin<int>());
    Arbin<int> emp3(3,Arbin<int>(),Arbin<int>());
    Arbin<int> arbEmp(1, emp2, emp3);
    check("empate: devuelve el izquierdo (2)", masProfundo(arbEmp) == 2);

    sep("EJ 35 - Contar nodos pares");
// arbol: nodos pares son 10, 20, 30 → 3
check("arbol tiene 3 nodos pares (10,20,30)", contarPares(arbol) == 3);
check("arbol vacio tiene 0 pares", contarPares(Arbin<int>()) == 0);
check("arbol con solo nodo 3 (impar) tiene 1 par", contarPares(soloRaiz) == 1);

sep("EJ 36 - existe (auxiliar)");
check("existe(6) en abb: true",  existe(abb, 6)  == true);
check("existe(1) en abb: true",  existe(abb, 1)  == true);
check("existe(5) en abb: false", existe(abb, 5)  == false);

sep("EJ 36 - predecesor en inorden");
// abb inorden: 1 3 4 6 7 8 14 16 20
check("predecesor(3) = 1",   predecesor(abb, 3)  == 1);
check("predecesor(8) = 7",   predecesor(abb, 8)  == 7);
check("predecesor(14) = 8",  predecesor(abb, 14) == 8);
check("predecesor(20) = 16", predecesor(abb, 20) == 16);
try {
    predecesor(abb, 1);
    cout << "  [!!] predecesor(1) deberia lanzar excepcion\n";
} catch (NoHayPredecesor) {
    ok("predecesor(1) lanza NoHayPredecesor correctamente");
}
try {
    predecesor(abb, 5);
    cout << "  [!!] predecesor(5) deberia lanzar excepcion\n";
} catch (NoHayPredecesor) {
    ok("predecesor(5) lanza NoHayPredecesor correctamente (no existe)");
}

sep("EJ 37 - Suma minima de camino");
    check("arbol: minimo 18 (10+5+3)", sumaMinCamino(arbol) == 18);
    check("A: minimo 7 (1+2+4)",       sumaMinCamino(A)     == 7);

    sep("EJ 38 - Longitud camino mas largo");
    check("arbol: longitud 4",    longitudLargo(arbol)     == 4);
    check("A: longitud 3",        longitudLargo(A)         == 3);
    check("un nodo: longitud 1",  longitudLargo(soloRaiz)  == 1);

    sep("EJ 39 - Suma total");
    check("arbol: suma 100",  sumaTotal(arbol)        == 100);
    check("A: suma 28",       sumaTotal(A)            == 28);
    check("vacio: suma 0",    sumaTotal(Arbin<int>()) == 0);

    sep("EJ 40 - Es completo");
    check("A es completo: true",         esCompleto(A)     == true);
    check("arbol NO es completo: false", esCompleto(arbol) == false);
    check("C es completo: true",         esCompleto(C)     == true);

    sep("EJ 41 - Todos con maximo un hijo");
    check("arbol: false", unoMax(arbol) == false);
    Arbin<int> c3b(3, Arbin<int>(), Arbin<int>());
    Arbin<int> c2b(2, c3b, Arbin<int>());
    Arbin<int> cadena(1, c2b, Arbin<int>());
    check("cadena 1->2->3: true", unoMax(cadena)    == true);
    check("un nodo: true",        unoMax(soloRaiz)  == true);

    sep("EJ 42 - Hijos ordenados");
    check("A: true",      hijosOrdenados(A)     == true);
    check("arbol: true",  hijosOrdenados(arbol) == true);
    Arbin<int> hd2(2, Arbin<int>(), Arbin<int>());
    Arbin<int> hd9(9, Arbin<int>(), Arbin<int>());
    Arbin<int> desordenado(5, hd9, hd2);
    check("desordenado (izq=9,der=2): false", hijosOrdenados(desordenado) == false);

    sep("EJ 43 - Solo hijo izquierdo");
    check("cadena 1->2->3: true", soloHijoIzq(cadena)    == true);
    check("arbol: false",         soloHijoIzq(arbol)     == false);
    check("un nodo: true",        soloHijoIzq(soloRaiz)  == true);

    sep("EJ 44 - Suma total caminos menores que cota");
    check("arbol cota=50: 40 (18+22)", sumaTotalMenor(arbol, 50) == 40);
    check("arbol cota=20: 18",         sumaTotalMenor(arbol, 20) == 18);
    check("arbol cota=10: 0",          sumaTotalMenor(arbol, 10) == 0);

    sep("EJ 45 - Menor de los mayores (sucesor raiz ABB)");
    check("abb raiz=8, sucesor=14", menorDeLosMayores(abb) == 14);

    sep("EJ 46 - Hay camino con N nodos");
    check("arbol: camino con 4 nodos: true",      hayCaminoNnodos(arbol, 4) == true);
    check("arbol: camino con 3 nodos: true",      hayCaminoNnodos(arbol, 3) == true);
    check("arbol: NO hay camino con 2: false",    hayCaminoNnodos(arbol, 2) == false);

    sep("EJ 47 - Carga par");
    check("A: true",        cargaPar(A)            == true);
    check("vacio: true",    cargaPar(Arbin<int>()) == true);
    check("arbol: false",   cargaPar(arbol)        == false);

    cout << "\n============================================\n";
    cout << "  Fin de los tests\n";
    cout << "============================================\n";
    return 0;
}
