#include "SQLAPI.h"
#include <src/Networking/sql.h>

SQL::SQL(std::string dataBase, std::string userName, std::string password, std::string tableName)
{
    _dataBase = dataBase;
    _userName = userName;
    _password = password;
    _tableName = tableName;
}

SQL::~SQL()
{

}

void SQL::SetTableName(std::string tableName)
{
    _tableName = tableName;
}

void SQL::Connect()
{
    try
    {
        _con.Connect(_TSA(_dataBase.c_str()), _TSA(_userName.c_str()), _TSA(_password.c_str()), _TSA(SA_MySQL_Client));
    }
    catch (SAException &x)
    {
        std::cout << x.ErrText().GetMultiByteChars() << "\n";
    }
}

void SQL::Disconnect()
{
    _con.Disconnect();
}

void SQL::CreateRow(std::vector<std::string> fields, std::vector<std::string> values, std::vector<SQLType> types)
{
    try
    {
        Connect();
        std::string fieldNames = "";
        std::accumulate(fields.begin(), fields.end(), fieldNames);
        std::string command = "INSERT INTO " + _tableName + "(Room_ID, Room_Name, Room_Password, Room_Member_Count, Room_Current_Member, Room_Last_Card, Room_Creation_Time, Room_Expiry_Time, Room_Last_Edited_Time) VALUES (:1, :2, :3, :4, :5, :6, :7, :8, :9)";
        SACommand cmd(&_con, _TSA(command.c_str()));
        for(int i = 0; i < values.size(); i++)
        {
            switch(types[i])
            {
                case SQLType::DEFAULT:
                    std::cout << "Default takes the value you have given in your database" << "\n";
                    break;
                case SQLType::INT:
                    cmd.Param(i + 1).setAsInt32() = stoi(values[i]);
                    break;
                case SQLType::STRING:
                    cmd.Param(i + 1).setAsString() = values[i].c_str();
                    break;
                case SQLType::DATETIME:
                    cmd.Param(i + 1).setAsDateTime() = ParseDateTime(values[i]);
                    break;
                case SQLType::DOUBLE:
                    cmd.Param(i + 1).setAsDouble() = stod(values[i]);
                    break;
                case SQLType::BOOL:
                    cmd.Param(i + 1).setAsBool() = values[i] == "true" ? true : false;
                    break;
                case SQLType::LONG:
                    cmd.Param(i + 1).setAsLong() = stol(values[i]);
                    break;
            }
        }
        cmd.Execute();
        Disconnect();
    }
    catch (SAException &x)
    {
        std::cout << x.ErrText().GetMultiByteChars() << "\n";
    }
}

void SQL::DeleteRow(std::string whereCommand)
{
    try
    {
        Connect();
        std::string command = "DELETE FROM " + _tableName + " WHERE " + whereCommand;
        SACommand cmd(&_con, _TSA(command.c_str()));
        cmd.Execute();
        Disconnect();
    }
    catch (SAException &x)
    {
        std::cout << x.ErrText().GetMultiByteChars() << "\n";
        Disconnect();
    }
}

SADateTime SQL::ParseDateTime(std::string& dateTime)
{
    int year, month, day, hour, minute, second, millisecond = 0;

    std::sscanf(dateTime.c_str(), "%d-%d-%d %d:%d:%d.%d", &year, &month, &day, &hour, &minute, &second, &millisecond);

    return SADateTime(year, month, day, hour, minute, second, millisecond);
}

template<>
int SQL::SelectData<int>(std::string fieldName, std::string whereCommand)
{
    try
    {
        Connect();
        std::string command = "SELECT " + fieldName + " FROM " + _tableName + " WHERE " + whereCommand;
        std::cout << command << "\n";
        SACommand cmd(&_con, _TSA(command.c_str()));
        cmd.Execute();
        while (cmd.FetchNext())
        {
            Disconnect();
            return cmd.Field(fieldName.c_str()).asInt32();
        }
        Disconnect();
        return -1;
    }
    catch (SAException &x)
    {
        std::cout << x.ErrText().GetMultiByteChars() << "\n";
        Disconnect();
        return -1;
    }
}

