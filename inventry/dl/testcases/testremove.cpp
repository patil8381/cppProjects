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
int code;
cout<<"Enter code to update : ";
cin>>code;
uom->setCode(code);
try
{
uomdao->remove(code);
cout<<"Unit of Measurement deleted."<<endl;

}catch(DAOException daoexception)
{
cout<<daoexception.what()<<endl;
}
cout<<"done"<<endl;
return 0;
}