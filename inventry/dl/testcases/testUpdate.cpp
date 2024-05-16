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
string title;
cout<<"Enter code to update : ";
cin>>code;
uom->setCode(code);
cout<<"Enter title :";
cin>>title;
uom->setTitle(title);

try
{
uomdao->update(uom);
cout<<"Unit of Measurement Title updated : "<<uom->getCode()<<", Title : "<<uom->getTitle()<<endl;

}catch(DAOException daoexception)
{
cout<<daoexception.what()<<endl;
}
cout<<"done"<<endl;
return 0;
}