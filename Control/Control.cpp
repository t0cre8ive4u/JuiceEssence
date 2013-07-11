
#define BOARD RASPBERRY_PI
#include <gnublin.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MILLI(x) x / 1000

void runSol(double[]), int[];

int main()
{
	clock_t start = clock();
	double testArray[5] = {30, 40, 10, 20, 0};
	int pinNum[5] = {14, 15, 18, 17, 22};			//Change output pins
	runSol(testArray, pinNum);						// Change pin order/number to fit SQL DB
	printf("Time elapsed: %f\n", ((double)clock() - start) / CLOCKS_PER_SEC);

	getchar();
    return 0;
}

void runSol(double drinkAmount[], int pinNum[]){

	double k = 5; //Scale with k being time for one valve to fill the cup
	double stepSize = 250;//ms that will be taken off of the drinkAmount every loop
	
	gnublin_gpio gpio;
	for (int x = 0; x < 5; x++){
		gpio.pinMode(pinNum[x],OUTPUT);	
	}

	
	
	//Convers percent values into the time values//
	for (int x = 0; x < 5; x++){
		drinkAmount[x] = k * (0.01 * drinkAmount[x]);
		printf("Drink Value TIME: %lf.\n", drinkAmount[x]);	
	}
	//TURNS ADD USED VALVES ON//
	for (int x = 0; x < 5; x++){
		if (drinkAmount[x] > 0){
			gpio.digitalWrite(punNum[x],HIGH);
		}	
	}
	//Steps the time remaining in incriments of StepSize//
	for (int y = 0; y < (k / MILLI(stepSize)); y++){//(StepSize / 1000)); y++){
		printf("Y: %d\n", y);
		
		for (int x = 0; x < 5; x++){

			if (drinkAmount[x] > 0)
				drinkAmount[x] -= MILLI(stepSize);
			else { //if (drinkAmount[x] <= 0){
				gpio.digitalWrite(punNum[x],LOW);	
			}	
		}
		_sleep((stepSize * 0.99));	
	}
}