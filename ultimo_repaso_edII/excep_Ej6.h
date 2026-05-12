#ifndef _EXCEP_SM_H_
#define _EXCEP_SM_H_

#include "excepcion.h" 

using namespace std;
 
class NoHaySiguienteMayor: public Excepcion {
  public:
     NoHaySiguienteMayor(): Excepcion("No hay Siguiente Mayor") {};
};

#endif

