
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
#define	  EMPTY		   -2

typedef  int          listref;          /* list element reference type      */

/****************************************************************************/
/*  Define list structure                                                   */
/****************************************************************************/

int     value[LSIZE];                 /* list values                        */
listref next[LSIZE];                  /* list next references               */
listref prev[LSIZE];                  /* list prev references               */
int 	nextrem[LSIZE];				  /* list next  element in remstack		*/

/****************************************************************************/
/* define list instance recursive/iterative                                 */
/****************************************************************************/

static listref  liststart = NULLREF;         /* ref to start of list        */
static listref  listend   = NULLREF;         /* ref to end of list          */

static listref  pcurr     = NULLREF;         /* ref to the current element  */
static listref  pprev     = NULLREF;         /* ref to the previous element */
static listref  pnew      = NULLREF;         /* ref to the new element      */

static int      numels    = 0;               /* number of elements          */
static int 		rempntr	  = 0;				 /* stack pointer nextrem array	*/

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

static int      is_empty(listref L)             { return L == NULLREF; }		//Tom lista ger return=1

static int      get_value(listref E)            {  return value[E]; }
static listref  get_next(listref E)             {  return next[E]; }
static listref  get_prev(listref E)             { return prev[E]; }

static void     set_value(listref E, int v)     { value[E]=v; }
static void     set_next(listref E, listref t)  { next[E]=t; }
static void     set_prev(listref E, listref t)  { prev[E]=t; }

/****************************************************************************/
/* All removed elements position will be stored here for reuse              */
/* e.g. if removing (1 and then 3) it will be stored as 1 | 3 in stack      */
/* If numels have reached 20, start using stack positions in order to swap	*/
/* e.g. full list () == 20 elements	print "Out of space                     */
/****************************************************************************/

static void set_remstack(int v) {
	if(rempntr<LSIZE){
		nextrem[rempntr]=v;
		rempntr++;
		printf("Set remstack setting position %d to %d\n", rempntr, v);
	}
	else
		printf("Out of space\n");		
}

/****************************************************************************/
/* Returns first available element that has been previously removed         */
/* and stored in the remstack. LIFO method is used.						    */
/* If rempntr == 0 means list is empty										*/
/****************************************************************************/

static int get_remstack() {
	int next;
	printf("rempntr: %d\n", rempntr);
	if(rempntr!=-1){
		rempntr--;
		next=nextrem[rempntr];
		printf("Get remstack returning rmpntr %d position: %d\n", rempntr, nextrem[rempntr]);
	}
	else{
		printf("No elements in array\n");
		next=-1;
	}
	
	return next;
}
/****************************************************************************/
/* create and initialise an element in the list                             */
/****************************************************************************/

static listref create_e(int v) { 
	int ret, next;
	if(numels<LSIZE){
		set_value(numels, v);
		set_next(numels, NULLREF);
		set_prev(numels, NULLREF);
		//pprev=pnew;
		ret=numels;
		numels++;
		//pnew=numels;
	}
	else{
		printf("Too many elements, max is %d", LSIZE);
		ret=-1;
	}	
	return ret; 
}

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
			int i=liststart,j=1;
			while(!is_empty(i)){
				printf("\n#%d	value: %d next: %d",j,get_value(i), get_value(get_next(i)));
				i=get_next(i);
				j++;
			}
			
		printf("\nEOL");

}

/****************************************************************************/
/* ADD to the list in ascending order by value                              */
/* e.g. b_add(4) on list (1, 2, 5, 7, 9) gives (1, 2, 4, 5, 7, 9)           */
/****************************************************************************/

static void b_add(int v) { 

	listref new = create_e(v);
	
	pprev = NULLREF; pcurr = liststart;
	while (!is_empty(pcurr) && (v > get_value(pcurr))) {
		pprev = pcurr;
		pcurr = get_next(pcurr);
	}
			
	set_prev(new, pprev);
	set_next(new, pcurr);
	if(is_empty(pprev))
		liststart=new;
	else 
		set_next(pprev, new);
	if(is_empty(pcurr))
		listend=new;
	else 
		set_prev(pcurr, new);
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
	listref new = create_e(v);
	
	if(new!=NULLREF){
		int i=0;
		
		pcurr=liststart;
		if(is_empty(liststart)){
			liststart=new;
			listend=new;
			pcurr=new;
		}
	else if(pos==1 && numels!=1){
			pcurr=liststart;
			liststart=new;
			set_next(new,pcurr);
			set_prev(new,NULLREF);
			set_prev(pcurr,new);
		}
	else if(pos==numels && numels!=1){
			pcurr=listend;
			listend=new;
			set_next(new,NULLREF);
			set_prev(new,pcurr);
			set_next(pcurr,new);
		}
	else{
		pcurr=liststart;
		i=0;
		while(i<pos-1){
			pprev=pcurr;
			pcurr=get_next(pcurr);
			i++;
		}
		set_next(new,pcurr);
		set_prev(new,pprev);
		set_prev(pcurr,new);
		set_next(pprev,new);
		}
	}
}

