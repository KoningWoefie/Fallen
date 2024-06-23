#include <stdlib.h>

#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <conio.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>

#ifdef WIN32
#include <windows.h>
#include <tchar.h>
#endif

#include <SQLAPI.h>
#include <samisc.h>

#include <iostream>
#include <string>

#include <vector>
#include <thread>

typedef struct {
	SAString data;
	size_t offset;
} FromStringWriterData;

size_t FromStringWriter(SAPieceType_t& ePieceType,
	void* pBuf, size_t nLen, void* pAddlData);

void IntoStringReader(
	SAPieceType_t ePieceType,
	void* pBuf,
	size_t nLen,
	size_t nBlobSize,
	void* pAddlData);

static FILE* pFile = NULL;
size_t nTotalBound;
size_t FromFileWriter(SAPieceType_t& ePieceType,
	void* pBuf, size_t nLen, void* pAddlData)
{
	if (ePieceType == SA_FirstPiece)
	{
		const char* sFilename = (const char*)pAddlData;
		pFile = fopen(sFilename, "rb");
		if (!pFile)
			SAException::throwUserException(-1, _TSA("Can not open file '%s'"),
				(const SAChar*)SAString(sFilename));
		nTotalBound = 0;
	}

	size_t nRead = fread(pBuf, 1, nLen, pFile);
	nTotalBound += nRead;

	// show progress
	printf("%ld bytes of file bound\n", nTotalBound);

	if (feof(pFile))
	{
		if (ePieceType == SA_FirstPiece)
			ePieceType = SA_OnePiece;
		else
			ePieceType = SA_LastPiece;

		fclose(pFile);
		pFile = NULL;
	}
	return nRead;
}

SAString ReadWholeFile(const char* sFilename, bool binaryData)
{
	SAString s;
	FILE* pFile = fopen(sFilename, binaryData ? "rb" : "rt");

	if (!pFile)
		SAException::throwUserException(-1, _TSA("Error opening file '%s'\n"),
			(const SAChar*)SAString(sFilename));

	fseek(pFile, 0L, SEEK_END);
	size_t fsz = ftell(pFile);
	char* sBuf = (char*)s.GetBinaryBuffer(fsz);
	fseek(pFile, 0L, SEEK_SET);

	size_t toRead = fsz;
	size_t totalRead = 0l;
	do
	{
		size_t nRead = fread(sBuf + totalRead, 1, toRead, pFile);
		if (nRead > 0)
			totalRead += nRead;
	} while (!feof(pFile));

	fclose(pFile);
	s.ReleaseBinaryBuffer(fsz);
	return s;
}

SAString ReadWholeTextFile(const SAChar* szFilename)
{
	SAString s(szFilename);
	char szBuf[32 * 1024];
	FILE* pFile = fopen(s.GetMultiByteChars(), "rb");

	if (!pFile)
		SAException::throwUserException(-1, _TSA("Error opening file '%s'\n"),
			(const SAChar*)SAString(szFilename));

	s.Empty();

	do
	{
		size_t nRead = fread(szBuf, 1, sizeof(szBuf), pFile);
		s += SAString(szBuf, nRead);
	} while (!feof(pFile));

	fclose(pFile);
	return s;
}

void WriteWholeFile(const char* sFilename, const SAString& data)
{
	FILE* pFile = fopen(sFilename, "wb");
	size_t n, written = 0, len = data.GetBinaryLength();
	const void* pData = (const void*)data;

	sa_tprintf(_TSA("PRGLEN: %ld\n"), len);

	if (!pFile)
		SAException::throwUserException(-1, _TSA("Error opening file '%s'\n"),
			(const SAChar*)SAString(sFilename));

	while (len > written) {
		n = fwrite((const char*)pData + written, 1, sa_min(1024, len - written), pFile);
		if (n <= 0)
			break;
		written += n;
	}

	fclose(pFile);
}

size_t nTotalRead;

