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
return compareStringIgnoreCase(left->c_str(),right->c_str());
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

//dataModel.codeWiseMap.insert(pair<int,IUnitOfMeasurement *>(dlUnitOfMeasurements->getCode(),&blUnitOfMeasurement));
//map<string *,abc::IUnitOfMeasurement *> titleWiseMap;
/*
map<int,abc::IUnitOfMeasurement *>::iterator i;
i=dataModel.codeWiseMap.begin();
while(i!=dataModel.codeWiseMap.end())
{
delete i->second;
++i;
}
*/
}

void UnitOfMeasurementManager::DataModel::populateDataStructures()
{
forward_list<inventory::data_layer::abc::IUnitOfMeasurement *> *dlUnitOfMeasurements;
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
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

codeWiseMap.insert(pair<int,_UnitOfMeasurement *>(dlUnitOfMeasurement->getCode(),blUnitOfMeasurement));
titleWiseMap.insert(pair<string *,_UnitOfMeasurement *>(title,blUnitOfMeasurement));

delete dlUnitOfMeasurement;	//releasing each object
}
dlUnitOfMeasurements->clear();
delete dlUnitOfMeasurements;	// releasing forward_list 

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
blException.addPropertyException("title","titlle required");
}
if(title.length()>50)
{
blException.addPropertyException("title","titlle cannot exceed 50 characters");
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
}
void UnitOfMeasurementManager::removeUnitOfMeasurementByCode(int code) throw(BLException)
{
}
void UnitOfMeasurementManager::removeUnitOfMeasurementByTitle(string &title) throw(BLException)
{
}
abc::IUnitOfMeasurement * UnitOfMeasurementManager::getUnitOfMeasurementByCode(int code) throw(BLException)
{
}
abc::IUnitOfMeasurement * UnitOfMeasurementManager::getUnitOfMeasurementByTitle(string &title) throw(BLException)
{
}
forward_list<abc::IUnitOfMeasurement *> * UnitOfMeasurementManager::getUnitOfMeasurements() throw(BLException)
{
}
int UnitOfMeasurementManager::unitOfMeasurementCodeExists(int code) throw(BLException)
{
}
int UnitOfMeasurementManager::unitOfMeasurementTitleExists(string &title) throw(BLException)
{
}
int UnitOfMeasurementManager::getUnitOfMeasurementCount() throw(BLException)
{
}

