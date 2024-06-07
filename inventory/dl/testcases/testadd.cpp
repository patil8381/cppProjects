#include<iostream>
#include<dl/iuom>
#include<dl/uom>
#include<dl/iuomdao>
#include<dl/uomdao>
#include<dl/daoexception>
using namespace std;
using namespace inventory;
using namespace data_layer;

int main()
{
abc::IUnitOfMeasurementDAO *uomdao = new UnitOfMeasurementDAO;
abc::IUnitOfMeasurement *uom = new UnitOfMeasurement();
string name;
cout<<"Enter unitOfMeasurement : ";
cin>>name;
uom->setTitle(string(name));
try
{
uomdao->add(uom);
cout<<"Unit of Measurement code "<<uom->getCode()<<endl;
}catch(DAOException daoexception)
{
cout<<daoexception.what()<<endl;
}
cout<<"done"<<endl;
return 0;
}