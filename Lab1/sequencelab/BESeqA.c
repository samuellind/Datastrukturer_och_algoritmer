
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

static int      is_empty(listref L)             { return L == NULLREF; }		//Tom lista ger return=1

static int      get_value(listref E)            {  return value[E]; }
static listref  get_next(listref E)             {  return next[E]; }
static listref  get_prev(listref E)             { return prev[E]; }

static void     set_value(listref E, int v)     { value[E]=v; }
static void     set_next(listref E, listref t)  { next[E]=t; }
static void     set_prev(listref E, listref t)  { prev[E]=t; }

/****************************************************************************/
/* create and initialise an element in the list                             */
/****************************************************************************/

static listref create_e(int v) { 
	int ret;
	if(numels<LSIZE){
		set_value(numels, v);
		set_next(numels, NULLREF);
		set_prev(numels, NULLREF);
		pprev=pnew;
		ret=numels;
		numels++;
		pnew=numels;
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
		//if(is_empty(pcurr)!=NULLREF){
			int i=liststart,j=1;
			printf("\nListstart value: %d\n", get_value(liststart));
			while(i!=-1){
				printf("#%d	value: %d\n",j,get_value(i));
				i=get_next(i);
				j++;
			}
			printf("***All elements***\n");
			for(i=0;i<20;i++){
				printf("#%d value: %d\n",i,get_value(i));
			}
		//}
		printf("EOL");
}

/****************************************************************************/
/* ADD to the list in ascending order by value                              */
/* e.g. b_add(4) on list (1, 2, 5, 7, 9) gives (1, 2, 4, 5, 7, 9)           */
/****************************************************************************/

static void b_add(int v) { 

	listref new = create_e(v);
	if(new!=-1){
		pcurr=liststart;
		if(is_empty(liststart)){
			printf("Tom lista");
			liststart=new;
			listend=new;
			printf("*********************************\n");
			printf("	Creating on index %d\n", numels-1);
			printf("#%d Liststart: %d listend: %d\n", new,liststart,listend);
			printf("getvalueliststart: %d getvaluelistend: %d\n", get_value(liststart),get_value(listend));
			printf("next: %d prev: %d\n", get_next(liststart),get_prev(liststart));
			printf("*********************************\n");
		}
		
		else if(v<=get_value(liststart)){
			printf("Liststart: %d\n",liststart);
			printf("Input value: %d	prev_value: %d prev index: %d \n",v,get_value(pcurr), pcurr);
			pprev=liststart;
			liststart=new;
			printf("*********************************\n");
			printf("	Creating on index %d\n", numels-1);
			printf("#%d Liststart: %d listend: %d\n", new, liststart,listend);
			printf("getvalueliststart: %d getvaluelistend: %d\n", get_value(liststart),get_value(listend));
			set_next(liststart,pprev);
			set_prev(pprev,liststart);
			printf("next: %d prev: %d\n", get_next(liststart),get_prev(liststart));
			printf("Prevnext: %d Prevprev: %d\n", get_next(pprev),get_prev(pprev));
			printf("*********************************\n");
		}
		else if(v>=get_value(listend)){
			pprev=listend;
			listend=new;
			printf("*********************************\n");
			printf("	Creating on index %d\n", numels-1);
			printf("#%d Liststart: %d listend: %d\n", new, liststart,listend);
			printf("getvalueliststart: %d getvaluelistend: %d\n", get_value(liststart),get_value(listend));
			set_prev(listend,pprev);
			set_next(pprev,listend);
			printf("next: %d prev: %d\n", get_next(listend),get_prev(listend));
			printf("Prevnext: %d Prevprev: %d\n", get_next(pprev),get_prev(pprev));
			printf("*********************************\n");
		}
		else{
			//printf("Går in i else");
			pcurr=liststart;
			while(v!=get_value(pcurr)){
				pprev=pcurr;
				pcurr=get_next(pcurr);
			}
			printf("Kan sätta in efter %d\n",pcurr);
			pprev=get_prev(pcurr);
			set_next(new,pcurr);
			set_prev(new,pprev);
			set_next(pprev,new);
			set_prev(pcurr,new);
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

static void b_addpos(int v, int pos){
	listref new = create_e(v);
	//printf("listref %d\n", new);
	if(new!=-1){
		int i=0;
		pcurr=0;
		if(is_empty(new)){
		//	set_next(new, NULLREF);			
		//	set_prev(new, NULLREF);
			liststart=new;
			listend=new;
			printf("*********************************\n");
			printf("*****EMPTY LIST*********\n");
			printf("	Creating on index %d\n", numels-1);
			printf("#%d Liststart: %d listend: %d\n", new,liststart,listend);
			printf("getvalueliststart: %d getvaluelistend: %d\n", get_value(liststart),get_value(listend));
			printf("next: %d prev: %d\n", get_next(liststart),get_prev(liststart));
			printf("*********************************\n");
			pcurr=new;
		}
	else if(pos==1){
			printf("pcurr %d pvalue %d pnext %d pprev %d\n", pcurr, get_value(pcurr), get_next(pcurr), get_prev(pcurr));
			printf("*********************************\n");
			printf("	Creating on index %d\n", numels-1);
			printf("#%d Liststart: %d listend: %d\n", new,liststart,listend);
			printf("getvalueliststart: %d getvaluelistend: %d\n", get_value(liststart),get_value(listend));
			printf("next: %d prev: %d\n", get_next(pcurr),get_prev(pcurr));
			printf("*********************************\n");
			pcurr=get_next(pcurr);
			set_next(new,pcurr);
			set_prev(new,pprev);
			set_prev(pcurr,new);
			
			if(v>=get_value(listend)){
				listend=new;
				printf("Duplicate listend updated\n");
				printf("#%d Liststart: %d listend: %d\n", new, liststart,listend);
				printf("getvalueliststart: %d getvaluelistend: %d\n", get_value(liststart),get_value(listend));
			}
			else if(v<=get_value(liststart)){
				liststart=new;
				printf("Dupcliate liststart updated\n");
				printf("#%d Liststart: %d listend: %d\n", new, liststart,listend);
				printf("getvalueliststart: %d getvaluelistend: %d\n", get_value(liststart),get_value(listend));
			}
		}
	else{
		while(i<pos-1){
			pprev=pcurr;
			pcurr=get_next(pcurr);
			i++;
		}
		
		set_next(new,pcurr);
		set_prev(new,pprev);
		set_next(pprev,new);
		set_prev(pcurr,new);
		
		printf("Test\n");	
		printf("*********************************\n");
		printf("	Creating on index %d\n", numels-1);
		printf("#%d Liststart: %d listend: %d\n", new,liststart,listend);
		printf("getvalueliststart: %d getvaluelistend: %d\n", get_value(liststart),get_value(listend));
		printf("next: %d prev: %d\n", get_next(pcurr),get_prev(pprev));
		printf("*********************************\n");
		
		if(v>=get_value(listend)){
			listend=new;
			printf("Duplicate listend updated\n");
			printf("#%d Liststart: %d listend: %d\n", new, liststart,listend);
			printf("getvalueliststart: %d getvaluelistend: %d\n", get_value(liststart),get_value(listend));
		}
		else if(v<=get_value(liststart)){
			liststart=new;
			printf("Dupcliate liststart updated\n");
			printf("#%d Liststart: %d listend: %d\n", new, liststart,listend);
			printf("getvalueliststart: %d getvaluelistend: %d\n", get_value(liststart),get_value(listend));
			}
		}
	}
}

/****************************************************************************/
/* REMove an element from the list by value: first occurrence for duplicates*/
/* if the value is not in the list: Error: value not in list                */
/* e.g. b_rem(4) on list (1, 2, 4, 7, 9) gives (1, 2, 7, 9)                 */
/* e.g. b_rem(4) on list (1, 4, 4, 7, 9) gives (1, 4, 7, 9)                 */
/* e.g. b_rem(4) on list (1, 2, 5, 7, 9) gives Error: value not in list     */
/****************************************************************************/

static void b_rem(int v) {listref pos;
							pos=b_find(v);
							pprev=get_prev(pos);
							pcurr=pos;
							set_next(pprev,pcurr);
							set_prev(pcurr,pprev);
						}

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

static listref b_find(int v) {
	listref ret=NULLREF;
	pcurr = liststart;
	
 	while(pcurr!= -1 && pcurr<numels){
 		printf("LOOOOOP!!! %d \n",get_value(pcurr));
 		if(v == get_value(pcurr))
 			return pcurr;
 		else
 			pcurr = get_next(pcurr);
 			printf("ret %d \n",ret);
 	}
 	return NULLREF;
}

/****************************************************************************/
/* FIND the number of elements in the list (cardinality)                    */
/* e.g. for list (1, 3, 5, 7) b_card returns 4                              */
/* e.g. empty list ()         b_card returns 0                              */
/****************************************************************************/

static int b_card() {return numels;}

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
static void b_next()    {pcurr=get_next(pcurr);}
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


