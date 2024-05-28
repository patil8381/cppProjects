#include<bl/iuom>
#include<bl/uom>
#include<iostream>
#include<bl/iuommanager>
#include<bl/uommanager>
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




}

void UnitOfMeasurementManager::DataModel::populateDataStructures()
{
forward_list<inventory::data_layer::abc::IUnitOfMeasurement *> *dlUnitOfMeasurements;
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
dlUnitOfMeasurements=unitOfMeasurementDAO.getAll();
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
forward_list<inventory::data_layer::abc::IUnitOfMeasurement *>::iterator i;
abc::IUnitOfMeasurement *blUnitOfMeasurement;
i=dlUnitOfMeasurements->begin();
inventory::data_layer::abc::IUnitOfMeasurement * dluom;
int code;
string title;
while(i!=dlUnitOfMeasurements->end())
{
dluom=*i;
blUnitOfMeasurement=new UnitOfMeasurement;
code=dluom->getCode();
title=dluom->getCode();
blUnitOfMeasurement->setCode(code);
blUnitOfMeasurement->setTitle(title);
codeWiseMap.insert(pair<int,abc::IUnitOfMeasurement *>(dluom->getCode(),blUnitOfMeasurement));
titleWiseMap.insert(pair<string *,abc::IUnitOfMeasurement *>(&title,blUnitOfMeasurement));

delete dluom;
++i;
}
delete dlUnitOfMeasurements;

}

UnitOfMeasurementManager::UnitOfMeasurementManager()
{
}
void UnitOfMeasurementManager::addUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) throw(BLException)
{
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

