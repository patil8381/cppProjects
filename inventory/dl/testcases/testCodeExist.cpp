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
try
{
int code;
cout<<"Enter code : ";
cin>>code;
int exists;
if(uomdao->codeExists(code)) 
{
cout<<"Code "<<code<<" exists in Unit Of Measurement."<<endl;
return 0;
}
cout<<"Unit of Measurement with code "<<code<<" does not exists."<<endl;
}catch(DAOException daoexception)
{
cout<<daoexception.what()<<endl;
}
cout<<"done"<<endl;
return 0;
}