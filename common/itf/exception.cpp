#include "common/itf/exception.h"

using namespace lb;

/// Creates a base exception for the given error \a code and exception \a
/// message.
///
/// \param code the error code to create an exception for
/// \param message the error message associated with this exception
Exception::Exception(unsigned int code, const std::string &message):
    message_(boost::lexical_cast<std::string>(code) + ": " + message)
{
}

const char *Exception::what() const
{
    return message_.c_str();
}

Exception &Exception::operator%(const std::string &argument)
{
    message_ = boost::str(boost::format(message) % argument);

    return *this;
}
