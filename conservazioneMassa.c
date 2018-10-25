
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define NPOINTSX 101
#define VPLASMA 2
#define INTERVAL 1

struct Vector 
{
    double *data;    // no place for x and n in readable code :-)
    size_t size;
};


void delVector (struct Vector *vector);
void printVector (struct Vector * vector);
void initRhos (struct Vector * vector);
void copyVector (struct Vector * oldVector, struct Vector * newVector);
void LaxWendroffStep (struct Vector * newVec, double cfl, double cfl2);
void LaxWendroff ();
void fileprintVector (struct Vector * vector, int ii);
char * genFilename(int counter);
struct Vector * newVector (size_t sz);

int main(int argc, char * argv[])
{


   LaxWendroff();	      
   

   //inserire parte grafici output su file, prova binario per output wr, output grafico python postscript
   return 0;
    
}


struct Vector * newVector (size_t sz) 
{
    // Try to allocate vector structure.
    
    struct Vector *retVal = malloc (sizeof (struct Vector));
    if (retVal == NULL)
        return NULL;
    
    // Try to allocate vector data, free structure if fail.
    
    retVal->data = malloc (sz * sizeof (double));
    if (retVal->data == NULL) 
    {
        free (retVal);
        return NULL;
    }
    
    // Set size and return.
    
    retVal->size = sz;
    return retVal;
}

char * genFilename(int counter)
{
    char * filename = malloc(sizeof(char)*20);


    char itnum[6];
    sprintf(itnum, "%05i", counter);

    char str[20];
    strcpy (str, "iteration_");
    strcat (str, itnum);
    strcat (str, ".txt");


    strcpy (filename, str);
    return filename;
   
}

void delVector (struct Vector * vector) 
{
    // Can safely assume vector is NULL or fully built.
    
    if (vector != NULL) 
    {
        free (vector->data);
        free (vector);
    }
}

void printVector (struct Vector * vector)
{

  

    for (int i = 0; i < vector->size; i++) 
    {
   
    printf ("%i) %lf\t", i, vector->data[i]);

        if (i%10 == 0)
        {
           printf("\n");
        }



    }



}

void fileprintVector (struct Vector * vector, int ii)
{
    FILE *fptr;
    char * str = genFilename(ii);

    fptr = fopen(str, "w"); //solo coorfdinata y sul file, coordinata x nel file python

    
    for (int i = 0; i < vector->size; i++) 
    {
         

   
        fprintf (fptr, "%lf\n", vector->data[i]);

        /*if (i%5 == 0)
        {
           fprintf(fptr, "\n");
        }*/



    }

    fprintf (fptr, "\n");

    fclose(fptr);



}



void initRhos (struct Vector * vector)
{   


	for (int i=0; i < vector->size; i++)
	{
		vector->data[i] = 0;
	}

	for (int i=2; i < 14; i++)
	{
		vector->data[i] = 1;
	}


}




void copyVector (struct Vector * oldVector, struct Vector * newVector)
{



	if (newVector->size != oldVector->size)
	{
		printf("\n Error \n");
		return;
	}
	

	for (int i=0; i < oldVector->size; i++)
	{
		newVector->data[i] = oldVector->data[i];
	}


}

void LaxWendroffStep (struct Vector * newVec, double cfl, double cfl2)
{

	struct Vector * oldVec = newVector(NPOINTSX);
	copyVector(newVec, oldVec);

	for(int i=1; i < NPOINTSX - 1; i++)
	{
	
	newVec->data[i] = oldVec->data[i] - cfl * 0.5 * (oldVec->data[i+1] - oldVec->data[i-1]) + 
	cfl2 * 0.5 * (oldVec->data[i+1] - 2.0 * oldVec->data[i] + oldVec->data[i-1]); //scomponi cfl per passi successivi

	}
    newVec->data[0] = newVec->data[1];
    newVec->data[NPOINTSX - 1] = newVec->data[NPOINTSX - 2];


}




void LaxWendroff ()
{
 	int ii=0;


 	double deltat;
    double deltax = (double) INTERVAL / (NPOINTSX - 1);
    double realtime = 0.0;

    printf ("Inserisci intervallo deltaT \n");
    scanf ("%lf", &deltat);    


    


    /*
    if (cfl > 1)
    {

        printf("\nErrore! Il metodo non converge per un numero CFL maggiore di 1\n");


    }
    else
    {
    */

    double Tmax = (double) INTERVAL / VPLASMA;

    
    
    //double deltat = cfl * deltax / VPLASMA; //deltat inserito da tastiera e successivamente conferma condizione di courant punto per punto 
    
    struct Vector * rhos = newVector(NPOINTSX);


    initRhos (rhos);

	
    do
	{
		
		ii++;
        double cfl = deltat * (double) VPLASMA / deltax; 
        double cfl2 = pow(cfl, 2);

        if (cfl <= 1)
        { 

    	   LaxWendroffStep(rhos, cfl, cfl2);
    	   printf("\n Iterazione %i Dt \n", ii);
        
    	   //printVector (rhos);  //Non più utile la stampa a schermo di tutti i valori di rho
           
           fileprintVector (rhos, ii);

    	   realtime += deltat;
        }
        else
        {
            printf("\nErrore! Il metodo non converge per un numero CFL maggiore di 1\n");
            exit(1);
        }
    }
    while (realtime < Tmax);



    delVector(rhos);
    


    //}

}

