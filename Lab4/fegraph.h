
/**************************************************************/
/* DSA list program example                                   */
/**************************************************************/
/* D.F. ROSS 120627 test version                              */
/**************************************************************/

#ifndef FELIST_H
#define FELIST_H

/****************************************************************************/
/* front end function prototypes                                            */
/****************************************************************************/

void display();
void displaym();

void addnode(char c);
void remnode(char c);

void addedge(char cs, char cd, int w);
void remedge(char cs, char cd);

void nmember(char c);
void emember(char cs, char cd);

int  nfound(char c);
int  efound(char cs, char cd);

void fDijkstra();
void fFloyd();
void fWarshall();
void fPrim();
void fKruskal();

#endif
/****************************************************************************/
/* end of front end function prototypes                                     */
/****************************************************************************/

