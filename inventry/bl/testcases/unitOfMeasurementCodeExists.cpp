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
int code;
cout<<"Enter code : ";
cin>>code;
if(uommanager.unitOfMeasurementCodeExists(code))
{
cout<<"yes"<<endl;
}
return 0;
}