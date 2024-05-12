#include<iostream>
#include<iuom>
#include<uom>
#include<iuomdao>
#include<uomdao>
#include<daoexception>
using namespace std;
using namespace inventory;
using namespace data_layer;

int main()
{
abc::IUnitOfMeasurementDAO *uomdao = new UnitOfMeasurementDAO;
abc::IUnitOfMeasurement *uom = new UnitOfMeasurement();
uom->setTitle(string("KG"));
try
{
int code;
cout<<"Enter code : ";
cin>>code;
uom=uomdao->getByCode(code);
cout<<"Code : "<<uom->getCode()<<", Title : "<<uom->getTitle()<<endl;
}catch(DAOException daoexception)
{
cout<<daoexception.what()<<endl;
}
return 0;
}