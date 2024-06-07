#include<bl/iuom>
#include<bl/uom>
#include<iostream>
#include<bl/iuommanager>
#include<bl/uommanager>
#include<bl/blexception>
#include<common/stringutils>
#include<dl/iuom>
#include<dl/uom>
#include<dl/daoexception>
#include<dl/iuomdao>
#include<dl/uomdao>
#include<forward_list>
#include<map>
using namespace inventory;
using namespace business_layer;
using namespace stringutils;

bool UnitOfMeasurementTitleComparator::operator()(string *left,string *right)
{
return (*left)<(*right);
}

UnitOfMeasurementManager::DataModel UnitOfMeasurementManager::dataModel;

UnitOfMeasurementManager::DataModel::DataModel()
{
populateDataStructures();
}

UnitOfMeasurementManager::DataModel::~DataModel()
{

/*
iterate any one map and release all bl UnitOfMeasurement objects
clear both maps.
*/


map<string *,_UnitOfMeasurement *>::iterator i;
_UnitOfMeasurement *blUnitOfMeasurement;
string *t;
i=dataModel.titleWiseMap.begin();
while(i!=dataModel.titleWiseMap.end())
{
blUnitOfMeasurement=i->second;
delete blUnitOfMeasurement->title;
delete blUnitOfMeasurement;
++i;
}
//cout<<"Destructor invoked, Releasing Dynamically allocated Memory"<<endl;
}

void UnitOfMeasurementManager::DataModel::populateDataStructures()
{
forward_list<inventory::data_layer::abc::IUnitOfMeasurement *> *dlUnitOfMeasurements;
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
try
{
dlUnitOfMeasurements=unitOfMeasurementDAO.getAll();

inventory::data_layer::abc::IUnitOfMeasurement *dlUnitOfMeasurement;
_UnitOfMeasurement *blUnitOfMeasurement;
forward_list<inventory::data_layer::abc::IUnitOfMeasurement *>::iterator i;
int code;
string *title;
for(i=dlUnitOfMeasurements->begin();i!=dlUnitOfMeasurements->end();++i)
{
dlUnitOfMeasurement=*i;
code=dlUnitOfMeasurement->getCode();
title=new string(dlUnitOfMeasurement->getTitle());
blUnitOfMeasurement=new _UnitOfMeasurement;
blUnitOfMeasurement->code=code;
blUnitOfMeasurement->title=title;
dataModel.codeWiseMap.insert(pair<int,_UnitOfMeasurement *>(dlUnitOfMeasurement->getCode(),blUnitOfMeasurement));
dataModel.titleWiseMap.insert(pair<string *,_UnitOfMeasurement *>(blUnitOfMeasurement->title,blUnitOfMeasurement));
delete dlUnitOfMeasurement;	//releasing each object
}
dlUnitOfMeasurements->clear();
delete dlUnitOfMeasurements;	// releasing forward_list 
}catch(inventory::data_layer::DAOException &daoException)
{
//do nothing 
}

/*
1) iterate the dlUnitOfMeasurements forward_list
2) On every iterator create an object of bl UnitOfMeasurements
3) Set Code and Title by picking up from dl UnitOfMeasurement
4) insert the address of bl UnitOfMeasurement in the 2 defined maps
	Note: in one map key will be whatever getCode returns
		in another map key will be the address of whatever getTitle returns
5) Free the dlUnitOfMeasurement ( inside the iteration of loop itself)
6) After the loop ends, free the forward_list object.
*/

}