void IntoFileReader(
	SAPieceType_t ePieceType,
	void* pBuf,
	size_t nLen,
	size_t nBlobSize,
	void* pAddlData)
{
	const char* sFilename = (const char*)pAddlData;

	if (ePieceType == SA_FirstPiece || ePieceType == SA_OnePiece)
	{
		nTotalRead = 0;

		pFile = fopen(sFilename, "wb");
		if (!pFile)
			SAException::throwUserException(-1, _TSA("Can not open file '%s' for writing"),
				(const SAChar*)SAString(sFilename));
	}

	fwrite(pBuf, 1, nLen, pFile);

	nTotalRead += nLen;

	if (ePieceType == SA_LastPiece || ePieceType == SA_OnePiece)
	{
		fclose(pFile);
		pFile = NULL;
		printf("%s : %ld bytes of %ld read\n",
			sFilename, nTotalRead, nBlobSize);
	}
}

//#include "Scrollable_Cursor.cpp"
//#include "step3.cpp"

void t1FetchAll(SACommand& cmd) {
	printf("\nStart fetching table t1\n");

	cmd.setCommandText("select f2 from t1 order by f1");
	cmd.Execute();

	while (cmd.FetchNext())
	{
		printf("%s\n", cmd.Field(1).asString().GetMultiByteChars());
	}

	printf("End fetching table t1\n");
}

int main2()
{
	SAOptions saOptions;
	const SAString saStringOption("TheOption");
	const SAString saStringValue("TheValue");

	saOptions.setOption(saStringOption) = saStringValue;

	using Options = std::vector<std::pair<SAString, SAString>>;
	const Options options{
		{ "UseSessionPool", "1" },
		{ "UseSessionPool_Timeout", "10000" },
		{ "UseSessionPool_Min", "10" },
		{ "UseSessionPool_Max", "100" },
		{ "UseSessionPool_Incr", "10" },
	};

	for (const Options::value_type& option : options)
		saOptions.setOption(option.first) = option.second;

	const auto& threadFunction = [&saOptions, &saStringOption](std::uint64_t counter)
		{
			std::cout << "Run thread #" << counter << std::endl;
			saOptions.Option(saStringOption);
		};

	std::vector<std::thread> threads;
	for (std::uint64_t i = 0; i < 350; ++i)
		threads.emplace_back(threadFunction, i);

	for (std::uint64_t i = 0; i < threads.size(); ++i)
		threads[i].join();

	return 0;
}

int main3(int argc, char* argv[]) {
	SAConnection con;
	try {
		con.Connect(_TSA("c:\\temp\\test.db"), _TSA(""), _TSA(""), SA_SQLite_Client);

		{
			SACommand sqlCreate(&con, _TSA("CREATE TABLE IF NOT EXISTS fetch (a VARCHAR(32), b VARCHAR(32))"));
			sqlCreate.Execute();
			con.Commit();
		}

		{
			SACommand sqlDrop(&con, _TSA("DELETE FROM fetch"));
			sqlDrop.Execute();
			con.Commit();
		}

		{
			SACommand sqlInsert(&con, _TSA("INSERT INTO fetch (a,b) VALUES (:1, :2)"));
			sqlInsert << _TSA("a1") << _TSA("b1");
			sqlInsert.Execute();
			sqlInsert << _TSA("a2") << _TSA("b2");
			sqlInsert.Execute();
			con.Commit();
		}

		{
			SACommand sqlQuery(&con, _TSA("SELECT a, b FROM fetch ORDER BY a ASC, b ASC"));
			sqlQuery.Execute();
			while (sqlQuery.FetchNext()) {
				SAString aValue = sqlQuery[1].asString();
				SAString bValue = sqlQuery[2].asString();
				std::cout << "AValue: "
					<< std::string(aValue.GetMultiByteChars(),
						aValue.GetLength()) << "; BValue: "
					<< std::string(bValue.GetMultiByteChars(),
						bValue.GetLength()) << std::endl;
			}
		}

	}
	catch (SAException& x) {
		printf("ERROR:\n%s\n", x.ErrText().GetMultiByteChars());
	}

	return 1;
}

