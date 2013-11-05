
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

/****************************************************************************/
/* define types & constants                                                 */
/****************************************************************************/

#define   LSIZE        20               /* max number of list elements      */
#define   NULLREF      -1               /* null reference for list          */

typedef  int          listref;          /* list element reference type      */

/****************************************************************************/
/*  Define list structure                                                   */
/****************************************************************************/

int     value[LSIZE];                 /* list values                        */
listref next[LSIZE];                  /* list next references               */
listref prev[LSIZE];                  /* list prev references               */

/****************************************************************************/
/* define list instance recursive/iterative                                 */
/****************************************************************************/

static listref  liststart = NULLREF;         /* ref to start of list        */
static listref  listend   = NULLREF;         /* ref to end of list          */

static listref  pcurr     = NULLREF;         /* ref to the current element  */
static listref  pprev     = NULLREF;         /* ref to the previous element */
static listref  pnew      = NULLREF;         /* ref to the new element      */

static int      numels    = 0;               /* number of elements          */

/****************************************************************************/
/****************************************************************************/
/* private operations on the list - primitive operationa                    */
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/* primitive functions                                                      */
/****************************************************************************/
/* is_empty:        listref            --> Boolean                          */
/* get_value:       listref            --> int                              */
/* get_next:        listref            --> listref                          */
/* get_prev:        listref            --> listref                          */
/* set_value:       int x listref      --> listref                          */
/* set_next:        listref x listref  --> listref                          */
/* set_prev:        listref x listref  --> listref                          */
/* create_e:        int                --> listref                          */
/****************************************************************************/

static int      is_empty(listref L)             { return liststart == NULLREF; }		//Tom lista ger return=1

static int      get_value(listref E)            {  return value[E]; }
static listref  get_next(listref E)             {  return get_value(next[E]); }
static listref  get_prev(listref E)             { return get_value(prev[E]); }

static void     set_value(listref E, int v)     { value[E]=v; }
static void     set_next(listref E, listref t)  { next[E]=t; }
static void     set_prev(listref E, listref t)  { prev[E]=t; }

/****************************************************************************/
/* create and initialise an element in the list                             */
/****************************************************************************/

static listref create_e(int v) { 
	if(numels>=LSIZE){
		set_value(numels, v);
		set_next(numels, NULLREF);
		set_prev(numels, NULLREF);
		numels++;
	}
	else
		printf("Too many elements, max is %d", LSIZE);
	return numels; }

/****************************************************************************/
/****************************************************************************/
/* private operations on the list - basic operationa                        */
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/* basic functions                                                          */
/****************************************************************************/
/* b_add:     int x listref          --> listref                            */
/* b_addpos:  int x listref x pos    --> listref                            */
/* b_rem:     int x listref          --> listref                            */
/* b_rempos:  int x listref x pos    --> listref                            */
/* b_find:    int x listref          --> listref                            */
/****************************************************************************/

/****************************************************************************/
/* display the list                                                         */
/* e.g. for list (1, 2, 5, 7, 9) gives List: 1 2 5 7 9 EOL                  */
/****************************************************************************/

static void b_disp() { 
		if(is_empty()!=NULLREF){
		int i;
		for(i=0;get_value(i)!=NULLREF;i++){
			printf("%d ", get_value(i));
		}
		printf("EOL");
	}
 }

/****************************************************************************/
/* ADD to the list in ascending order by value                              */
/* e.g. b_add(4) on list (1, 2, 5, 7, 9) gives (1, 2, 4, 5, 7, 9)           */
/****************************************************************************/

static void b_add(int v) { 
		listref new = create_e(v);
	if(isEmpty()){
		set_next(new, NULLREF);			
		set_prev(new, NULLREF);			
	else if(v>listend){
		set_next(new, NULLREF);
		set_prev(new, get_next(numels-2));
		listend=v
		
	}
	else if(v<liststart){	//Minindex
		set_prev(new, NULLREF);
		set_next(new, liststart);
		liststart=v;
	}
	
	else{
	
		while(1){}}
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

static void b_addpos(int v, int pos) { 
	create_e(v);
	//set_next(get_value(pos)) 
	}

/****************************************************************************/
/* REMove an element from the list by value: first occurrence for duplicates*/
/* if the value is not in the list: Error: value not in list                */
/* e.g. b_rem(4) on list (1, 2, 4, 7, 9) gives (1, 2, 7, 9)                 */
/* e.g. b_rem(4) on list (1, 4, 4, 7, 9) gives (1, 4, 7, 9)                 */
/* e.g. b_rem(4) on list (1, 2, 5, 7, 9) gives Error: value not in list     */
/****************************************************************************/

static void b_rem(int v) { /* TO DO */ }

/****************************************************************************/
/* REMove an element from position p of the list                            */
/* the legal positions are 1..size(list)  otherwise give an error message   */
/* e.g. b_rempos(0) on (1, 3, 5, 7, 9) gives Error: invalid position        */
/* e.g. b_rempos(2) on (1, 3, 5, 7, 9) gives (1, 5, 7, 9)                   */
/* e.g. b_rempos(5) on (1, 3, 5, 7, 9) gives (1, 3, 5, 7)                   */
/* e.g. b_rempos(6) on (1, 3, 5, 7, 9) gives Error: invalid position        */
/****************************************************************************/

static void b_rempos(int pos) { /* TO DO */ }

/****************************************************************************/
/* FIND an element in the list                                              */
/* FOUND:     return a reference to the element                             */
/* NOT FOUND: return NULLREF                                                */
/* e.g. b_find(4) in (1, 3, 4, 6) return reference(4)                       */
/* e.g. b_find(5) in (1, 3, 4, 6) return NULLREF                            */
/****************************************************************************/

static listref b_find(int v) { /* TO DO */ return NULLREF; }

/****************************************************************************/
/* FIND the number of elements in the list (cardinality)                    */
/* e.g. for list (1, 3, 5, 7) b_card returns 4                              */
/* e.g. empty list ()         b_card returns 0                              */
/****************************************************************************/

static int b_card() { /* TO DO */ return 0; }

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

static void b_disp_C()  { /* TO DO */ }  /* display current element (pcurr) */
static void b_first()   { /* TO DO */ }
static void b_next()    { /* TO DO */ }
static int  b_exist_e() { /* TO DO */ return 0; }

/****************************************************************************/
/****************************************************************************/
/* public operations on the list                                            */
/****************************************************************************/
/****************************************************************************/

void disp()                   { b_disp(); }

void add(int v)               { b_add(v); }
void addpos(int v, int pos)   { b_addpos(v, pos); }

void rem(int v)               { b_rem(v); }
void rempos(int pos)          { b_rempos(pos); }

int is_member(int v)          { return !is_empty(b_find(v)); }
int cardinality()             { return b_card(); }

void bfirst()                 { b_first();   }
void bnext()                  { b_next();    }
void disp_C()                 { b_disp_C();  }
int  exist_e()                { return b_exist_e(); }

/****************************************************************************/
/* end of basic functions                                                   */
/****************************************************************************/



