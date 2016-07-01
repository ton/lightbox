#ifndef LB_MEMORY_FILM_H
#define LB_MEMORY_FILM_H

#include "core/itf/film.h"

#include <cstdint>

namespace lb {

class MemoryFilm : public Film
{
    public:
        MemoryFilm(int xResolution, int yResolution, uint32_t* buffer);

        void addSample(const Sample& sample, float l);

    private:
        uint32_t* buffer_;
};

}

#endif
