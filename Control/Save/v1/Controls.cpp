#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <mysql.h>
#include <cstring>
#define MILLI(x) x / 1000000
#define SERVER "localhost"
#define USER "pi"
#define PASSWORD ""
#define DATABASE "queued_drinks"
using namespace std;

void pinConfig(int[], int[]);
void cupWait(int[]);
char** getOrder();
char** hold;
void runSol(double[], int[]);
int main(){

	double testArray[6] = {100, 75, 50, 25, 12};
	double drinkOrder[6];
	
	int solPinNum[5] = {0, 1, 2, 3, 5};	//sol pin outs
	int buttonPinNum[3] = {5, 6, 7};   //button, wait led, running led

	pinConfig(solPinNum, buttonPinNum);
	
	for(int x = 0; x < 2; x++){
		cupWait(buttonPinNum);
		hold = getOrder();
		printf("sup from line 33");
		for (int y = 1; y  < 6; y++){
			drinkOrder[y-1] = double(atoi((hold[y])));
			}
		runSol(drinkOrder, solPinNum);				// Change pin order/number to fit SQL DB
		
	}
	getchar();
    return 0;
}


void pinConfig(int solPinNum[], int buttonPinNum[]){
	wiringPiSetup();
	for (int x = 0; x < 5; x++){
		pinMode(solPinNum[x], OUTPUT);				//activate pins
		digitalWrite(solPinNum[x], LOW); 		
	}
	
	pinMode(buttonPinNum[0], INPUT);				//activate pins
	pinMode(buttonPinNum[1], OUTPUT);
	pinMode(buttonPinNum[2], OUTPUT);
	digitalWrite(buttonPinNum[1], HIGH);
	digitalWrite(buttonPinNum[2], LOW);
}

void runSol(double drinkAmount[], int pinNum[]){

	double k = 10; 		//Scale with k being time for one valve to fill the cup
	double stepSize = 250000;  //us that will be taken off of the drinkAmount every loop
	double temp = k / (MILLI(stepSize));
	//printf("Should grow with k: %f\n", temp);
	printf("0 = %lf\n", drinkAmount[0]);
	printf("1 = %lf\n", drinkAmount[1]);
	printf("2 = %lf\n", drinkAmount[2]);
	printf("3 = %lf\n", drinkAmount[3]);
	printf("4 = %lf\n", drinkAmount[4]);
	printf("5 = %lf\n", drinkAmount[5]);
	for (int x = 1; x < 6; x++){
		drinkAmount[x-1] = k * (0.01 * drinkAmount[x]);//convert drink % to s
		printf("PIN AMONT: %lf\n %d\n", drinkAmount[x-1], x);
	}
			
	//TURNS ADD USED VALVES ON//
	for (int x = 0; x < 5; x++){
		if (drinkAmount[x] > 0){	
			digitalWrite(pinNum[x], HIGH); 
		}	
	}
	//Steps the time remaining in incriments of StepSize//
	for (int y = 0; y < (k / (MILLI(stepSize))); y++){//(StepSize / 1000)); y++){
		usleep((stepSize));	
		for (int x = 0; x < 5; x++){
		
			if (drinkAmount[x] > 0){
				drinkAmount[x] -= MILLI(stepSize);
				}
			else { //if (drinkAmount[x] <= 0){
				digitalWrite(pinNum[x], LOW);
			}	
		}
		//printf("Y: %d\n", y);

	}
		for (int x = 0; x < 5; x++){
		digitalWrite(pinNum[x], LOW); 		
	}
	
}

void cupWait(int buttonPinNum[]){
	
	digitalWrite(buttonPinNum[1], HIGH);
	digitalWrite(buttonPinNum[2], LOW);

	for (int x = 0; x < 1;){
		if (digitalRead(buttonPinNum[0]) == 0){
			x = 1;
			digitalWrite(buttonPinNum[1], LOW);
			digitalWrite(buttonPinNum[2], HIGH);	
		}
		usleep((250000));	
	}

}

char **getOrder(){
MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row = NULL;
   conn = mysql_init(NULL);
   /* Connect to database */
   if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
   }
   
	if (mysql_query(conn, "SELECT * FROM queue LIMIT 1")) {
		fprintf(stderr, "%s\n", mysql_error(conn));
}
   res = mysql_use_result(conn);
   int num_fields = mysql_num_fields(res);
   /* output table name */
   printf("MySQL Tables in mysql database:\n");
row = mysql_fetch_row(res);
	   for(int i = 0; i < num_fields; i++) 
	   { 
			  printf("%s ", row[i] ? row[i] : "NULL"); 
	   } 
			  printf("line: 134\n"); 
	
	printf("LINE: 136");
   	if (mysql_query(conn, "DELETE FROM queue LIMIT 1")) 
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		printf("LINE: 140");
	}
	
   /* close connection */
   mysql_free_result(res);
   mysql_close(conn);
   //char * returnRow = row;
   printf("LINE: 147");
return row;
}
	