void test1()
{
	SAConnection con;
	try
	{
		con.Connect(_TSA("D:\\BullMT4PluginKeyManagerSimple.db"),
			_TSA(""), _TSA(""), SA_SQLite_Client);
		SACommand cmd(&con, _TSA("select * from MT4Plugins"));
		cmd.Execute();

		while (cmd.FetchNext()) {
			for (int i = 1; i <= cmd.FieldCount(); ++i)
			{
				printf(i > 1 ? ", %s = %s" : "%s = %s",
					cmd.Field(i).Name().GetMultiByteChars(),
					cmd.Field(i).asString().GetMultiByteChars());
			}
			printf("\n");
		}
	}
	catch (SAException& x)
	{
		printf("ERROR:\n%s\n", x.ErrText().GetMultiByteChars());
	}
}

void Ora_Fetch_Cursor(SACommand& cmd, int stage)
{
	for (int s = 1; s < stage; ++s) printf(" ");

	printf("START CURSOR #%d\n", stage);

	try
	{
		if (cmd.isResultSet())
		{
			//cmd.setOption(SACMD_PREFETCH_ROWS) = _TSA("5");
			while (cmd.FetchNext())
			{
				for (int i = 1; i <= cmd.FieldCount(); ++i)
				{
					SAField& f = cmd.Field(i);
					if (SA_dtCursor == f.FieldType())
					{
						SACommand* cur = f.asCursor();
						if (NULL == cur)
						{
							for (int s = 1; s < stage; ++s) printf(" ");

							printf("NULL result set\n");
						}
						else
							Ora_Fetch_Cursor(*cur, stage + 1);
					}
					else
					{
						for (int s = 1; s < stage; ++s) printf(" ");

						printf("VAL #%d: %s\n",
							i, f.asString().GetMultiByteChars());
					}
				}
			}
		}
		else
		{
			for (int s = 1; s < stage; ++s) printf(" ");

			printf("Empty result set\n");
		}
	}
	catch (SAException& x)
	{
		for (int s = 1; s < stage; ++s) printf(" ");

		printf("ERROR: %s\n", x.ErrText().GetMultiByteChars());
	}

	for (int s = 1; s < stage; ++s) printf(" ");

	printf("END CURSOR #%d\n", stage);
}

using namespace std;

void test_connect(SAPI& api, int i)
{
	try
	{
		SAConnection con(&api);
		cout << "Connection " << i << "...";
		con.Connect(_TSA("localhost@test"), _TSA("sa"), _TSA("Java_1970"));
		cout << "OK" << endl;
	}
	catch (SAException& x)
	{
		printf("ERROR:\n%s\n", x.ErrText().GetMultiByteChars());
	}
}

void sqlapi_trace(
	SATraceInfo_t traceInfo, //!< Tracing into label.
	SAConnection* pCon, //!< Related SAConnection or NULL.
	SACommand* pCmd, //!< Related SACommand or NULL.
	const SAChar* szTraceInfo, //!< Tracing text.
	void* pData //!< User provided data.
)
{
	printf("TRACE: %s\n", szTraceInfo);
}

void printVersion(SAConnection& con)
{
	long lClientVersion = con.ClientVersion();
	cout << "ClientVersion = " << HIWORD(lClientVersion) << "." << LOWORD(lClientVersion) << endl;
	long lServerVersion = con.ServerVersion();
	cout << "Server Version = " << HIWORD(lServerVersion) << "." << LOWORD(lServerVersion) << " " << con.ServerVersionString().GetMultiByteChars() << std::endl;
}

