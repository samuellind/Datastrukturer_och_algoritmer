
/**************************************************************/
/* DSA Example program - Donald F. Ross 121013               */
/**************************************************************/

/**************************************************************/
/* include files and  global data objects                     */
/**************************************************************/

#include <stdio.h>
#include <string.h>
#include "fetree.h"

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
int        echomode=1;                /* echo mode on/off     */
int        treemode=0;                /* BST (default)        */

/*****************************************************************************/
/*  get_choice: get user input from keyboard (1 character)                   */
/*****************************************************************************/

static char get_choice() { scanf("%s", lnbuff); return(lnbuff[0]); }

/****************************************************************************/
/* here - a debugging function                                              */
/****************************************************************************/

static void here(char * msg) { if (DEBUG) printf("\n *** In %s ", msg); }

/****************************************************************************/
/* User dialog function                                                     */
/****************************************************************************/

static int dialog() {
  
  int i;

  printf(" Enter a value:  ");
  scanf("%d", &i);
  if (echomode) printf(" %d", i);
  return i;
  
  }

/****************************************************************************/
/* UI functions                                                             */
/****************************************************************************/

static void uadd()
{
   switch (treemode) {
      case 0: addval(dialog());               break;
      case 1: addhval(dialog());              break;
      }
}

static void uremove()
{ 
   switch (treemode) {
      case 0: remval(dialog());               break;
      case 1: remhval(dialog());              break;
      }
}

static void ufind()
{
   switch (treemode) {
      case 0: memberb(dialog("number"));      break;
      case 1: memberc(dialog("number"));      break;
      }
}

static void showmode()
{ 
   switch (treemode) {
      case 0: printf(" BST  mode ");          break;
      case 1: printf(" Complete Tree mode "); break;
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
   printf("***   m:   display this menu                                ***\n");
   printf("***   k:   display current mode (BST/Complete Tree)         ***\n");
   printf("***   p:   display the READ_ME text (program documentation) ***\n");
   printf("***                                                         ***\n");
   printf("***   w:   tree is a BST                                    ***\n");
   printf("***   x:   tree is a Complete Tree (CT)                     ***\n");
   printf("***                                                         ***\n");
   printf("***   y:   display the tree array                           ***\n");
   printf("***   d:   display the tree (in/pre/post)                   ***\n");
   printf("***   e:   display the tree (pre_order)                     ***\n");
   printf("***   i:   display the tree (in_order)                      ***\n");
   printf("***   o:   display the tree (post_order)                    ***\n");
   printf("***   t:   display the tree (2D)                            ***\n");
   printf("***                                                         ***\n");
   printf("***   a:   add a value to the tree                          ***\n");
   printf("***   r:   remove a value from the tree                     ***\n");
   printf("***   f:   find a value in the tree                         ***\n");
   printf("***   h:   find the height of the tree                      ***\n");
   printf("***   g:   heapify the tree (must be a Complete Tree)       ***\n");
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
      printf("\n Enter choice => "); choice = get_choice();
      if (echomode) printf(" %c \n", choice);
      switch(choice) {

         case 'm': case 'M': dispmenu();                        break;
         case 'k': case 'K': showmode();                        break;
         case 'p': case 'P': READ_ME();                         break;
         case 'w': case 'W': treemode=0;                        break;
         case 'x': case 'X': treemode=1;                        break;
         case 'z': case 'Z': echomode=1;                        break;

         case 'y': case 'Y': darray();                          break;
         case 'd': case 'D': display();                         break;
         case 'e': case 'E': displaypre();                      break;
         case 'i': case 'I': displayin();                       break;
         case 'o': case 'O': displaypost();                     break;
         case 't': case 'T': display2D();                       break;

         case 'a': case 'A': uadd();                            break;
         case 'r': case 'R': uremove();                         break;
         case 'f': case 'F': ufind();                           break;
         case 'h': case 'H': height();                          break;
         case 'g': case 'G': heapify();                         break;


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

