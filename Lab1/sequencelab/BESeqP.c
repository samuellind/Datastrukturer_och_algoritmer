
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

/***************************************************************************/
/* define types                                                            */
/***************************************************************************/

#define   NULLREF      NULL         /* null reference for list             */

/***************************************************************************/
/* list element definition (this is hidden!)                               */
/***************************************************************************/

typedef struct listelem * listref;

typedef struct listelem {
        int        value;
        listref    next;
        listref    prev;
        } listelem;

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

static int      is_empty(listref L)                      { return L==NULLREF; }

static int      get_value(listref E)            { return E->value; }
static listref  get_next(listref E)             { return E->next; }
static listref  get_prev(listref E)             { return E->prev; }

static void     set_value(listref E, int v)     { E->value = v; }
static void     set_next(listref E, listref t)  { E->next = t; }
static void     set_prev(listref E, listref t)  { E->prev = t; }

/****************************************************************************/
/* create and initialise an element in the list                             */
/****************************************************************************/

static listref create_e(int v) {
	
	listref ret;
	
	if(numels<20){
	
		struct listelem *new=malloc(sizeof(struct listelem));
			set_value(new, v);
			set_next(new, NULLREF);
			set_prev(new, NULLREF);
			ret=new;
			numels++;
	}
	else{
		printf("Too many elements!\n");
		ret=NULLREF;
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
	if(!is_empty(liststart)){
			listref i=liststart;
			int j=1;
			while(i!=NULLREF){
				//printf("\n#%d	value: %d //adress: %p	next: %p	prev: %p",j,get_value(i),i,get_next(i),get_prev(i));
				printf("\nvalue: %d",get_value(i));
				i=get_next(i);
				j++;
			}
		} 
	printf("\nEOL"); 
}

/****************************************************************************/
/* ADD to the list in ascending order by value                              */
/* e.g. b_add(4) on list (1, 2, 5, 7, 9) gives (1, 2, 4, 5, 7, 9)           */
/****************************************************************************/

static void b_add(int v) { 
	listref new = create_e(v);
	if(new!=NULLREF){
		pcurr=liststart;
		pprev=NULLREF;
		if(is_empty(liststart)){
			liststart=new;
			listend=new;
			pcurr=new;
		}
		
		else if(v<=get_value(liststart)){
			pprev=liststart;
			liststart=new;
			set_next(liststart,pprev);
			set_prev(pprev,liststart);
		}
		else if(v>=get_value(listend)){
			pprev=listend;
			listend=new;
			set_prev(new,pprev);
			set_next(pprev,listend);
		}
		else{
			pcurr=liststart;
			while(v>get_value(pcurr))
			{
				pprev=pcurr;
				pcurr=get_next(pcurr);
			}
			set_next(new, pcurr);
			set_prev(new,pprev);
			set_prev(pcurr,new);
			set_next(pprev,new);
		}
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

static listref b_find(int v) { pcurr = liststart;
	int i=0;
 	while(pcurr!= NULLREF && i<numels){
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

static void b_rem(int v) { listref pos;
							pos=b_find(v);

							if(pos==listend && pos==liststart){
									liststart=NULLREF;
									numels--;
									}
							else if(pos==liststart){
									liststart=get_next(liststart);
									set_prev(liststart,NULLREF);
									numels--;
								}
							else if(pos==listend){
									listend=get_prev(listend);
									set_next(listend,NULLREF);
									numels--;
									}
									
							else if(pos!=NULLREF){
								pprev=get_prev(pos);
								pcurr=get_next(pos);
								set_next(pprev,pcurr);
								set_prev(pcurr,pprev);
								numels--;
							}	
							else
								printf("Error: Value not in the list");
							
							free(pos);
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
			numels--;
		}
		else if(pcurr==liststart){
			liststart=get_next(liststart);
			set_prev(liststart,NULLREF);
			numels--;
		}
		else if(pcurr==listend){
			listend=get_prev(listend);
			set_next(listend,NULLREF);
			numels--;
		}
		else{
			pcurr=get_next(pcurr);
			set_next(pprev,pcurr);
			set_prev(pcurr,pprev);
			numels--;
		}
		free(pcurr);
}
/****************************************************************************/
/* FIND the number of elements in the list (cardinality)                    */
/* e.g. for list (1, 3, 5, 7) b_card returns 4                              */
/* e.g. empty list ()         b_card returns 0                              */
/****************************************************************************/

static int b_card() { return numels; }

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
static void b_next()    {if(get_next(pcurr)!=NULLREF)
								pcurr=get_next(pcurr);
							else{
								printf("Reached last element\n");
								printf("Previous element:");
							}
						}
						
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
int cardinality()             { return b_card(); }

void bfirst()                 { b_first();   }
void bnext()                  { b_next();    }
void disp_C()                 { b_disp_C();  }
int  exist_e()                { return b_exist_e(); }

/****************************************************************************/
/* end of basic functions                                                   */
/****************************************************************************/



