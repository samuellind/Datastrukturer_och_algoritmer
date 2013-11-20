
/**************************************************************/
/* DSA tree program example                                   */
/**************************************************************/
/* D.F. ROSS 121013 test version                              */
/**************************************************************/

#ifndef BETREE_H
#define BETREE_H

/**************************************************************/
/* function prototypes                                        */
/**************************************************************/

void disp_2D();
void disp_array();

void disp_pre();
void disp_in();
void disp_post();

void add(int v);
void rem(int v);
void addh(int v);
void remh(int v);

int is_memberb(int v);
int is_memberc(int v);
int cardinality();
int bheight();

void bheapify();

#endif
/**************************************************************/
/* end of definitions                                         */
/**************************************************************/

