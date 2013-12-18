
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
#include "betree.h"


/****************************************************************************/
/* define types & constants                                                 */
/****************************************************************************/

#define   NULLREF      -1               /* null reference for list          */
#define   EMPTY		   -2
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
int init=0;
clock_t t1,t2;							//Stores time for the different algorithms

/*****************************************************************************/
/*  get_choice: get user input from keyboard (1 character)                   */
/*****************************************************************************/

static char get_choice() { scanf("%s", lnbuff); return(lnbuff[0]); }
/****************************************************************************/
/****************************************************************************/
/* private operations on the list - primitive operationa                    */
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/* set sorted to value 1 in order to be able to run binary search */
/****************************************************************************/
static int set_sorted(int v)	{return sorted=v;}


/****************************************************************************/
/* Updates the LSIZE value prior to creating an array 			  */
/* using this variable 																  */
/****************************************************************************/

static void set_LSIZE(int v)	{LSIZE = v; init=1;}


/****************************************************************************/
/* switch function to modify the LSIZE value                          */
/****************************************************************************/

void setLSize(){
	 
	 int choice;

	  printf("Set array size.\n");
	  printf("1. 1024\t2. 2048.\t3. 4096\t4. 8192\t5. 16384\n");
	  printf("\n Enter choice => "); choice = get_choice();
      switch(choice) {

         case '1': set_LSIZE(1024);                        break;
		 case '2': set_LSIZE(2048);                        break;
		 case '3': set_LSIZE(4096);                        break;
		 case '4': set_LSIZE(8192);                        break;
		 case '5': set_LSIZE(16384);                      break;
		 case '0': set_LSIZE(1);								break;

         default:  printf("\n INVALID MENU CHOICE ***\n");
					setLSize();
					break;
					//choice=NULL;
                   //setLSize();                     break;
         }
}

/****************************************************************************/
/* fills array[LSIZE] with random integers                                */
/****************************************************************************/
void fillRand(){

	set_sorted(0);
	int i;
	srand(time(NULL)); // randomize seedsrand()
	for(i=0;i<LSIZE;i++){
		array[i]=rand()%LSIZE+1;
	}
	printf("Random sequence generated\n");
}

/****************************************************************************/
/* fills array[LSIZE] with integer values starting from 0...LSIZE*/
/* Ascending fill																		   */
/****************************************************************************/
void fillAsc(){
	int i,x=1;
	set_sorted(1);
	printf("sorted: %d\n",sorted);
	for(i=0;i<=LSIZE;i++){
		array[i]=x++;
	}
	printf("Ascending sequence generated\n");
}
/****************************************************************************/
/* fills array[LSIZE] with integer values starting from LSIZE...0*/
/*	Descending fill																	   */
/****************************************************************************/
void fillDsc(){
	int i,x=LSIZE+1;
	
	for(i=0;i<=LSIZE;i++){
		array[i]=x--;
	}
	printf("Descending sequence generated\n");
}

/****************************************************************************/
/* Switch function in order to choose with what values the    */
/* Array should be populated													  */
/****************************************************************************/

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

/****************************************************************************/
/* creates an Array with LSIZE positions and goes on to        */
/* fillArray() function in order to fill the array with values		  */
/****************************************************************************/

void creArr(){
	setLSize();
	array[LSIZE];
	printf("Array created with %d positions \n", LSIZE);
	fillArray();
	
	
}

/****************************************************************************/
/* Linear search function for array											  */
/****************************************************************************/

int linSrch(int v){
	
	int i;
	
	for(i=0;i<LSIZE&&array[i]!=v;i++){
	}
		return i;
	}      

/****************************************************************************/
/* fills array[LSIZE] with integer values starting from 0...LSIZE*/
/****************************************************************************/
	
void LSrch(){
	int v,pos;
	printf("Enter value to find: ");
	scanf("%d", &v);
	
	t1=clock();
	pos= linSrch(v);
	if(pos==LSIZE) // även om v är på sista positionen
		printf("value %d not found ",v);
	else
		printf("Value %d found ",v);
	t2=clock();
	float seconds = (float)(t2 - t1);
	printf("Time taken: %f", seconds);
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
	
	if(sorted==1){
		
		//SORTED??
		printf("vad söks?");
		scanf("%d", &v);
		t1=clock();
		pos=binSrch(array, v, 0, LSIZE-1);
		if(pos==-1)
			printf("Value %d not found ",v);
		else
			printf("Value %d found! ",v);
		t2=clock();
		float seconds = (float)(t2 - t1);
		printf("Time taken: %f", seconds);
	} 

	else
		printf("Sequence is not sorted");

}

