#ifndef LB_EXCEPTION_H
#define LB_EXCEPTION_H

#include <exception>

namespace lb {

/// Base class for LightBox exceptions.
class Exception: public std::exception
{
    public:
        Exception(unsigned int code, const std::string &message);

        const char *what() const;

        Exception &operator%(const std::string &argument);

    private:
        /// Error message associated with the exception.
        std::string message_;
}

/// Base class for runtime exceptions.
class RuntimeException: public std::exception
{
    public:
        /// Creates a runtime exception for the given error \a code and
        /// exception \a message.
        ///
        /// \param code the error code to create a runtime exception for
        /// \param message the error message associated with this runtime
        ///     exception
        RuntimeException(unsigned int code, const std::string &message): Exception(code, message);
};

}

#endif
