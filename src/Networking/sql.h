#ifndef SQL_H
#define SQL_H

#include <string>
#include <vector>
#include <SQLAPI.h>
#include <iostream>
#include <numeric>

enum class SQLType
{
    INT,
    STRING,
    DOUBLE,
    DATETIME,
    BOOL,
    LONG,
    DEFAULT
};

class SQL
{
public:
    SQL(std::string dataBase, std::string userName, std::string password, std::string tableName);
    ~SQL();

    // If the values and types are not the same size this function will not work
    void CreateRow(std::vector<std::string> fields, std::vector<std::string> values = {}, std::vector<SQLType> type = {});

    void UpdateData(std::string fieldAndValue, std::string whereCommand = "1");

    template <typename T>

    T SelectData(std::string fieldName, std::string whereCommand = "1");


    void DeleteRow(std::string whereCommand);

    void SetTableName(std::string tableName);

private:
    void Connect();
    void Disconnect();

    SADateTime ParseDateTime(std::string& date);

    std::string _dataBase;
    std::string _userName;
    std::string _password;
    std::string _tableName;

    SAConnection _con;
};

#endif
