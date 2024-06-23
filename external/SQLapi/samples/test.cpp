#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

#include <SQLAPI.h>
#include <samisc.h>

int main(int argc, char* argv[]) {
	SAConnection con;
	try {
		con.Connect(_TSA("test.sqlite"), _TSA(""), _TSA(""), SA_SQLite_Client);

		{
			SACommand sqlCreate(&con, _TSA("CREATE TABLE IF NOT EXISTS T1(F1 BIGINT, F2 BIGINT)"));
			sqlCreate.Execute();
			con.Commit();
		}

		{
			SACommand sqlDrop(&con, _TSA("DELETE FROM T1"));
			sqlDrop.Execute();
			con.Commit();
		}

		{
			SACommand sqlInsert(&con, _TSA("INSERT INTO T1 (F1,F2) VALUES (1, :1)"));
			sqlInsert.Param(1).setAsInt64() = - (sa_int64_t)0x1A0000000;
			sqlInsert.Execute();
			con.Commit();
		}

		{
			SACommand sqlQuery(&con, _TSA("SELECT F1, F2 FROM T1"));
			sqlQuery.Execute();
			while (sqlQuery.FetchNext()) {
				printf("F1=%s, F2=%s\n", 
					sqlQuery[1].asString().GetMultiByteChars(),
					sqlQuery[2].asString().GetMultiByteChars());
			}
		}

	}
	catch (SAException& x) {
		printf("ERROR:\n%s\n", x.ErrText().GetMultiByteChars());
	}

	return 1;
}