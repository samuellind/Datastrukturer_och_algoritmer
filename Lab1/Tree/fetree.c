
/**************************************************************/
/* DSA tree program example                                   */
/**************************************************************/
/* D.F. ROSS 121013 test version                              */
/**************************************************************/

/**************************************************************/
/* include files                                              */
/**************************************************************/

#include <stdio.h>
#include "betree.h"

/****************************************************************************/
/* front end functions                                                      */
/****************************************************************************/

void display2D() { disp_2D(); }

void darray()    { disp_array(); }

void displaypre()  
   { printf(" TREE (%d nodes, height %d) is preorder:  ", cardinality(), bheight()); 
     disp_pre(); }
void displayin()
   { printf(" TREE (%d nodes, height %d) is inorder:   ", cardinality(), bheight());
     disp_in(); }
void displaypost()
   { printf(" TREE (%d nodes, height %d) is postorder: ", cardinality(), bheight());
     disp_post();}

void display()
{
    printf("\n"); displayin();
    printf("\n"); displaypre();
    printf("\n"); displaypost();
}

void addval (int v) { add(v);  }
void remval (int v) { rem(v);  }
void addhval(int v) { addh(v); }
void remhval(int v) { remh(v); }

void memberb(int v) {
   if (is_memberb(v)) printf(" *** %d found ***", v);
   else printf(" *** %d not found ***", v);
   }
   
void memberc(int v) {
   if (is_memberc(v)) printf(" *** %d found ***", v);
   else printf(" *** %d not found ***", v);
   }

void height()  { printf(" TREE height is %d ", bheight()); }
void heapify() { bheapify(); }

/****************************************************************************/
/* end of front end functions                                               */
/****************************************************************************/



