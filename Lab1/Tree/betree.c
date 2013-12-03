
/**************************************************************/
/* DSA tree program example                                   */
/**************************************************************/
/* D.F. ROSS 121013 test version                              */
/**************************************************************/

/**************************************************************/
/* include files and  global data objects                     */
/**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**************************************************************/
/* define constants & types                                   */
/**************************************************************/

#define ARRLEN 100
#define NILL   NULL

/**************************************************************/
/* tree element definition (this is hidden!)                  */
/**************************************************************/

typedef struct treenode * treeref;

typedef struct treenode {
        int        value;
        int        height;
        treeref    LC;
        treeref    RC;
        } treenode;

/**************************************************************/
/* define tree instance                                       */
/**************************************************************/

static treeref T     = (treeref) NULL;

/**************************************************************/
/* define heap array instance                                 */
/**************************************************************/

static int first=NILL,  last=NILL;
static int qfirst=0, qlast=0;

static treeref heaparr[ARRLEN];
static treeref queue[ARRLEN];


/****************************************************************************/
/****************************************************************************/
/* private operations on the tree - primitive operationa                    */
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/* primitive functions                                                      */
/****************************************************************************/
/* is_empty:        treeref       --> Boolean                               */
/* get_value:       treeref       --> int                                   */
/* get_height:      treeref       --> int                                   */
/* get_LC:          treeref       --> treeref                               */
/* get_RC:          treeref       --> treeref                               */
/* set_value:       int x treeref --> treeref                               */
/* set_LC:          treeref       --> treeref                               */
/* set_RC:          treeref       --> treeref                               */
/* create_node:     int           --> treeref                               */
/****************************************************************************/

static int      is_empty(treeref T)             { return (T==(treeref)NULL); }

static int      get_value(treeref T)            { return T->value; }
static int      get_height(treeref T)           { return T->height; }
static treeref  get_LC(treeref T)               { return T->LC; }
static treeref  get_RC(treeref T)               { return T->RC; }

static treeref  set_value(treeref T, int v)     { T->value = v; return T; }
static treeref  set_height(treeref T, int h)    { T->height = h; return T; }
static treeref  set_LC(treeref T, treeref L)    { T->LC = L; return T; }
static treeref  set_RC(treeref T, treeref R)    { T->RC = R; return T; }

/****************************************************************************/
/* create and initialise an element in the tree                             */
/****************************************************************************/

static treeref create_node(int v) { 	

	
	struct treenode *new=malloc(sizeof(struct treenode));
		
	set_value(new, v);
	set_height(new, 0);
	set_LC(new, (treeref)NULL);
	set_RC(new, (treeref)NULL);

	return new; }

/****************************************************************************/
/****************************************************************************/
/* private operations on the tree - basic operationa                        */
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/* basic functions                                                          */
/****************************************************************************/
/* cons:      treeref x treeref x treeref      --> treeref                  */
/* b_add:     int x treeref                    --> treeref                  */
/* b_rem:     int x treeref                    --> treeref                  */
/* b_find:    int x treeref                    --> Boolean                  */
/****************************************************************************/

/****************************************************************************/
/* LC, Node, RC - a RECURSIVE view of the tree                              */
/****************************************************************************/

static treeref node(treeref T)             { /* TO DO */ return NULL; }
static treeref LC(treeref T)               { /* TO DO */ return NULL; }
static treeref RC(treeref T)               { /* TO DO */ return NULL; }

/****************************************************************************/
/* CONStruct a new tree from a LC, Node and RC                              */
/****************************************************************************/

static treeref cons(treeref LC, treeref N, treeref RC) { 
	set_LC(N,LC); 
	set_RC(N,RC); 
	return N; }

/****************************************************************************/
/* FIND the height of the tree                                              */
/****************************************************************************/

static int max(int a, int b) { if(a<b) return b;
								else return a; }

static int b_height(treeref T) { 
	if(!is_empty(T))
		return 1+max(b_height(get_LC(T)),b_height(get_RC(T)));
	else
		return 0; }

/****************************************************************************/
/* display the tree ELEMENT                                                 */
/****************************************************************************/

static void b_disp_el(treeref T) { printf("\n%d", get_value(T)); }

/****************************************************************************/
/* display the heap array                                                   */
/****************************************************************************/

static void b_disp_array() { /* TO DO */ }
/****************************************************************************/
/* FIND the number of element in the tree (cardinality)                     */
/****************************************************************************/

static int b_card(treeref T) { if(is_empty(T)) return 0 ;
								else 
									return 1+b_card(get_LC(T))+b_card(get_RC(T)); }

/****************************************************************************/
/* Queue array initialized with NULLREF			                            */
/****************************************************************************/

static void fillqueue(){
	
	int i=0,j=(int)(pow(2,b_height(T))-1);
	while(i<j){
		queue[i]=NILL;
		i++;
	}
}

/****************************************************************************/
/* Tree to array via a queue (breadth-first search)                         */
/****************************************************************************/
/* Transforms a binary tree to a sequence (including NULL references)       */
/* e.g.  the following tree:                   [5]                          */
/*                                     [2]            [7]                   */
/*                               [nil]     [3]    [6]     [nil]             */
/*                                                                          */
/* becomes: [5] [2] [7] [nil] [3] [6] [nil]                                 */
/****************************************************************************/
static void T2Q(treeref T, int qpos) { 
if(!is_empty(T)){queue[qpos]=T;T2Q(get_LC(T),qpos*2);T2Q(get_RC(T),(qpos*2)+1);} 
}
/****************************************************************************/
/* display the T2Q array                                                    */
/****************************************************************************/

