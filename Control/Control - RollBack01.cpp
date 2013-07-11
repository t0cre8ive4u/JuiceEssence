#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void runSol(double[]);
int main()
{
	clock_t start = clock();
	double TestArray[5] = {50, 40, 50, 20, 30};
	runSol(TestArray);
	printf("Time elapsed: %f\n", ((double)clock() - start) / CLOCKS_PER_SEC);
	getchar();

    return 0;
}

void runSol(double DrinkAmount[]){
	double k = 5; //Scale with k being time for one valve to fill the cup
	double StepSize = 250;//ms that will be taken off of the DrinkAmount every loop
	int x, y, z, temp;
	//Convers percent values into the time values//
	for (x=0; x<5;){
		DrinkAmount[x] = k*(0.01*DrinkAmount[x]);
		printf( "Drink Value TIME: %lf.\n", DrinkAmount[x]);	
		x++;
	}
	//TURNS ADD USED VALVES ON//
		for (x=0; x<5;){
			if (DrinkAmount[x] > 0){
				//TURN VAVLE X ON//
			}	
		x++;
	}
	//Steps the time remaining in incriments of StepSize//
	x = 0;
	for (y=0; y<(k/(StepSize/1000));){
		printf("Y: %d\n", y);
		
		for (x=0; x<5;){

			if (DrinkAmount[x] > 0)
				DrinkAmount[x] = DrinkAmount[x]-(StepSize/1000);
			if (DrinkAmount[x] <= 0){
				// Turn sol off here//
				printf( "Drink %d is all finished %lf.\n", x, DrinkAmount[x]);	
			}	
				x++;
		}
		_sleep((StepSize*0.99));
		y++;
	}
}