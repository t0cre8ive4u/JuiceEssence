/* Simple program that connects to MySQL Database server*/
#include <mysql.h>
#include <stdio.h>

#define SERVER "localhost"
#define USER "pi"
#define PASSWORD ""
#define DATABASE "queued_drinks"

int main() {
   MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row;
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
   while ((row = mysql_fetch_row(res)) != NULL){
      
   for(int i = 0; i < num_fields; i++) 
      { 
          printf("%s ", row[i] ? row[i] : "NULL"); 
      } 
          printf("\n"); 
		  }
   	if (mysql_query(conn, "DELETE FROM queue LIMIT 1")) {
		fprintf(stderr, "%s\n", mysql_error(conn));
}
     //	 printf("%s \n", row[1]);
   /* close connection */
   mysql_free_result(res);
   mysql_close(conn);
   
   return 0;
}