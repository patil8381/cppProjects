#include<blexception>
#include<string.h>
using namespace inventory;
using namespace business_layer;
BLException::BLException()
{
this->genericException="";
}
BLException::BLException(string genericException)
{
this->genericException=genericException;
}
BLException::BLException(const BLException &other)
{
this->genericException=other.genericException;
}
BLException::~BLException() throw()
{
//do nothing
}
BLException & BLException::operator=(const BLException &other)
{
this->genericException=other.genericException;
return *this;
}
BLException & BLException::operator=(const char *genericException)
{
this->genericException=genericException;
return *this;
}
const char * BLException::what() const throw()
{
return this->genericException.c_str();
}



