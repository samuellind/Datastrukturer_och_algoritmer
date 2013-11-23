
/**************************************************************/
/* DSA node program example                                   */
/**************************************************************/
/* D.F. ROSS 120627 test version                              */
/**************************************************************/

/**************************************************************/
/* include files and  global data objects                     */
/**************************************************************/

#include <stdio.h>
#include <stdlib.h>

/**************************************************************/
/* define types & constants                                   */
/**************************************************************/

#define MAXNOD 20
#define NULLREF NULL

/**************************************************************/
/* node element definition (this is hidden!)                  */
/**************************************************************/

typedef struct nodeelem * noderef;

typedef struct nodeelem {
        char       nname;
        int        ninfo;
        noderef    edges;
        noderef    nodes;
        } nodeelem;

/**************************************************************/
/* define graph instance                                      */
/**************************************************************/

static noderef G     = (noderef) NULL;

static int adjmat[MAXNOD][MAXNOD];
static int nnodes;

/****************************************************************************/
/****************************************************************************/
/* private operations on the node - primitive operationa                    */
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/* primitive functions                                                      */
/****************************************************************************/
/* is_empty:        noderef           --> Boolean                           */
/*                                                                          */
/* get_nname:       noderef           --> char                              */
/* get_ninfo:       noderef           --> int                               */
/* get_edges:       noderef           --> noderef                           */
/* get_nodes:       noderef           --> noderef                           */
/*                                                                          */
/* set_nname:       char    x noderef --> noderef                           */
/* set_ninfo:       int     x noderef --> noderef                           */
/* set_edges:       noderef x noderef --> noderef                           */
/* set_nodes:       noderef x noderef --> noderef                           */
/*                                                                          */
/* create_n:        char x int        --> noderef                           */
/****************************************************************************/

static int      is_empty(noderef N)             {  return N==NULLREF;}

static char     get_nname(noderef N)            { return N->nname; }
static int      get_ninfo(noderef N)            { return N->ninfo; }
static noderef  get_edges(noderef N)            { return N->edges;}
static noderef  get_nodes(noderef N)            { return N->nodes; }

static noderef  set_nname(noderef N, char c)    { N->nname = c; return N; }
static noderef  set_ninfo(noderef N, int v)     { N->ninfo = v; return N; }
static noderef  set_edges(noderef N, noderef E) { N->edges = E; return N; }
static noderef  set_nodes(noderef N, noderef M) { N->nodes = M; return N; }

/****************************************************************************/
/* create and initialise an element in the node                             */
/****************************************************************************/

static noderef create_n(char c, int w) { 
	struct nodeelem *new=malloc(sizeof(struct nodeelem)); 
	set_nname(new, c);
	set_ninfo(new, w);
	set_edges(new, NULLREF);
	set_nodes(new, NULLREF);
	nnodes++;
	return new; }

/****************************************************************************/
/****************************************************************************/
/* private operations on the graph - basic operations                       */
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/* basic functions                                                          */
/****************************************************************************/
/* nhead:     noderef                --> noderef                            */
/* ntail:     noderef                --> noderef                            */
/* ehead:     noderef                --> noderef                            */
/* etail:     noderef                --> noderef                            */
/* ncons:     noderef x noderef      --> noderef                            */
/* econs:     noderef x noderef      --> noderef                            */
/* b_nadd:    int x noderef          --> noderef                            */
/* b_eadd:    int x noderef          --> noderef                            */
/* b_nrem:    int x noderef          --> noderef                            */
/* b_erem:    int x noderef          --> noderef                            */
/* b_nfind:   int x noderef          --> noderef                            */
/* b_efind:   int x noderef          --> noderef                            */
/****************************************************************************/

/****************************************************************************/
/* head and tail - a RECURSIVE view of the sequence                         */
/****************************************************************************/

static noderef nhead(noderef N)     { /* TO DO */ return NULLREF; }
static noderef ntail(noderef N)     { /* TO DO */ return NULLREF; }

static noderef ehead(noderef E)     { /* TO DO */ return NULLREF; }
static noderef etail(noderef E)     { /* TO DO */ return NULLREF; }

/****************************************************************************/
/* CONStruct a new node with the element at the head of the node            */
/****************************************************************************/

static noderef ncons(noderef e, noderef N) { set_nodes(N,e); return N; }
static noderef econs(noderef e, noderef E) { set_edges(E,e); return E; }

/****************************************************************************/
/* display the edges                                                        */
/****************************************************************************/

static void b_edisp(noderef E) { /* TO DO */ }

/****************************************************************************/
/* display the nodes                                                        */
/****************************************************************************/

static void b_ndisp(noderef G) { /* TO DO */ }

/****************************************************************************/
/* ADD to the node in ascending order                                       */
/****************************************************************************/

static noderef b_addn(char c, noderef G) {  /* TO DO */ return NULLREF; }

/****************************************************************************/
/* ADD to the edge in ascending order                                       */
/****************************************************************************/

