#include<iostream>
#include<fstream>
#include<string.h>
#include<iuom>
#include<uom>
#include<daoexception>
#include<iuomdao>
#include<uomdao>
#include<forward_list>
using namespace std;
using namespace inventory;
using namespace data_layer;

class Header
{
public:
int lastGeneratedCode;
int records;
};

class _UnitOfMeasurementDAO
{
private:
int code;
char title[51];
public:
void setCode(int code)
{
this->code=code;
}
int getCode()
{
return this->code;
}
void setTitle(string &title)
{
strcpy(this->title,title.c_str());
}
string getTitel()
{
return string(this->title);
}
};

void UnitOfMeasurementDAO::add(abc::IUnitOfMeasurement *unitOfMeasurement) throw(DAOException)
{
/*	
    check validations--------
	uom!=NULL;
	check title is not null
	check title does not exceeds 25 char
	code==0

	if invalid the throw/raise DAOException message

if data valid 
perform title duplicacy check (Incase sensitive)
{
skip first record

traverse through all records(loop) 
on every cycle 
compare string (Title)
}
else raise DAOException

	file banegi
	file k first block me lastGeneratedCode and numberOfRecords hoga

	file me add ka logic

	openfile "fileName" filename which is declared static
	iuomdao abstract class me dataFile ki static property bana denge

if file empty then add header +record
header me ky lastgeneratedCode  1
	and  noOfRecords 	1

open file in binary mode 
read write object 

if not empty 
{
jb record add karna hoga to new code kya 
newCode = lastGeneratedCode+1;

add record at end and update header

}

try
{
m.add(&k);

what is the allotted code (default zero mangvaya) mtlb lastGeneratedCode update karna hai

update the code in newly generated code 
in which the object which the uom pointer is pointing 

}catch(DAOException &d)
{
}


*/


fstream f;
f.open(DATA_FILE,ios::out);

f.close();

}
void UnitOfMeasurementDAO::update(abc::IUnitOfMeasurement *unitOfMeasurement) throw(DAOException)
{
}
void UnitOfMeasurementDAO::remove(int code) throw(DAOException)
{
}
abc::IUnitOfMeasurement * UnitOfMeasurementDAO::getByCode(int code) throw(DAOException)
{
return NULL;
}
abc::IUnitOfMeasurement * UnitOfMeasurementDAO::getByTitle(string title) throw(DAOException)
{
return NULL;
}
forward_list<abc::IUnitOfMeasurement *> * UnitOfMeasurementDAO::getAll() throw(DAOException)
{
/*
create a new forward list by dynamic memory allocation

traverse dataFile 
skip header 
on every cycle, create an Object of Designation(or uom)
and add to forward_list 

in the end return the reference of forward_list


how the memory of forward_list will be realeased ?
and Object of IUnitOfMeasurement ?

*/



return NULL;
}
int UnitOfMeasurementDAO::codeExists(int code) throw(DAOException)
{
return 0;
}
int UnitOfMeasurementDAO::titleExists(string title) throw(DAOException)
{
return 0;
}
int UnitOfMeasurementDAO::getCount() throw(DAOException)
{
return 0;
}

int main()
{
abc::IUnitOfMeasurementDAO *iuomdao = new UnitOfMeasurementDAO;

abc::IUnitOfMeasurement *iuom = new UnitOfMeasurement();

return 0;
}