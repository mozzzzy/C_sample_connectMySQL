#include <stdio.h>
#include <mysql/mysql.h>

int main(){

	char *db_hostname = "localhost";	//database hostname
	char *db_username = "user20160817";	//database username
	char *db_password = "password";		//database password
	char *db_name = "C_connect";		//database name
	int db_port = 3306;			//database port


	//connect
	MYSQL *connect;
	connect = mysql_init(NULL);
	if (!mysql_real_connect(connect, db_hostname, db_username, db_password, db_name, db_port, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(connect));
		return 1;
	}

	//exicute sql
	char sql_str[255];
	snprintf( &sql_str[0] , sizeof(sql_str)-1 , "show columns from table1" );
	if( mysql_query( connect , &sql_str[0] ) ){
		// error
		mysql_close(connect);
		return 1;
	}

	MYSQL_RES *resp = NULL;
	MYSQL_ROW row;

	//response
	resp = mysql_use_result(connect);
	while((row = mysql_fetch_row(resp)) != NULL ){
		printf( "%d : %s\n" , atoi(row[0]) , row[1] );
	}

	//release, close
	mysql_free_result(resp);
	mysql_close(connect);


	return 0;
}
