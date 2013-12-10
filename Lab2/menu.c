
/**************************************************************/
/* DSA Example program - Donald F. Ross 120627                */
/**************************************************************/

/**************************************************************/
/* include files and  global data objects                     */
/**************************************************************/

#include <stdio.h>
#include <string.h>

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

int       lnbuff[MAXLN];          /* input line buffer       */
int        echomode=0;             /* echo mode on/off        */
int        seqmode=0;              /* sorted/pos&stack/queue  */

/*****************************************************************************/
/*  get_choice: get user input from keyboard (1 character)                   */
/*****************************************************************************/

static char get_choice() { scanf("%s", lnbuff); return(lnbuff[0]); }

/****************************************************************************/
/* here - a debugging function                                              */
/****************************************************************************/

static void here(char * msg) { if (DEBUG) printf("\n *** In %s ", msg); }

/****************************************************************************/
/* User dialog functions                                                    */
/****************************************************************************/

static int dialogv() {
  
  int i;

  printf(" Enter a value: ");
  scanf("%d", &i);
  if (echomode) printf(" %d", i);
  return i;
  
  }

/****************************************************************************/
/* UI functions                                                             */
/****************************************************************************/

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
   printf("***   ... measures different sorting and searching          ***\n");
   printf("***   algorithms.                                           ***\n");
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
   printf("***   a:   create and fill array                            ***\n");
   printf("***   b:	 bubble sort   		                            ***\n");
   printf("***   c:   insertion sort                                   ***\n");
   printf("***   d:   quick sort	                                    ***\n");
   printf("***                                                         ***\n");
   printf("***   h:   display this menu                                ***\n");
   printf("***   p:   display the READ_ME text (program documentation) ***\n");
   printf("***                                                         ***\n");
   printf("***   v:   sequence search mode is Linear                   ***\n");
   printf("***   w:   sequence search mode is Binear Search            ***\n");
   printf("***   x:   Search in Binary Search Tree                     ***\n");
   printf("***                                                         ***\n");
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
         case 'p': case 'P': READ_ME();                         break;

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

