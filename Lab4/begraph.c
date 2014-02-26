
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
#include <limits.h>

/**************************************************************/
/* define types & constants                                   */
/**************************************************************/

#define MAXNOD 20
#define NULLREF NULL
#define true 1
#define false 0
#define INF 999

/**************************************************************/
/* node element definition (this is hidden!)                  */
/**************************************************************/

typedef struct nodeelem * noderef;

typedef struct nodeelem {
        char       nname;
        int        ninfo;				//Edges use ninfo as cost and nodes as visisted=1/unvisited=0
        noderef    edges;
        noderef    nodes;
        } nodeelem;
		
/**************************************************************/
/* Dijkstra + SPT struct definition (this is hidden!) */
/**************************************************************/

typedef struct dStruct * dRef;

typedef struct dStruct dijStruct;

typedef struct dStruct {
        char       n;			//Nodes
	    int 		cost;		//Shortest path
        char          el;		//Edge
	    int 		eCost;	//Edge cost
		noderef dNode;
        } dStruct;


/**************************************************************/
/* define graph instance                                      */
/**************************************************************/

static noderef G     = (noderef) NULL;

static int adjmat[MAXNOD][MAXNOD];
static int Fm[MAXNOD][MAXNOD];
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
static int      get_visited(noderef N)            { return N->ninfo; }
static noderef  get_edges(noderef N)            { return N->edges;}
static noderef  get_nodes(noderef N)            { return N->nodes; }

static noderef  set_nname(noderef N, char c)    { N->nname = c; return N; }
static noderef  set_ninfo(noderef N, int v)     { N->ninfo = v; return N; }
static noderef  set_visited(noderef N, int v)    { N->ninfo = v; return N; }
static noderef  set_edges(noderef N, noderef E) { N->edges = E; return N; }
static noderef  set_nodes(noderef N, noderef M) { N->nodes = M; return N; }

static char get_n(struct dStruct N)	{ return N.n;	}			//Gets the Dijkstra struct  values
static int	get_cost(struct dStruct N)	{ return N.cost;	}
static char get_el(struct dStruct N)	{ return N.el;	}
static noderef get_dNode(struct dStruct N)	{return N.dNode;	}
static int get_eCost(struct dStruct N) { return N.eCost;		}

static struct dStruct set_n(struct dStruct N, char node)	{ N.n = node; return N;	}			//Updates the Dijkstra struct with provided parameter values
//static dRef set_n(dRef D, char node)	{ D->n = node; return D;	} 
static struct dStruct	set_cost(struct dStruct N, int c)	{ N.cost = c; return N;	}
static struct dStruct set_el(struct dStruct N, char e)	{ N.el = e; return N;	}
static struct dStruct set_eCost(struct dStruct N, int eC) { N.eCost = eC; return N;		}	

/****************************************************************************/
/* create and initialise an element in the node                             */
/****************************************************************************/

