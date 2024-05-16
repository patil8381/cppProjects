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
try
{
string title;
cout<<"Enter title : ";
cin>>title;
int exists;
if(uomdao->titleExists(title)) 
{
cout<<title<<" title exists in Unit Of Measurement."<<endl;
return 0;
}
cout<<title <<" in Unit of Measurement does not exists."<<endl;
}catch(DAOException daoexception)
{
cout<<daoexception.what()<<endl;
}
cout<<"done"<<endl;
return 0;
}