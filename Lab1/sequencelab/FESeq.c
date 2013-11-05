
/**************************************************************/
/* DSA list program example                                   */
/**************************************************************/
/* D.F. ROSS 120627 test version                              */
/**************************************************************/

/**************************************************************/
/* include files                                              */
/**************************************************************/

#include <stdio.h>
#include "BESeq.h"

/****************************************************************************/
/* front end functions                                                      */
/****************************************************************************/

int size() {return cardinality(); }   

void display() {printf(" SEQUENCE (size %d) is: ", size()); disp();}

void addval   (int v)   { add(v); }

void addvalpos(int v, int pos)  { 
   if (pos<1 || pos > size()+1) printf("\n Error: invalid position");
   else addpos(v, pos); 
   }

void remval   (int v)   { rem(v); }

void remvalpos(int pos) {
   if (pos<1 || pos > size()) printf("\n Error: invalid position");
   else rempos(pos);
   }

void member(int v) {
   if (is_member(v)) printf(" *** %d found ***", v);
   else printf(" *** %d not found ***", v);
   }
   
void f_first()   { bfirst(); disp_C(); }
void f_next()    { bnext();  disp_C(); }
int  f_exist_e() { return exist_e(); }

/****************************************************************************/
/* end of front end functions                                               */
/****************************************************************************/



