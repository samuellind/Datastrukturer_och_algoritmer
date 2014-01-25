
/**************************************************************/
/* DSA Example program - Donald F. Ross 120627                */
/**************************************************************/

/**************************************************************/
/* include files and  global data objects                     */
/**************************************************************/

#include <stdio.h>
#include <string.h>
#include "fegraph.h"

#define   NAMELEN  30
#define   MAXLNC   80        /* max number of input line chars*/
#define   MAXLN    MAXLNC+1  /* max size of input line buffer */

#define   DEBUG    0         /* DEBUG ON/OFF                  */

/**************************************************************/
/* define types                                               */
/**************************************************************/

/**************************************************************/
/* global data objects                                        */
/**************************************************************/

char       lnbuff[MAXLN];             /* input line buffer    */
int        echomode=0;                /* echo mode on/off     */
int        udirmode=1;                /* graph: dir / undir   */

/*****************************************************************************/
/*  get_input: get user input from keyboard (1 character)                   */
/*****************************************************************************/

static char get_input()  { scanf("%s", lnbuff); return(lnbuff[0]); }
static int  get_weight() { int w; scanf("%d", &w); return w; }

/****************************************************************************/
/* here - a debugging function                                              */
/****************************************************************************/

static void here(char * msg) { if (DEBUG) printf("\n *** In %s ", msg); }

/****************************************************************************/
/* UI functions                                                             */
/****************************************************************************/

static void udisplay()   { display(); }
static void udisplaym()  { displaym(); }

static void uaddnode()  { 

   char c;

   printf(" enter name: "); c = get_input(); if (echomode) printf(" %c", c);
   if (nfound(c)) printf("\n Node already exists! ");
   else addnode(c);
   }

static void uaddedge()  {
 
   char cs, cd; int w;

   printf(" enter node 1:   "); cs = get_input();  if (echomode) printf(" %c", cs);
   printf(" enter node 2:   "); cd = get_input();  if (echomode) printf(" %c", cd);
   printf(" enter a weight: "); w  = get_weight(); if (echomode) printf(" %d", w);

   if (efound(cs, cd)) printf("\n *** Edge already exists! ");
   else {addedge(cs, cd, w); if (udirmode && (cd != cs)) addedge(cd, cs, w); }
   }


static void uremnode()  {

   char c;

   printf(" enter name: "); c = get_input();   if (echomode) printf(" %c", c);
   remnode(c);
   }

static void uremedge()  {

   char cs, cd;

   printf(" enter node 1: "); cs = get_input(); if (echomode) printf(" %c", cs);
   printf(" enter node 2: "); cd = get_input(); if (echomode) printf(" %c", cd);
   if (efound(cs, cd)) remedge(cs, cd);
   else printf(" *** Edge does not exist! ");
   if (udirmode) 
      if (efound(cd, cs)) remedge(cd, cs);
   }

static void umembnode() { 
   
   char c;

   printf(" enter name: "); c = get_input(); if (echomode) printf(" %c", c);
   nmember(c);
   }

static void umembedge() {

   char cs, cd;

   printf(" enter node 1: "); cs = get_input(); if (echomode) printf(" %c", cs);
   printf(" enter node 2: "); cd = get_input(); if (echomode) printf(" %c", cd);
   emember(cs, cd);
   }

static void showmode()
{ 
   switch (udirmode) {
      case 0: printf(" directed graph mode ");    break;
      case 1: printf(" undirected graph mode ");  break;
      }
}

/*****************************************************************************/
/*  READ_ME: explain what this program does...                               */
/*****************************************************************************/

static void READ_ME()

{
   
   here( " IN  READ_ME() ");

   printf("\n");
   printf("***************************************************************\n");
   printf("***                                                         ***\n");
   printf("***   This program...                                       ***\n");
   printf("***   ... manipulates a sequence of elements                ***\n");
   printf("***                                                         ***\n");
   printf("***************************************************************\n");
   printf("\n");
   
   here( " OUT READ_ME() ");

   }

/*****************************************************************************/
/*  dispmenu: display the user menu                                          */
/*****************************************************************************/

static void dispmenu()

{
   here( " IN  dispmenu() ");
   
   printf("\n");
   printf("***************************************************************\n");
   printf("***                                                         ***\n");
   printf("***   h:   display this menu                                ***\n");
   printf("***   p:   display the READ_ME text (program documentation) ***\n");
   printf("***   u:   set the mode to undirected graph                 ***\n");
   printf("***   i:   set the mode to   directed graph                 ***\n");
   printf("***   k:   display the mode (directed / undirected)         ***\n");
   printf("***                                                         ***\n");
   printf("***   d:   display the graph                                ***\n");
   printf("***   m:   display the matrix                               ***\n");
   printf("***                                                         ***\n");
   printf("***   a:   add a  node to the graph                         ***\n");
   printf("***   b:   add an edge to the graph                         ***\n");
   printf("***   r:   remove a  node from the graph                    ***\n");
   printf("***   s:   remove an edge from the graph                    ***\n");
   printf("***                                                         ***\n");
   printf("***   n:   find a  node in the graph                        ***\n");
   printf("***   e:   find an edge in the graph                        ***\n");
   printf("***                                                         ***\n");
   printf("***   t:   Dijkstra + SPT                                   ***\n");
   printf("***   v:   Floyd                                            ***\n");
   printf("***   w:   Warshall                                         ***\n");
   printf("***   x:   Prim                                             ***\n");
   printf("***   y:   Kruskal                                          ***\n");
   printf("***                                                         ***\n");
   printf("***   q:   quit the program                                 ***\n");
   printf("***                                                         ***\n");
   printf("***************************************************************\n");
   printf("\n");

   here( " OUT dispmenu() ");
   }

/****************************************************************************/
/*  runmenu: execute the user menu                                          */
/****************************************************************************/

void runmenu()

{
   char   choice;                     /* user menu selection  */

   here( " IN  runmenu() ");
   dispmenu();
   do {
      printf("\n Enter choice => "); choice = get_input();
      if (echomode) printf(" %c \n", choice);
      switch(choice) {

         case 'h': case 'H': dispmenu();                        break;
         case 'p': case 'P': READ_ME();                         break;
         case 'z': case 'Z': echomode=1;                        break;
         case 'u': case 'U': udirmode=1;                        break;
         case 'i': case 'I': udirmode=0;                        break;
         case 'k': case 'K': showmode();                        break;

         case 'd': case 'D': udisplay();                        break;
         case 'm': case 'M': udisplaym();                       break;

         case 'a': case 'A': uaddnode();                        break;
         case 'b': case 'B': uaddedge();                        break;

         case 'r': case 'R': uremnode();                        break;
         case 's': case 'S': uremedge();                        break;

         case 'n': case 'N': umembnode();                       break;
         case 'e': case 'E': umembedge();                       break;
         
         case 't': case 'T': fDijkstra();                       break;
         case 'v': case 'V': fFloyd();                          break;
         case 'w': case 'W': fWarshall();                       break;
         case 'x': case 'X': fPrim();                           break;
         case 'y': case 'Y': fKruskal();                        break;

         case 'q': case 'Q': printf(" *** BYE BYE! ***");       break;

         default:  printf("\n INVALID MENU CHOICE ***\n");
                   dispmenu();                                  break;
         }
      } while (choice != 'Q' && choice != 'q');
      printf("\n");
      here( " OUT runmenu() ");
   }

/****************************************************************************/
/* end of menu functions                                                    */
/****************************************************************************/

