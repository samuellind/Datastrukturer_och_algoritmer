
/**************************************************************/
/* DSA list program example                                   */
/**************************************************************/
/* D.F. ROSS 120627 test version                              */
/**************************************************************/

#ifndef BELIST_H
#define BELIST_H

/**************************************************************/
/* function prototypes                                        */
/**************************************************************/

void gdisp();
void mdisp();

void addn(char c);
void remn(char c);

void adde(char cs, char cd, int v);
void reme(char cs, char cd);

int is_nmember(char c);
int is_emember(char cs, char cd);

int cardinality();

void bDijkstra();
void bFloyd();
void bWarshall();
void bPrim();
void bKruskal();

#endif
/**************************************************************/
/* end of definitions                                         */
/**************************************************************/

