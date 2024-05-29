#include<iostream>
#include<bl/iuom>
#include<bl/uom>
#include<bl/blexception>
#include<bl/iuommanager>
#include<bl/uommanager>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
UnitOfMeasurementManager uommanager;
UnitOfMeasurement uom;
uom.setTitle("kgs");
try
{
cout<<"In Progress."<<endl;
uommanager.addUnitOfMeasurement(&uom);
cout<<"Done"<<endl;
}catch(BLException blException)
{
if(blException.hasException())
{
if(blException.hasPropertyExceptions())
{
cout<<blException.getPropertyException(string("title"))<<endl;
}
if(blException.hasGenericException())
{
cout<<blException.getGenericException()<<endl;
//cout<<blException.what()<<endl;
}
}

}

return 0;
}