
/**************************************************************/
/* DSA list program example                                   */
/**************************************************************/
/* A.K Krupalija & Samuel Lind 091213                         */
/**************************************************************/

/**************************************************************/
/* include files and  global data objects                     */
/**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/****************************************************************************/
/* define types & constants                                                 */
/****************************************************************************/

#define   NULLREF      -1               /* null reference for list          */
#define	  EMPTY		   -2
#define   MAXLNC   80        /* max number of input line chars*/
#define   MAXLN    MAXLNC+1  /* max size of input line buffer */

/****************************************************************************/
/*  Define list structure                                                   */
/****************************************************************************/

char    lnbuff[MAXLN];          /* input line buffer       */
int		LSIZE=0;
int     array[16400];             	   /* array for storing int              */
int 	mid;
int 	sorted=0;

/*****************************************************************************/
/*  get_choice: get user input from keyboard (1 character)                   */
/*****************************************************************************/

static char get_choice() { scanf("%s", lnbuff); return(lnbuff[0]); }
/****************************************************************************/
/****************************************************************************/
/* private operations on the list - primitive operationa                    */
/****************************************************************************/
/****************************************************************************/

static int      is_empty()             { return LSIZE==0; }		//Tom lista ger return=1
static int 		is_sorted(){return sorted;}

static int set_sorted()	{sorted=1;}

static void set_LSIZE(int v)	{LSIZE = v;}
void setLSize(){
	 
	 int choice;

	  printf("Set array size.\n");
	  printf("1. 1024\t2. 2048.\t3. 4096\t3. 8192\t4. 16384\n");
	  printf("\n Enter choice => "); choice = get_choice();
      switch(choice) {

         case '1': set_LSIZE(1024);                        break;
		 case '2': set_LSIZE(2048);                        break;
		 case '3': set_LSIZE(4096);                        break;
		 case '4': set_LSIZE(8192);                        break;
		 case '5': set_LSIZE(16384);                       break;

         default:  printf("\n INVALID MENU CHOICE ***\n");
					setLSize();
					break;
					//choice=NULL;
                   //setLSize();                     break;
         }
}

void fillRand(){

	int i;
	srand(time(NULL)); // randomize seedsrand()
	for(i=0;i<LSIZE;i++){
		array[i]=rand()%LSIZE+1;
	}
	printf("Random sequence generated\n");
}

void fillAsc(){
	int i,x=1;
	set_sorted();
	for(i=0;i<=LSIZE;i++){
		array[i]=x++;
	}
	printf("Ascending sequence generated\n");
}

void fillDsc(){
	int i,x=LSIZE+1;
	
	for(i=0;i<=LSIZE;i++){
		array[i]=x--;
	}
	printf("Descending sequence generated\n");
}


void fillArray(){
		
	int choice;
	
	  printf("Fill array.\n");
	  printf("1. Random\t2. Ascending.\t3. Descending\n");
      printf("\n Enter choice => "); 
	  scanf("%d",&choice);
      switch(choice) {

         case 1: fillRand();	                      break;
		 case 2: fillAsc();                         break;
		 case 3: fillDsc();                        break;

         default:  printf("\n INVALID MENU CHOICE ***\n");
                   fillArray();                                  break;
         }
}

void creArr(){
	setLSize();
	array[LSIZE];
	printf("Array created with %d positions \n", LSIZE);
	fillArray();
	
	
}

int linSrch(int v){
	
	int i;
	
	for(i=0;i<LSIZE&&array[i]!=v;i++){
	}
	return i;
	}      
	
void LSrch(){
	int v,pos;
	printf("Enter value to find: ");
	scanf("%d", &v);
	pos= linSrch(v);
	if(pos==LSIZE) // även om v är på sista positionen
		printf("value not found");
	else
		printf("Value found");
}      

int binSrch(int array[], int v, int low, int high){
	if(high<low)
		return -1;
	mid=(low+high)/2;
	if(array[mid]>v)
		return binSrch(array,v,low,mid-1);
	else if(array[mid]<v)
		return binSrch(array,v,mid+1,high);
	else
		return mid;
	
	}  
void BSrch(){
	
	int v, pos;
	
	if(is_sorted()==1)
		
		//SORTED??
		printf("vad söks?");
		scanf("%d", &v);
		pos=binSrch(&array[LSIZE], v, 0, LSIZE-1);
		if(pos==-1)
			printf("Value not found");
	   

	else
		printf("Sequence is not sorted");

}
                          
void BST(){	} 
                        
void bSort(){
	
	int i,j;
	
	for(i=0;i<LSIZE;i++)
		for(j=0;j<LSIZE;j++)
			if(array[j]>array[j+1])
				int temp=array[j];
				array[j+1]=array[j];
				array[i]=temp;
	
	}                        	  
void insSort(){}                         
void qSort(){}                        	  

void disp()                   { /*b_disp();*/ }

/****************************************************************************/
/* end of basic functions                                                   */
/****************************************************************************/


