#include<tmsqlite>
#include<iostream>
using namespace std;
using namespace sqlite;

int main()
{
SqliteDB sqliteDB("somename.db");
try
{
string sql="insert into student values(108,'Eminem','M');";
sqliteDB.executeInsert(sql);
}catch(SQLiteDBException &sqliteException)
{
cout<<sqliteException.what()<<endl;
}
sqliteDB.close();
return 0;
}