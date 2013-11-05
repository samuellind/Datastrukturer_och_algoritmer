
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

void addval(int v);
void addvalpos(int v, int pos);

void remval(int v);
void remvalpos(int pos);

void member(int v);

int  size();

void f_first();
void f_next();
int  f_exist_e();

#endif
/****************************************************************************/
/* end of front end function prototypes                                     */
/****************************************************************************/

