#include <wiringPi.h>
#define gpio

int main ()
{
 wiringPiSetup () ;
 pinMode (0, OUTPUT) ;
 pinMode (1, OUTPUT) ;
 pinMode (2, OUTPUT) ;
 pinMode (3, OUTPUT) ;
 pinMode (4, OUTPUT) ;

 for (int x = 0; x<5; x++)
 {
   digitalWrite (0, HIGH) ; delay (500) ;
   digitalWrite (0,  LOW) ; delay (500) ;

   digitalWrite (1, HIGH) ; delay (500) ;
   digitalWrite (1,  LOW) ; delay (500) ;

   digitalWrite (2, HIGH) ; delay (500) ;
   digitalWrite (2,  LOW) ; delay (500) ;

   digitalWrite (3, HIGH) ; delay (500) ;
   digitalWrite (3  LOW) ; delay (500) ;

   digitalWrite (4, HIGH) ; delay (500) ;
   digitalWrite (4,  LOW) ; delay (500) ;
 }


}