/****************************************************************************/
/* FIND an element in the list                                              */
/* FOUND:     return a reference to the element                             */
/* NOT FOUND: return NULLREF                                                */
/* e.g. b_find(4) in (1, 3, 4, 6) return reference(4)                       */
/* e.g. b_find(5) in (1, 3, 4, 6) return NULLREF                            */
/****************************************************************************/

static listref b_find(int v) {
	pcurr = liststart;
	int i =0; 
 	while(!is_empty(pcurr) && i<numels){
 		if(v == get_value(pcurr))
 		{
 			return pcurr;
 		}
 		else{
 			pcurr = get_next(pcurr);
			}
		i++;
	}
 	
 	return NULLREF;
}

/****************************************************************************/
/* REMove an element from the list by value: first occurrence for duplicates*/
/* if the value is not in the list: Error: value not in list                */
/* e.g. b_rem(4) on list (1, 2, 4, 7, 9) gives (1, 2, 7, 9)                 */
/* e.g. b_rem(4) on list (1, 4, 4, 7, 9) gives (1, 4, 7, 9)                 */
/* e.g. b_rem(4) on list (1, 2, 5, 7, 9) gives Error: value not in list     */
/****************************************************************************/

static void b_rem(int v) {
	
	listref pos;
	pos=b_find(v);

	if(pos==listend && pos==liststart){
		liststart=NULLREF;
		//numels--;
		}
	else if(pos==liststart){
		printf("Liststart");
		pprev= liststart;
		liststart=get_next(liststart);
		set_next(pprev,NULLREF);
		set_prev(liststart,NULLREF);
		//numels--;
		}
	else if(pos==listend){
		listend=get_prev(listend);
		set_next(listend,NULLREF);
		//numels--;
		}
			
	else if(pos!=NULLREF){
		printf("Rem else if");
		pprev=get_prev(pos);
		pcurr=get_next(pos);
		set_next(pprev,pcurr);
		set_prev(pcurr,pprev);
		//numels--;
	}	
	else
		printf("Error: Value not in the list");
	
}
						
/****************************************************************************/
/* REMove an element from position p of the list                            */
/* the legal positions are 1..size(list)  otherwise give an error message   */
/* e.g. b_rempos(0) on (1, 3, 5, 7, 9) gives Error: invalid position        */
/* e.g. b_rempos(2) on (1, 3, 5, 7, 9) gives (1, 5, 7, 9)                   */
/* e.g. b_rempos(5) on (1, 3, 5, 7, 9) gives (1, 3, 5, 7)                   */
/* e.g. b_rempos(6) on (1, 3, 5, 7, 9) gives Error: invalid position        */
/****************************************************************************/

static void b_rempos(int pos) { 
		int i=0;
		pcurr=liststart;
		while(i<pos-1){
			pprev=pcurr;
			pcurr=get_next(pcurr);
			i++;
		}
		if(pcurr==listend && pcurr==liststart){
			liststart=NULLREF;
			listend=NULLREF;
			//numels--;
		}
		else if(pcurr==liststart){
			liststart=get_next(liststart);
			set_prev(liststart,NULLREF);
			//numels--;
		}
		else if(pcurr==listend){
			listend=get_prev(listend);
			set_next(listend,NULLREF);
			//numels--;
		}
		else{
			pcurr=get_next(pcurr);
			set_next(pprev,pcurr);
			set_prev(pcurr,pprev);
			//numels--;
		}
		
}
/****************************************************************************/
/* FIND the number of elements in the list (cardinality)                    */
/* e.g. for list (1, 3, 5, 7) b_card returns 4                              */
/* e.g. empty list ()         b_card returns 0                              */
/****************************************************************************/

static int b_card(listref E) {if(!is_empty(E)) return 1+b_card(get_next(E));
								else return 0;}

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

static void b_disp_C()  {printf("%d\n",get_value(pcurr));}  /* display current element (pcurr) */
static void b_first()   {pcurr=liststart;}
static void b_next()    {if(!is_empty(pcurr)&&get_value(get_next(pcurr))!=0)
								pcurr=get_next(pcurr);
							else{
								printf("Reached last element\n");
								printf("Previous element:");
							}
						}/*{if(!is_empty(pcurr)){pcurr=get_next(pcurr);}
							else printf("EOL\n");}*/
static int  b_exist_e() { if(pcurr == NULLREF)
								return 0;
						  else	
						  	return 1;
}

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
int cardinality()             { return b_card(liststart); }

void bfirst()                 { b_first();   }
void bnext()                  { b_next();    }
void disp_C()                 { b_disp_C();  }
int  exist_e()                { return b_exist_e(); }

/****************************************************************************/
/* end of basic functions                                                   */
/****************************************************************************/


