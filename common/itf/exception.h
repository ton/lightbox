#ifndef LB_EXCEPTION_H
#define LB_EXCEPTION_H

#include <exception>
#include <sstream>

namespace lb {

/// Base class for LightBox exceptions.
class Exception: public std::exception
{
    public:
        template<typename ErrorCode>
        Exception(ErrorCode code): code_((unsigned int)(code))
        {
            std::ostringstream ss;
            ss << "Error " << code_ << ": " << code << ".";

            message_ = ss.str();
        }

        const char *what() const throw() { return message_.c_str(); }

        /// Replace the first occurrence of an argument placeholder (%#%) in an exception
        /// message with the given argument, where the # represents a number to be able
        /// to order multiple arguments in the exception message.
        template<typename T>
        Exception operator %(const T &argument)
        {
            // Search all argument placeholders, and remember the location of the
            // argument placeholder with the smallest associated index.
            std::string::size_type placeHolderPos = message_.find('%');

            unsigned int minimumPlaceHolderIndex = 0;
            std::string::size_type minimumPlaceHolderPos = std::string::npos;

            while (placeHolderPos != std::string::npos)
            {
                std::stringstream ss(message_.substr(placeHolderPos + 1));

                unsigned int placeHolderIndex = 0;
                ss >> std::noskipws >> placeHolderIndex;

                char c;
                ss >> std::noskipws >> c;

                // In case a valid placeholder was found, check whether it is the
                // placeholder with the lowest index yet.
                if (ss.good() && c == '%')
                {
                    if (placeHolderIndex < minimumPlaceHolderIndex || minimumPlaceHolderPos == std::string::npos)
                    {
                        minimumPlaceHolderIndex = placeHolderIndex;
                        minimumPlaceHolderPos = placeHolderPos;
                    }

                    // Advance over the current placeholder token.
                    placeHolderPos = message_.find('%', placeHolderPos + 1 + ss.tellg());
                }
                else
                {
                    // The percentage character did not belong to a placeholder token,
                    // skip over it.
                    placeHolderPos = message_.find('%', placeHolderPos + 1);
                }
            }

            // In case a valid minimum place holder was found, replace it with the given
            // argument.
            if (minimumPlaceHolderPos != std::string::npos)
            {
                // Replace the placeholder token with the argument.
                std::ostringstream ss;
                ss << argument;

                // Calculate the length of the placeholder token.
                size_t placeHolderLength = message_.find('%', minimumPlaceHolderPos + 1) - minimumPlaceHolderPos + 1;

                // Replace the placeholder with the textual representation of
                // the given argument.
                message_.replace(minimumPlaceHolderPos, placeHolderLength, ss.str());
            }

            return *this;
        }

    private:
        /// Error code associated with this exception.
        unsigned int code_;
        /// Error message associated with this exception.
        std::string message_;
};

/// Base class for runtime exceptions.
class RuntimeException: public Exception
{
    public:
        /// Creates a runtime exception for the given error \a code and
        /// exception \a message.
        template<typename ErrorCode>
        RuntimeException(ErrorCode code): Exception(code) { }

        // See Exception::operator %().
        template<typename T>
        RuntimeException operator %(const T &argument) { return RuntimeException(Exception::operator %(argument)); }
};

/// Base class for parse exceptions.
class ParseException: public Exception
{
    public:
        /// Creates a parse exception for the given error \a code and exception
        /// \a message.
        template<typename ErrorCode>
        ParseException(ErrorCode code): Exception(code) { }

        // See Exception::operator %().
        template<typename T>
        ParseException operator %(const T &argument) { return ParseException(Exception::operator %(argument)); }
};

}

#endif