UnitOfMeasurementManager::UnitOfMeasurementManager()
{
// do nothing for now.
}
void UnitOfMeasurementManager::addUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) throw(BLException)
{
BLException blException;
if(unitOfMeasurement==NULL) 
{
blException.setGenericException("Unit Of Measurement required, NULL encountered");
throw blException;
}
int code=unitOfMeasurement->getCode();
string title=unitOfMeasurement->getTitle();
if(code!=0)
{
blException.addPropertyException("code","code should be zero");
}
if(title.length()==0)
{
blException.addPropertyException("title","title required");
}
if(title.length()>50)
{
blException.addPropertyException("title","title cannot exceed 50 characters");
}
if(blException.hasException())
{
throw blException;
}
map<string *,_UnitOfMeasurement *>::iterator i;
i=dataModel.titleWiseMap.find(&title);
if(i!=dataModel.titleWiseMap.end())
{
blException.addPropertyException("title","Given title exists");
throw blException;
}
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
try
{
inventory::data_layer::abc::IUnitOfMeasurement *dlUnitOfMeasurement;
dlUnitOfMeasurement=new inventory::data_layer::UnitOfMeasurement;
dlUnitOfMeasurement->setCode(0);
dlUnitOfMeasurement->setTitle(title);
unitOfMeasurementDAO.add(dlUnitOfMeasurement);
unitOfMeasurement->setCode(dlUnitOfMeasurement->getCode());
delete dlUnitOfMeasurement;
string *t=new string(title);
_UnitOfMeasurement *blUnitOfMeasurement;
blUnitOfMeasurement=new _UnitOfMeasurement;
blUnitOfMeasurement->code=code;
blUnitOfMeasurement->title=t;
dataModel.codeWiseMap.insert(pair<int,_UnitOfMeasurement *>(dlUnitOfMeasurement->getCode(),blUnitOfMeasurement));
dataModel.titleWiseMap.insert(pair<string *,_UnitOfMeasurement *>(t,blUnitOfMeasurement));
}catch(inventory::data_layer::DAOException daoException)
{
BLException blException;
blException.setGenericException(daoException.what());
throw blException;
}

}
void UnitOfMeasurementManager::updateUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) throw(BLException)
{
BLException blException;
if(unitOfMeasurement==NULL) 
{
blException.setGenericException("Unit Of Measurement required, NULL encountered");
throw blException;
}
int code=unitOfMeasurement->getCode();
string title=unitOfMeasurement->getTitle();
if(code<=0)
{
blException.addPropertyException("code","Invalid code");
}
if(title.length()==0)
{
blException.addPropertyException("title","title required");
}
if(title.length()>50)
{
blException.addPropertyException("title","title cannot exceed 50 characters");
}
if(blException.hasException())
{
throw blException;
}
int found=0;
map<int,_UnitOfMeasurement *>::iterator i;
i=dataModel.codeWiseMap.find(code);
if(i!=dataModel.codeWiseMap.end() && *(i->second->title)==title) //if(compareStringIgnoreCase(title.c_str(),unitOfMeasurement->getTitle().c_str())==0)
{
found=1;
}
else
{
blException.setGenericException("No such Unit Of Measurement exists");
throw blException;
}
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
try
{
inventory::data_layer::abc::IUnitOfMeasurement *dlUnitOfMeasurement;
dlUnitOfMeasurement=new inventory::data_layer::UnitOfMeasurement;
dlUnitOfMeasurement->setCode(code);
dlUnitOfMeasurement->setTitle(title);
unitOfMeasurementDAO.update(dlUnitOfMeasurement);

delete dlUnitOfMeasurement;

string *t=new string(title);
_UnitOfMeasurement *blUnitOfMeasurement;
blUnitOfMeasurement=i->second;
blUnitOfMeasurement->code=code;
blUnitOfMeasurement->title=t;
map<string *,_UnitOfMeasurement *>::iterator j=dataModel.titleWiseMap.find(&title);
t=j->first;
dataModel.titleWiseMap.erase(t);
dataModel.titleWiseMap.insert(pair<string *,_UnitOfMeasurement *>(t,blUnitOfMeasurement));

}catch(inventory::data_layer::DAOException daoException)
{
BLException blException;
blException.setGenericException(daoException.what());
throw blException;
}
}
void UnitOfMeasurementManager::removeUnitOfMeasurementByCode(int code) throw(BLException)
{
BLException blException;
if(code<=0)
{
blException.setGenericException("Invalid code.");
}
if(blException.hasException())
{
throw blException;
}
map<int ,_UnitOfMeasurement *>::iterator i;
i=dataModel.codeWiseMap.find(code);
if(i==dataModel.codeWiseMap.end())
{
blException.setGenericException("Invalid code.No such Unit of Measurement.");
throw blException;
}
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
try
{
unitOfMeasurementDAO.remove(code);

_UnitOfMeasurement *blUnitOfMeasurement;
map<int,_UnitOfMeasurement *>::iterator i=dataModel.codeWiseMap.find(code);
blUnitOfMeasurement=i->second;
dataModel.codeWiseMap.erase(code);
string *t=blUnitOfMeasurement->title;
map<string *,_UnitOfMeasurement *>::iterator j=dataModel.titleWiseMap.find(t);
dataModel.titleWiseMap.erase(t);
}catch(inventory::data_layer::DAOException daoException)
{
BLException blException;
blException.setGenericException(daoException.what());
throw blException;
}
}
void UnitOfMeasurementManager::removeUnitOfMeasurementByTitle(string &title) throw(BLException)
{
BLException blException;
string vTitle=trimmed(title);
if(vTitle.length()<=0)
{
blException.setGenericException("Invalid title.title length cannot be zero.");
}
if(vTitle.length()>50)
{
blException.setGenericException("Invalid title.title length cannot exceed 50 characters.");
}
if(blException.hasException())
{
throw blException;
}
map<string *,_UnitOfMeasurement *>::iterator i;
string *t=&vTitle;
i=dataModel.titleWiseMap.find(t);
if(i==dataModel.titleWiseMap.end())
{
blException.addPropertyException("title","Invalid title.No such Unit of Measurement.");
throw blException;
}
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
try
{
map<string *,_UnitOfMeasurement *,UnitOfMeasurementTitleComparator>::iterator i=dataModel.titleWiseMap.find(&vTitle);
if(i==dataModel.titleWiseMap.end())
{
blException.addPropertyException("title","No such Unit of Measurement.");
throw blException;
}
_UnitOfMeasurement *blUnitOfMeasurement;
blUnitOfMeasurement=i->second;
int code=blUnitOfMeasurement->code;
t=blUnitOfMeasurement->title;
unitOfMeasurementDAO.remove(code);
dataModel.codeWiseMap.erase(code);
dataModel.titleWiseMap.erase(t);
}catch(inventory::data_layer::DAOException daoException)
{
BLException blException;
blException.setGenericException(daoException.what());
throw blException;
}
}
abc::IUnitOfMeasurement * UnitOfMeasurementManager::getUnitOfMeasurementByCode(int code) throw(BLException)
{
BLException blException;
if(code<=0)
{
blException.setGenericException("Invalid code.");
}
if(blException.hasException())
{
throw blException;
}
map<int ,_UnitOfMeasurement *>::iterator i;
i=dataModel.codeWiseMap.find(code);
if(i==dataModel.codeWiseMap.end())
{
blException.setGenericException("Invalid code.No such Unit of Measurement.");
throw blException;
}
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
try
{
_UnitOfMeasurement *blUnitOfMeasurement;
blUnitOfMeasurement=i->second;
abc::IUnitOfMeasurement *unitOfMeasurement;
unitOfMeasurement=new UnitOfMeasurement;
int code=blUnitOfMeasurement->code;
string *t=new string(*(blUnitOfMeasurement->title));
unitOfMeasurement->setCode(code);
unitOfMeasurement->setTitle(*t);
return unitOfMeasurement;
}catch(inventory::data_layer::DAOException daoException)
{
BLException blException;
blException.setGenericException(daoException.what());
throw blException;
}
}
abc::IUnitOfMeasurement * UnitOfMeasurementManager::getUnitOfMeasurementByTitle(string &title) throw(BLException)
{
BLException blException;
string vTitle=trimmed(title);
if(vTitle.length()<=0)
{
blException.addPropertyException("title","Invalid title.Title length cannot be zero.");
}
if(vTitle.length()>50)
{
blException.addPropertyException("title","Invalid title.Title length cannot exceed 50 characters.");
}
if(blException.hasException())
{
throw blException;
}
string *t = new string(vTitle);
map<string *,_UnitOfMeasurement *,UnitOfMeasurementTitleComparator>::iterator i;
i=dataModel.titleWiseMap.begin();
_UnitOfMeasurement *bluom;
while(i!=dataModel.titleWiseMap.end())
{
bluom=i->second;
++i;
}

i=dataModel.titleWiseMap.find(&vTitle);
if(i==dataModel.titleWiseMap.end())
{
blException.addPropertyException("title","Invalid title.No such Unit of Measurement.");
throw blException;
}
try
{
_UnitOfMeasurement *blUnitOfMeasurement;
blUnitOfMeasurement=i->second;
abc::IUnitOfMeasurement *unitOfMeasurement;
unitOfMeasurement=new UnitOfMeasurement;
int code=blUnitOfMeasurement->code;
t=new string(*(blUnitOfMeasurement->title));
unitOfMeasurement->setCode(code);
unitOfMeasurement->setTitle(*t);
return unitOfMeasurement;
}catch(inventory::data_layer::DAOException daoException)
{
BLException blException;
blException.setGenericException(daoException.what());
throw blException;
}

}
forward_list<abc::IUnitOfMeasurement *> * UnitOfMeasurementManager::getUnitOfMeasurements() throw(BLException)
{
map<string *,_UnitOfMeasurement *>::iterator i=dataModel.titleWiseMap.begin();
_UnitOfMeasurement *_unitOfMeasurement;
abc::IUnitOfMeasurement *blUnitOfMeasurement;
forward_list<abc::IUnitOfMeasurement *> *unitOfMeasurements;
unitOfMeasurements=new forward_list<abc::IUnitOfMeasurement *>;
forward_list<abc::IUnitOfMeasurement *>::iterator listi=unitOfMeasurements->before_begin();
while(i!=dataModel.titleWiseMap.end())
{
_unitOfMeasurement=i->second;
blUnitOfMeasurement=new UnitOfMeasurement;
blUnitOfMeasurement->setCode(_unitOfMeasurement->code);
blUnitOfMeasurement->setTitle(*(_unitOfMeasurement->title));
listi=unitOfMeasurements->insert_after(listi,blUnitOfMeasurement);
++i;
}
return unitOfMeasurements;
}
int UnitOfMeasurementManager::unitOfMeasurementCodeExists(int code) throw(BLException)
{
if(code<=0)
{
return 0;
}
map<int ,_UnitOfMeasurement *>::iterator i;
i=dataModel.codeWiseMap.find(code);
if(i!=dataModel.codeWiseMap.end())
{
return 1;
}
else return 0;
}
int UnitOfMeasurementManager::unitOfMeasurementTitleExists(string &title) throw(BLException)
{
string vTitle=trimmed(title);
if(vTitle.length()<=0)
{
return 0;
}
if(vTitle.length()>50)
{
return 0;
}
map<string *,_UnitOfMeasurement *,UnitOfMeasurementTitleComparator>::iterator i;
i=dataModel.titleWiseMap.find(&vTitle);

if(i!=dataModel.titleWiseMap.end())
{
return 1;
}
else return 0;
}
int UnitOfMeasurementManager::getUnitOfMeasurementCount() throw(BLException)
{
int count=0;
map<int,_UnitOfMeasurement *>::iterator i=dataModel.codeWiseMap.begin();
while(i!=dataModel.codeWiseMap.end())
{
count++;
++i;
}
return count;
}