static noderef b_adde(char c, int w, noderef E) { /* TO DO */ return NULLREF; }

/****************************************************************************/
/* REMove a  node from the graph                                            */
/****************************************************************************/

static noderef b_remn(char c, noderef G) { /* TO DO */ return NULLREF; }

/****************************************************************************/
/* REMove an edge from the graph                                            */
/****************************************************************************/

static noderef b_reme(char c, noderef E) { /* TO DO */ return NULLREF; }

/****************************************************************************/
/* REMove all edges for a given node from the graph                         */
/****************************************************************************/

static void b_remalle(char c, noderef G) { /* TO DO */ }

/****************************************************************************/
/* FIND a  node in the graph                                                */
/****************************************************************************/

static noderef b_findn(char c, noderef G) { /* TO DO */ return NULLREF; }

/****************************************************************************/
/* FIND an edge in the graph                                                */
/****************************************************************************/

static noderef b_finde(char c, noderef E) { /* TO DO */ return NULLREF; }

/****************************************************************************/
/* FIND the number of nodes in the graph (cardinality nodes)                */
/****************************************************************************/

static int b_card(noderef G) { return nnodes; }

/****************************************************************************/
/* CREATE the adjacency matrix (AM)                                         */
/****************************************************************************/

/****************************************************************************/
/* Find the position (index) of a node in the adjacency list (node list)    */
/* NB: this is used to determine the index for the edge                     */
/*     this index is in turn used to fill in the weight in the AM           */
/* e.g. for an adjacency list:                                              */
/*               (position 0)   a => b(3) -> c(2) eol                       */
/*               (position 1)   b => a(3) -> c(7) eol                       */
/*               (position 2)   c => a(2) -> b(7) eol                       */
/*                              eol                                         */
/* get_pos("b") will give 1 (and hence AM[0][1] is set to 3 i.e. a-3-b)     */
/****************************************************************************/

static int get_pos(char fname)  { /* TO DO */ return 0; }

/****************************************************************************/
/* Fill in the values in the adjancy matrix from the adjacency list         */
/* e.g. for an adjacency list:                                              */
/*               (position 0)   a => b(3) -> c(2) eol                       */
/*               (position 1)   b => a(3) -> c(7) eol                       */
/*               (position 2)   c => a(2) -> b(7) eol                       */
/*                              eol                                         */
/*                                         0       1       2      (index)   */
/* this will give an adjacency matrix:     a       b       c                */
/*                                    -------------------------             */
/*                      (index 0)     a |  0       3       2                */
/*                      (index 1)     b |  3       0       7                */
/*                      (index 2)     c |  2       7       0                */
/****************************************************************************/

static void cre_adjmat(noderef G) {/* TO DO */ }

/****************************************************************************/
/* DISPLAY the adjacency matrix                                             */
/****************************************************************************/

static void b_mdisp(noderef G) {/* TO DO */ }

/****************************************************************************/
/* GRAPH ALGORITHMS                                                         */
/****************************************************************************/

void b_Dijkstra() { /* TO DO */ }
void b_Floyd()    { /* TO DO */ }
void b_Warshall() { /* TO DO */ }
void b_Prim()     { /* TO DO */ }
void b_Kruskal()  { /* TO DO */ }

void b_dispSPT()  { /* TO DO */ }
void b_dispFm()   { /* TO DO */ }
void b_dispTC()   { /* TO DO */ }
void b_dispMST()  { /* TO DO */ }

/****************************************************************************/
/****************************************************************************/
/* public operations on the node                                            */
/****************************************************************************/
/****************************************************************************/

void gdisp()       { b_ndisp(G); }
void mdisp()       { b_mdisp(G); }

void addn(char c)  { G = b_addn(c, G); }
void remn(char c)  { G = b_remn(c, G); b_remalle(c, G); }

void adde(char cs, char cd, int v) {
   set_edges(b_findn(cs, G), b_adde(cd, v, get_edges(b_findn(cs, G))));
   }

void reme(char cs, char cd) {
   set_edges(b_findn(cs, G), b_reme(cd, get_edges(b_findn(cs, G))));
   }

int is_nmember(char c) { return !is_empty(b_findn(c, G)); }

int is_emember(char cs, char cd) {
   return is_nmember(cs) &&
          !is_empty(b_finde(cd, get_edges(b_findn(cs, G))));
   }

int cardinality() { return b_card(G); }

/****************************************************************************/
/* GRAPH ALGORITHMS                                                         */
/****************************************************************************/

void bDijkstra()  { b_Dijkstra(); b_dispSPT(); }
void bFloyd()     { b_Floyd();    b_dispFm();  }
void bWarshall()  { b_Warshall(); b_dispTC();  }
void bPrim()      { b_Prim();     b_dispMST(); }
void bKruskal()   { b_Kruskal();  b_dispMST(); }

/****************************************************************************/
/* end of basic functions                                                   */
/****************************************************************************/