static void prntT2Q(){

int i,j=(pow(2,b_height(T))-1);

for(i=1;i<=j;i++){
	if(!is_empty(queue[i]))
	printf("[%d] ",get_value(queue[i]));
	else printf("[nil]");
	}
}

/****************************************************************************/
/* display the tree in 2D                                                   */
/****************************************************************************/
/* step 1: transform the tree to an array (Q) using T2Q() above             */
/* e.g. array [5] | [2] [7] | [nil] [3] [6] [nil] | etc.                    */
/*      level (1) | (2) (2) | (3)   (3) (3) (3)   | (4) ...                 */
/* step 2: then print the nodes at each level of the tree to give           */
/* level 1 (1 node)                           [5]                           */
/* level 2 (2 nodes)                   [2]            [7]                   */
/* level 3 (4 nodes)             [nil]     [3]    [6]     [nil]             */
/****************************************************************************/

static void b_disp_2D() { 
	fillqueue();
	T2Q(T,1);
	//prntT2Q();
	int x=1, y=0;
	
	int i=(pow(2,b_height(T))-1),curr=1;
	
	while(curr<=i){
		int j=0;
		while(j<x){
			if(!is_empty(queue[curr])){
				y=x;
				while((i/4)>y){
					printf("\t");
					y++;
				}
				printf("[%d] ",get_value(queue[curr]));
			}
			else printf("[nil] ");
			curr++;
			j++;
		}
		printf("\n");
		x=x*2;
	}
}
/****************************************************************************/
/* display the tree (pre-order)                                             */
/****************************************************************************/

static void b_disp_pre(treeref T) { 
	if(!is_empty(T)){
		b_disp_el(T);
		b_disp_pre(get_LC(T));
		b_disp_pre(get_RC(T));
		
	}
	else ;
 }

/****************************************************************************/
/* display the tree (in-order)                                              */
/****************************************************************************/

static void b_disp_in(treeref T) { 
	if(!is_empty(T)){
		b_disp_in(get_LC(T));
		b_disp_el(T);
		b_disp_in(get_RC(T));
		
	}
	else ;
}
/****************************************************************************/
/* display the tree (post-order)                                            */
/****************************************************************************/

static void b_disp_post(treeref T) { 
	if(!is_empty(T)){
		b_disp_post(get_LC(T));
		b_disp_post(get_RC(T));
		b_disp_el(T);	
		
	} 
	else ;
}

/****************************************************************************/
/* ADD to the tree in BST order                                             */
/****************************************************************************/

static treeref b_add(treeref T, treeref N) { 

	if(is_empty(T)){
		return N;
	}
	else if(get_value(N)>get_value(T)){
		set_height(N,get_height(N)+1);
		return cons(get_LC(T),T,b_add(get_RC(T),N));
	}
	else if(get_value(N)<get_value(T)){
		set_height(N,get_height(N)+1);
		return cons(b_add(get_LC(T),N),T,get_RC(T));
	}
	else
		return T;
	set_height(N,b_height(N));
}

/****************************************************************************/
/* REMove an element from the tree / BST order                              */
/****************************************************************************/

static treeref b_rem(treeref T, int v) { 
	
	if(is_empty(T)){
		free(T);
		return T;
	}
	else if(v<get_value(T))
		return cons(b_rem(get_LC(T),v),T,get_RC(T));
	else if(v>get_value(T))
		return cons(get_LC(T),T,b_rem(get_RC(T),v));
	else
		return b_add(get_LC(T),get_RC(T));
}

/****************************************************************************/
/* Build heap tree                                                          */
/****************************************************************************/

static void build_HT() { /* TO DO */ }

/****************************************************************************/
/* ADD to the tree in heap order                                            */
/****************************************************************************/

static treeref b_addh(treeref N) { /* TO DO */ return NULL; }

/****************************************************************************/
/* REMove an element from the tree in heap order                            */
/****************************************************************************/

static treeref b_remh(int v) { /* TO DO */ return NULL; }

/****************************************************************************/
/* FIND an element in the BST (Binary Search Tree)                          */
/****************************************************************************/

static int b_findb(treeref T, int v) { 
	
	if(is_empty(T))
		return 0;
	else if(v>get_value(T))
		return b_findb(get_RC(T),v);
	else if(v<get_value(T))
		return b_findb(get_LC(T),v);
	else
		return 1; 
}


/****************************************************************************/
/* FIND an element in the complete tree                                     */
/****************************************************************************/

static int b_findc(treeref T, int v) { /* TO DO */ return 0; }



/****************************************************************************/
/* Heapify the tree (heap)                                                  */
/****************************************************************************/

static treeref b_heapify(treeref T) { return T; /* TO DO */ return NULL; }

/****************************************************************************/
/****************************************************************************/
/* public operations on the tree                                            */
/****************************************************************************/
/****************************************************************************/

void disp_2D()                { b_disp_2D();   }
void disp_array()             { b_disp_array();  }

void disp_pre()               { b_disp_pre(T);  }
void disp_in()                { b_disp_in(T);   }
void disp_post()              { b_disp_post(T); }

void add(int v)               { T = b_add(T, create_node(v)); }
void rem(int v)               { T = b_rem(T, v); }

void addh(int v)              { T = b_addh(create_node(v)); }
void remh(int v)              { T = b_remh(v); }

int is_memberb(int v)         { return b_findb(T, v); }
int is_memberc(int v)         { return b_findc(T, v); }

int cardinality()             { return b_card(T); }
int bheight()                 { return b_height(T); }

void bheapify()               { T = b_heapify(T); }

/****************************************************************************/
/* end of basic functions                                                   */
/****************************************************************************/



