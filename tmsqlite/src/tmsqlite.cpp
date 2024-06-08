#include<tmsqlite>
#include<iostream>
#include<string.h>
using namespace std;
using namespace sqlite;

SQLiteDBException::SQLiteDBException()
{
this->errorMessage=NULL;
}
SQLiteDBException::SQLiteDBException(const char *errorMessage)
{
this->errorMessage=errorMessage;
}
SQLiteDBException & SQLiteDBException::operator=(const char *errorMessage)
{
this->errorMessage=errorMessage;
return *this;
}
SQLiteDBException::~SQLiteDBException() throw()
{
delete this->errorMessage;
}
const char * SQLiteDBException::what() const throw()
{
return (this->errorMessage);
}

int SqliteDB::Row::hasMoreRows()
{

}
Row & SqliteDB::Row::getRow()
{
}
int SqliteDB::Row::getInt(char *)
{
}
string SqliteDB::Row::getString(char *)
{
}


SqliteDB::SqliteDB()
{
//do nothing
}
SqliteDB::SqliteDB(const string &fileName)
{
this->open(fileName);
}
void SqliteDB::operator=(const string &fileName)
{
this->open(fileName);
}
int SqliteDB::open(const string &fileName)
{
strcpy(this->file_name,fileName.c_str());
this->result=sqlite3_open(this->file_name,&(this->db));
if(result=SQLITE_OK)
{
sqlite3_errmsg(this->db);
throw SQLiteDBException(sqlite3_errmsg(this->db));
}
return 1;
}
void SqliteDB::close()
{
sqlite3_close(this->db);
}
int SqliteDB::executeInsert(const string &sql)
{
SQLiteDBException sqlException;
strcpy(this->sql,sql.c_str());
this->result=sqlite3_exec(this->db,this->sql,0,0,&(this->errorMessage));
if(result!=SQLITE_OK)
{
throw SQLiteDBException(sqlite3_errmsg(this->db));
}
return 1;
}
int SqliteDB::executeUpdate(const string &sql)
{
SQLiteDBException sqlException;
strcpy(this->sql,sql.c_str());
this->result=sqlite3_exec(this->db,this->sql,0,0,&(this->errorMessage));
if(result!=SQLITE_OK)
{
throw SQLiteDBException(sqlite3_errmsg(this->db));
}
return 1;
}
int SqliteDB::executeDelete(const string &sql)
{
SQLiteDBException sqlException;
strcpy(this->sql,sql.c_str());
this->result=sqlite3_exec(this->db,this->sql,0,0,&(this->errorMessage));
if(result!=SQLITE_OK)
{
throw SQLiteDBException(sqlite3_errmsg(this->db));
}
return 1;
}

