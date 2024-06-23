#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SQLAPI.h>

#include <sl3API.h>

int main(int argc, char **argv)
{
    SAConnection con;

    try
    {
        con.Connect(_TSA("c:\\sample.sqlite"), _TSA(""), _TSA(""), SA_SQLite_Client);

        sl3API* pAPI = (sl3API*)con.NativeAPI();
        sl3ConnectionHandles* pConH = (sl3ConnectionHandles*)con.NativeHandles();

        if (NULL != pAPI->sqlite3_key)
        {
            pAPI->sqlite3_key(pConH->pDb, "abcde", 5);
        }
    }
    catch (SAException& x)
    {
        printf("ERROR:\n%s\n", x.ErrText().GetMultiByteChars());
    }

    return 0;
}
