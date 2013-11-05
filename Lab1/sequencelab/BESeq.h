
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

void disp();

void add(int v);
void addpos(int v, int pos);

void rem(int v);
void rempos(int pos);

int is_member(int v);
int cardinality();

void bfirst();
void bnext();
void disp_C();
int  exist_e();

#endif
/**************************************************************/
/* end of definitions                                         */
/**************************************************************/

