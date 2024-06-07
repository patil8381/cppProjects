#include<dl/daoexception>
#include<string.h>
using namespace inventory;
using namespace data_layer;
DAOException::DAOException()
{
this->message="";
}
DAOException::DAOException(string message)
{
this->message=message;
}
DAOException::DAOException(const DAOException &other)
{
this->message=other.message;
}
DAOException::~DAOException() throw()
{
//do nothing
}
DAOException & DAOException::operator=(const DAOException &other)
{
this->message=other.message;
return *this;
}
DAOException & DAOException::operator=(const char *message)
{
this->message=message;
return *this;
}
const char * DAOException::what() const throw()
{
return this->message.c_str();
}

