#ifndef LB_OBJ_READER_H
#define LB_OBJ_READER_H

#include "core/itf/mesh.h"

#include <iosfwd>
#include <memory>

namespace lb {

class Mesh;

/// Class implementing an OBJ format reader.
class ObjReader
{
    public:
        ObjReader() = default;

        std::unique_ptr<Mesh> loadMesh(std::istream& is);

    private:
        void parseVertex(std::stringstream &in, int &v, int &vt, int &vn) const;
};

}

#endif
