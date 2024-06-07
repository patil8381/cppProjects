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
string title;
cout<<"Enter title : ";
cin>>title;
if(uommanager.unitOfMeasurementTitleExists(title))
{
cout<<"yes"<<endl;
}
return 0;
}