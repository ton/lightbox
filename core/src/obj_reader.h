#ifndef LB_OBJ_READER_H
#define LB_OBJ_READER_H

#include "core/itf/mesh.h"

#include <fstream>

namespace lb {

/// Class implementing an OBJ format reader.
class ObjReader
{
    public:
        ObjReader(std::ifstream &objFile);

        /// Returns the mesh represented by the parsed OBJ file.
        ///
        /// \returns the mesh represented by the parsed OBJ file
        const Mesh &mesh() const { return mesh_; }

    private:
        void parseVertex(std::stringstream &in, int &v, int &vt, int &vn) const;

        /// The mesh that was just read.
        Mesh mesh_;
};

}

#endif
