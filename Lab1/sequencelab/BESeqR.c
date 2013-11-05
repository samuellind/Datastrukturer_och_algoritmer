
/**************************************************************/
/* DSA list program example                                   */
/**************************************************************/
/* D.F. ROSS 120627 test version                              */
/**************************************************************/

/**************************************************************/
/* include files and  global data objects                     */
/**************************************************************/

#include <stdio.h>
#include <stdlib.h>

/**************************************************************/
/* define types                                               */
/**************************************************************/

#define   NULLREF      NULL     /* null reference for list    */

/**************************************************************/
/* list element definition (this is hidden!)                  */
/**************************************************************/

typedef struct listelem * listref;

typedef struct listelem {
        int        value;
        listref    tail;
        } listelem;

/**************************************************************/
/* define list instance                                       */
/**************************************************************/

static listref L     = (listref) NULL;
static listref C     = (listref) NULL;

/****************************************************************************/
/****************************************************************************/
/* private operations on the list - primitive operationa                    */
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/* primitive functions                                                      */
/****************************************************************************/
/* is_empty:        listref       --> Boolean                               */
/* get_value:       listref       --> int                                   */
/* get_tail:        listref       --> listref                               */
/* set_value:       int x listref --> listref                               */
/* set_tail:        listref       --> listref                               */
/* create_e:        int           --> listref                               */
/****************************************************************************/

static int      is_empty(listref L)             { return 1; /* TO DO */ }

static int      get_value(listref E)            { return 0; /* TO DO */ }
static listref  get_tail(listref E)             { return NULLREF; /* TO DO */ }

static listref  set_value(listref E, int v)     { return NULLREF; /* TO DO */ }
static listref  set_tail(listref E, listref t)  { return NULLREF; /* TO DO */ }

/****************************************************************************/
/* create and initialise an element in the list                             */
/****************************************************************************/

static listref create_e(int v)
{
   return NULLREF; /* TO DO */
}

/****************************************************************************/
/****************************************************************************/
/* private operations on the list - basic operationa                        */
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/* display functions                                                        */
/****************************************************************************/

static void print_el(int v) { printf(" -%d- ", v); }
static void print_eol()     { printf(" EOL "); }

/****************************************************************************/
/* basic functions                                                          */
/****************************************************************************/
/* head:      listref                --> listref                            */
/* tail:      listref                --> listref                            */
/* cons:      listref x listref      --> listref                            */
/* b_add:     int x listref          --> listref                            */
/* b_addpos:  int x listref x pos    --> listref                            */
/* b_rem:     int x listref          --> listref                            */
/* b_rempos:  int x listref x pos    --> listref                            */
/* b_find:    int x listref          --> listref                            */
/****************************************************************************/

/****************************************************************************/
/* head and tail - a RECURSIVE view of the sequence                         */
/****************************************************************************/

static listref head(listref L)     { return NULLREF; /* TO DO */  }
static listref tail(listref L)     { return NULLREF; /* TO DO */  }

/****************************************************************************/
/* CONStruct a new list with the element at the head of the list            */
/****************************************************************************/

static listref cons(listref e, listref L) { return NULLREF; /* TO DO */  }

/****************************************************************************/
/* display the list                                                         */
/* e.g. for list (1, 2, 5, 7, 9) gives List: 1 2 5 7 9 EOL                  */
/****************************************************************************/

static void b_disp(listref L) {

/* TO DO */ 

}

/****************************************************************************/
/* ADD to the list in ascending order by value                              */
/* e.g. b_add(4) on list (1, 2, 5, 7, 9) gives (1, 2, 4, 5, 7, 9)           */
/****************************************************************************/

static listref b_add(int v, listref L)
{
  return NULLREF; /* TO DO */
}

/****************************************************************************/
/* Add a new element at position p of the list                              */
/* the legal positions are 1..size(list)+1                                  */
/* otherwise give an error message - Error: invalid position                */
/* i.e. for a list of 5 elements positions: 1,2,3,4,5                       */
/* e.g. b_addpos(8, 0) on (1, 3, 5, 7, 9) gives Error: invalid position     */
/* e.g. b_addpos(8, 1) on (1, 3, 5, 7, 9) gives (8, 1, 3, 5, 7, 9)          */
/* e.g. b_addpos(8, 2) on (1, 3, 5, 7, 9) gives (1, 8, 3, 5, 7, 9)          */
/* e.g. b_addpos(8, 5) on (1, 3, 5, 7, 9) gives (1, 3, 5, 7, 8, 9)          */
/* e.g. b_addpos(8, 6) on (1, 3, 5, 7, 9) gives (1, 3, 5, 7, 9, 8)          */
/* e.g. b_addpos(8, 7) on (1, 3, 5, 7, 9) gives Error: invalid position     */
/****************************************************************************/

