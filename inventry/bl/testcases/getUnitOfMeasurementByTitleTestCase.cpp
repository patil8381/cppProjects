#include<iostream>
#include<bl/iuom>
#include<bl/uom>
#include<bl/blexception>
#include<bl/uommanager>
using namespace std;
using namespace inventory;
using namespace business_layer;
using namespace abc;
int main()
{
UnitOfMeasurementManager uommanager;
IUnitOfMeasurement *uom;
string title;
cout<<"Enter title : ";
cin>>title;
try
{
uom=uommanager.getUnitOfMeasurementByTitle(title);
cout<<"Code : "<<uom->getCode()<<",Title : "<<uom->getTitle()<<endl;
}catch(BLException &blException)
{
if(blException.hasException())
{
if(blException.hasGenericException())
{
cout<<blException.getGenericException()<<endl;
}
if(blException.hasPropertyException("code"))
{
cout<<blException.getPropertyException("code")<<endl;
}

}
}

return 0;
}