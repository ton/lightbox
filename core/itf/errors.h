#ifndef LB_ERRORS_H
#define LB_ERRORS_H

namespace lb {

/// Define all error codes that may occur in the core component of LightBox.
/// @{
enum class ErrorCode
{
    OBJ_READER_INVALID_TOKEN = 100001,
};
/// @}

/// Converts an error code to an error message.
std::ostream &operator <<(std::ostream &out, ErrorCode errorCode)
{
    switch (errorCode)
    {
        case ErrorCode::OBJ_READER_INVALID_TOKEN:
            out << "OBJ reader encoutered invalid token '%1%' on line '%2%'";
            break;
    }

    return out;
}

}

#endif
