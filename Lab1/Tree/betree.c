
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
#define NILL   -1

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
static int qfirst=NILL, qlast=NILL;

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

static int      is_empty(treeref T)             { /* TO DO */ return 1; }

static int      get_value(treeref T)            { /* TO DO */ return 0; }
static int      get_height(treeref T)           { /* TO DO */ return 0; }
static treeref  get_LC(treeref T)               { /* TO DO */ return NULL; }
static treeref  get_RC(treeref T)               { /* TO DO */ return NULL; }

static treeref  set_value(treeref T, int v)     { /* TO DO */ return NULL; }
static treeref  set_height(treeref T, int h)    { /* TO DO */ return NULL; }
static treeref  set_LC(treeref T, treeref L)    { /* TO DO */ return NULL; }
static treeref  set_RC(treeref T, treeref R)    { /* TO DO */ return NULL; }

/****************************************************************************/
/* create and initialise an element in the tree                             */
/****************************************************************************/

static treeref create_node(int v) { /* TO DO */ return NULL; }

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

static treeref cons(treeref LC, treeref N, treeref RC) {/* TO DO */ return NULL; }

/****************************************************************************/
/* FIND the height of the tree                                              */
/****************************************************************************/

static int max(int a, int b) { /* TO DO */ return 0; }

static int b_height(treeref T) { return 0; /* TO DO */ return 0; }

/****************************************************************************/
/* display the tree ELEMENT                                                 */
/****************************************************************************/

static void b_disp_el(treeref T) { /* TO DO */ }

/****************************************************************************/
/* display the heap array                                                   */
/****************************************************************************/

static void b_disp_array() { /* TO DO */ }

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

static void T2Q() { /* TO DO */ }

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

static void b_disp_2D() { /* TO DO */ }

/****************************************************************************/
/* display the tree (pre-order)                                             */
/****************************************************************************/

static void b_disp_pre(treeref T) { /* TO DO */ }

/****************************************************************************/
/* display the tree (in-order)                                              */
/****************************************************************************/

static void b_disp_in(treeref T) { /* TO DO */ }
/****************************************************************************/
/* display the tree (post-order)                                            */
/****************************************************************************/

static void b_disp_post(treeref T) { /* TO DO */ }

/****************************************************************************/
/* ADD to the tree in BST order                                             */
/****************************************************************************/

static treeref b_add(treeref T, treeref N) { /* TO DO */ return NULL; }

/****************************************************************************/
/* REMove an element from the tree / BST order                              */
/****************************************************************************/

static treeref b_rem(treeref T, int v) { /* TO DO */ return NULL; }

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

static int b_findb(treeref T, int v) { /* TO DO */ return 0; }

/****************************************************************************/
/* FIND an element in the complete tree                                     */
/****************************************************************************/

static int b_findc(treeref T, int v) { /* TO DO */ return 0; }

/****************************************************************************/
/* FIND the number of element in the tree (cardinality)                     */
/****************************************************************************/

static int b_card(treeref T) { return 0; /* TO DO */ return 0; }


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



