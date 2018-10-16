#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

struct connection_details {

  const char *server;
  const char *user;
  const char *password;
  const char *database;
  const char *table;
};

MYSQL* mysql_connection_setup(struct connection_details mysql_details) {

  MYSQL *connection = mysql_init(NULL);

  if(!mysql_real_connect(connection, mysql_details.server, mysql_details.user, mysql_details.password, mysql_details.database, 0, NULL, 0)) {

    printf("Connection error : %s\n", mysql_error(connection));
    exit(1);

  }
  return connection;
}

MYSQL_RES* mysql_perform_query(MYSQL *connection, char *sql_query) {

  if(mysql_query(connection, sql_query)) {

    printf("MYSQL query error : %s\n", mysql_error(connection));
    exit(1);

  }
  return mysql_use_result(connection);
}


int main() {

  MYSQL *conn;
  MYSQL_RES *res4, *res, *res_insert;
  MYSQL_ROW row;

  struct connection_details mysqlD;
  mysqlD.server = "localhost";
  mysqlD.user = "root";
  mysqlD.password = "";
  mysqlD.database = "iwc_data";
  mysqlD.table = "win_bet";
  //connect to mysql using data                                                                                                                                                      
  conn = mysql_connection_setup(mysqlD);

  res4 = mysql_perform_query(conn, "use iwc_data");
  mysql_free_result(res4);

  res_insert = mysql_perform_query(conn, "INSERT INTO `win_bet` (`id`,`transID`,`transType`,`amount`,`history`,`userID`,`gameID`,`roundID`,`thirdParty`,`transTime`,`category`) VALU\
ES (NULL, \"3496586\", \"WIN\", \"0\", \"\", \"ibct_iwc\", \"PSS-ON-00102\", \"0\", \"29\", \"2018-10-14 16:33:15\", \"\")");
  mysql_free_result(res_insert);


  res = mysql_perform_query(conn, "select *from win_bet");
  while((row = mysql_fetch_row(res)) != NULL)
    printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", row[0], row[1], row[2], row[3],
           row[4], row[5], row[6], row[7], row[8], row[9], row[10], row[11]);

  mysql_free_result(res);
  mysql_close(conn);
}


