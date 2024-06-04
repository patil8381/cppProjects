#include<stdio.h>
#include<iostream>
#include<dl/iuom>
#include<dl/uom>
#include<dl/iuomdao>
#include<dl/uomdao>
#include<dl/daoexception>
#include<common/stringutils>
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
if(unitOfMeasurement->getCode()<=0) 
{
throw DAOException(string("unitOfMeasurement code cannot be 0 or less."));
}
string title=trimmed(unitOfMeasurement->getTitle());
if(title=="") throw DAOException(string ("Invalid unitOfMeasurement."));
Header header;
fstream dataFile(FILE_NAME,ios::in | ios::out | ios::binary);
if(dataFile.fail()) throw DAOException(string("Invalid UnitOfMeasurement."));
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail()) 
{
dataFile.close();
throw DAOException(string("Invalid UnitOfMeasurement."));
}
if(header.records==0)
{
dataFile.close();
throw DAOException(string("Invalid UnitOfMeasurement."));
}
_UnitOfMeasurement _unitOfMeasurement;
int pos=dataFile.tellg();
int found=0;
//loop to search if uom exists or not.
while(1)
{
pos=dataFile.tellg();
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(_unitOfMeasurement.code==unitOfMeasurement->getCode())
{
if(compareStringIgnoreCase(_unitOfMeasurement.title,unitOfMeasurement->getTitle().c_str())==0)
{
found=1;
break;
}
}
}
if(found==0)
{
dataFile.close();
throw DAOException(string("Invalid UnitOfMeasurement."));
}
cout<<"Current code : "<<unitOfMeasurement->getCode()<<", Title : "<<unitOfMeasurement->getTitle()<<endl;
cout<<"Enter new title : ";
cin>>title;
title=trimmed(title);
if(title.length()<=0 || title.length()>50) 
{
dataFile.close();
throw DAOException(string("Invalid UnitOfMeasurement."));
}
dataFile.seekg(8,ios::beg);
while(1)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_unitOfMeasurement.title,title.c_str())==0)
{
dataFile.close();
throw DAOException(string("Invalid UnitOfMeasurement. Same title already exists."));
}
}
unitOfMeasurement->setTitle(title);
_unitOfMeasurement.code=unitOfMeasurement->getCode();
strcpy(_unitOfMeasurement.title,title.c_str());
cout<<"writing at pos : "<<pos<<endl;
dataFile.clear();
dataFile.seekp(pos,ios::beg);
cout<<"writing at pos : "<<pos<<endl;
dataFile.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) 
{
dataFile.close();
cout<<"Size of UnitOfMeasurement : "<<sizeof(UnitOfMeasurement)<<endl;
cout<<"Size of _UnitOfMeasurement : "<<sizeof(_UnitOfMeasurement)<<endl;
cout<<"Size of _unitOfMeasurement : "<<sizeof(_unitOfMeasurement)<<endl;
throw DAOException(string("Invalid UnitOfMeasurement."));
}
}
void UnitOfMeasurementDAO::remove(int code) throw(DAOException)
{
if(code<=0)
{
throw DAOException(string("code cannot be less than zero"));
}
Header header;
char arr[101];
fstream dataFile(FILE_NAME,ios::in | ios::out | ios::binary);
if(dataFile.fail()) 
{
sprintf(arr,"Invalid Code : %d",code);
throw DAOException(string(arr));
}
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
sprintf(arr,"Invalid Code : %d",code);
throw DAOException(string(arr));
}
if(header.records==0)
{
dataFile.close();
sprintf(arr,"Invalid Code : %d",code);
throw DAOException(string(arr));
}
_UnitOfMeasurement _unitOfMeasurement;
int found=0;
while(1)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(_unitOfMeasurement.code==code)
{
found=1;
break;
}
}
if(found==0)
{
dataFile.close();
sprintf(arr,"Invalid Code : %d",code);
throw DAOException(string(arr));
}
dataFile.clear();
header.records--;
dataFile.seekg(sizeof(Header),ios::beg);
ofstream tmpFile("tmp.tmp",ios::out | ios::binary);
tmpFile.write((char *)&header,sizeof(Header));
while(1)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(_unitOfMeasurement.code!=code) 
{
tmpFile.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
}
}
dataFile.close();
tmpFile.close();
ifstream tmpF("tmp.tmp",ios::in | ios::binary);
ofstream dataF(FILE_NAME,ios::out | ios::binary);
tmpF.read((char *)&header,sizeof(Header));
dataF.write((char *)&header,sizeof(Header));
while(1)
{
tmpF.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(tmpF.fail()) break;
dataF.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
}
dataF.close();
tmpF.close();
tmpFile.open("tmp.tmp");
tmpFile.close();
}
abc::IUnitOfMeasurement * UnitOfMeasurementDAO::getByCode(int code) throw(DAOException)
{
UnitOfMeasurementDAO *unitOfMeasurementDAO;
if(unitOfMeasurementDAO->codeExists(code)==0) 
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
}
abc::IUnitOfMeasurement * UnitOfMeasurementDAO::getByTitle(string title) throw(DAOException)
{
UnitOfMeasurementDAO *unitOfMeasurementDAO;
if(unitOfMeasurementDAO->titleExists(title)==0) 
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
iuom->setTitle(string(_unitOfMeasurement.title));
i=f_list->insert_after(i,iuom);
}

return f_list;
}
int UnitOfMeasurementDAO::codeExists(int code) throw(DAOException)
{
fstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
return 0;
}
Header header;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
return 0;
}
if(header.records==0)
{
dataFile.close();
return 0;
}
_UnitOfMeasurement _unitOfMeasurement;
while(1)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(_unitOfMeasurement.code==code) return 1;
}
dataFile.close();
return 0;
}
int UnitOfMeasurementDAO::titleExists(string title) throw(DAOException)
{
fstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
return 0;
}
Header header;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
return 0;
}
if(header.records==0)
{
dataFile.close();
return 0;
}
_UnitOfMeasurement _unitOfMeasurement;
while(1)
{
dataFile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_unitOfMeasurement.title,title.c_str())==0) return 1;
}
dataFile.close();
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
