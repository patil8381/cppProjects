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
uom->setTitle(string("Gram"));
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