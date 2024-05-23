#include<bl/uommanager>
#include<iostream>
#include<bl/iuom>
#include<bl/uom>
using namespace inventory;
using namespace business_layer;
void IUnitOfMeasurementManager::addUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) throw(BLException)
{

//validations and then call the method to add from/in dataLayer

}
void IUnitOfMeasurementManager::updateUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) throw(BLException)
{
}
void IUnitOfMeasurementManager::removeUnitOfMeasurementByCode(int code) throw(BLException)
{
}
void IUnitOfMeasurementManager::removeUnitOfMeasurementByTitle(string &title) throw(BLException)
{
}
IUnitOfMeasurement * IUnitOfMeasurementManager::getUnitOfMeasurementByCode(int code) throw(BLException)
{
}
IUnitOfMeasurement * IUnitOfMeasurementManager::getUnitOfMeasurementByTitle(string &title) throw(BLException)
{
}
forward_list<IUnitOfMeasurement *> * IUnitOfMeasurementManager::getUnitOfMeasurements() throw(BLException)
{
}
int IUnitOfMeasurementManager::unitOfMeasurementCodeExists(int code) throw(BLException)
{
}
int IUnitOfMeasurementManager::unitOfMeasurementTitleExists(string &title) throw(BLException)
{
}
int IUnitOfMeasurementManager::getUnitOfMeasurementCount() throw(BLException)
{

}
