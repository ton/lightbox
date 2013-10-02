#ifndef LB_UI_ERROR_H
#define LB_UI_ERROR_H

#include <ostream>

namespace lb {
namespace ui {

enum ErrorCode
{
    SDL_ERROR_INITIALIZING_TTF_SUBSYSTEM = 100000,
};

std::ostream &operator<<(std::ostream &out, ErrorCode e)
{
    switch (e)
    {
        case SDL_ERROR_INITIALIZING_TTF_SUBSYSTEM:
            out << "Error initializing SDL TTF subsystem: %1%";
        default:
            break;
    }

    return out;
}

}}

#endif