template<>
std::string SQL::SelectData<std::string>(std::string fieldName, std::string whereCommand)
{
    try
    {
        Connect();
        fieldName = "SELECT " + fieldName + " FROM " + _tableName + " WHERE " + whereCommand;
        SACommand cmd(&_con, _TSA(fieldName.c_str()));
        cmd.Execute();
        while (cmd.FetchNext())
        {
            Disconnect();
            return cmd.Field(fieldName.c_str()).asString().GetMultiByteChars();
        }
        Disconnect();
        return "not able to find data";
    }
    catch (SAException &x)
    {
        std::cout << x.ErrText().GetMultiByteChars() << "\n";
        return "something went wrong";
    }
}

template <>
long SQL::SelectData<long>(std::string fieldName, std::string whereCommand)
{
    try
    {
        Connect();
        fieldName = "SELECT " + fieldName + " FROM " + _tableName + " WHERE " + whereCommand;
        SACommand cmd(&_con, _TSA(fieldName.c_str()));
        cmd.Execute();
        while (cmd.FetchNext())
        {
            Disconnect();
            return cmd.Field(fieldName.c_str()).asLong();
        }
        Disconnect();
        return -1;
    }
    catch (SAException &x)
    {
        std::cout << x.ErrText().GetMultiByteChars() << "\n";
        Disconnect();
        return -1;
    }
}

template <>
bool SQL::SelectData<bool>(std::string fieldName, std::string whereCommand)
{
    try
    {
        Connect();
        fieldName = "SELECT " + fieldName + " FROM " + _tableName + " WHERE " + whereCommand;
        SACommand cmd(&_con, _TSA(fieldName.c_str()));
        cmd.Execute();
        while (cmd.FetchNext())
        {
            Disconnect();
            return cmd.Field(fieldName.c_str()).asBool();
        }
        Disconnect();
        return false;
    }
    catch (SAException &x)
    {
        std::cout << x.ErrText().GetMultiByteChars() << "\n";
        Disconnect();
        return false;
    }
}

template <>
double SQL::SelectData<double>(std::string fieldName, std::string whereCommand)
{
    try
    {
        Connect();
        fieldName = "SELECT " + fieldName + " FROM " + _tableName + " WHERE " + whereCommand;
        SACommand cmd(&_con, _TSA(fieldName.c_str()));
        cmd.Execute();
        while (cmd.FetchNext())
        {
            Disconnect();
            return cmd.Field(fieldName.c_str()).asDouble();
        }
        Disconnect();
        return -1;
    }
    catch (SAException &x)
    {
        std::cout << x.ErrText().GetMultiByteChars() << "\n";
        Disconnect();
        return -1;
    }
}

template <>
SADateTime SQL::SelectData<SADateTime>(std::string fieldName, std::string whereCommand)
{
    try
    {
        Connect();
        std::string command = "SELECT " + fieldName + " FROM " + _tableName + " WHERE " + whereCommand;
        SACommand cmd(&_con, _TSA(command.c_str()));
        cmd.Execute();
        while (cmd.FetchNext())
        {
            Disconnect();
            return cmd.Field(fieldName.c_str()).asDateTime();
        }
        Disconnect();
        return SADateTime();
    }
    catch (SAException &x)
    {
        std::cout << x.ErrText().GetMultiByteChars() << "\n";
        Disconnect();
        return SADateTime();
    }
}

void SQL::UpdateData(std::string fieldAndValue, std::string whereCommand)
{
    try
    {
        Connect();
        std::string command = "UPDATE " + _tableName + " SET " + fieldAndValue + " WHERE " + whereCommand;
        SACommand cmd(&_con, _TSA(command.c_str()));
        cmd.Execute();
        Disconnect();
    }
    catch (SAException &x)
    {
        std::cout << x.ErrText().GetMultiByteChars() << "\n";
        Disconnect();
    }
}
