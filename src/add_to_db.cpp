#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <chrono> //testing purpose
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


void tokenize(std::string const &str, const char delim,
	      std::vector<std::string> &out)
{
  size_t start;
  size_t end = 0;

  while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
      end = str.find(delim, start);
      out.push_back(str.substr(start, end - start));
    }
}

std::string refactorTime(std::string str) {
  //std::string str = "2018-01-01 00:00:00";
  std::size_t index = str.find("-");
  while(index != std::string::npos) {
    str.erase(index, 1);
    index = str.find("-");
  }
  index = str.find(" ");
  if (index != std::string::npos)
    str.erase(index, 1);
  index = str.find(":");
  while(index != std::string::npos) {
    str.erase(index, 1);
    index = str.find(":");
  }
  return str;
}


bool addToDB () {
  MYSQL *conn;
  MYSQL_RES *res4, *res, *res_insert;
  MYSQL_ROW row;
  std::string transType, userID, transID, transTime, transContent, amount, thirdParty;
  struct connection_details mysqlD;
  mysqlD.server = "localhost";
  mysqlD.user = "root";
  mysqlD.password = "ibct!@#$";
  mysqlD.database = "iwc_data";
  mysqlD.table = "win_bet";
  std::ifstream ifs("/home/eos/contracts/IWC_DEV/log/parsed_json.txt");
  std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );

  //connect to mysql using data                                                  
  conn = mysql_connection_setup(mysqlD);
  res4 = mysql_perform_query(conn, "use iwc_data");
  mysql_free_result(res4);
  //if api call is successful
  std::ofstream out_average; 
  out_average.open("/home/eos/contracts/IWC_DEV/log/average_upload_time.txt", ios::app); // TODO: TEST OUTPUT GOES HERE!
  if (content.find("Success") != std::string::npos) {
    //remove string "success"
    auto start = std::chrono::high_resolution_clock::now();
    std::string success = "Success";
    size_t pos = content.find(success);
    content.erase(pos, success.length());
     
    //split transactions
    const char delim = '$';
    std::vector<std::string> out;
    tokenize(content, delim, out);

    for (int i =0; i < out.size(); i++) {
      char delim = ',';
      std::vector <std::string> transaction;
      tokenize(out[i], delim, transaction);
      if ((transaction[6]).compare("PLAYSTAR") == 0 || (transaction[6]).compare("MOCA_GAME") == 0) {
	std::cout << "Success!" << endl;
	std::string insert_command =  "INSERT INTO `win_bet` (`transType`,`userID`,`transID`,`transTime`,`transContent`,`amount`,`thirdParty`) VALUES (\"" + transaction[0] + "\", \"" + transaction[1] + "\", \"" + transaction[2] + "\", \"" + transaction[3] + "\", \"" + transaction[4] + "\", \"" + transaction[5] + "\", \"" + transaction[6] + "\")";
	char *command = new char[insert_command.length() + 1];
	res_insert = mysql_perform_query(conn, std::strcpy(command, insert_command.c_str()));
	mysql_free_result(res_insert);
	std::string push_action = "cleos push action chromemoney1 update '[chromemoney1 " + transaction[0] + " " + transaction[1] + " " + transaction[2] + " " + refactorTime(transaction[3]) + " " + transaction[4] + " " + transaction[5] + " " + transaction[6] + "]' -p chromemoney1@active";
	cout << push_action << endl;
	system(push_action.c_str());
      }
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "********Time Passed to upload " <<out.size()<< " items: " << chrono::duration_cast<chrono::milliseconds>(finish - start).count() << "ms  ********"<< std::endl;
    double avg = chrono::duration_cast<chrono::milliseconds>(finish - start).count()/ (double)out.size();
    std::cout << "***AVERAGE = " << avg << "ms*************" << std::endl;
    out_average << avg << endl;
  }
  else if (content.find("fail") != std::string::npos) {
    //if fail, don't increment time
    std::cout << "FAIL!" << std::endl;
  }
  else if (content.find("empty") != std::string::npos) {
    //if empty don't do anything
    std::cout << "EMPTY!" << std::endl;
  }
  out_average.close();
  std::string show_content = "select *from win_bet";
  res = mysql_perform_query(conn, "select *from win_bet");
  mysql_free_result(res);
  mysql_close(conn);
  return true;
}