int main(int argc, char** argv)
{
	//SAGlobals::SetTraceFunction(SATraceInfo_t::SA_Trace_QueryText, sqlapi_trace, NULL);

#if defined(_DEBUG) && defined(WIN32)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	setlocale(LC_ALL, "");

	SAConnection con;

	try
	{
		//con.setOption(_TSA("UseAPI")) = _TSA("OLEDB"); // force SQLAPI to use OLEDB instead of ODBC
		//con.setOption(_TSA("OLEDBProvider")) = _TSA("CompactEdition.4.0");
		//con.setClient(SA_SQLServer_Client);

		/*
		con.setOption(_TSA("DBPROP_INIT_TIMEOUT")) = _TSA("5"); // 5 second DB connect time out - not network connect time out!
		con.setOption(_TSA("CreateDatabase")) = _TSA("TRUE");
		con.setOption(_TSA("DBPROP_SSCE_ENCRYPTDATABASE")) = _TSA("VARIANT_TRUE");
		con.setOption(_TSA("DBPROP_SSCE_MAXBUFFERSIZE")) = _TSA("102400"); // what is the maximum size possible? "The largest amount of memory, in kilobytes, that SQL Server Compact Edition can use before it starts flushing changes to disk. The default value is 640 kilobytes."
		con.setOption(_TSA("DBPROP_SSCE_MAX_DATABASE_SIZE")) = _TSA("4091");
		con.setOption(_TSA("DBPROP_SSCE_TEMPFILE_MAX_SIZE")) = _TSA("4091");
		con.setOption(_TSA("DBPROP_SSCE_DEFAULT_LOCK_ESCALATION")) = _TSA("250000");  // http://msdn.microsoft.com/en-us/library/ms172010(SQL.100).aspx
		con.setOption(_TSA("DBPROP_SSCE_AUTO_SHRINK_THRESHOLD")) = _TSA("100"); // disable auto shrink
		con.setOption(_TSA("DBPROP_SSCE_DEFAULT_LOCK_TIMEOUT")) = _TSA("500"); // 0.5 seconds
		*/
		//con.Connect(_TSA("D:\\1a0f1652-1e85-4048-8b8f-1574793ab8bd.sdf"), _TSA("sa"), _TSA("{F084AF71-AA6F-45c2-A0C3-5160070C0F52}"));

		//con.setOption(_TSA("SQLNCLI.LIBS")) = _TSA("sqlsrv32.dll");

		//con.Connect(_TSA("server=demo12"), _TSA("DBA"), _TSA("sql"), SA_SQLAnywhere_Client);
		//con.Connect(_TSA("server=demo17"), _TSA("DBA"), _TSA("sql"), SA_SQLAnywhere_Client);
		//con.Connect(_TSA("ol_ids_1410"), _TSA("informix"), _TSA("java"), SA_Informix_Client);
		//con.Connect(_TSA("bedlam-wx\\sql2017,49805@test"), _TSA(""), _TSA(""), SA_SQLServer_Client);		
		//con.setOption(_TSA("UseAPI")) = _TSA("OLEDB");
		//con.setOption(_TSA("SQLNCLI.LIBS")) = _TSA("sqlncli11.dll");
		//con.Connect(_TSA("bedlam-m\\sql2014en@test"), _TSA(""), _TSA(""), SA_SQLServer_Client);
		//con.Connect(_TSA("Driver=SQLite3 ODBC Driver;Database=d:\\sqlite.db;"), _TSA(""), _TSA(""), SA_ODBC_Client);
		//con.Connect(_TSA("ora111"), _TSA("sys"), _TSA("java"), SA_Oracle_Client);
		//con.Connect(_TSA("ora1221"), _TSA(""), _TSA(""), SA_Oracle_Client);
		//con.Connect(_TSA("localhost@test"), _TSA("postgres"), _TSA("java"), SA_PostgreSQL_Client);

		//con.setOption(_TSA("CS_SEC_ENCRYPTION")) = _TSA("CS_TRUE");
		//api.setClient(SA_Sybase_Client);
		//con.Connect(_TSA("xxx@master"), _TSA("sa"), _TSA("java1970"), SA_Sybase_Client);

		//con.Connect(_TSA("SAMPLE"), _TSA("db2admin"), _TSA("java"), SA_DB2_Client);
		//con.Connect(_TSA("DSN=SAMPLE;TraceFileName=d:\\db2.log;Trace=1;TraceFlush=1"), _TSA(""), _TSA(""), SA_DB2_Client);

		//con.setOption(_TSA("IBASE.LIBS")) = _TSA("fbclient.dll");
		//con.Connect(_TSA("localhost/ibxe3:d:/Test_xe3.gdb"), _TSA("SYSDBA"), _TSA("masterkey"), SA_InterBase_Client);

		//con.setOption(_TSA("IBASE.LIBS")) = _TSA("fbclient.dll");
		//con.Connect(_TSA("localhost:d:/Firebird/3.0.2-x64/test.gdb"), _TSA("SYSDBA"), _TSA("masterkey"), SA_InterBase_Client);
		//con.Connect(_TSA("xnet://d:/Firebird/3.0.2-x64/test.gdb"), _TSA("SYSDBA"), _TSA("masterkey"), SA_InterBase_Client);

		//SAString sVer = con.ServerVersionString();

		//con.setOption(SACON_OPTION_APPNAME) = _TSA("SQLAPI");
		//con.Connect(_TSA("localhost@test2"), _TSA("admin"), _TSA("admin"), SA_CubeSQL_Client);

		//con.Connect(_TSA("Server=(localdb)\\MSSQLLocalDB;AttachDbFileName=D:\\TEST.MDF"), _TSA(""), _TSA(""), SA_SQLServer_Client);

		//con.setAutoCommit(SAAutoCommit_t::SA_AutoCommitOff);
		//con.setOption(_TSA("MYSQL.LIBS")) = _TSA("D:\\mysql\\5.7.18-winx64\\lib\\libMySQL.dll");
		//long x = con.ClientVersion();

		//con.Connect(_TSA("localhost@test"), _TSA("root"), _TSA(""), SA_MySQL_Client);

		//con.setOption(_TSA("SQLNCLI.LIBS")) = _TSA("sqlncli11.dll");
		//con.setOption(_TSA("SQLNCLI.LIBS")) = _TSA("sqlsrv32.dll");
		//con.Connect(_TSA("bedlam-m\\sql2014en@test"), _TSA(""), _TSA(""), SA_SQLServer_Client);
		//con.Connect(_TSA("SQL2014EN"), _TSA(""), _TSA(""), SA_ODBC_Client);
		//con.setOption(_TSA("UseAPI")) = ("OLEDB");
		//con.Connect(_TSA("bedlam-m\\sql2017@test"), _TSA(""), _TSA(""), SA_SQLServer_Client);
		//con.Connect(_TSA("kdx"), _TSA("yas"), _TSA("java"), SA_Oracle_Client);

		//con.setOption(_TSA("LIBPQ.LIBS")) = _TSA("sqlite3.dll");
		//con.Connect(_TSA("localhost@test"), _TSA("postgres"), _TSA("java"), SA_PostgreSQL_Client);

		//con.setOption(_TSA("UseAPI")) = ("OLEDB");
		//con.setOption(_TSA("OLEDBProvider")) = _TSA("SQLOLEDB");
		//con.Connect(_TSA("d:/test.db"), _TSA(""), _TSA(""), SA_SQLite_Client);

		//con.Connect(_TSA("localhost@license"), _TSA("LICENSE_USER"), _TSA("LICENSE_USER"), SA_MySQL_Client);

		//con.setOption(_TSA("OCI_ATTR_DEFAULT_LOBPREFETCH_SIZE")) = _TSA("2000");
		//con.setOption(_TSA("OCI_ATTR_LOBPREFETCH_LENGTH")) = _TSA("1");
		//con.setOption(_TSA("OCI_ATTR_LOBPREFETCH_SIZE")) = _TSA("4000");
		//con.Connect(_TSA("localhost/kdx"), _TSA("PCODEFR_OWNER"), _TSA("pcodefreaov"), SA_Oracle_Client);

		//con.Connect(_TSA("localhost@test"), _TSA("postgres"), _TSA("java"), SA_PostgreSQL_Client);
		//con.setOption(_TSA("UseAPI")) = ("OLEDB");
		//con.setOption(_TSA("OLEDBProvider")) = _TSA("SQLOLEDB");
		//con.setOption(_TSA("OLEDBProvider")) = _TSA("SQLNCLI11");
		//con.setOption(_TSA("SSPROP_AUTH_MODE")) = _TSA("ActiveDirectoryIntegrated");
		//con.setOption("SSPROP_INIT_TRUST_SERVER_CERTIFICATE") = _TSA("VARIANT_TRUE");
		//con.Connect(_TSA("bedlam-m\\SQL2019@test"), _TSA(""), _TSA(""), SA_SQLServer_Client);			
		//con.Connect(_TSA("TEST"), _TSA(""), _TSA(""), SA_DB2_Client);

		//con.setOption(_TSA("IBASE.LIBS")) = _TSA("fbclient.dll");
		//con.Connect(_TSA("localhost:employee"), _TSA("SYSDBA"), _TSA("masterkey"), SA_InterBase_Client);			

		con.setOption(_TSA("UseAPI")) = _TSA("OLEDB");
		con.setOption(_TSA("OLEDBProvider")) = _TSA("MSOLEDBSQL19");
		con.setOption(_TSA("SSPROP_INIT_ENCRYPT")) = _TSA("no");
		//con.Connect(_TSA("localhost@test"), _TSA("sa"), _TSA("Java_1970"), SA_SQLServer_Client);
		//con.Connect(_TSA("localhost@test;Encrypt=Optional"), _TSA("sa"), _TSA("Java_1970"), SA_SQLServer_Client);
		//con.Connect(_TSA("MSSQL22"), _TSA("sa"), _TSA("Java_1970"), SA_ODBC_Client);
		//con.Connect(_TSA("localhost/XEPDB1"), _TSA("yas"), _TSA("java$"), SA_Oracle_Client);
		//con.Connect(_TSA("test"), _TSA("sysdba"), _TSA("masterkey"), SA_InterBase_Client);
		//con.Connect(_TSA("localhost@test"), _TSA("root"), _TSA(""), SA_MariaDB_Client);
		//con.setOption(_TSA("NLS_CHAR")) = _TSA("ZHS16GBK");
		//con.Connect(_TSA("localhost/KDX"), _TSA("STRATEGIE_OWNER"), _TSA("strategieeaov"), SA_Oracle_Client);

		//con.Connect(_TSA("localhost@test"), _TSA("ßüäö"), _TSA("java"), SA_PostgreSQL_Client);

		con.Connect(_TSA("localhost/XEPDB1"), _TSA("yas"), _TSA("java$"), SA_Oracle_Client);
		//con.Connect(_TSA("test.db"), _TSA(""), _TSA(""), SA_SQLite_Client);

		//con.Connect(_TSA("localhost@test;Encrypt=Optional"), _TSA("sa"), _TSA("Java_1970"), SA_SQLServer_Client);
		cout << "Connected." << endl;
		printVersion(con);

		SACommand cmd(&con);

		/*
		cmd.setCommandText(_TSA("update t1 set fblob=:1 where id=1"));
		cmd.Prepare();
		FromStringWriterData data;
		data.data = SAString(_TSA('a'), 1024 * 3);
		data.offset = size_t(0);
		cmd.Param(_TSA("1")).setAsBLob(FromStringWriter, 1024, &data);
		cmd.Execute();
		*/

		cmd.setOption(SACMD_PREFETCH_ROWS) = _TSA("6");
		cmd.setCommandText(_TSA("SELECT ID from t1"));
		cmd.Execute();

		while (cmd.FetchNext())
		{
			printf("%s\n", cmd[1].asString().GetMultiByteChars());
		}

		printf("OK\n");
	}
	catch (SAException& x)
	{
		printf("ERROR:\n%s\n", x.ErrText().GetMultiByteChars());
	}

	SAGlobals::UnInitialize();

#if defined(_DEBUG) && defined(WIN32)
	_CrtDumpMemoryLeaks();
#endif
	return 0;
}


size_t FromStringWriter(SAPieceType_t& ePieceType,
	void* pBuf, size_t nLen, void* pAddlData)
{
	FromStringWriterData* data = (FromStringWriterData*)pAddlData;
	size_t toWrite = sa_min(nLen, data->data.GetBinaryLength() - data->offset);
	
	if (toWrite > 0)
		memcpy(pBuf, (const void*)(data->data), toWrite);
	else
		toWrite = 0l;

	if (toWrite < nLen)
		ePieceType = SA_LastPiece;
	
	data->offset += toWrite;
	
	return toWrite;
}

void IntoStringReader(
	SAPieceType_t ePieceType,
	void* pBuf,
	size_t nLen,
	size_t nBlobSize,
	void* pAddlData)
{
	SAString* data = (SAString*)pAddlData;
	size_t oldLen = data->GetBinaryLength();
	memcpy((char*)data->GetBinaryBuffer(oldLen + nLen) + oldLen, pBuf, nLen);
	data->ReleaseBinaryBuffer(oldLen + nLen);
}
