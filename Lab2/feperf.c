
/**************************************************************/
/* DSA list program example                                   */
/**************************************************************/
/* D.F. ROSS 120627 test version                              */
/**************************************************************/

/**************************************************************/
/* include files                                              */
/**************************************************************/

#include <stdio.h>
#include "beperf.h"

/****************************************************************************/
/* front end functions                                                      */
/****************************************************************************/

void display()  {printf("\n GRAPH  (%d nodes) is: \n", cardinality()); gdisp();}
void displaym() {printf("\n MATRIX (%d nodes) is: \n", cardinality()); mdisp();}

void addnode(char c) { addn(c); }
void remnode(char c) {
   if (is_nmember(c)) remn(c); else printf("\n *** ERROR %c not in Graph", c);
}

void addedge(char cs, char cd, int w) { 
   if (!is_nmember(cs)) printf("\n *** ERROR %c not in Graph", cs);
   else if (!is_nmember(cd)) printf("\n *** ERROR %c not in Graph", cd);
   else adde(cs, cd, w);
   }

void remedge(char cs, char cd) {
    if (is_emember(cs, cd)) reme(cs, cd);
    else printf("\n *** %c-%c not found ***", cs, cd);
}

void nmember(char c) {
   if (is_nmember(c)) printf(" *** %c found ***", c);
   else printf(" *** %c not found ***", c);
   }

void emember(char cs, char cd) {
   if (is_emember(cs, cd)) printf(" *** %c-%c found ***", cs, cd);
   else printf(" *** %c-%c not found ***", cs, cd);
   }

int nfound(char c) { return is_nmember(c); }

int efound(char cs, char cd) { return is_emember(cs, cd); }

/****************************************************************************/
/* Graph Algorithms                                                         */
/****************************************************************************/

void fDijkstra() { bDijkstra(); }
void fFloyd()    { bFloyd();    }
void fWarshall() { bWarshall(); }
void fPrim()     { bPrim();     }
void fKruskal()  { bKruskal();  }

/****************************************************************************/
/* end of front end functions                                               */
/****************************************************************************/



