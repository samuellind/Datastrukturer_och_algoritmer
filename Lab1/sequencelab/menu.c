
/**************************************************************/
/* DSA Example program - Donald F. Ross 120627                */
/**************************************************************/

/**************************************************************/
/* include files and  global data objects                     */
/**************************************************************/

#include <stdio.h>
#include <string.h>
#include "FESeq.h"

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

static int dialogp(int upper) {
  
  int i;

     printf("\n Enter a position (1..%d): ", size()+upper);
     scanf("%d", &i);
     if (echomode) printf(" %d", i);
     return i;
  }

/****************************************************************************/
/* UI functions                                                             */
/****************************************************************************/

static void uaddsort() { addval(dialogv()); }

static void uremsort() { 
   if (size() == 0) printf("\n Error: empty sequence");
   else remval(dialogv()); 
   }

static void uaddpos()  { addvalpos(dialogv(), dialogp(1)); }

static void urempos()  { 
   if (size() == 0) printf("\n Error: empty sequence");
   else remvalpos(dialogp(0)); 
   }

static void upush()    { addvalpos(dialogv(), 1); }

static void upop()     { 
   if (size() == 0) printf("\n Error: empty stack");
   else remvalpos(1);
   }

static void uenqueue() { addvalpos(dialogv(), size()+1); }

static void udequeue() { 
   if (size() == 0) printf("\n Error: empty queue");
   else remvalpos(1);
   }

static void udisplay() { display(); }

static void uadd()
{
   switch (seqmode) {
      case 0: uaddsort();   break;
      case 1: uaddpos();    break;
      case 2: upush();      break;
      case 3: uenqueue();   break;
      }
}

static void uremove()
{
   switch (seqmode) {
      case 0: uremsort();   break;
      case 1: urempos();    break;
      case 2: upop();       break;
      case 3: udequeue();   break;
      }
}

static void ufind()    { member(dialogv()); }

static void showmode()
{ 
   switch (seqmode) {
      case 0: printf(" SORTED mode ");        break;
      case 1: printf(" POSITION mode ");      break;
      case 2: printf(" STACK mode ");         break;
      case 3: printf(" QUEUE mode ");         break;
      }
}

static void ufirst()    { f_first(); }
static void unext()     { f_next(); }

static void uexist_e()  { 
   if (f_exist_e()) printf(" element exists");
   else printf(" element does not exist");
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
   printf("***   m:   display current mode (sorted/pos/stack/queue)    ***\n");
   printf("***   p:   display the READ_ME text (program documentation) ***\n");
   printf("***                                                         ***\n");
   printf("***   v:   sequence is sorted                               ***\n");
   printf("***   w:   sequence is by position                          ***\n");
   printf("***   x:   sequence is a stack                              ***\n");
   printf("***   y:   sequence is a queue                              ***\n");
   printf("***                                                         ***\n");
   if (seqmode==0 || seqmode==1) {
   printf("***   d:   display the sequence                             ***\n");
   printf("***   a:   add a value to the sequence                      ***\n");
   printf("***   f:   find a value in the sequence                     ***\n");
   printf("***   r:   remove a value from the sequence                 ***\n");
   }
   else if (seqmode==2) {
   printf("***   d:   display the stack                                ***\n");
   printf("***   a:   add a value to the stack (push)                  ***\n");
   printf("***   f:   find a value in the stack                        ***\n");
   printf("***   r:   remove a value from the stack (pop)              ***\n");
   }
   else {
   printf("***   d:   display the queue                                ***\n");
   printf("***   a:   add a value to the queue (enqueue)               ***\n");
   printf("***   f:   find a value in the queue                        ***\n");
   printf("***   r:   remove a value from the queue (dequeue)          ***\n");
   }
   if (seqmode==0 || seqmode==1) {
   printf("***                                                         ***\n");
   printf("***   i:   display the first element in the sequence        ***\n");
   printf("***   n:   display the next  element in the sequence        ***\n");
   printf("***   e:   is there a valid  element in the sequence?       ***\n");
   }
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

         case 'h': case 'H': dispmenu();                        break;
         case 'm': case 'M': showmode();                        break;
         case 'p': case 'P': READ_ME();                         break;

         case 'v': case 'V': seqmode=0;                         break;
         case 'w': case 'W': seqmode=1;                         break;
         case 'x': case 'X': seqmode=2;                         break;
         case 'y': case 'Y': seqmode=3;                         break;
         case 'z': case 'Z': echomode=1;                        break;

         case 'd': case 'D': udisplay();                        break;
         case 'a': case 'A': uadd();                            break;
         case 'f': case 'F': ufind();                           break;
         case 'r': case 'R': uremove();                         break;

         case 'i': case 'I': ufirst();                          break;
         case 'n': case 'N': unext();                           break;
         case 'e': case 'E': uexist_e();                        break;

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

