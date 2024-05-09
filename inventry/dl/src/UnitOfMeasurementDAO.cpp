#include<iostream>
#include<iuom>
#include<uom>
#include<iuomdao>
#include<uomdao>
#include<daoexception>
#include<stringutils>
#include<fstream>
#include<string.h>
#include<forward_list>
using namespace std;
using namespace inventory;
using namespace data_layer;
using namespace stringutils;

class UnitOfMeasurementDAO::Header
{
public:
int lastGeneratedCode;
int records;
};

class UnitOfMeasurementDAO::_UnitOfMeasurementDAO
{
public:
int code;
char title[51];
};

void UnitOfMeasurementDAO::add(abc::IUnitOfMeasurement *unitOfMeasurement) throw(DAOException)
{
if(unitOfMeasurement==NULL) 
{
throw DAOException("Pointer cannot be NULL");
}
const string vTitle=unitOfMeasurement->getTitle();
string title = trimmed(vTitle);
if(title.length()==0)
{
throw DAOException("Title required, length is zero");
}
if(title.length()>50)
{
throw DAOException("Title cannot exceed 50");
}

Header header;
_UnitOfMeasurementDAO _unitOfMeasurementDAO;
fstream dataFile(FILE_NAME,ios::out | ios::in | ios::binary);
if(dataFile.fail())
{
fstream dFile(FILE_NAME,ios::app | ios::binary);
header.lastGeneratedCode=1;
header.records=1;
dFile.write((char *)&header,sizeof(Header));
_unitOfMeasurementDAO.code=1;
strcpy(_unitOfMeasurementDAO.title,title.c_str());
dFile.write((char *)&_unitOfMeasurementDAO,sizeof(_UnitOfMeasurementDAO));
dFile.close();
unitOfMeasurement->setCode(1);
return;
}
dataFile.read((char *)&header,sizeof(Header));
while(1)
{
dataFile.read((char *)&_unitOfMeasurementDAO,sizeof(_UnitOfMeasurementDAO));
if(dataFile.fail()) break;
cout<<title<<" 1 "<<endl;				//delete this later
cout<<_unitOfMeasurementDAO.title<<" 2 "<<endl;		//delete this later
if(compareStringIgnoreCase(_unitOfMeasurementDAO.title,title.c_str())==0) 
{
dataFile.close();
throw DAOException(title+" Exists");
}
}
header.lastGeneratedCode++;
header.records++;
_unitOfMeasurementDAO.code=header.lastGeneratedCode;
strcpy(_unitOfMeasurementDAO.title,title.c_str());
cout<<title<<" 3 "<<endl;					//delete this later
cout<<_unitOfMeasurementDAO.title<<" 4 "<<endl;		//delete this later
dataFile.seekp(0,ios::end);
dataFile.write((char *)&_unitOfMeasurementDAO,sizeof(_UnitOfMeasurementDAO));
dataFile.seekp(0,ios::beg);
dataFile.write((char *)&header,sizeof(Header));
dataFile.close();
unitOfMeasurement->setCode(_unitOfMeasurementDAO.code);

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
create a new forward list by dynamic memory allocation .

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

