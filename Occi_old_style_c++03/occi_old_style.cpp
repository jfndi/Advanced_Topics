#include <iostream>
#include <string>
#include <occi.h>

using namespace std;
using namespace oracle::occi;

int main()
{
	string dbConn = "172.17.42.1", user = "herbert",
		password = "NSA_go_away";

	Environment* env = Environment::createEnvironment();
	Connection* conn = env->createConnection(user, password,
		dbConn);

	string query = "select problem from my_solutions"
		" where award_worthy != 0";
	Statement* stmt = conn->createStatement(query);
	ResultSet* rs = stmt->executeQuery();

	while (rs->next())
		cout << rs->getString(1) << endl;

	stmt->closeResultSet(rs);
	conn->terminateStatement(stmt);
	env->terminateConnection(conn);
	Environment::terminateEnvironment(env);
}