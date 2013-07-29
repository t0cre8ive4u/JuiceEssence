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
char *globalRow;
double valueTwo;
void runSol(double[], int[]);

int main()
{

	double testArray[6] = {100, 75, 50, 25, 12};
	double drinkOrder[5];
	
	int solPinNum[5] = {0, 1, 2, 3, 4};	//sol pin outs
	int buttonPinNum[3] = {5, 6, 7};   //button, wait led, running led

	pinConfig(solPinNum, buttonPinNum);
	
	for(int x = 0; x < 1; x++)
	{
		cupWait(buttonPinNum);
		hold = getOrder();
		drinkOrder[0] = valueTwo;
		for (int y = 1; y  < 6; y++)
		{
			drinkOrder[y-1] = double(atoi((hold[y])));
		}
		drinkOrder[0] = valueTwo;
		runSol(drinkOrder, solPinNum);				// Change pin order/number to fit SQL DB
			
	}
	getchar();
    return 0;
}


void pinConfig(int solPinNum[], int buttonPinNum[])
{
	wiringPiSetup();
	for (int x = 0; x < 5; x++)
	{
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

	for (int x = 0; x < 5; x++)
	{
		drinkAmount[x] = k * (0.01 * drinkAmount[x]);//convert drink % to s
		printf("\nPIN: %d AMONT: %lf\n %d\n", x, drinkAmount[x]);
	}
			
	//TURNS ADD USED VALVES ON//
	for (int x = 0; x < 5; x++)
	{
		if (drinkAmount[x] > 0)
		{	
			digitalWrite(pinNum[x], HIGH); 
			
		}	
	}
	//Steps the time remaining in incriments of StepSize//
	for (int y = 0; y < (k / (MILLI(stepSize))); y++)//(StepSize / 1000)); y++){
	{
		usleep((stepSize));	
		for (int x = 0; x < 5; x++)
		{
			if (drinkAmount[x] > 0)
			{
				drinkAmount[x] -= MILLI(stepSize);
			}
			else  //if (drinkAmount[x] <= 0){
			{
				digitalWrite(pinNum[x], LOW);
			}	
		}

	}
	for (int x = 0; x < 5; x++)
	{
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
   char *returnRow;
   
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
row = mysql_fetch_row(res);
		printf("\n\n", num_fields);
	  for(int i = 0; i < num_fields; i++) 
	   { 
			  printf("%s ", row[i] ? row[i] : "NULL");
	   } 
	   globalRow = row[1];
	   valueTwo = double(atoi((row[1])));
	 
	   

   	if (mysql_query(conn, "DELETE FROM queue LIMIT 1")) 
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
	}
	
   /* close connection */
   mysql_free_result(res);
   mysql_close(conn);
return row;
}
	