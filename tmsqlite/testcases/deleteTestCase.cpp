#include<tmsqlite>
#include<iostream>
using namespace std;
using namespace sqlite;

int main()
{
SqliteDB sqliteDB("somename.db");
try
{
string sql="delete from student where roll_number=102;";
sqliteDB.executeInsert(sql);
}catch(SQLiteDBException &sqliteException)
{
cout<<sqliteException.what()<<endl;
}
sqliteDB.close();
return 0;
}