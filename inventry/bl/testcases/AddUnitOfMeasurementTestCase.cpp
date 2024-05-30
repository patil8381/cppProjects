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
uom.setCode(0);
string title;
cout<<"Enter title : ";
cin>>title;
uom.setTitle(title);
try
{
uommanager.addUnitOfMeasurement(&uom);
}catch(BLException blException)
{
cout<<"Some problem"<<endl;
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