static noderef create_n(char c, int w) { 
	struct nodeelem *new=malloc(sizeof(struct nodeelem)); 
	set_nname(new, c);
	set_ninfo(new, w);
	//set_visited(new, 0);
	set_edges(new, NULLREF);
	set_nodes(new, NULLREF);
	//nhead(new);
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

static noderef nhead(noderef N)     { return N; }
static noderef ntail(noderef N)     { return get_nodes(N); }

static noderef ehead(noderef E)     {  return E; }
static noderef etail(noderef E)     {  return get_edges(E); }

/****************************************************************************/
/* CONStruct a new node with the element at the head of the node            */
/****************************************************************************/

static noderef ncons(noderef e, noderef N) { set_nodes(e,N); return e; }
static noderef econs(noderef e, noderef E) { set_edges(e,E); return e; }

/****************************************************************************/
/* User dialog function                                                     */
/****************************************************************************/

static int dialog() {
  
  int i;

  printf(" Enter a value:  ");
  getchar();
  scanf("  %d", &i);
  return i;
  
  }
/****************************************************************************/
/* display the edges                                                        */
/****************************************************************************/

static void b_edisp(noderef E) {
	if(is_empty(E))
		printf("EOF");
	else { 
		printf("-%c-",  get_nname(E));
		b_edisp(get_edges(E));
	} }

/****************************************************************************/
/* display the nodes                                                        */
/****************************************************************************/

static void b_ndisp(noderef G) { 
	
	if(is_empty(G))
		printf("EOF");
	else { 
		printf("-%c-", get_nname(G));
		b_edisp(get_edges(G));
		printf("\n");
		b_ndisp(get_nodes(G));
	}
}

/****************************************************************************/
/* ADD to the node in ascending order                                       */
/****************************************************************************/

static noderef b_addn(char c, noderef G) {  
	noderef N=create_n(c,0);
	
	if(is_empty(G))
		return N;
	else if(c<get_nname(G))
		return ncons(N, G);
	else 
		return ncons(G, b_addn(c, ntail(G)));	
	 }

/****************************************************************************/
/* ADD to the edge in ascending order                                       */
/****************************************************************************/

static noderef b_adde(char c, int w, noderef E) { 
	while(w==0){
		printf("Cost cannot be set to 0. Choose another cost.");
		w=dialog();//return b_adde(c,dialog(),E);
	}
	noderef N=create_n(c,w);
	if(is_empty(E))
		return N;
		
	else if(c<get_nname(E))
		return econs(E,N);
	else  
		return econs(E, b_adde(c, w, etail(E)));
}

/****************************************************************************/
/* REMove a  node from the graph                                            */
/****************************************************************************/

static noderef b_remn(char c, noderef G) { 
	if(is_empty(G)){ 
		return G;
	}
	if(get_nname(G)==c){
		return ntail(G);
	}
	else
		return ncons(G, b_remn(c, ntail(G)));
		}
/****************************************************************************/
/* REMove an edge from the graph                                            */
/****************************************************************************/

static noderef b_reme(char c, noderef E) { 
	if(is_empty(E)){
		return  E;
	}
	if(get_nname(E)==c){
		return etail(E);
	}
	else
		return econs(E, b_reme(c, etail(E)));
 }
/****************************************************************************/
/* FIND a  node in the graph                                                */
/****************************************************************************/

static noderef b_findn(char c, noderef G) { 
		
	if(is_empty(G) || c==get_nname(G))
		return G;
	else 
		return b_findn(c, ntail(G));
}

/****************************************************************************/
/* REMove all edges for a given node from the graph                         */
/****************************************************************************/

static void b_remalle(char c, noderef G) { 
	
	if(!is_empty(G)){
		
		econs(b_findn(c,G), NULLREF);
		
		noderef N=G;
		while(!is_empty(N)){
			b_reme(c,N);
			N=ntail(N);
			}
		}
	 }


/****************************************************************************/
/* FIND an edge in the graph                                                */
/****************************************************************************/

static noderef b_finde(char c, noderef E) { 
	if(is_empty(E) || c==get_nname(E))
		return E;
	else 
		return b_finde(c, etail(E));}

/****************************************************************************/
/* FIND the number of nodes in the graph (cardinality nodes)                */
/****************************************************************************/

static int b_card(noderef G) { 
	if(is_empty(G)) return 0 ;
	else 
		return 1+b_card(get_nodes(G));
}

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

static int get_pos(char fname)  { 
	
	int i=0;
	noderef f=G;
	
	while(get_nname(f)!=fname){
		i++;
		f=ntail(f);
	}
	return i;
 }
/****************************************************************************/
/* Clear the adj.list												        */
/* 							                                                */
/****************************************************************************/

static void clr_adjmat(){

int i,j;

for(i=0;i<b_card(G);i++)
	for(j=0;j<b_card(G);j++)
		adjmat[i][j]=0;
}

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

static void cre_adjmat(noderef G) {
	if(!is_empty(G)){
	noderef e;

	int i,j;
	
	e= get_edges(G);
	
	for(i=0;G!=(noderef)NULL;i++){
		fflush(stdout);
		for(j=0;e!=(noderef)NULL;j++){
			fflush(stdout);
			if(j==get_pos(get_nname(e))){
				fflush(stdout);
				adjmat[i][j]=get_ninfo(e);
				e=etail(e);
				j=0;
			}
			else if(i==j){
				fflush(stdout);
				adjmat[i][j]=0;
			}
		}
			
		G=ntail(G);
		if(!is_empty(G))
			e= get_edges(G);
		
	}
	
}
 }
/****************************************************************************/
/* DISPLAY top level of adjacency matrix                                    */
/****************************************************************************/

static void b_mtopdisp(){
	
	int i=0;
	noderef g=G;
	
	while(g!=(noderef)NULL){
		printf("	 %d",i);
		i++;
		g=ntail(g);
	}
	printf("\n");
	g=G;
	while(g!=(noderef)NULL){
		printf("	 %c",get_nname(g));
		g=ntail(g);
	}
	printf("\n----");
	
	for(i=0;i<=b_card(G);i++)
		printf("-------");
	printf("\n");
	
}

/****************************************************************************/
/* DISPLAY the adjacency matrix                                             */
/****************************************************************************/

static void b_mdisp(noderef G) { 
	
	int i=0,j=0,max=b_card(G);
	cre_adjmat(G);
	b_mtopdisp();
		
		for(i=0;!is_empty(G);i++){
		printf("%c |",get_nname(G));
		
			for(j=0;j!=max;j++){
				printf("	 %d",adjmat[i][j]);
			}
		printf("\n");
		G=ntail(G); 
		}
}

/****************************************************************************/
/* Function to select which node to start from when 			  */
/* running Dijkstra                                									  */
/****************************************************************************/

noderef node_sel()
{
	char c;
	printf("Select start node: \n");
	scanf(" %c", &c);
	
	if(c!='0'){
		noderef N=b_findn(c, G);
		if(!is_empty(N))
			return N;
		else{
			printf("Node not found. Try again.\n");
			return node_sel();
		}
	}
	else
		exit(1);
}

/****************************************************************************/
/* Calculates the cost from one node to another                    */
/****************************************************************************/
/*
int calc_cost(char c, noderef G){
	
	noderef E=b_finde(c,G);
	
	if(!is_empty(E))
		return get_ninfo(E);
	else return -1;
	
}*/

/****************************************************************************/
/* Initializes the Dijkstra struct with  all nodes and cost		  */
/* from the start node				   	                                             */
/****************************************************************************/

void fill_dijk(struct dStruct dijk[], noderef startNode, int size){

	int i;
	
	char sNodeName = get_nname(startNode);			//Hämtar NodeName för StatNoden man valt att utgå ifrån
	printf("Startnode: %c\n" , sNodeName);
	noderef currNode=G;
	
	for(i=0;i< size;i++){
			if(sNodeName==get_nname(currNode))
				currNode=get_nodes(currNode);
	
			dijk[i].n=get_nname(currNode);				//Fyller varje arrayposition med nästa Nod
			dijk[i].dNode=currNode;							//Lagrar en pekare till nodreferensen till S
			printf("dNode set to: %p		", dijk[i].dNode);
			dijk[i].el=sNodeName;			//Fyller varje el position med startnoden
				
			if(b_finde(sNodeName,currNode)){
				printf("Edge found, setting cost to: %d", get_ninfo(b_finde(get_nname(startNode),currNode)));
				int edgeCost=get_ninfo(b_finde(get_nname(startNode),currNode));
				dijk[i].cost=edgeCost;
				dijk[i].eCost=edgeCost;
				}
			else{
				dijk[i].cost=-1;
				dijk[i].eCost=-1;
			}
			
			printf("%c	%d	%c	%d\n", get_n(dijk[i]), dijk[i].cost, dijk[i].el, dijk[i].eCost);
			currNode = get_nodes(currNode);
		}
}
/****************************************************************************/
/* Find shortest edge					                                             */
/****************************************************************************/	

noderef sEdge(noderef N){
	int min=32600;
	noderef ret;
	while(!is_empty(get_edges(N))){
		if(get_ninfo(get_edges(N))<min){
			min = get_ninfo(get_edges(N));
			ret = get_edges(N);}
			}
			return ret;
		}
			
		
	

/****************************************************************************/
/* Fills S Set with nodes				                                             */
/****************************************************************************/		

void fill_s(noderef N){
	set_visited(N,1);
}
/*
int search_dijk(start?, char s){
	int i=0;
	while(dijk[i]!=EOF){
		if(dijk[i].n == s)
			return i
		else
			i++
			
	}
}*/



/****************************************************************************/
/* Choose min D[v] in V-S (Nodes with visited=0)                   */
/****************************************************************************/		

noderef next_unvisited(noderef G){	if(!get_visited(G))	return	 G;	else return next_unvisited(get_nodes(G));	}

/****************************************************************************/
/* Choose min D[v] in V-S (Nodes with visited=0)                   */
/****************************************************************************/		
void dij_while(dStruct dijk[], int size, noderef startNode){
	
	char sNodeName = get_nname(startNode);
	int lowest;
	
	noderef VS = next_unvisited(G);
	while(!is_empty(VS)){	
		
		noderef w = next_unvisited(G);							//
		
		while(!is_empty(w)){
			
			
			
			w = next_unvisited(w);
		}
		VS=next_unvisited(VS);
	}
}

/****************************************************************************/
/* GRAPH ALGORITHMS                                                         */
/****************************************************************************/

void b_Dijkstra() { 
	
	int size =(b_card(G)-1);
	
	noderef startNode=node_sel();			//Select node to start from

	if(size!=0){
		fill_s(startNode);
		struct dStruct dijk[size];
		struct dStruct S[size+1];
		printf("DijkStruct with %d positions created \n", size);
		fill_dijk(dijk, startNode, size);
		dij_while(dijk,size, startNode);
		
	}
	
	else
		printf("Create more nodes in order to run Dijkstra");

}

int b_Floyd(noderef G)    { 
	if(is_empty(G))					// is there a graph
		return 0;
	
		int max= b_card(G);
		int i,j,k;
		
		for(i=0;i<max;i++){				// enter all immidiate connections
			for(j=0;j<max;j++){
				if (adjmat[i][j]>0)
					Fm[i][j]=adjmat[i][j];
				else 
					Fm[i][j]= INF;
			}
		}
		for (k = 0; k < max; k++){
			for (i = 0; i < max; i++){
				for (j = 0; j < max; j++){
					if (Fm[i][k] + Fm[k][j] < Fm[i][j])
						Fm[i][j] = Fm[i][k] + Fm[k][j];
				}
			}
		}
			
		
		
		 return 1;}
int b_Warshall(noderef G) {
	if(is_empty(G))					// is there a graph
		return 0;
	
	int TC[MAXNOD][MAXNOD];
	int max = b_card(G);
	int i,j,k;
	
	for(i=0;i<max;i++){				// enter all immidiate connections
		for(j=0;j<max;j++){
			if (adjmat[i][j]>0)
				TC[i][j]=1;
			else 
				TC[i][j]= 0;
		}
	}
	
	for (k = 0; k < max; k++){			// find all connections through	
            for (i = 0; i < max; i++){	// neighbouring nodes
                for (j = 0; j < max; j++)
                    TC[i][j] = (TC[i][j] || (TC[i][k] && TC[k][j]));
            }
     }
	printf("\n");

	b_mtopdisp(G);						//print warshall matrix
	for(i=0;!is_empty(G);i++){
		printf("%c |",get_nname(G));
		
			for(j=0;j!=max;j++){
				printf("	 %i",TC[i][j]);
			}
		printf("\n");
		G=ntail(G); 
		}
	return 1;
	}
void b_Prim()     { /* TO DO */ }
void b_Kruskal()  { /* TO DO */ }

void b_dispSPT()  { /* TO DO */ }
void b_dispFm(noderef G)   { 
	int i,j;
	int max = b_card(G);
	b_mtopdisp(G);						//print warshall matrix
	for(i=0;!is_empty(G);i++){
		printf("%c |",get_nname(G));
		
			for(j=0;j!=max;j++){
				if(Fm[i][j] < INF)
				printf("	 %i",Fm[i][j]);
				else 
				printf("	INF");
			}
		printf("\n");
		G=ntail(G); 
		}}
void b_dispTC()   { /* TO DO */ }
void b_dispMST()  { /* TO DO */ }

/****************************************************************************/
/****************************************************************************/
/* public operations on the node                                            */
/****************************************************************************/
/****************************************************************************/

void gdisp()       { b_ndisp(G); }
void mdisp()       { if(!is_empty(G)) b_mdisp(G); }

void addn(char c)  { G = b_addn(c, G); }
void remn(char c)  { b_remalle(c, G); G = b_remn(c, G);clr_adjmat();}

void adde(char cs, char cd, int v) {
   set_edges(b_findn(cs, G), b_adde(cd, v, get_edges(b_findn(cs, G))));
   }

void reme(char cs, char cd) {
   set_edges(b_findn(cs, G), b_reme(cd, get_edges(b_findn(cs, G))));clr_adjmat();;
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
void bFloyd()     { cre_adjmat(G); b_Floyd(G);    b_dispFm(G);  }
void bWarshall()  { cre_adjmat(G); b_Warshall(G); b_dispTC();  }
void bPrim()      { b_Prim();     b_dispMST(); }
void bKruskal()   { b_Kruskal();  b_dispMST(); }

/****************************************************************************/
/* end of basic functions                                                   */
/****************************************************************************/



