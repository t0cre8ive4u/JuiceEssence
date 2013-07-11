#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void runSol(double[]);
int main()
{
    printf( "I am Alive!  Beware.\n" );
	double TestArray[5] = {50, 40, 50, 20, 30};
	runSol(TestArray);
	getchar();

    return 0;
}

void runSol(double DrinkAmount[]){
	int k = 5; //Scale with k being time for one valve to fill the cup
	int StepSize = 250;//ms that will be taken off of the DrinkAmount every loop
	int x;

	//Convers percent values into the time values//
	for (x=0; x<5;){
		DrinkAmount[x] = k*(0.01*DrinkAmount[x]);
		printf( "Drink Value %lf.\n", DrinkAmount[x]);	
		x++;
	}

	//Steps the time remaining in incriments of StepSize//
	for (x=0; x<5;){
		DrinkAmount[x] = k*(0.01*DrinkAmount[x]);
		printf( "Drink Value %lf.\n", DrinkAmount[x]);	
		x++;
		printf( "I am Alive!  Beware.\n" );
	}

	printf( "runSol!  Beware.\n" );

}