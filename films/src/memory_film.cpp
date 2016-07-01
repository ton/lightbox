#include "films/itf/memory_film.h"

#include "core/itf/sampling.h"

using namespace lb;

MemoryFilm::MemoryFilm(int xResolution, int yResolution, uint32_t* buffer):
    Film(xResolution, yResolution),
    buffer_(buffer)
{
}

void MemoryFilm::addSample(const Sample& sample, float f)
{
    char v = 255 * f;
    *(buffer_ + sample.imageX + xResolution_ * sample.imageY) = (v << 16) + (v << 8) + v;
}