void bstBest(){
	int i;
	for(i=0;i<LSIZE;i++)
		add(i);
}

void bstWorst(){
		add(0);
}

void bstRand(){
	int i;
	srand(time(NULL)); // randomize seedsrand()
	for(i=0;i<LSIZE;i++)
		add(rand()%LSIZE+1);
}

                          
void addBST(){
	
	int choice;
	setLSize();
	
	 printf("Set BST type.\n");
	 printf("1. Random\t2. add 1,2,3...n\t3. add all zeroes\n");
     printf("\n Enter choice => "); 
	 scanf("%d",&choice);
     switch(choice) {

         case 1: bstRand();	                      break;
		 case 2: bstBest();                         break;
		 case 3: bstWorst();                        break;

         default:  printf("\n INVALID MENU CHOICE ***\n");
                   addBST();                                  break;
         }
}
void BST(){
	
	int v, pos;
	
		//SORTED??
		printf("vad söks?");
		scanf("%d", &v);
		t1=clock();
		pos = find(v);
		if(pos==1)
			printf("value %d found ", v);
		else 
			printf("value %d not found ",v);
	t2=clock();
	float seconds = (float)(t2 - t1);
	printf("Time taken: %f", seconds);
	unlink();
}
           
  /****************************************************************************/
/* BubbleSort																			   */
/****************************************************************************/                      
void bSort(){
	
	int j,swapped,temp;
	t1=clock();
	
	do{
		swapped=0;
		for(j=0;j<LSIZE-1;j++){
			if(array[j]>array[j+1]){
				temp=array[j];
				array[j]=array[j+1];
				array[j+1]=temp;
				swapped=1;
			}
		}
	}while(swapped);
	
	printf("Bubble sort finished!\n");
	t2=clock();
	float seconds = (float)(t2 - t1);
	printf("Time taken: %f", seconds);
}     

/****************************************************************************/
/* Insertion Sort																		  */
/****************************************************************************/                   	  
void insSort(){
	
	int c,d,t;
	t1=clock();
	for (c = 1 ; c <= LSIZE - 1; c++) {
		d = c;
		while ( d >= 0 && array[d] < array[d-1]) {
		  t          = array[d];
		  array[d]   = array[d-1];
		  array[d-1] = t	;
	 
		  d--;
		}
	}
	
	printf("Insertion sort finished!\n");
	t2=clock();
	float seconds = (float)(t2 - t1);
	printf("Time taken: %f", seconds);
}
/****************************************************************************/
/* Partition function that sets the pivot for the QuickSort		  */
/* function etc.																		  */
/****************************************************************************/
int Partition(int array[], int a, int b) { 
	int pivot, lower, upper, temp; 
	pivot = array[a]; 
	lower = a + 1; 
	upper = b; 

	do{ 
		while (array[lower] <= pivot && lower <= upper) 
		lower = lower + 1; 
		while (array[upper] > pivot && lower <= upper) 
		upper = upper - 1; 
	if (lower <= upper) { 
		temp = array[lower]; 
		array[lower] = array[upper]; 
		array[upper] = temp; 
		lower = lower + 1; 
		upper = upper - 1; 
	} 

	}while (lower <= upper); 

	temp = array[upper]; 
	array[upper] = array[a]; 
	array[a] = temp; 

	return upper; 
}

/****************************************************************************/
/* QuickSort algorithm for array												  */
/****************************************************************************/

void quickSort(int v[], int a, int b){ 
	int k; 

	if (a < b) { 
		k = Partition(v, a, b); 
		quickSort(v, a, k-1); 
		quickSort(v, k+1, b);  
	}
}

/****************************************************************************/
/* Clocks ans runs the Quicksort algorithm above				  */
/****************************************************************************/
							
void qSort(){
	t1=clock();
	quickSort(array,0,LSIZE-1);
	printf("QuickSort finished!\n");
	t2=clock();
	float seconds = (float)(t2 - t1);
	printf("Time taken: %f", seconds);
}

/****************************************************************************/
/* Prints the binary search tree												  */
/****************************************************************************/

void prntBST(){
	printBST();
}

/****************************************************************************/
/* Prints the 10 first elements of the array								  */
/****************************************************************************/

void disp()                   {  
	
	int i;
	
	for(i=0;i<=10;i++){
		printf("%d ", array[i]);
	} 
}

/****************************************************************************/
/* end of basic functions                                                   */
/****************************************************************************/

