
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

static int      is_empty(listref L)             { return L==(listref)NULL; }

static int      get_value(listref E)            { return E->value; }
static listref  get_tail(listref E)             { return E->tail;  }

static listref  set_value(listref E, int v)     { E->value = v; return E;}
static listref  set_tail(listref E, listref t)  { E->tail = t; return E;}


/****************************************************************************/
/* FIND the number of elements in the list (cardinality)                    */
/* e.g. for list (1, 3, 5, 7) b_card returns 4                              */
/* e.g. empty list ()         b_card returns 0                              */
/****************************************************************************/

static int b_card(listref L) { 
	if(is_empty(L))
		return 0;
	else return (1+b_card(L->tail));
	}

/****************************************************************************/
/* create and initialise an element in the list                             */
/****************************************************************************/

static listref create_e(int v)
{
	listref ret;
	
	if(b_card(L)<20){ // how do??!
	
		struct listelem *new=malloc(sizeof(struct listelem));
			set_value(new, v);
			set_tail(new, NULLREF);
			ret=new;
			C=new;
	}
	else{
		printf("Too many elements!\n");
		ret=(listref)NULL;
	}
	return ret;
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

static listref head(listref L)     { return C; }
static listref tail(listref L)     { return L; }

/****************************************************************************/
/* CONStruct a new list with the element at the head of the list            */
/****************************************************************************/

static listref cons(listref e, listref L) { 
		set_tail(e, L);
	return e; }

/****************************************************************************/
/* display the list                                                         */
/* e.g. for list (1, 2, 5, 7, 9) gives List: 1 2 5 7 9 EOL                  */
/****************************************************************************/

static void b_disp(listref L) {

	if(!is_empty(L)){
		print_el(get_value(L));
		b_disp(get_tail(L));
	}
	else
	print_eol();

}

/****************************************************************************/
/* ADD to the list in ascending order by value                              */
/* e.g. b_add(4) on list (1, 2, 5, 7, 9) gives (1, 2, 4, 5, 7, 9)           */
/****************************************************************************/

static listref b_add(int v, listref L)
{
  listref new = create_e(v);
  if(!is_empty(new)){
	  if(!is_empty(L)){
			if(v>get_value(L)){
				return cons(L, b_add(v, get_tail(L)));
				}
			else 
				return cons(new, L);
  	}
  		else 
			return cons(new, L);
	}
  	
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

static listref b_addpos(int v, listref L, int pos){
listref new = create_e(v);
	if(!is_empty(new)){
	  if(!is_empty(L)){
			if(1<pos){
				return cons(L, b_addpos(v, get_tail(L),pos-1));
				}
			else 
				return cons(new, L);
	  }
	  else
		return cons(new, L);
	}
}

/****************************************************************************/
/* REMove an element from the list by value: first occurrence for duplicates*/
/* if the value is not in the list: Error: value not in list                */
/* e.g. b_rem(4) on list (1, 2, 4, 7, 9) gives (1, 2, 7, 9)                 */
/* e.g. b_rem(4) on list (1, 4, 4, 7, 9) gives (1, 4, 7, 9)                 */
/* e.g. b_rem(4) on list (1, 2, 5, 7, 9) gives Error: value not in list     */
/****************************************************************************/

static listref b_rem(int v, listref L) {
	
		if(!is_empty(L)){
			if(v==get_value(L)){
				return get_tail(L);
				}
			else {
				return cons(L, b_rem(v,get_tail(L)));
			}
		}
		else
			return NULLREF;
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
	
	if(!is_empty(L)){
		if(1<pos){
			return cons(L, b_rempos(get_tail(L),pos-1));
			}
		else 
			return get_tail(L);
  }
  else 
	return NULLREF;
   
}

/****************************************************************************/
/* FIND an element in the list                                              */
/* FOUND:     return a reference to the element                             */
/* NOT FOUND: return NULLREF                                                */
/* e.g. b_find(4) in (1, 3, 4, 6) return reference(4)                       */
/* e.g. b_find(5) in (1, 3, 4, 6) return NULLREF                            */
/****************************************************************************/

static listref b_find(int v, listref L) {
 
 	if(!is_empty(L)){
 		if(v==get_value(L)){
			return L;
			}
		else {
		return b_find(v,get_tail(L));
		}
	}
	else
		return NULLREF;
 	
}


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

static void b_first()     { if(!is_empty(L)) C=L; printf("%d\n",get_value(L));  }
static void b_next()      {	if(!is_empty(get_tail(C))&& !is_empty(L)) C=get_tail(C); 
							else 
								printf("Reached last element\n previous element: ");
							printf("%d\n",get_value(C));}

static void b_disp_C(){//if(!is_empty(C))  printf("%d\n",get_value(C));
   }
   
static int b_exist_e()  { if(!is_empty(get_tail(C))) return 1;
							else 
								return 0;  }

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



