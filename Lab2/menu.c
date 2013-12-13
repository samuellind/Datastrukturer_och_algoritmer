
/**************************************************************/
/* DSA Example program - Donald F. Ross 120627                */
/**************************************************************/

/**************************************************************/
/* include files and  global data objects                     */
/**************************************************************/

#include <stdio.h>
#include <string.h>
#include "BEPerf.h"

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

char       lnbuff[MAXLN];          /* input line buffer       */
int        echomode=0;             /* echo mode on/off        */
int        dispmode=0;              /* sorted/pos&stack/queue  */

/*****************************************************************************/
/*  get_choice: get user input from keyboard (1 character)                   */
/*****************************************************************************/

static char get_choice() { scanf("%s", lnbuff); return(lnbuff[0]); }

/****************************************************************************/
/* here - a debugging function                                              */
/****************************************************************************/

static void here(char * msg) { if (DEBUG) printf("\n *** In %s ", msg); }

/****************************************************************************/
/* UI functions                                                             */
/****************************************************************************/

/*****************************************************************************/
/*  dispmenu: display the user menu                                          */
/*****************************************************************************/

static void dispmenu()

{
   here( " IN  dispmenu() ");
   
   printf("\n");
   printf("***************************************************************\n");
   printf("***   a:   create and fill array                            ***\n");
   if(init==1){
   printf("***   b:	 bubble sort   		                            ***\n");
   printf("***   c:   insertion sort                                   ***\n");
   printf("***   d:   quick sort	                                    ***\n");
   printf("***                                                         ***\n");
   printf("***   h:   display this menu                                ***\n");
   printf("***   p:   display the array						 ***\n");
   printf("***                                                         ***\n");
   printf("***   v:   sequence search mode is Linear                   ***\n");
   printf("***   w:   sequence search mode is Binear Search            ***\n");
   printf("***                                                         ***\n");
   printf("***                                                         ***\n");
}
   printf("***   o:    fill BST                                                  ***\n");
   printf("***   x:   Search in Binary Search Tree                     ***\n");
   printf("***                                                         ***\n");
   printf("***   0:   quit the program                                 ***\n");
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
   do {
		dispmenu();
      printf("\n Enter choice => "); choice = get_choice();
      if (echomode) printf(" %c \n", choice);
      switch(choice) {

         case 'h': case 'H': dispmenu();                        break;
         case 'p': case 'P': 
								if(dispmode==0) disp();  else prntBST();                       break;
		 case 'o' : case 'O': dispmode=1; printf("dispmode: %d ",dispmode); addBST();								break;

         case 'v': case 'V': LSrch();                         break;
		 case 'w': case 'W': BSrch();                         break;

         case 'a': case 'A': creArr();                          break;
		 case 'x': case 'X': BST();	                         break;
		 
		  case 'b': case 'B': bSort();                        	  break;
		  case 'c': case 'C': insSort();                         break;
		  case 'd': case 'D': qSort();                        	  break;

         case '0': printf(" *** BYE BYE! ***");       break;

         default:  printf("\n INVALID MENU CHOICE ***\n");
                   dispmenu();                                  break;
         }
      } while (choice != '0');
      printf("\n");
      here( " OUT runmenu() ");
   }

/****************************************************************************/
/* end of menu functions                                                    */
/****************************************************************************/

