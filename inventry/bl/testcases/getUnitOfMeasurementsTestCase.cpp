#include<iostream>
#include<bl/iuom>
#include<bl/uom>
#include<bl/blexception>
#include<bl/uommanager>
#include<forward_list>
using namespace std;
using namespace inventory;
using namespace business_layer;
using namespace abc;
int main()
{
UnitOfMeasurementManager uommanager;
IUnitOfMeasurement *uom;
forward_list<IUnitOfMeasurement *> *unitOfMeasurements;
unitOfMeasurements=uommanager.getUnitOfMeasurements();

forward_list<IUnitOfMeasurement *>::iterator i=unitOfMeasurements->begin();
if(i==unitOfMeasurements->end())
{
cout<<"No records"<<endl;
}
while(i!=unitOfMeasurements->end())
{
uom=*i;
cout<<"Code : "<<uom->getCode()<<",Title : "<<uom->getTitle()<<endl;
++i;
}

return 0;
}