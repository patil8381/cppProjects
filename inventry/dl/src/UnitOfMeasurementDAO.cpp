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
class UnitOfMeasurementDAO::_UnitOfMeasurement
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
_UnitOfMeasurement _unitOfMeasurement;
fstream dataFile(FILE_NAME,ios::out | ios::in | ios::binary);
if(dataFile.fail())
{
fstream dFile(FILE_NAME,ios::app | ios::binary);
header.lastGeneratedCode=1;
header.records=1;
dFile.write((char *)&header,sizeof(Header));
_unitOfMeasurement.code=1;
strcpy(_unitOfMeasurement.title,title.c_str());
dFile.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
dFile.close();
unitOfMeasurement->setCode(1);
return;
}
dataFile.read((char *)&header,sizeof(Header));
while(1)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_unitOfMeasurement.title,title.c_str())==0) 
{
dataFile.close();
throw DAOException(title+" Exists");
}
}
dataFile.clear();
header.lastGeneratedCode++;
header.records++;
_unitOfMeasurement.code=header.lastGeneratedCode;
strcpy(_unitOfMeasurement.title,title.c_str());
dataFile.seekp(0,ios::end);
dataFile.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
dataFile.seekp(0,ios::beg);
dataFile.write((char *)&header,sizeof(Header));
dataFile.close();
unitOfMeasurement->setCode(_unitOfMeasurement.code);
}
void UnitOfMeasurementDAO::update(abc::IUnitOfMeasurement *unitOfMeasurement) throw(DAOException)
{
}
void UnitOfMeasurementDAO::remove(int code) throw(DAOException)
{
}
abc::IUnitOfMeasurement * UnitOfMeasurementDAO::getByCode(int code) throw(DAOException)
{
fstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
dataFile.close();
throw DAOException(string("File is Empty"));
}
Header header;
_UnitOfMeasurement _unitOfMeasurement;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException(string("File is Empty"));
}
if(header.records==0)
{
dataFile.close();
throw DAOException(string("File is Empty"));
}
abc::IUnitOfMeasurement *iuom;
while(1)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(_unitOfMeasurement.code==code) 
{
iuom=new UnitOfMeasurement;
iuom->setCode(_unitOfMeasurement.code);
iuom->setTitle(string(_unitOfMeasurement.title));
dataFile.close();
return iuom;
}
}
throw DAOException("Code in Unit of Measurement not exist.");
}
abc::IUnitOfMeasurement * UnitOfMeasurementDAO::getByTitle(string title) throw(DAOException)
{
Header header;
fstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
dataFile.close();
throw DAOException(string("File not exist."));
}
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException(string("File not exist."));
}
if(header.records==0)
{
dataFile.close();
throw DAOException(string("No UnitOfMeasurement data available."));
}
_UnitOfMeasurement _unitOfMeasurement;
abc::IUnitOfMeasurement *iuom;
while(1)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_unitOfMeasurement.title,title.c_str())==0) 
{
iuom=new UnitOfMeasurement;
iuom->setCode(_unitOfMeasurement.code);
iuom->setTitle(string(_unitOfMeasurement.title));
return iuom;
}
}
throw DAOException(string("No such title in Unit Of Measurement."));
}
forward_list<abc::IUnitOfMeasurement *> * UnitOfMeasurementDAO::getAll() throw(DAOException)
{
fstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
throw DAOException(string("File is Empty"));
}
Header header;
_UnitOfMeasurement _unitOfMeasurement;
forward_list<abc::IUnitOfMeasurement *> *f_list=new forward_list<abc::IUnitOfMeasurement *>;
forward_list<abc::IUnitOfMeasurement *>::iterator i=f_list->before_begin();
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
throw DAOException(string("File is Empty"));
}
if(header.records==0)
{
throw DAOException(string("File is Empty"));
}
abc::IUnitOfMeasurement *iuom;
while(1)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
iuom=new UnitOfMeasurement;
iuom->setCode(_unitOfMeasurement.code);
iuom->setTitle(_unitOfMeasurement.title);
i=f_list->insert_after(i,iuom);
}

return f_list;
}
int UnitOfMeasurementDAO::codeExists(int code) throw(DAOException)
{
fstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
throw DAOException(string("File is Empty"));
}
Header header;
_UnitOfMeasurement _unitOfMeasurement;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
throw DAOException(string("File is Empty"));
}
if(header.records==0)
{
throw DAOException(string("File is Empty"));
}
while(1)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(_unitOfMeasurement.code==code) return 1;
}
return 0;
}
int UnitOfMeasurementDAO::titleExists(string title) throw(DAOException)
{
return 0;
}
int UnitOfMeasurementDAO::getCount() throw(DAOException)
{
Header header;
fstream dataFile(FILE_NAME,ios::in | ios::binary);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
return 0;
}
if(header.records==0)
{
return 0;
}
return header.records;
}
