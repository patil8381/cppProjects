#include<iostream>
#include<forward_list>
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
uom->setTitle(string("liter"));
try
{
//uomdao->add(uom);
//cout<<"Unit of Measurement code "<<uom->getCode()<<endl;
forward_list<abc::IUnitOfMeasurement *> *fwdList;
fwdList=uomdao->getAll();
forward_list<abc::IUnitOfMeasurement *>::iterator i;
i=fwdList->begin();
while(i!=fwdList->end())
{
cout<<"Code : "<<(*i)->getCode()<<", Title : "<<(*i)->getTitle()<<endl;
++i;
}

}catch(DAOException daoexception)
{
cout<<daoexception.what()<<endl;
}
return 0;
}