static listref b_addpos(int v, listref L, int pos)
{
   return NULLREF; /* TO DO */
}

/****************************************************************************/
/* REMove an element from the list by value: first occurrence for duplicates*/
/* if the value is not in the list: Error: value not in list                */
/* e.g. b_rem(4) on list (1, 2, 4, 7, 9) gives (1, 2, 7, 9)                 */
/* e.g. b_rem(4) on list (1, 4, 4, 7, 9) gives (1, 4, 7, 9)                 */
/* e.g. b_rem(4) on list (1, 2, 5, 7, 9) gives Error: value not in list     */
/****************************************************************************/

static listref b_rem(int v, listref L) {

    return NULLREF; /* TO DO */
}

/****************************************************************************/
/* REMove an element from position p of the list                            */
/* the legal positions are 1..size(list)  otherwise give an error message   */
/* e.g. b_rempos(0) on (1, 3, 5, 7, 9) gives Error: invalid position        */
/* e.g. b_rempos(2) on (1, 3, 5, 7, 9) gives (1, 5, 7, 9)                   */
/* e.g. b_rempos(5) on (1, 3, 5, 7, 9) gives (1, 3, 5, 7)                   */
/* e.g. b_rempos(6) on (1, 3, 5, 7, 9) gives Error: invalid position        */
/****************************************************************************/

static listref b_rempos(listref L, int pos) {

   return NULLREF; /* TO DO */
}

/****************************************************************************/
/* FIND an element in the list                                              */
/* FOUND:     return a reference to the element                             */
/* NOT FOUND: return NULLREF                                                */
/* e.g. b_find(4) in (1, 3, 4, 6) return reference(4)                       */
/* e.g. b_find(5) in (1, 3, 4, 6) return NULLREF                            */
/****************************************************************************/

static listref b_find(int v, listref L) {

   return NULLREF; /* TO DO */
}

/****************************************************************************/
/* FIND the number of elements in the list (cardinality)                    */
/* e.g. for list (1, 3, 5, 7) b_card returns 4                              */
/* e.g. empty list ()         b_card returns 0                              */
/****************************************************************************/

static int b_card(listref L) { return 0; /* TO DO */  }

/****************************************************************************/
/* navigation & display functions                                           */
/****************************************************************************/
/* b_disp_C:     void --> void  (side effect)                               */
/* e.g. for list (1,3,5,7) and pcurr refers to value 3 display 3            */
/* e.g. IF pcurr is NULLREF display Error: invalid element                  */
/* b_first:      void --> void  (side effect)                               */
/* e.g. for list (1,3,5,7) set pcurr to refer to 1                          */
/* b_next:       void --> void  (side effect)                               */
/* e.g. for list (1,3,5,7) and pcurr is 1 set pcurr to refer to 3           */
/* b_exist_e:    void --> int                                               */
/* e.g. if pcurr == NULLREF return FALSE                                    */
/* e.g. if pcurr != NULLREF return TRUE                                     */
/****************************************************************************/

static void b_first()     { /* TO DO */  }
static void b_next()      { /* TO DO */  }

static void b_disp_C() {
   /* TO DO */ 
   }
   
static int b_exist_e()  { return 0; /* TO DO */  }

/****************************************************************************/
/****************************************************************************/
/* public operations on the list                                            */
/****************************************************************************/
/****************************************************************************/

void disp()                   { b_disp(L); }

void add(int v)               { L = b_add(v, L); }
void addpos(int v, int pos)   { L = b_addpos(v, L, pos); }

void rem(int v)               { L = b_rem(v, L); }
void rempos(int pos)          { L = b_rempos(L, pos); }

int is_member(int v)          { return !is_empty(b_find(v, L)); }
int cardinality()             { return b_card(L); }

void bfirst()                 { b_first();   }
void bnext()                  { b_next();    }
void disp_C()                 { b_disp_C();  }
int  exist_e()                { return b_exist_e(); }

/****************************************************************************/
/* end of basic functions                                                   */
/****************************************************************************/



